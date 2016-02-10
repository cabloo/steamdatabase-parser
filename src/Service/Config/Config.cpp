#include "Config.hpp"
#include "Util/String/String.hpp"

// string operations
using std::string;
using std::getline;

// file operations
using std::ifstream;
using std::istringstream;

const char* Config::FILE_FORMAT = "config/%s.ini";
const char* Config::REQUIRED = "<required>";
const char Config::DELIM = '=';

string Config::fileName()
{
	return Util::String::format(FILE_FORMAT, file);
}

string Config::str(Config::Key key)
{
	ifstream configFile;
	Pair pair;

	configFile.open(fileName(), ifstream::in);
	while (getPair(configFile, pair))
		if (pair.first.compare(key) == 0)
			return pair.second;

	return NULL;
}

int Config::integer(Config::Key key)
{
    return std::stoi(str(key));
}

bool Config::getPair(ifstream& configFile, Config::Pair& keyValue)
{
	string line, key, value;

	if (!getline(configFile, line))
		return false;

	istringstream lineStream(line);
	if (!getline(lineStream, key, DELIM))
		return false;

	// TODO: trim whitespace on key and value
	getline(lineStream, value);
	keyValue.first = Util::String::trim(key);
	keyValue.second = Util::String::trim(value);
	return true;
}

bool Config::incomplete()
{
	ifstream configFile;
	Pair pair;

	configFile.open(fileName(), ifstream::in);
	while (getPair(configFile, pair))
		if (pair.second.compare(REQUIRED) == 0)
			return true;

	return false;
}
