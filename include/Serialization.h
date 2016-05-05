#ifndef INCLUDE_SERIALIZATION_H
#define INCLUDE_SERIALIZATION_H

#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>

template<class T>
std::string toJSON(const T& o)
{
    std::stringstream buffer;
    {
        cereal::JSONOutputArchive archive(buffer);
        serialize(archive, const_cast<T&>(o));
    }
    return buffer.str();
}

template<class T>
T fromJSON(const std::string& json)
{
    T o;
    std::stringstream buffer(json);
    cereal::JSONInputArchive archive(buffer);
    serialize(archive, o);
    return o;
}

#endif