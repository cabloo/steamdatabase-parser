/**
 * Config
 * =====
 * Responsibilities
 *  - Parse config files for the application
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <fstream>
#include <sstream>

class Config {
private:
const char * file;
static const char * FILE_FORMAT;
static const char * REQUIRED;
static const char DELIM;

public:
typedef std::pair<std::string, std::string> Pair;

typedef const char* Key;
Config(const char * file) : file(file)
{
}

/**
 * Determine the filename to look up.
 * @return the file to look in for config values
 */
std::string fileName();

/**
 * Fetch a string config value by key.
 * @param  key
 * @return the config value matching key, or null if none is found.
 */
std::string str(Key key);

/**
 * C-string alias for str().
 *
 * @param  key
 *
 * @return the config value matching key, or null if none is found.
 */
void c_str(Key key, const char * *store);

/**
 * Fetch an integer config value by key.
 * TODO: what happens for empty/unset values
 *
 * @param  key
 * @return the config value matching key
 */
int integer(Key key);

/**
 * Get a key/value pair from the config file.
 * @return true if a valid key/value pair was found.
 */
bool getPair(std::ifstream& configFile, Pair& keyValue);

/**
 * Check if the configuration file is incomplete.
 * Checks for any value that equals <required>
 * @return true if the config is invalid or incomplete
 */
bool incomplete();
};

#endif
