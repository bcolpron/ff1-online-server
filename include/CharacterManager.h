#ifndef INCLUDE_CHARACTERMANAGER_H
#define INCLUDE_CHARACTERMANAGER_H

#include "CharacterRegistry.h"

class CharacterManager: public CharacterRegistry
{
public:
    
    virtual void addOrUpdate(const CharacterId& id, const Character& c)
    {
        characters_[id] = c;
    }
    
    virtual Characters getAll() const
    {
        return characters_;
    }
    
    virtual void remove(const CharacterId& id)
    {
        characters_.erase(id);
    }
    
    virtual bool isFree(int x, int y)
    {
        for (const auto& entry : characters_)
        {
            if (x == entry.second.x && y == entry.second.y)
            {
                return false;
            }
        }
        return true;
    }
    
private:
    Characters characters_;
};

#endif