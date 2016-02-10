#include "DatabaseSetup.hpp"

typedef DatabaseSetup::Table Table;
typedef DatabaseSetup::TableName TableName;
typedef DatabaseSetup::HasTableMap HasTableMap;

// Variables
const char * CREATE = "CREATE TABLE IF NOT EXISTS";
const char * TABLE = "ENGINE=InnoDB DEFAULT CHARSET=latin1";

Table ApiKeys = {"api_keys", R"EOF(
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `key` varchar(32) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `key` (`key`)
)EOF"};
Table Tf2UserItems = {"tf2_user_items", R"EOF(

)EOF"};

Table tables[] = {
	ApiKeys,
	Tf2UserItems
};

bool DatabaseSetup::required()
{
	// Load the table map.
	loadState();

	for (Table table : tables)
		if (!hasTable(table))
			return true;
	return false;
}

void DatabaseSetup::run()
{
	loadState();

	for (Table table : tables)
		if (!hasTable(table))
			setup(table);
}

void DatabaseSetup::loadState()
{
	if (loaded++ > 1) return;

	db->query("SHOW TABLES");

	// Add each table to the map
	for (Table table : tables)
		foundTable(db->prefixed(table.name));
}

bool DatabaseSetup::hasTable(Table table)
{
	return hasTableMap.count(db->prefixed(table.name)) > 0;
}

void DatabaseSetup::foundTable(TableName name)
{
	hasTableMap.insert(HasTableMap::Pair(name, true));
}

void DatabaseSetup::setup(Table table)
{
	db->exec(
		"%s `%s` (%s) %s",
		CREATE,
		db->prefixed(table.name),
		table.structure,
		TABLE
	);
}
