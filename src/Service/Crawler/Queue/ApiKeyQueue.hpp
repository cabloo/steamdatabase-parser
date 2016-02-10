/**
 * API Key Queue
 * =====
 * Provides a queueing interface for grabbing usable API keys from the database.
 * Currently, an API key is used 10 times each time it is fetched to avoid
 * exceeeding the rate limit. In the future, this could be quite a bit smarter.
 */

#ifndef APIKEYQUEUE_H
#define APIKEYQUEUE_H

#include "DatabaseQueue.hpp"
#include "Util/Queue/PopQueue.hpp"
#include "Service/Api/Object/ApiKey.hpp"

class ApiKeyQueue : public DatabaseQueue, public PopQueue<ApiKey> {
protected:
/**
 * The number of times a key will be used before a new one is fetched.
 */
static const int KEY_USAGE;

// TODO: move current_key and current_key_usage into a struct
/**
 * Stores the current API Key in memory.
 */
ApiKey* current_key = NULL;

/**
 * How many times the current key has been used.
 */
int current_key_usage = 0;

/**
 * Get the table API Keys are stored in.
 */
std::string table();

/**
 * Get a fresh API Key from the database and store it in the current_key.
 * Also resets the internal usage count.
 * @throws EmptyQueue
 */
void freshKey();

public:
/**
 * Destructor for cleanup.
 */
~ApiKeyQueue()
{
	delete current_key;
}

/**
 * Get a usable API key from the database, and iterate its usage count.
 */
ApiKey pop();

/**
 * Check that the queue is not empty without iterating the count.
 * Fetches the next key and stores it.
 */
void checkKey();
};

#endif
