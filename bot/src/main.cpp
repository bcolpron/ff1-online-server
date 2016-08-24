#include <iostream>




/*#include "Bot.h"
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
    WebSocketClient(boost::asio::io_service& io, CharacterManager& manager)
    : manager_(manager)
    {
        client_.init_asio(&io);
        client_.set_open_handler(std::bind(&ThisType::on_open,this,::_1));
        client_.set_close_handler(std::bind(&ThisType::on_close,this,::_1));
        client_.set_fail_handler(std::bind(&ThisType::on_fail,this,::_1));
        client_.set_message_handler(std::bind(&ThisType::on_message,this,::_1,::_2));
        client_.clear_access_channels(websocketpp::log::alevel::all);
    }
    
    void start()
    {
        connect();
        client_.run();
    }
    
private:

    void connect()
    {
        websocketpp::lib::error_code ec;
        connection_ = client_.get_connection("ws://localhost:4280/ws/?location=world", ec);
        if (ec) {
            std::cout << "could not create connection because: " << ec.message() << std::endl;
            throw std::system_error(ec);
        } 
        client_.connect(connection_);
    }

    void on_open(websocketpp::connection_hdl hdl)
    {
        std::cout << "Connected!" << std::endl;
    }
    
    void on_fail(websocketpp::connection_hdl hdl)
    {
        std::cerr << "disconnected!" << std::endl;
        connect();
    }
    
    void on_close(websocketpp::connection_hdl hdl)
    {
        std::cerr << "Disconnected!" << std::endl;
        connect();
    }

    void on_message(websocketpp::connection_hdl hdl, Client::message_ptr msg)
    {
        const auto m = fromJSON<Message>(msg->get_payload());
        for(const auto update: m.update) {
            manager_.addOrUpdate(update);
        }
        for(const auto id: m.removal) {
            manager_.remove(id);
        }
    }
    
    virtual void send(const Message& msg) override
    {
        connection_->send(toJSON(msg), websocketpp::frame::opcode::TEXT);
    }
    
    CharacterManager& manager_;
    Client client_;
    Client::connection_ptr connection_;
};*/

#include "Message.h"


int main(int argc, const char* argv[])
{
    /*boost::asio::io_service io;
    CharacterManager manager;
    WebSocketClient client(io, manager);
    Bot bot(io, static_cast<Comm&>(client), manager, argv[1]);
    client.start();*/
    
    //std::cout << std::toJSON(std::string("allo")) << std::endl;
    
    auto c = fromJSON<Character>("{\"id\": \"server-bot\", \"left\":152,\"top\":159,\"direction\":0,\"class\":\"town/coneria/knight\"}");
    std::cout << toJSON(c) << std::endl;
    
    std::cout << toJSON(fromJSON<int>("42")) << std::endl;
    std::cout << toJSON(fromJSON<std::string>("\"allo\"")) << std::endl;
    
    auto m = fromJSON<Message>("{\"update\": [ {\"id\": \"server-bot\", \"left\":152,\"top\":159,\"direction\":0,\"class\":\"town/coneria/knight\"} ], \"removal\": [\"a\", \"b\"] }");
    m.update.push_back(c);
    m.update.push_back(c);
    m.removal.push_back("abc122");
    m.removal.push_back("abc123");
    std::cout << toJSON(m) << std::endl;
}
