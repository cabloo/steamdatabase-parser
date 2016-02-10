#include "UserQueue.hpp"
#include "Util/String/String.hpp"
#include <iostream>

using Column = UserQueue::Column;
using string = Util::String::string;

/**
 * The UserQueue table.
 */
static const char * QUEUE_TABLE =
    "user_queue"
;

/**
 * The name of the UserQueue.
 */
static const char * QUEUE_NAME =
    "User"
;

/**
 * Updates a queued user to checked status,
 * storing their user ID via LAST_INSERT_ID.
 */
static const char * QUERY_POP =
	"UPDATE %s SET checked = 1, timestamp = CURRENT_TIMESTAMP,"
	"steamid = LAST_INSERT_ID(steamid) "
	"WHERE checked = 0 ORDER BY timestamp ASC LIMIT 1"
;

/**
 * The columns that need values when inserting.
 */
static Column::Name QUEUE_COLUMNS[1] = {
    "steamid"
};

/**
 * The query format to insert Users into the Database Queue.
 */
static const char * QUERY_INSERT =
    "'%s'"
;

Column::Array UserQueue::columns() const
{
	return Column::Array(
        QUEUE_COLUMNS,
        QUEUE_COLUMNS + sizeof(QUEUE_COLUMNS) / sizeof(Column::Name)
    );
}

string UserQueue::table()
{
	return db->prefixed(QUEUE_TABLE);
}

User::Ptr UserQueue::pop()
{
    string query = Util::String::format(QUERY_POP, table().c_str());

	if (!db->exec(query)->hasInsertId())
		throw EmptyQueue(QUEUE_NAME);

	return std::make_shared<User>(db->getInsertId());
}

void UserQueue::push(User::Ptr user)
{
    string query = Util::String::format(QUERY_INSERT, user->getId32());

    std::cout << query << std::endl;
	queueInsert(query);
}
