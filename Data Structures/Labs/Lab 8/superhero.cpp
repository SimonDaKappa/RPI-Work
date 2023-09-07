#include "superhero.h"

std::ostream &operator<<(std::ostream &os, const Superhero &s)
{

    if (s.isGood())
        os << "Superhero ";
    else
        os << "Supervillain ";
    os
        << s.getName()
        << " has power "
        << s.getPower()
        << '\n';
    return os;
}

bool Superhero::operator>(const Superhero &hero2)
{
    if (power == "Wood")
    {
        if (hero2.power == "Fire")
            return false;
        else if (hero2.power == "Water")
            return true;
    }
    else if (power == "Fire")
    {
        if (hero2.power == "Water")
            return false;
        else if (hero2.power == "Wood")
            return true;
    }
    else if (power == "Water")
    {
        if (hero2.power == "Wood")
            return false;
        if (hero2.power == "Fire")
            return true;
    }
    //Non Elemental Powers - String Compare
    return (power > hero2.power);
}