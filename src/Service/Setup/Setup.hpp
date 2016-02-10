/**
 * Setup
 * =====
 * Responsibilities:
 *  - Determine if any setup is required, and do it if so.
 */

#ifndef SETUP_H
#define SETUP_H

#include "DatabaseSetup.hpp"
#include "Service/Config/Config.hpp"

class Setup {
protected:
DatabaseSetup dbSetup;

public:
Setup()
{
}

/**
 * Determine if setup is required.
 */
bool required()
{
	return dbSetup.required();
}

/**
 * Run setup.
 */
void run()
{
	if (dbSetup.required()) {
		dbSetup.run();
	}
}
};

#endif
