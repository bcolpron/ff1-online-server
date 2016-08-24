#ifndef INCLUDE_CHARACTER_H
#define INCLUDE_CHARACTER_H

#include "Serialization.h"

typedef std::string CharacterId;

struct Character
{
    CharacterId id;
    int x;
    int y;
    int direction;
    std::string class_;
};

template<class Serializer>
void serialize(Serializer& serial, Character& o)
{
    serial("id", o.id);
    serial("left", o.x);
    serial("top", o.y);
    serial("direction", o.direction);
    serial("class", o.class_);
}

std::ostream& operator<<(std::ostream& out, const Character& c)
{
    out << toJSON(c);
    return out;
}

#endif