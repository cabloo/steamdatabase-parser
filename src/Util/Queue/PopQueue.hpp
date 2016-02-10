#ifndef POP_QUEUE_H
#define POP_QUEUE_H

#include "EmptyQueue.hpp"

/**
 * A generic Queue implementation
 */
template<class Class>
class PopQueue {
private:

public:
    /**
     * Remove the top item from the Queue.
     *
     * @return the top item
     */
    virtual Class pop() = 0;
};

#endif
