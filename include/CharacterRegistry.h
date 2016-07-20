#ifndef INCLUDE_CHARACTERREGISTRY_H
#define INCLUDE_CHARACTERREGISTRY_H

#include "Character.h"
#include <map>

typedef std::string CharacterId;

class CharacterRegistry
{
public:
    typedef std::map<CharacterId, Character> Characters;
    
    virtual void addOrUpdate(const Character& c) = 0;
    virtual Characters getAll() const = 0;
    virtual void remove(const CharacterId& id) = 0;
    virtual bool isFree(int x, int y) = 0;
};

#endif