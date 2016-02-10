/**
 * Database Queue
 * =====
 * Pull and/or push to the Database.
 */

#ifndef DATABASEQUEUE_H
#define DATABASEQUEUE_H

#include <memory>
#include "Service/Database/Database.hpp"

class DatabaseQueue {
protected:
typedef std::unique_ptr< Database > DatabasePtr;
DatabasePtr db;

public:
DatabaseQueue() : db(DatabasePtr(new Database))
{
}
};

#endif
