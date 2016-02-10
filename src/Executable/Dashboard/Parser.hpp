/**
 * Parser
 * =====
 * Handles the Command Line-accessible controls for the entire Parser.
 * Responsibilities:
 *  - Accept command line input from user to run parser commands.
 *  - Check if any setup is required, require user to do it if so.
 * TODO:
 *  - Allow user to start worker instances.
 *  - Keep tabs on what workers have been started
 *  - Ability to turn off running worker threads
 */

#ifndef PARSER_H
#define PARSER_H

#include "Util/Cli/Cli.hpp"
#include "Service/Config/Config.hpp"
#include "Status.hpp"
#include "Workers.hpp"

class Parser {
private:
Config DBConfig = Config("db");
Workers workers;
Util::Cli cli;

const char * NOT_CONFIGURED = "Please edit %s then try running setup again.";

public:
typedef ParserStatus Status;
/**
 * Command line initialization.
 *
 * @param  argv number of command line args
 * @param  argc command line args
 */
Parser(int argv, char **& argc);

/**
 * Show the Menu.
 * If this function returns, the program ends -
 * but normally it will call itself again.
 */
void showMenu();

Util::CliOptions options(Status& state);

/**
 * Get the current parser status.
 *
 * @return the Parser's current state
 */
Status status();
};

#endif
