#include "Api.hpp"
#include "Util/String/String.hpp"
#include "Util/Log/Log.hpp"
#include <unistd.h>
#include <iostream>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

using namespace curlpp::options;
using namespace Util::String;

static Util::Log* logger = new Util::Log;

/**
 * Cleanup resources (RAII style).
 */
static curlpp::Cleanup myCleanup;

static const char * URL_FRIENDS =
	"http://api.steampowered.com/ISteamUser/GetFriendList/v0001"
;

string userQueryString(User::Ptr user)
{
	return format(
        "SteamId=%s",
		user->getId64() // "76561197997430743" : cabloo
	);
}

string itemsUrl(User::Ptr user, const Parser::Ptr& parser)
{
	return parser->itemsUrl(user);
}

string friendsUrl(User::Ptr user)
{
	return addQueryString(
		URL_FRIENDS,
		userQueryString(user)
	);
}

int Api::Api::items(const Parser::Ptr& parser, const ApiKey& key, User::Ptr user)
{
	Response resp = get(key, itemsUrl(user, parser));

	return parser->items(resp, user, queue);
}

Response Api::Api::get(const ApiKey& key, string url)
{
    // The return value of this function.
	Response resp;

    // The HTTP Request.
    // The output stream of this request will be written to the Response object.
	curlpp::Easy myRequest;

    // Add the API Key to the URL.
    url = addQueryParams(
        url,
        "key=%s",
        key.value().c_str()
    );

    logger->debug(url);

	try
	{
        // Prepare the HTTP Request.
		myRequest.setOpt<Url>(url);
		myRequest.setOpt<WriteStream>(resp.getStream());
        myRequest.setOpt<FollowLocation>(true);

        // Perform the HTTP Request.
		myRequest.perform();
	}
    // Log any curl errors that occur.
	catch (curlpp::RuntimeError & e)
	{
		logger->handle(e);
	}
	catch (curlpp::LogicError & e)
	{
		logger->handle(e);
	}

	return resp;
}

List<User::Ptr> Api::Api::friends(ApiKey& key, User::Ptr user)
{
	// The return value of this function.
	List<User::Ptr> result;

	// Loop Variable: the steam ID of the user.
	string steamid;

	/**
	 * JSON Values.
	 * NOTE:
	 *  !emptyValue == true
	 *  emptyValue.asString() == ""
	 */
	Response::JsonValue emptyValue, friends, root;

	// Prepare the tree
	root = *get(key, friendsUrl(user)).json();
	friends = root
		.get("friendslist", emptyValue)
		.get("friends", emptyValue)
	;

	if (!friends) return result;

	// Process the tree
	for (auto user : friends) {
		steamid = user.get("steamid", emptyValue).asString();

		if (steamid == "") {
			logger->error("Parsing User's friend list failed: steam ID not found.");
			continue;
		}

		result.add(std::make_shared<User>(steamid));
	}

	return result;
}
