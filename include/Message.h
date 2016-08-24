#ifndef INCLUDE_MESSAGE_H 
#define INCLUDE_MESSAGE_H

#include "Character.h"

struct Message
{
    std::vector<Character> update;
    std::vector<std::string> removal;
};

/*template<class Archive>
void serialize(Archive& archive, Message& o)
{
    archive(cereal::make_nvp("update", o.update),
            cereal::make_nvp("removal", o.removal));
}*/

/*template<class T>
void serialize(T& json, Message& o)
{
    serialize(json, "update", o.update);
    serialize(json, "removal", o.removal);
}*/

std::ostream& operator<<(std::ostream& out, const Message& m)
{
    out << toJSON(m);
    return out;
}

#endif