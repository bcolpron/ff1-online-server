#include "Bot.h"
#include "Comm.h"
#include "CharacterManager.h"
#include <set>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/client.hpp>

using std::placeholders::_1;
using std::placeholders::_2;

class WebSocketClient: public Comm
{
     typedef websocketpp::client<websocketpp::config::asio> Client;
     typedef WebSocketClient ThisType;
public:
    WebSocketClient()
    {
        client_.init_asio();
        client_.set_open_handler(std::bind(&ThisType::on_open,this,::_1));
        client_.set_close_handler(std::bind(&ThisType::on_close,this,::_1));
        client_.set_message_handler(std::bind(&ThisType::on_message,this,::_1,::_2));
        client_.clear_access_channels(websocketpp::log::alevel::all);
        
        bot_ = std::make_unique<Bot>(client_.get_io_service(), *this, manager_);
    }
    
    void start()
    {
        websocketpp::lib::error_code ec;
        connection_ = client_.get_connection("ws://localhost:4280", ec);
        if (ec) {
            std::cout << "could not create connection because: " << ec.message() << std::endl;
            throw std::system_error(ec);
        } 
        client_.connect(connection_);
        client_.run();
    }
    
    virtual void send(const Message& msg)
    {
    }
    
private:

    void on_open(websocketpp::connection_hdl hdl)
    {
        std::cout << "Connected!" << std::endl;
    }
    
    void on_close(websocketpp::connection_hdl hdl)
    {
        std::cout << "Disconnected!" << std::endl;
    }

    void on_message(websocketpp::connection_hdl hdl, Client::message_ptr msg)
    {
        const auto m = fromJSON<Message>(msg->get_payload());
        std::cout << m << std::endl;
        for(const auto update: m.update) {
            manager_.addOrUpdate(m.id, update);
        }
        for(const auto id: m.removal) {
            manager_.remove(id);
        }

    }
    
    virtual void sendAll(const Message& msg)
    {
        connection_->send(toJSON(msg), websocketpp::frame::opcode::TEXT);
    }
    
    Client client_;
    Client::connection_ptr connection_;
    CharacterManager manager_;
    std::unique_ptr<Bot> bot_;
};

int main()
{
    WebSocketClient client;
    client.start();
}