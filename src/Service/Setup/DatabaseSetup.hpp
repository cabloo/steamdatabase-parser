/**
 * Database Setup
 * =====
 * Responsibilities:
 *  - Check if the database is setup (via SHOW TABLES)
 *  - Create database tables for those that don't already exist.
 */

#ifndef DATABASESETUP_H
#define DATABASESETUP_H

#include "Service/Database/Database.hpp"
#include "Util/Map/Map.hpp"
#include <string>

class DatabaseSetup {
public:
// Table structure
typedef std::string TableName;
typedef const char * TableStructure;
typedef Map<TableName, bool> HasTableMap;

struct Table {
	TableName name;
	TableStructure structure;
};

protected:
typedef std::unique_ptr< Database > DatabasePtr;

private:
// Services
DatabasePtr db;

// State
HasTableMap hasTableMap;
int loaded = 0;

/**
 * Setup a specific table.
 *
 * @param  table the table to setup
 */
void setup(Table table);

/**
 * Check if the database has the given table.
 *
 * @param  table
 * @return true if the table exists
 */
bool hasTable(Table table);

/**
 * Set a table name as already loaded in the database.
 *
 * @param name the full name of the table
 */
void foundTable(TableName name);

public:
DatabaseSetup()
: db(DatabasePtr())
{
}

/**
 * Check if any setup is needed.
 *
 * @return true if setup is required
 */
bool required();

/**
 * Run any setup that is needed.
 */
void run();

/**
 * Load the state from the database
 */
void loadState();
};

#endif
