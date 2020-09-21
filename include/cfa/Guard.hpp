#ifndef Guard_hpp
#define Guard_hoo
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
class Guard
{
private:
    std::string guardStr;
public:
    Guard(/* args */);
    ~Guard();
    std::string getGuardStr();
    void setGuardStr();
    std::string toString();
};

Guard::Guard(/* args */)
{
}

Guard::~Guard()
{
}


#endif
