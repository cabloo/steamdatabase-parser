#ifndef LIST_H
#define LIST_H

#include <vector>
#include "ListIterator.hpp"

template <class Class>
class List {
private:
    std::vector<Class> items;

public:
    typedef ListIterator<Class> Iterator;

    /**
     * Add an item to the list.
     * @param item
     */
    void add(Class item) {
        items.push_back(item);
    }

    /**
     * Get the number of items in the list.
     */
    int count() {
        return items.size();
    }

    /**
     * Determine whether or not the List is empty.
     * @return int 1 if empty, 0 if not
     */
    int empty() {
        return items.empty();
    }

    /**
     * Get an iterator starting at the first element in the List.
     */
    Iterator first() {
        return Iterator(items.begin(), items.end());
    }
};

#endif
