#include "Database.hpp"
#include "MySQL/MySQLDispatcher.hpp"

using string = Util::String::string;

/**
 * The query for getting the last inserted id.
 * NOTE: LAST_INSERT_ID is connection-dependent, and therefore thread-safe for our case.
 */
static const char * QUERY_POPPED_ID =
    "SELECT LAST_INSERT_ID()"
;

/**
 * The file the database config is stored in.
 */
static const char * DB_CONFIG_FILE =
    "db"
;

/**
 * The database config key for prefix.
 */
static const char * DB_CONFIG_PREFIX =
    "prefix"
;

Database::Database()
    : dispatcher(DispatcherPtr(new MySQLDispatcher)),
      config(ConfigPtr(new Config(DB_CONFIG_FILE)))
{
}

Database* Database::exec(const char* query)
{
	dispatcher->exec(query);

    return this;
}

Database* Database::exec(string query)
{
	return exec(query.c_str());
}

Database* Database::query(const char* query)
{
    dispatcher->query(query);

    return this;
}

Database* Database::query(string query)
{
	return this->query(query.c_str());
}

bool Database::next()
{
    return dispatcher->next();
}

bool Database::hasInsertId()
{
    return query(QUERY_POPPED_ID)->next();
}

string Database::getInsertId()
{
    return dispatcher->get(1);
}

string Database::get(string key)
{
    return dispatcher->get(key);
}

string Database::get(int key)
{
    return dispatcher->get(key);
}

int Database::count()
{
	return dispatcher->count();
}

const std::string Database::getPrefix()
{
	prefix = prefixChecked ? prefix : config->str(DB_CONFIG_PREFIX);
	prefixChecked = true;
	return prefix;
}

const char* Database::prefixed(const std::string table)
{
	return (getPrefix() + table).c_str();
}

Database* Database::debug(DatabaseException &e)
{
    std::cerr << e.what() << "\n";

    return this;
}
