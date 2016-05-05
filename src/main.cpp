#include "Bot.h"
#include "Comm.h"
#include "CharacterManager.h"
#include <set>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

using std::placeholders::_1;
using std::placeholders::_2;

class WebSocketServer: public Comm {
     typedef websocketpp::server<websocketpp::config::asio> Server;
     typedef WebSocketServer ThisType;
public:
    WebSocketServer()
    {
        server_.init_asio();
                
        server_.set_open_handler(std::bind(&ThisType::on_open,this,::_1));
        server_.set_close_handler(std::bind(&ThisType::on_close,this,::_1));
        server_.set_message_handler(std::bind(&ThisType::on_message,this,::_1,::_2));
        
        bot_ = std::make_unique<Bot>(server_.get_io_service(), *this, manager_);
    }
    
    void run(uint16_t port)
    {
        server_.set_reuse_addr(true);
        server_.listen(port);
        server_.start_accept();
        server_.run();
    }
    
    virtual void sendAll(const Message& msg)
    {
        const auto m = toJSON(msg);
        for (const auto& entry : connections_)
        {
            server_.send(entry.first, m, websocketpp::frame::opcode::TEXT);
        }
        
    }
    
private:
    typedef std::owner_less<websocketpp::connection_hdl> HdlCompare;
    typedef std::map<websocketpp::connection_hdl, CharacterId, HdlCompare> Connections;

    void on_open(websocketpp::connection_hdl hdl)
    {
        for (const auto& entry : manager_.getAll())
        {
            server_.send(hdl,toJSON(Message{entry.first, {entry.second}}), websocketpp::frame::opcode::TEXT);
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
            sendAll(Message{id, {}, {id}});
        }
    }
    
    void on_message(websocketpp::connection_hdl hdl, Server::message_ptr msg)
    {
        const auto m = fromJSON<Message>(msg->get_payload());
        connections_[hdl] = m.id;
        assert (m.update.size() == 1);
        manager_.addOrUpdate(m.id, m.update.front());
        
        for (const auto& entry : connections_)
        {
            if (HdlCompare()(entry.first, hdl) || HdlCompare()(hdl, entry.first))
            {
                server_.send(entry.first,msg);
            }
        }
    }
    
    Server server_;
    Connections connections_;
    CharacterManager manager_;
    std::unique_ptr<Bot> bot_;
};

int main()
{
    WebSocketServer server;

    std::cout << "websocket server started" << std::endl; 
    server.run(4280);
}