#ifndef INCLUDE_CHARACTER_H
#define INCLUDE_CHARACTER_H

#include "Serialization.h"

struct Character
{
    std::string id;
    int x;
    int y;
    int direction;
    std::string class_;
};

template<class Archive>
void serialize(Archive& archive, Character& o)
{
    archive(cereal::make_nvp("id", o.id),
        cereal::make_nvp("left", o.x),
        cereal::make_nvp("top", o.y),
        cereal::make_nvp("direction", o.direction),
        cereal::make_nvp("class", o.class_));
}

std::ostream& operator<<(std::ostream& out, const Character& c)
{
    out << toJSON(c);
    return out;
}

#endif