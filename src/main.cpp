#include "Message.h"
#include "CharacterManager.h"
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <set>

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
                server_.send(entry.first, m, websocketpp::frame::opcode::TEXT);
            }
            catch(const std::exception& e)
            {
                std::cerr << "failed to send message to " << entry.second << " " << e.what() << std::endl;
            }
        }
        
    }
    
    typedef std::owner_less<websocketpp::connection_hdl> HdlCompare;
    typedef std::map<websocketpp::connection_hdl, CharacterId, HdlCompare> Connections;

    void on_open(websocketpp::connection_hdl hdl)
    {
        for (const auto& entry : manager_.getAll())
        {
            server_.send(hdl,toJSON(Message{{entry.second}, {}}), websocketpp::frame::opcode::TEXT);
        }
    }
    
    void on_close(websocketpp::connection_hdl hdl)
    {
        auto found = connections_.find(hdl);
        if (found != connections_.end())
        {
            const auto id = found->second;
            connections_.erase(found);
            manager_.remove(id);
            sendAll(Message{{}, {id}});
        }
    }
    
    void on_message(websocketpp::connection_hdl hdl, Server::message_ptr msg)
    {
        //std::cout << msg->get_payload() << std::endl;
        const auto m = fromJSON<Message>(msg->get_payload());
        assert (m.update.size() >= 1);
        connections_[hdl] = m.update.front().id;
        manager_.addOrUpdate(m.update.front());
        
        for (const auto& entry : connections_)
        {
            if (HdlCompare()(entry.first, hdl) || HdlCompare()(hdl, entry.first))
            {
                server_.send(entry.first, msg);
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