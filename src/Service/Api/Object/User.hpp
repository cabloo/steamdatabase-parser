/**
 * An object version of an evaluated user returned by the Steam API.
 */

#ifndef USER_H
#define USER_H

#include <memory>
#include "UserId.hpp"
#include "Util/Steam/Steam.hpp"
#include "Util/String/String.hpp"

using string = Util::String::string;

class User {
public:
typedef std::shared_ptr< User > Ptr;
private:
typedef std::unique_ptr< UserId > UserIdPtr;

/**
 * The 32 bit Steam ID for the User.
 */
UserIdPtr id;

public:
User(UserId* id) : id(UserIdPtr(id))
{
}

User(UserId userId) : id(UserIdPtr(userId.copy()))
{
}

User(const User & other) : User(other.id->copy())
{

}

User(User&& user) noexcept : id(std::move(user.id)) {}

~User()
{
    id.reset(nullptr);
}

User& operator=(User && user)
{
	id = std::move(user.id);
	return *this;
}

const char * getId32()
{
    return id->str32();
}

const char * getId64()
{
    return id->str64();
}
};

#endif
