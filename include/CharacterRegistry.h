#ifndef INCLUDE_CHARACTERREGISTRY_H
#define INCLUDE_CHARACTERREGISTRY_H

class CharacterRegistry
{
public:
    virtual bool isFree(int x, int y) = 0;
};

#endif