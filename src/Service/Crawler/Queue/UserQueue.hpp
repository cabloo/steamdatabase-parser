/**
 * Crawler User Queue
 * =====
 * Handles the interface between the app and the database's user queue.
 */

#ifndef USERQUEUE_H
#define USERQUEUE_H

#include "InsertQueue.hpp"
#include "Util/Queue/PushQueue.hpp"
#include "Util/Queue/PopQueue.hpp"
#include "Service/Api/Object/User.hpp"
#include <string>

class UserQueue : public InsertQueue, public PopQueue<User::Ptr>, public PushQueue<User::Ptr> {
protected:
typename Column::Array columns() const;

std::string table();

public:

/**
 * Pop the next user's steam ID off the queue.
 *
 * @throws EmptyQueue if no results are found.
 */
User::Ptr pop();

/**
 * Save a User for future scanning.
 * @param user the user to save to the database
 */
void push(User::Ptr user);
};

#endif
