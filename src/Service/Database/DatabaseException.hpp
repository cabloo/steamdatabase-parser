#ifndef DATABASE_EXCEPTION_H
#define DATABASE_EXCEPTION_H

#include <exception>
#include "Util/String/String.hpp"

class DatabaseException : public std::exception {
protected:
int error;
const char * msg;
const char * sql;
const char * FORMAT = "Database Error #%d: %s\n"
    "Query: %s";

public:
DatabaseException(int error, const char * what, const char * sql)
	: error(error), msg(what), sql(sql)
{
}

const char * what() const noexcept
{
	return Util::String::format(FORMAT, error, msg, sql).c_str();
}
};

#endif
