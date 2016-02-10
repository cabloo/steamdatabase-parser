/**
 * Database
 * =====
 * Responsibilities:
 *  - Gets Database auth info via Config.
 *  - Uses Database auth info to connect to the MySQL database.
 *  - Provides an interface to a DatabaseDispatcher for running raw queries on that database.
 */

#ifndef DATABASE_H
#define DATABASE_H

#include <memory>
#include "Dispatcher.hpp"
#include "DatabaseException.hpp"
#include "Service/Config/Config.hpp"
#include "Util/String/String.hpp"

using string = Util::String::string;

class Database {
public:
typedef DatabaseDispatcher Dispatcher;
typedef std::unique_ptr< Dispatcher > DispatcherPtr;
typedef std::unique_ptr< Config > ConfigPtr;

private:
DispatcherPtr dispatcher;
ConfigPtr config;
string prefix;
bool prefixChecked = false;

public:
/**
 * Create a Database Instance.
 * NOTE: the database is initialized across multiple classes,
 * so this class should keep a reference to a global
 * database connection or something.
 */
Database();

/**
 * Required for Unique Pointers to work.
 */
Database(Database const &)
{
    Database();
}

/**
 * Run a query using string formatting.
 * NOTE: Since this is a template function it must be defined in the header file.
 *
 * @param format the query format string
 * @param mixed ... the values to format into the string
 */
template<typename ... Args>
Database* exec(const char* format, Args ... args)
{
	return exec(Util::String::format(format, args ...));
}

/**
 * Run an already prepared query.
 *
 * @param query
 */
Database* exec(const char* query);

/**
 * Run an already prepared query.
 *
 * @param query
 */
Database* exec(string query);


/**
 * Run a query using string formatting.
 * NOTE: Since this is a template function it must be defined in the header file.
 *
 * @param format the query format string
 * @param mixed ... the values to format into the string
 */
template<typename ... Args>
Database* query(const char* format, Args ... args)
{
	return query(Util::String::format(format, args ...));
}

/**
 * Run an already prepared query.
 *
 * @param query
 */
Database* query(const char* query);

/**
 * Run an already prepared query.
 *
 * @param query
 */
Database* query(string query);

/**
 * Move to the next row in the result set.
 */
bool next();

/**
 * Run LAST_INSERT_ID and determine if an ID is found.
 *
 * @return true if an ID was inserted.
 */
bool hasInsertId();

/**
 * Get the value of the last insert ID.
 * NOTE: Must call hasInsertId() before.
 *
 * @return the string version of the last inserted ID.
 */
string getInsertId();

/**
 * Get a column by string name.
 *
 * @param  key the name of the column
 *
 * @return the value of the column on the current row
 */
string get(string key);

/**
 * Get a column by index (starting at 1).
 *
 * @param key the index of the column (starting at 1).
 *
 * @return the value of the column at the given index.
 */
string get(int key);

/**
 * Return the number of results from the last Database Query.
 * TODO: Should the function be passed a query object?
 *
 * @return count results
 */
int count();

/**
 * Get from the Cache or Config the Database table prefix.
 * The prefix is cached in this Class,
 * that way we don't have to check the config file every time.
 *
 * @return the DB string prefix
 */
const string getPrefix();

/**
 * Prefix a table name with the configured DB Prefix.
 *
 * @param  table
 *
 * @return prefixed table
 */
const char* prefixed(string table);

/**
 * Output a DatabaseException to debug.
 *
 * @param e
 */
Database* debug(DatabaseException &e);
};

#endif
