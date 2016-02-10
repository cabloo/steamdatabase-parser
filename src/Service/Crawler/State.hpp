#include "Util/String/String.hpp"
#include <string>

class State {
private:
int start;
int mode = 1;     // TODO: class constants?

public:
State();

/**
 * Get the current UNIX timestamp.
 */
int time();

/**
 * Get the time the crawler was started.
 */
int startTime();

/**
 * Enable debug mode.
 */
void debug()
{
	mode = 0;
}

/**
 * Set status after processing a user.
 */
void processed()
{

}

/**
 * Print debug info, if currently in debug mode.
 */
void debug(std::string message);

/**
 * Full message c-string alias for debug()
 * @param format the c-string message
 */
void debug(const char* message)
{
    debug(std::string(message));
}

/**
 * String formatted version of debug()
 */
template<typename ... Args>
void debug(const char* format, Args ... args)
{
	debug(Util::String::format(format, args ...));
}

/**
 * Print info.
 */
void info(std::string message);
};
