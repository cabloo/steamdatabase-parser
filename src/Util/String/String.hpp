/**
 * String Utils
 * =====
 * The Util::String namespace.
 * Responsibilities:
 *  - Formatting strings
 *  - Trimming strings
 */

#ifndef UTIL_STRING_H
#define UTIL_STRING_H

#include <memory>
#include <iostream>
#include <string>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

#define EOL "\n";

namespace Util
{
namespace String
{

// Common types
typedef std::string string;
typedef std::pointer_to_unary_function<int, int> IntPointerFunc;
typedef std::unary_negate<IntPointerFunc> NegIntPointerFunc;

/**
 * Return a space finder for string iterators.
 * @return callback function, returns true if the char is a space.
 */
IntPointerFunc is_space();

/**
 * Return a non-space finder for string iterators.
 *
 */
NegIntPointerFunc not_space();

string addQueryString(string url, string query);

/**
 * Trim whitespace from the left side of a string.
 * NOTE: This function modifies the argument in place.
 *
 * @param  s the string to trim (will be modified in place)
 * @return the modified string
 */
string& ltrim(string& s);

/**
 * Trim whitespace from the left side of a string.
 * NOTE: This function modifies the argument in place.
 *
 * @param  s the string to trim (will be modified in place)
 * @return the modified string
 */
string& rtrim(string& s);

/**
 * Trim whitespace from both sides of a string.
 * NOTE: This function modifies the argument in place.
 *
 * @param  s the string to trim (will be modified in place)
 * @return the modified string
 */
string& trim(string& s);

/**
 * Get an iterator at the first non-space character in the string.
 * TODO: What does this return on empty strings?
 *
 * @param  s  the string to find the space in
 *
 * @return    an iterator at the position containing the non-space character.
 */
string::iterator findNonSpace(string& s);

/**
 * Get an iterator at the first or last non-space character in the string.
 * TODO: What does this return on empty strings?
 *
 * @param  s        the string to find the space in
 * @param  fromBack true to start from the last non-space character.
 *
 * @return          an iterator at the position containing the non-space character.
 */
string::iterator findNonSpace(string& s, bool fromBack);

/**
 * Format a string according to a given string format.
 * NOTE: Since this is a template function, it must be defined in the hpp file.
 *
 * @param format the format string
 * @param [,params...] the parameters to format into the string.
 *
 * @return the formatted string
 */
template<typename ... Args>
string format(string fmt, Args ... args)
{
    const char * format = fmt.c_str();
	size_t size = snprintf(nullptr, 0, format, args ...) + 1;   // Extra space for '\0'

	std::unique_ptr<char[]> buf(new char[ size ]);

	snprintf(buf.get(), size, format, args ...);
	return string(buf.get(), buf.get() + size - 1);   // We don't want the '\0' inside
}

template<typename ... Args>
string addQueryParams(string url, string argFormat, Args ... args)
{
	return addQueryString(url, format(argFormat, args ...));
}

}
}

#endif
