/**
 * Empty Queue Exception
 */

#ifndef EMPTY_QUEUE_H
#define EMPTY_QUEUE_H

#include <exception>
#include "Util/String/String.hpp"

struct EmptyQueue : public std::exception {
	const char * format = "The %s Queue is Empty.";
	const char * type;

	EmptyQueue(const char * type) : type(type)
	{}

	const char * what() const throw()
	{
		return Util::String::format(format, type).c_str();
	}
};

#endif
