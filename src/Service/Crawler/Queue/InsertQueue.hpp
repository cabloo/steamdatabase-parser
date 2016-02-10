/**
 * Insert Queue
 * =====
 * Store queries for insert into the Database.
 */

#ifndef INSERTQUEUE_H
#define INSERTQUEUE_H

#include "Util/String/String.hpp"
#include "DatabaseQueue.hpp"

#include <vector>
#include <string>

class InsertQueue : public DatabaseQueue {
public:
/**
 * Column struct:
 * =====
 * Name: acts like a c string
 * Array: acts like a std vector
 */
struct Column {
	typedef const char * Name;
	typedef const std::vector<Name> Array;
};

private:
const int MAX_ITEMS = 100;
int insert_count = 0;
std::string insert = "";

protected:
InsertQueue()
{
}

// Required abstract methods
virtual typename Column::Array columns() const = 0;
virtual std::string table() = 0;

/**
 * Get the Insert query string format.
 */
const char* queryFormat()
{
	return "INSERT INTO %s (%s) VALUES %s ON DUPLICATE KEY UPDATE %s";
}

/**
 * Add an insert to the Queue, then check if it's ready to send.
 */
void queueInsert(std::string ins)
{
	char delim = insert_count ? ',' : ' ';

    insert += Util::String::format("%c(%s)", delim, ins.c_str());
	if (insert_count++ >= MAX_ITEMS)
		send();
}

/**
 * Prepare the query for sending.
 * @return the query to run on the database
 */
std::string prepareQuery()
{
	char column_sep;
	std::string column_names;
	std::string key_updates;

	// Prepare the columns
	typename Column::Array cols = columns();
	typename Column::Name last_col = cols.back();

	for (auto column : cols) {
		column_sep = (column == last_col) ? '\0' : ',';

		// INSERT INTO <table> (...)
		column_names = Util::String::format(
			"%s%s%c",
			column_names.c_str(),
			column,
			column_sep
		);

		// ON DUPLICATE KEY UPDATE ...
		key_updates = Util::String::format(
			"%s%s = VALUES(%s)%c",
			key_updates.c_str(),
			column,
			column,
			column_sep
		);
	}

	// Finalize the query
	return Util::String::format(
		queryFormat(),
		table().c_str(),
		column_names.c_str(),
		insert.c_str(),
		key_updates.c_str()
	);
}

public:
/**
 * Reset the insert queue
 */
void empty()
{
	insert_count = 0;
	insert = "";
}

/**
 * Handle the queue by sending it off to the database.
 */
void send()
{
	if (insert.empty())
		return;

	// Insert the items in the database and empty the queue
	this->db->exec(prepareQuery());
	empty();
}
};

#endif
