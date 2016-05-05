#ifndef INCLUDE_MESSAGE_H 
#define INCLUDE_MESSAGE_H

#include "Character.h"

struct Message
{
    std::string id;
    std::vector<Character> update;
    std::vector<std::string> removal;
};

template<class Archive>
void serialize(Archive& archive, Message& o)
{
    archive(cereal::make_nvp("id", o.id),
            cereal::make_nvp("update", o.update),
            cereal::make_nvp("removal", o.removal));
}

std::ostream& operator<<(std::ostream& out, const Message& m)
{
    out << toJSON(m);
    return out;
}

#endif