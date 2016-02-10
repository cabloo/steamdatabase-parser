/**
 * Database Dispatcher
 * =====
 * Responsibilities:
 *  - Dispatches raw queries to an already-open database connection.
 */

#ifndef DATABASE_DISPATCHER_H
#define DATABASE_DISPATCHER_H

#include <stdlib.h>
#include <string>

using string = std::string;

class DatabaseDispatcher {
public:
DatabaseDispatcher()
{
}

/**
 * Dispatch a query to be run on the Database.
 *
 * @param query the query to be executed
 */
virtual void query(const char * query) = 0;

/**
 * Dispatch a query to be run on the Database.
 *
 * @param query the query to be executed
 */
virtual void exec(const char * query) = 0;

/**
 * Get the number of results for the query.
 */
virtual size_t count() = 0;

/**
 * Move to the next row in the result set.
 */
virtual bool next() = 0;

/**
 * Get a column by string name.
 *
 * @param  key the name of the column
 *
 * @return the value of the column on the current row
 */
virtual string get(string key) = 0;

/**
 * Get a column by index (starting at 1).
 *
 * @param key the index of the column (starting at 1).
 *
 * @return the value of the column at the given index.
 */
virtual string get(int key) = 0;

};

#endif
