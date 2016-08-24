#ifndef INCLUDE_MESSAGE_H 
#define INCLUDE_MESSAGE_H

#include "Character.h"

struct Message
{
    std::vector<Character> update;
    std::vector<std::string> removal;
};

template<class Serializer>
void serialize(Serializer& serial, Message& o)
{
    serial("update", o.update);
    serial("removal", o.removal);
}

std::ostream& operator<<(std::ostream& out, const Message& m)
{
    out << toJSON(m);
    return out;
}

#endif