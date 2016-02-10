/**
 * Crawler
 * Author: Zane Hooper <zanehooper.com>
 * Authorized use only. Please email zanehoop@gmail.com to request access.
 * Do not use, share, or sell this code without authorization!
 * =====
 * Crawls the entire Steam Database for users' friends and backpack contents.
 */

#include <memory>
#include "Crawler.hpp"
#include "Service/Api/Parser/TF2Parser.hpp"
#include "Service/Api/Parser/Dota2Parser.hpp"
#include "Util/String/String.hpp"

using Util::String::string;

static const char * USER_PROCESSED =
	"Finished processing user ID %s.\n"
	"Friends: %d.\n"
	"Items: %d."
;
static const char * USER_GET_FRIENDS =
	"Requesting friends for Steam ID: %s"
;
static const char * USER_GET_ITEMS =
	"Requesting items for Steam ID: %s"
;
static const char * USER_NO_FRIENDS =
	"Empty friends list, probably a private profile."
;

/**
 * Whether or not the crawler has done any work yet.
 */
bool processed = false;

/**
 * Whether or not the crawler has been initialized.
 */
bool initialized = false;

Crawler::Crawler()
	: api(ApiPtr(new Api::Api)),
	userQueue(UserQueuePtr(new UserQueue)),
	apiKeyQueue(ApiKeyQueuePtr(new ApiKeyQueue))
{
    addParser<TF2Parser>();
}

const ApiKey Crawler::key()
{
	return apiKeyQueue->pop();
}

void Crawler::initData()
{
	// Initialize the crawler
	initialized = true;
}

void Crawler::processUser(User::Ptr user)
{
    // Save this function's own copy of the ID string.
    string userIdStr = user->getId32();
    const char * userId = userIdStr.c_str();

    // Get and store the user's friends.
	state.debug(USER_GET_FRIENDS, userId);
	int countFriends = queueFriends(user);

    // Get and store the user's items.
	state.debug(USER_GET_ITEMS, userId);
	int countItems = queueItems(user);

    // Store debug statistics.
	state.debug(USER_PROCESSED, userId, countFriends, countItems);
	processed = true;
}

/**
 * Where the magic happens.
 *
 * @throws EmptyQueue if ApiKey or User Queue is empty.
 */
void Crawler::dequeue()
{
	// Check that we have a fresh enough API Key (throws EmptyQueue exception).
	apiKeyQueue->checkKey();

	// Process the next user in the queue.
	processUser(userQueue->pop());

	// Run this function again (won't happen if ApiKey or User Queue was empty).
	dequeue();
}

bool Crawler::start()
{
	if (!initialized)
		initData();

	try {
		dequeue();
	} catch (EmptyQueue& e) {
		// Display empty queue (could be ApiKey or User Queue), and end scanning.
		state.info(e.what());
	}

	return processed;
}

int Crawler::queueFriends(User::Ptr user)
{
	ApiKey apiKey = key();
	List<User::Ptr> friends = api->friends(apiKey, user);

	if (friends.empty()) {
		state.debug(USER_NO_FRIENDS);
		return 0;
	}

	return userQueue->pushList(friends);
}

int Crawler::queueItems(User::Ptr user)
{
	int count = 0;
	List<Item> items;

	for (auto parser : parsers) {
        const ApiKey apiKey = key();
		count += api->items(parser, apiKey, user);
	}

	return count;
}
