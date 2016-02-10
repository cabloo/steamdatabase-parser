/**
 * Command Line Interface
 * =====
 * Responsibilities
 *  - Accept input from command line
 *  - Output terminal-friendly text
 */

#ifndef CLI_H
#define CLI_H

#include "Util/Map/Map.hpp"
#include "Util/String/String.hpp"
#include "CliOptions.hpp"
#include <iostream>

namespace Util
{

class Cli {
private:
const char HEADER_CHAR = '=';
const char* OPTION = " %d. %s";
const char* INVALID_OPTION = "Invalid Option. Please try again, or press Ctrl-C to force exit (does not kill workers).";

public:
Cli()
{
}

/**
 * Display a list of options for the user to choose from.
 * @param  opts
 * @return the chosen option
 */
CliOptions::Key options(CliOptions& opts)
{
	typedef Map<int, CliOptions::Key> IntMap;
	IntMap optIndex;
	CliOptions::Iterator it;
	int i = 1;

	// Output list of options
	for (it = opts.begin(); it != opts.end(); ++it, ++i) {
		optIndex.insert(IntMap::Pair(i, it->first));
		output(OPTION, i, it->second);
	}

	// Get user input
	int input = in();

	// Map the user input index back to the option index, and return it.
	CliOptions::Key val = optIndex[input];
	if (!val) {
		output(INVALID_OPTION);
		return options(opts);
	}

	return val;
}

/**
 * Output a header.
 * @param text the text to put in the header
 */
void outputHeader(std::string text)
{
	std::string out = Util::String::format("| %s |", text.c_str());
	std::string head(out.length(), HEADER_CHAR);

	output("%s\n%s\n%s", head.c_str(), out.c_str(), head.c_str());
}

/**
 * Output a string, with a new line.
 * @param out the string to output
 */
void output(const std::string out)
{
	output(out.c_str());
}

/**
 * Output a string, with a new line.
 * @param out the string to output
 */
void output(const char* out)
{
	std::cout << out << EOL;
}

/**
 * Output a string using string formatting, with a new line.
 * @param out the string to output
 * @param mixed ... the values to format into the string
 */
template<typename ... Args>
void output(const char* format, Args ... args)
{
	output(Util::String::format(format, args ...));
}

/**
 * Get an int via stdin.
 * @return -1 on invalid input.
 */
int in()
{
	std::string in = "";

	std::cin >> in;
	try {
		return std::stoi(in);
	} catch (std::invalid_argument) {
		return -1;
	}
}
};

}

#endif
