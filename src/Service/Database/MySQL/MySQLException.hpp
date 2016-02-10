/**
 * MySQLException
 * =====
 * Implements the generic DatabaseException class for MySQL Exceptions.
 */
#ifndef MYSQL_EXCEPTION_H
#define MYSQL_EXCEPTION_H

#include "Service/Database/DatabaseException.hpp"

class MySQLException : public DatabaseException {
protected:
const char * FORMAT = "MySQL Error #%d: %s\n"
					  "Query: %s";

public:
MySQLException(int error, const char * what, const char * sql)
	: DatabaseException(error, what, sql)
{
}
};

#endif
