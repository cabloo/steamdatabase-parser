#include "Steam.hpp"

#include <iostream>
using Id64 = Util::Steam::Id64;
using Id32 = Util::Steam::Id32;

static unsigned long long OFFSET_64 = 61197960265728;

Id64 Util::Steam::to64Bit(Id32 id)
{
    int64_t id64 = id + OFFSET_64;

	return ("765" + std::to_string(id64)).c_str();
}

Id32 Util::Steam::to32Bit(Id64 id)
{
    // TODO
	return std::stol(id);
}
