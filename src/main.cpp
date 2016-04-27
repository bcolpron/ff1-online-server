#include <set>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

using std::placeholders::_1;
using std::placeholders::_2;

class WebSocketServer {
     typedef websocketpp::server<websocketpp::config::asio> Server;
     typedef WebSocketServer ThisType;
public:
    WebSocketServer()
    {
        m_server.init_asio();
                
        m_server.set_open_handler(std::bind(&ThisType::on_open,this,::_1));
        m_server.set_close_handler(std::bind(&ThisType::on_close,this,::_1));
        m_server.set_message_handler(std::bind(&ThisType::on_message,this,::_1,::_2));
    }
    
    void run(uint16_t port)
    {
        m_server.set_reuse_addr(true);
        m_server.listen(port);
        m_server.start_accept();
        m_server.run();
    }
private:
    typedef std::owner_less<websocketpp::connection_hdl> HdlCompare;
    typedef std::map<websocketpp::connection_hdl, std::string, HdlCompare> Connections;

    void on_open(websocketpp::connection_hdl hdl) {
        for (auto it : m_connections)
        {
            m_server.send(hdl,it.second, websocketpp::frame::opcode::TEXT);
        }
    }
    
    void on_close(websocketpp::connection_hdl hdl) {
        m_connections.erase(hdl);
    }
    
    void on_message(websocketpp::connection_hdl hdl, Server::message_ptr msg)
    {
        m_connections[hdl] = msg->get_payload();
        for (auto it : m_connections)
        {
            if (HdlCompare()(it.first, hdl) || HdlCompare()(hdl, it.first))
            {
                m_server.send(it.first,msg);
            }
        }
    }

    Server m_server;
    Connections m_connections;
};

int main() {
    WebSocketServer server;
    
    std::cout << "websocket server started" << std::endl; 
    server.run(4280);
}