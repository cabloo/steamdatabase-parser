#ifndef PUSH_QUEUE_H
#define PUSH_QUEUE_H

#include "EmptyQueue.hpp"
#include "Util/List/List.hpp"

/**
 * A generic Queue implementation
 */
template<class Class>
class PushQueue {
private:

public:
typedef std::shared_ptr< PushQueue<Class> > Ptr;

/**
 * Add an item to the Queue.
 * @param Class the item to add
 */
virtual void push(Class) = 0;

/**
 * Add all the items from a given List to the Queue.
 * @param items the List of items to push onto the Queue.
 * @return int the number of items that were added to the queue.
 */
int pushList(List<Class>& items)
{
	int i = 0;

	// Add each item from the list to the Queue.
	for (ListIterator<Class> it = items.first(); !it.end(); it.next()) {
		push(it.value());
		i++;
	}

	return i;
}
};

#endif
