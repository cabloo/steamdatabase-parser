/**
 * Database Dispatcher
 * =====
 * Responsibilities:
 *  - Dispatches raw queries to the database.
 */

#ifndef MYSQL_DISPATCHER_H
#define MYSQL_DISPATCHER_H

#include "Service/Database/Dispatcher.hpp"
#include "MySQLException.hpp"

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <memory>

class MySQLDispatcher : public DatabaseDispatcher {
public:
/**
 * Typedefs
 */
typedef MySQLException Exception;
typedef sql::Driver Driver;
typedef sql::Connection Connection;
typedef std::unique_ptr<Connection> ConnPtr;
typedef sql::Statement Statement;
typedef std::unique_ptr<Statement> StmtPtr;
typedef sql::ResultSet Result;
typedef std::unique_ptr<Result> ResPtr;
typedef sql::SQLException SQLException;

/**
 * Initialize an instance of the MySQL Dispatcher class.
 */
MySQLDispatcher() : stmt(StmtPtr()), result(ResPtr())
{
}

/**
 * Required for Unique Pointers to work.
 */
MySQLDispatcher(MySQLDispatcher const &)
{
    MySQLDispatcher();
}

/**
 * Run a Query on the MySQL database.
 *
 * @param query the already prepared query string.
 */
void query(const char * query);

/**
 * Run a Query on the MySQL database.
 *
 * @param query the already prepared query string.
 */
void exec(const char * query);

/**
 * Get the number of results for the query.
 */
size_t count();

/**
 * Move to the next row in the result set.
 */
bool next();

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

protected:

/**
 * MySQL storage variables
 */
static Driver *driver;
static ConnPtr con;
StmtPtr stmt;
ResPtr result;

/**
 * Ensure the Database is connected.
 * This should be called before every query.
 */
static void init();

/**
 * Determine if the connection to the database is valid.
 * Drops the connection if it's not valid.
 */
static bool connected();

/**
 * Connect to the database.
 * This function should only be called once, or again after a manual disconnect().
 */
static void connect();

/**
 * Disconnect from the database.
 * This function does not raise an exception if the database was not already connected.
 */
static void disconnect();

/**
 * Handle a MySQL Exception for a specific query.
 *
 * @param e the MySQL Exception thrown by the library
 * @param query the MySQL Query string.
 */
static void handle(SQLException &e, const char * query);

/**
 * Convert a MySQL Exception thrown by the library to our own.
 *
 * @param e the MySQL Exception thrown by the library
 *
 * @return MySQLException
 */
static Exception except(SQLException &e, const char * query);

/**
 * Convert a MySQL Exception thrown by the library to our own.
 *
 * @param the MySQL Exception thrown by the library
 */
static Exception except(SQLException &e);
};

#endif
