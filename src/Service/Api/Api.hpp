/**
 * API
 * =====
 * Responsibilities:
 *  - Communicates with the Steam API via HTTP.
 *  - Parses Response into usable C++ objects.
 */

#ifndef API_H
#define API_H

// Library includes
#include "Util/Steam/Steam.hpp"
#include "Util/List/List.hpp"
#include "Util/Queue/PushQueue.hpp"

// Api Includes
#include "Parser/Parser.hpp"
#include "Object/User.hpp"
#include "Object/Item.hpp"
#include "Object/ApiKey.hpp"
#include "Response.hpp"

namespace Api {
class Api {
private:
Response get(const ApiKey& key, string url);

public:
int items(const Parser::Ptr& parser, const ApiKey& key, User::Ptr user);

List<User::Ptr> friends(const ApiKey& key, User::Ptr user);
};
}

#endif
