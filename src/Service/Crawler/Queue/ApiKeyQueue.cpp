#include "ApiKeyQueue.hpp"
#include "Util/String/String.hpp"

using string = Util::String::string;

/**
 * The name of the API Key Queue.
 */
static const char * QUEUE_NAME =
    "API Key"
;

/**
 * The query to get an API Key from the database.
 */
static const char * QUERY_POP =
    "SELECT value FROM %s"
;

/**
 * The API Keys table.
 */
static const char * TABLE =
    "api_keys"
;

/**
 * The column that the API Key is stored in on the API Keys table.
 */
static const char * COLUMN_KEY =
    "value"
;

/**
 * The number of times a key will be used before a new one is fetched.
 */
const int ApiKeyQueue::KEY_USAGE = 10;

/**
 * Throw the Empty API Key Queue error.
 *
 * @throws EmptyQueue
 */
void throwEmpty()
{
    throw EmptyQueue(QUEUE_NAME);
}

std::string ApiKeyQueue::table()
{
	return db->prefixed(TABLE);
}

void ApiKeyQueue::freshKey()
{
	try {
        db->query(QUERY_POP, table().c_str());
    } catch (DatabaseException &e) {
        db->debug(e);
        throwEmpty();
    }

    if (!db->next())
        throwEmpty();

	current_key = new ApiKey(db->get(COLUMN_KEY));
	current_key_usage = 0;
}

ApiKey ApiKeyQueue::pop()
{
	// Fetch a fresh key if necessary
	checkKey();

	// Iterate the usage count and then return the key.
	current_key_usage++;
	return *current_key;
}

void ApiKeyQueue::checkKey()
{
	if (!current_key || current_key_usage >= KEY_USAGE)
		freshKey();
}
