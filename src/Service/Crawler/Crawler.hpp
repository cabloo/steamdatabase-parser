/**
 * Crawler
 * =====
 * The interface between the API and the Database Queues.
 * When the Crawler is finished, it pushes all buffered queues to the database.
 *
 * Responsibilities:
 *  - Pull from API Key and User Queue
 *  - Trigger API requests (using API Key and User)
 *  - Pass the results along to the Item and User Queue
 */

#include "State.hpp"
#include "Queue/UserQueue.hpp"
#include "Queue/ItemQueue.hpp"
#include "Queue/ApiKeyQueue.hpp"
#include "Service/Api/Api.hpp"
#include "Service/Api/Parser/Parser.hpp"
#include <string>

class Crawler {
private:
typedef std::unique_ptr< Api::Api > ApiPtr;
typedef std::unique_ptr< UserQueue > UserQueuePtr;
typedef std::unique_ptr< ApiKeyQueue > ApiKeyQueuePtr;

ApiPtr api;
UserQueuePtr userQueue;
ApiKeyQueuePtr apiKeyQueue;
std::vector<Parser::Ptr> parsers;

void initData();
void dequeue();

/**
 * Get and store a Steam User's friends.
 * @param user the User whose friends list will be checked.
 * @return int the number of users that got stored
 */
int queueFriends(User::Ptr user);

/**
 * Get and store a Steam user's items.
 * @param user the User whose backpack will be checked.
 * @return int the number of items that got stored
 */
int queueItems(User::Ptr user);

/**
 * Process a user's friends and items.
 * @param user the User to process
 */
void processUser(User::Ptr user);

const ApiKey key();

public:
State state;

Crawler();

Crawler(const Crawler &)
	: Crawler()
{
}

/**
 * When the crawler exits, clear out the Queues.
 * Perhaps this should be an option on the Queue?
 * e.g. userQueue.sendOnDestroy();
 */
~Crawler()
{
	userQueue->send();
	for (auto parser : parsers)
		parser->queue()->send();
}

template <class Parser>
void addParser()
{
	std::shared_ptr< Parser > parser = std::make_shared< Parser >(
		std::make_shared< ItemQueue >()
	);
	parsers.push_back(parser);
}

/**
 * Start crawling.
 * @return true if any users were processed.
 */
bool start();
};
