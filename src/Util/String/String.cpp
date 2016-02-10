#include "String.hpp"

using std::string;

Util::String::IntPointerFunc Util::String::is_space()
{
	return Util::String::IntPointerFunc(std::isspace);
}

Util::String::NegIntPointerFunc Util::String::not_space()
{
	return std::not1(Util::String::is_space());
}

string& Util::String::ltrim(string& s)
{
	s.erase(s.begin(), Util::String::findNonSpace(s));
	return s;
}

string& Util::String::rtrim(string& s)
{
	s.erase(Util::String::findNonSpace(s, true), s.end());
	return s;
}

string::iterator Util::String::findNonSpace(string& s)
{
	return Util::String::findNonSpace(s, false);
}

string::iterator Util::String::findNonSpace(string& s, bool fromBack)
{
	if (fromBack) {
		return std::find_if(s.rbegin(), s.rend(), Util::String::not_space()).base();
	}

	return std::find_if(s.begin(), s.end(), Util::String::not_space());
}

string& Util::String::trim(string&s)
{
	return ltrim(rtrim(s));
}

string Util::String::addQueryString(string url, string query)
{
    char delim = url.find_first_of('?') == string::npos ? '?' : '&';

	return url + delim + query;
}
