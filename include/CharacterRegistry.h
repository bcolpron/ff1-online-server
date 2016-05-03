#ifndef INCLUDE_CHARACTERREGISTRY_H
#define INCLUDE_CHARACTERREGISTRY_H

#include "Character.h"

typedef std::string CharacterId;

class CharacterRegistry
{
public:
    virtual bool isFree(int x, int y) = 0;
};

#endif