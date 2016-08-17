#include "Message.h"
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
        std::string location;
        Character character;
    };
    
    typedef std::owner_less<websocketpp::connection_hdl> HdlCompare;
    
    struct ById {};
    struct ByCon {};
    struct ByLocation {};
    typedef boost::multi_index::multi_index_container<
        Entry,
        boost::multi_index::indexed_by<
            boost::multi_index::ordered_unique<boost::multi_index::tag<ById>, BOOST_MULTI_INDEX_MEMBER(Entry,CharacterId,id)>,
            boost::multi_index::ordered_unique<boost::multi_index::tag<ByCon>, BOOST_MULTI_INDEX_MEMBER(Entry,websocketpp::connection_hdl,con), HdlCompare>,
            boost::multi_index::ordered_non_unique<boost::multi_index::tag<ByLocation>, BOOST_MULTI_INDEX_MEMBER(Entry,std::string,location)>>
    > Connections;

    void on_open(websocketpp::connection_hdl hdl)
    {
        auto range = connections_.get<ByLocation>().equal_range(getLocation(hdl));
        std::for_each(range.first, range.second, [&](const auto& entry)
        {
            server_.send(hdl,toJSON(Message{{entry.character}, {}}), websocketpp::frame::opcode::TEXT);
        });
    }
    
    void on_close(websocketpp::connection_hdl hdl)
    {
        auto found = connections_.get<ByCon>().find(hdl);
        if (found != connections_.get<ByCon>().end())
        {
            const auto id = found->id;
            connections_.get<ByCon>().erase(found);
            sendAll(Message{{}, {id}});
        }
    }
    
    std::string getLocation(websocketpp::connection_hdl hdl)
    {
        const auto path = server_.get_con_from_hdl(hdl)->get_uri()->get_resource();
        const auto found = path.find("?location=");
        assert(found != std::string::npos);
        return path.substr(found + 10);
    }
    
    void on_message(websocketpp::connection_hdl hdl, Server::message_ptr msg)
    {
        //std::cout << msg->get_payload() << std::endl;
        const auto m = fromJSON<Message>(msg->get_payload());
        assert (m.update.size() >= 1);
        const auto id = m.update.front().id;
        const auto location = getLocation(hdl);
        auto inserted = connections_.insert(Entry{id, hdl, location});
        if (inserted.second)
        {
            std::cout << "Client " << id << " connected in '" << location << "'" << std::endl;
        }
        
        connections_.modify(inserted.first, [&](Entry& entry)
        {
            entry.character = m.update.front();
        });
        
        auto range = connections_.get<ByLocation>().equal_range(location);
        std::for_each(range.first, range.second, [&](const auto& entry)
        {
            if (HdlCompare()(entry.con, hdl) || HdlCompare()(hdl, entry.con))
            {
                server_.send(entry.con, msg);
            }
        });
    }
    
    Server server_;
    Connections connections_;
};

int main()
{
    WebSocketServer server;
    std::cout << "websocket server started" << std::endl; 
    server.run(4280);
}