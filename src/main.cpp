#include <set>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

using std::placeholders::_1;
using std::placeholders::_2;

std::vector<std::string> botMoves = {
    "{\"from\": \"server-bot\", \"update\": {\"left\":152,\"top\":159,\"direction\":0,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":152,\"top\":160,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":152,\"top\":161,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":152,\"top\":162,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":152,\"top\":163,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":152,\"top\":164,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":151,\"top\":164,\"direction\":6,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":150,\"top\":164,\"direction\":6,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":149,\"top\":164,\"direction\":6,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":148,\"top\":164,\"direction\":6,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":147,\"top\":164,\"direction\":6,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":146,\"top\":164,\"direction\":6,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":145,\"top\":164,\"direction\":6,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":145,\"top\":163,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":145,\"top\":162,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":145,\"top\":161,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":145,\"top\":160,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":145,\"top\":159,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":145,\"top\":158,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":145,\"top\":157,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":145,\"top\":156,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":145,\"top\":155,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":145,\"top\":154,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":145,\"top\":153,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":145,\"top\":152,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":145,\"top\":151,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":144,\"top\":151,\"direction\":6,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":143,\"top\":151,\"direction\":6,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":142,\"top\":151,\"direction\":6,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":141,\"top\":151,\"direction\":6,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":140,\"top\":151,\"direction\":6,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":139,\"top\":151,\"direction\":6,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":139,\"top\":150,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":139,\"top\":149,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":139,\"top\":148,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":139,\"top\":147,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":139,\"top\":146,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":139,\"top\":145,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":139,\"top\":144,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":139,\"top\":143,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":139,\"top\":142,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":139,\"top\":141,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":139,\"top\":140,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":139,\"top\":139,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":138,\"top\":139,\"direction\":6,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":137,\"top\":139,\"direction\":6,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":136,\"top\":139,\"direction\":6,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":135,\"top\":139,\"direction\":6,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":135,\"top\":138,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":135,\"top\":137,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":135,\"top\":136,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":135,\"top\":135,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":135,\"top\":134,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":135,\"top\":133,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":134,\"top\":133,\"direction\":6,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":134,\"top\":133,\"direction\":2,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":134,\"top\":132,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":134,\"top\":131,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":134,\"top\":130,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":133,\"top\":130,\"direction\":6,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":132,\"top\":130,\"direction\":6,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":132,\"top\":130,\"direction\":2,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":132,\"top\":129,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":132,\"top\":128,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":132,\"top\":127,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":132,\"top\":126,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":132,\"top\":125,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":132,\"top\":124,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":131,\"top\":124,\"direction\":6,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":130,\"top\":124,\"direction\":6,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":129,\"top\":124,\"direction\":6,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":129,\"top\":123,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":130,\"top\":123,\"direction\":0,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":131,\"top\":123,\"direction\":7,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":132,\"top\":123,\"direction\":7,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":133,\"top\":123,\"direction\":7,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":134,\"top\":123,\"direction\":7,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":134,\"top\":124,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":134,\"top\":125,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":134,\"top\":126,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":134,\"top\":127,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":134,\"top\":128,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":134,\"top\":129,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":134,\"top\":130,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":134,\"top\":131,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":135,\"top\":131,\"direction\":7,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":136,\"top\":131,\"direction\":7,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":136,\"top\":131,\"direction\":3,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":136,\"top\":132,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":136,\"top\":133,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":136,\"top\":134,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":136,\"top\":135,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":136,\"top\":136,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":136,\"top\":137,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":136,\"top\":138,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":136,\"top\":139,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":136,\"top\":140,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":136,\"top\":141,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":137,\"top\":141,\"direction\":7,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":138,\"top\":141,\"direction\":7,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":139,\"top\":141,\"direction\":7,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":139,\"top\":142,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":139,\"top\":143,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":139,\"top\":144,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":140,\"top\":144,\"direction\":7,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":141,\"top\":144,\"direction\":7,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":141,\"top\":145,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":141,\"top\":146,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":141,\"top\":147,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":142,\"top\":147,\"direction\":7,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":142,\"top\":148,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":142,\"top\":149,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":142,\"top\":150,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":142,\"top\":151,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":143,\"top\":151,\"direction\":7,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":144,\"top\":151,\"direction\":7,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":145,\"top\":151,\"direction\":7,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":146,\"top\":151,\"direction\":7,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":146,\"top\":152,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":146,\"top\":153,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":147,\"top\":153,\"direction\":7,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":148,\"top\":153,\"direction\":7,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":148,\"top\":154,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":148,\"top\":155,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":149,\"top\":155,\"direction\":7,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":150,\"top\":155,\"direction\":7,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":151,\"top\":155,\"direction\":7,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":152,\"top\":155,\"direction\":7,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":153,\"top\":155,\"direction\":7,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":154,\"top\":155,\"direction\":7,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":155,\"top\":155,\"direction\":7,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":156,\"top\":155,\"direction\":7,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":156,\"top\":156,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":156,\"top\":157,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":157,\"top\":157,\"direction\":7,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":158,\"top\":157,\"direction\":7,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":158,\"top\":158,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":158,\"top\":159,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":158,\"top\":160,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":158,\"top\":161,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":158,\"top\":162,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":158,\"top\":163,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":158,\"top\":164,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":158,\"top\":165,\"direction\":4,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":157,\"top\":165,\"direction\":6,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":156,\"top\":165,\"direction\":6,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":155,\"top\":165,\"direction\":6,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":154,\"top\":165,\"direction\":6,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":153,\"top\":165,\"direction\":6,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":153,\"top\":165,\"direction\":2,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":153,\"top\":164,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":153,\"top\":163,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":153,\"top\":162,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":153,\"top\":161,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":153,\"top\":160,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":153,\"top\":159,\"direction\":5,\"class\":\"rm\"}}",
    "{\"from\": \"server-bot\", \"update\": {\"left\":153,\"top\":159,\"direction\":1,\"class\":\"rm\"}}" };


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
        
        m_timer = std::make_unique<boost::asio::deadline_timer>(m_server.get_io_service(), boost::posix_time::seconds(1));
        m_timer->async_wait(std::bind(&WebSocketServer::handleTimer, this, std::placeholders::_1));
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
    
    void sendAll(const std::string& msg)
    {
        for (auto it : m_connections)
        {
            m_server.send(it.first, msg, websocketpp::frame::opcode::TEXT);
        }
        
    }
    
    void handleTimer(const boost::system::error_code& e)
    {
            sendAll(*nextBotMove++);
            if (nextBotMove == botMoves.end())
            {
                nextBotMove = botMoves.begin();
            }
        
            m_timer->expires_at(m_timer->expires_at() + boost::posix_time::milliseconds(375));
            m_timer->async_wait(std::bind(&WebSocketServer::handleTimer, this, std::placeholders::_1));
    }
    
    Server m_server;
    Connections m_connections;
    std::unique_ptr<boost::asio::deadline_timer> m_timer;
    std::vector<std::string>::const_iterator nextBotMove = botMoves.begin();
};

int main() {
    WebSocketServer server;

    std::cout << "websocket server started" << std::endl; 
    server.run(4280);
}