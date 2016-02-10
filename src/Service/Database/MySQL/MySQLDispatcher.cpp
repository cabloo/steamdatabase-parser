#include "MySQLDispatcher.hpp"
#include "Util/String/String.hpp"
#include "Service/Config/Config.hpp"
// For outputting MySQL Errors to cerr
#include <iostream>

using SQLException = MySQLDispatcher::SQLException;
using Exception = MySQLDispatcher::Exception;
using string = Util::String::string;

MySQLDispatcher::Driver *MySQLDispatcher::driver = get_driver_instance();

MySQLDispatcher::ConnPtr MySQLDispatcher::con = MySQLDispatcher::ConnPtr();

void MySQLDispatcher::connect()
{
	// Get database credentials
	Config DBConfig = Config("db");
	string host = DBConfig.str("host");
	string user = DBConfig.str("user");
	string pass = DBConfig.str("pass");
	string name = DBConfig.str("database");

	host = Util::String::format("tcp://%s", host.c_str());

	// Initiate connection
	try {
		con.reset(
			driver->connect(host.c_str(), user.c_str(), pass.c_str())
		);
		con->setSchema(name.c_str());
	} catch (SQLException &e) {
		disconnect();
		throw except(e);
	}
}

void MySQLDispatcher::disconnect()
{
	con.release();
}

bool MySQLDispatcher::connected()
{
	if (con != NULL && con->isClosed())
		disconnect();

	return con != NULL;
}

void MySQLDispatcher::init()
{
	if (!connected())
		connect();
}

void MySQLDispatcher::query(const char* query)
{
	// Ensure Database is connected.
	init();

	// Run the query
	try {
        std::cout << query << std::endl;
		stmt.reset(con->createStatement());
		result.reset(stmt->executeQuery(query));
	} catch (SQLException &e) {
		handle(e, query);
	}
}

void MySQLDispatcher::exec(const char* query)
{
	// Ensure Database is connected.
	init();

	// Run the query
	try {
        std::cout << query << std::endl;
		stmt.reset(con->createStatement());
		stmt->execute(query);
	} catch (SQLException &e) {
		handle(e, query);
	}
}

size_t MySQLDispatcher::count()
{
	return result ? result->rowsCount() : 0;
}

bool MySQLDispatcher::next()
{
    return result ? result->next() : false;
}

string MySQLDispatcher::get(string key)
{
    return result ? result->getString(key) : "";
}

string MySQLDispatcher::get(int key)
{
    return result ? result->getString(key) : "";
}

Exception MySQLDispatcher::except(SQLException &e, const char * query)
{
	return Exception(e.getErrorCode(), e.what(), query);
}

Exception MySQLDispatcher::except(SQLException &e)
{
	return Exception(e.getErrorCode(), e.what(), "");
}

void MySQLDispatcher::handle(SQLException &e, const char * query)
{
	throw except(e, query);
}
