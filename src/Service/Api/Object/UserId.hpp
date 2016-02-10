#ifndef USER_ID_H
#define USER_ID_H

#include "Util/Steam/Steam.hpp"
#include "Util/String/String.hpp"

class UserId {
private:
typedef unsigned long long Id;
Id id;

public:
UserId(Id id) : id(id)
{
}

UserId(const UserId& userId) : id(userId.id) {}

UserId& operator=(UserId&& other)
{
    id = other.id;
    return *this;
}
UserId(UserId&& other)
{
    *this = std::move(other);
}

UserId(Util::String::string id) : UserId(id.c_str())
{
}

UserId(const char * id) : id(std::stol(id))
{
}

UserId* copy()
{
    return new UserId(id);
}

const char * str32()
{
    return std::to_string(id).c_str();
}

const char * str64()
{
    return Util::Steam::to64Bit(id);
}
};

#endif
