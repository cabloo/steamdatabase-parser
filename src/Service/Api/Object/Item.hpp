#ifndef ITEM_H
#define ITEM_H

#include <memory>
#include "User.hpp"
#include "ItemAttribute.hpp"

/**
 * An object version of an evaluated backpack item returned by the Steam API.
 */
class Item {
private:
User::Ptr _user;

int _craftNumber, _effect, _defindex, _level, _quality, _origin;
bool _craftable, _tradable;
unsigned long long _id;

std::shared_ptr<ItemAttribute::List> _attributes;

public:
typedef std::shared_ptr<Item> Ptr;
/**
 * @param user the User that owns this item
 */
Item(User::Ptr user) : _user(user)
{
    reset();
}

/**
 * Reset everything that was not passed via constructor.
 * Allows efficient reuse of the same Item object.
 */
void reset()
{
    _craftNumber = 0;
    _effect = 0;
    _defindex = 0;
    _id = 0;
    _level = 0;
    _quality = 0;
    _origin = 0;
    _craftable = false;
    _tradable = false;
    _attributes = std::make_shared<ItemAttribute::List>();
}

User::Ptr user()
{
    return _user;
}

int defindex()
{
    return _defindex;
}

Item* defindex(int val)
{
    _defindex = val;
    return this;
}

unsigned long long id()
{
    return _id;
}

Item* id(unsigned long long val)
{
    _id = val;
    return this;
}

int effect()
{
    return _effect;
}

Item* effect(int val)
{
    _effect = val;
    return this;
}

int level()
{
    return _level;
}

Item* level(int val)
{
    _level = val;
    return this;
}

int quality()
{
    return _quality;
}

Item* quality(int val)
{
    _quality = val;
    return this;
}

int origin()
{
    return _origin;
}

Item* origin(int val)
{
    _origin = val;
    return this;
}

bool craftable()
{
    return _craftable;
}

Item* craftable(bool val)
{
    _craftable = val;
    return this;
}

bool tradable()
{
    return _tradable;
}

Item* tradable(bool val)
{
    _tradable = val;
    return this;
}

int craftNumber()
{
    return _craftNumber;
}

Item* craftNumber(int val)
{
    _craftNumber = val;
    return this;
}

std::shared_ptr<ItemAttribute::List> attributes()
{
    return _attributes;
}

/*Item(const Item & item)
{
    user = std::move(item.user);
}

Item& operator=(const Item & item)
{
	user = std::move(item.user);
	return *this;
}*/
};

#endif
