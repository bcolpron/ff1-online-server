#include "Bot.h"
#include "Comm.h"
#include "CharacterManager.h"
#include <set>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

using std::placeholders::_1;
using std::placeholders::_2;

class WebSocketServer: public Comm, public CharacterRegistry {
     typedef websocketpp::server<websocketpp::config::asio> Server;
     typedef WebSocketServer ThisType;
public:
    WebSocketServer()
    {
        m_server.init_asio();
                
        m_server.set_open_handler(std::bind(&ThisType::on_open,this,::_1));
        m_server.set_close_handler(std::bind(&ThisType::on_close,this,::_1));
        m_server.set_message_handler(std::bind(&ThisType::on_message,this,::_1,::_2));
        
        bot_ = std::make_unique<Bot>(m_server.get_io_service(), *this, manager_);
    }
    
    void run(uint16_t port)
    {
        m_server.set_reuse_addr(true);
        m_server.listen(port);
        m_server.start_accept();
        m_server.run();
    }
    
    virtual void sendAll(const Message& msg)
    {
        const auto m = toJSON(msg);
        for (const auto& entry : m_connections)
        {
            m_server.send(entry.first, m, websocketpp::frame::opcode::TEXT);
        }
        
    }
    
private:
    typedef std::owner_less<websocketpp::connection_hdl> HdlCompare;
    typedef std::map<websocketpp::connection_hdl, CharacterId, HdlCompare> Connections;

    void on_open(websocketpp::connection_hdl hdl)
    {
        for (const auto& entry : manager_.getAll())
        {
            m_server.send(hdl,toJSON(entry), websocketpp::frame::opcode::TEXT);
        }
    }
    
    void on_close(websocketpp::connection_hdl hdl)
    {
        m_connections.erase(hdl);
    }
    
    void on_message(websocketpp::connection_hdl hdl, Server::message_ptr msg)
    {
        const auto m = fromJSON<Message>(msg->get_payload());
        m_connections[hdl] = m.from;
        manager_.addOrUpdate(m.from, m.update);
        
        for (const auto& entry : m_connections)
        {
            if (HdlCompare()(entry.first, hdl) || HdlCompare()(hdl, entry.first))
            {
                m_server.send(entry.first,msg);
            }
        }
    }
    
    virtual bool isFree(int x, int y)
    {
        return manager_.isFree(x,y);
    }
    
    Server m_server;
    Connections m_connections;
    CharacterManager manager_;
    std::unique_ptr<Bot> bot_;
};

int main()
{
    WebSocketServer server;

    std::cout << "websocket server started" << std::endl; 
    server.run(4280);
}