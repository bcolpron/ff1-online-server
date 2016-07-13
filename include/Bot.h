#ifndef INCLUDE_BOT_H
#define INCLUDE_BOT_H

#include "Message.h"
#include "Comm.h"
#include "CharacterRegistry.h"
#include "boost/asio/io_service.hpp"
#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "boost/uuid/uuid_io.hpp"
#include "boost/asio/deadline_timer.hpp"
#include <fstream>

class Bot
{
public:
    Bot(boost::asio::io_service& service, Comm& comm, CharacterRegistry& registry)
    : id_("bot_" + to_string(boost::uuids::random_generator()())), timer_(service, boost::posix_time::seconds(1)), comm_(comm), registry_(registry)
    {
        loadFromFile("bot-moves.txt");
        timer_.async_wait(std::bind(&Bot::handleTimer, this, std::placeholders::_1));
    }
    
private:

    void loadFromFile(const char* path)
    {
        std::ifstream file(path);
        std::string line;
        while(file) {
            getline(file, line);
            if (file) {
                botMoves_.push_back(line);
            }
        }
        std::cout << "Loaded " << botMoves_.size() << " bot moves from file " << path << std::endl;
        nextBotMove_ = botMoves_.begin();
    }
    
    void handleTimer(const boost::system::error_code& e)
    {
            if (nextBotMove_ == botMoves_.end()) return;   // no moves, no bot
        
            auto m = fromJSON<Message>(*nextBotMove_);
            m.id = id_;
            assert(m.update.size() == 1);
            
            if (registry_.isFree(m.update.front().x, m.update.front().y))
            {
                registry_.addOrUpdate(m.id, m.update.front());
                comm_.sendAll(m);
                if (++nextBotMove_ == botMoves_.end())
                {
                    nextBotMove_ = botMoves_.begin();
                }
            }
        
            timer_.expires_at(timer_.expires_at() + boost::posix_time::milliseconds(375));
            timer_.async_wait(std::bind(&Bot::handleTimer, this, std::placeholders::_1));
    }
    
    std::string id_;
    std::vector<std::string> botMoves_;
    boost::asio::deadline_timer timer_;
    Comm& comm_;
    CharacterRegistry& registry_;
    std::vector<std::string>::const_iterator nextBotMove_ = botMoves_.begin();
};

#endif