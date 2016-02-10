/**
 * Crawler Queue
 * =====
 * Provides a queueing interface for saving user's backpack information to the database.
 */

#ifndef ITEMQUEUE_H
#define ITEMQUEUE_H

#include "InsertQueue.hpp"
#include "Util/Queue/PushQueue.hpp"
#include "Util/String/String.hpp"
#include "Service/Api/Object/Item.hpp"
#include <string>
#include "ItemQueueGame.hpp"

class ItemQueue : public InsertQueue, public PushQueue<Item::Ptr> {
protected:
typename Column::Array columns() const;

std::string table();

//static Util::String::string gameName = Game::name();
public:
typedef std::shared_ptr<ItemQueue> Ptr;
/**
 * Add an item onto the queue to be sent to the database.
 * @param item the item to be saved
 */
void push(Item::Ptr item);
};

#endif
