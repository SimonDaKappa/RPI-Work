#ifndef _super_
#define _super_

#include <string>
#include <iostream>
#include <iomanip>

class Superhero{
public:
    friend class Team;
    Superhero(std::string n, std::string i, std::string p)
        : nickname(n), identity(i), power(p), alignment(true) {}

    std::string getName() const { return nickname; }
    std::string getPower() const { return power; }
    bool isGood() const { return alignment; }

    bool operator>(const Superhero& rhs);
    bool operator==(const std::string & name) const { return identity == name; }
    bool operator!=(const std::string   & name) const { return !(identity == name); }
    Superhero& operator-() { alignment = !alignment; return *this;}
    friend std::ostream &operator<<(std::ostream &, const Superhero &s);

private:
    std::string getTrueIdentity() const { return identity; }

    std::string nickname;
    std::string identity;
    std::string power;
    bool alignment;
};



#endif

