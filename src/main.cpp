#include "Message.h"
#include "CharacterManager.h"
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>

using std::placeholders::_1;
using std::placeholders::_2;

class WebSocketServer {
     typedef websocketpp::server<websocketpp::config::asio> Server;
     typedef WebSocketServer ThisType;
public:
    WebSocketServer()
    {
        server_.init_asio();
        server_.set_open_handler(std::bind(&ThisType::on_open,this,::_1));
        server_.set_close_handler(std::bind(&ThisType::on_close,this,::_1));
        server_.set_message_handler(std::bind(&ThisType::on_message,this,::_1,::_2));
        server_.clear_access_channels(websocketpp::log::alevel::all);
    }
    
    void run(uint16_t port)
    {
        server_.set_reuse_addr(true);
        server_.listen(port);
        server_.start_accept();
        server_.run();
    }
    
private:
    void sendAll(const Message& msg)
    {
        const auto m = toJSON(msg);
        for (const auto& entry : connections_)
        {
            try
            {
                server_.send(entry.con, m, websocketpp::frame::opcode::TEXT);
            }
            catch(const std::exception& e)
            {
                std::cerr << "failed to send message to " << entry.id << " " << e.what() << std::endl;
            }
        }
        
    }
    
    struct Entry
    {
        CharacterId id;
        websocketpp::connection_hdl con;
    };
    
    typedef std::owner_less<websocketpp::connection_hdl> HdlCompare;
    
    struct ById {};
    struct ByCon {};
    typedef boost::multi_index::multi_index_container<
        Entry,
        boost::multi_index::indexed_by<
            boost::multi_index::ordered_unique<boost::multi_index::tag<ById>, BOOST_MULTI_INDEX_MEMBER(Entry,CharacterId,id)>,
            boost::multi_index::ordered_unique<boost::multi_index::tag<ByCon>, BOOST_MULTI_INDEX_MEMBER(Entry,websocketpp::connection_hdl,con), HdlCompare>>
    > Connections;

    void on_open(websocketpp::connection_hdl hdl)
    {
        for (const auto& entry : manager_.getAll())
        {
            server_.send(hdl,toJSON(Message{{entry.second}, {}}), websocketpp::frame::opcode::TEXT);
        }
    }
    
    void on_close(websocketpp::connection_hdl hdl)
    {
        auto found = connections_.get<ByCon>().find(hdl);
        if (found != connections_.get<ByCon>().end())
        {
            const auto id = found->id;
            connections_.get<ByCon>().erase(found);
            manager_.remove(id);
            sendAll(Message{{}, {id}});
        }
    }
    
    void on_message(websocketpp::connection_hdl hdl, Server::message_ptr msg)
    {
        std::cout << server_.get_con_from_hdl(hdl)->get_uri()->str() << std::endl;
        //std::cout << msg->get_payload() << std::endl;
        const auto m = fromJSON<Message>(msg->get_payload());
        assert (m.update.size() >= 1);
        connections_.insert(Entry{m.update.front().id, hdl});
        manager_.addOrUpdate(m.update.front());
        
        for (const auto& entry : connections_)
        {
            if (HdlCompare()(entry.con, hdl) || HdlCompare()(hdl, entry.con))
            {
                server_.send(entry.con, msg);
            }
        }
    }
    
    Server server_;
    Connections connections_;
    CharacterManager manager_;
};

int main()
{
    WebSocketServer server;
    std::cout << "websocket server started" << std::endl; 
    server.run(4280);
}