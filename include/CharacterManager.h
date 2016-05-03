#ifndef INCLUDE_CHARACTERMANAGER_H
#define INCLUDE_CHARACTERMANAGER_H

#include "CharacterRegistry.h"

class CharacterManager: public CharacterRegistry
{
    typedef std::map<CharacterId, Character> Characters;
    typedef std::vector<Character> List;
public:
    
    void addOrUpdate(const CharacterId& id, const Character& c)
    {
        characters_[id] = c;
    }
    
    Characters getAll() const
    {
        List result;
        result.reserve(characters_.size());
        
        auto select2nd = [] (auto&& pair) {return std::forward<decltype(pair)>(pair).second;};
        std::transform(begin(characters_), end(characters_), std::back_inserter(result), select2nd);
        return result;
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