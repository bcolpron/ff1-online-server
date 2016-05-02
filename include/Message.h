#ifndef INCLUDE_MESSAGE_H
#define INCLUDE_MESSAGE_H

#include "Character.h"

struct Message
{
    std::string from;
    Character update;
};

template<class Archive>
void serialize(Archive& archive, Message& o)
{
    archive(cereal::make_nvp("from", o.from),
               cereal::make_nvp("update", o.update));
}

std::ostream& operator<<(std::ostream& out, const Message& m)
{
    out << toJSON(m);
    return out;
}

#endif