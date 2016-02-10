/**
 * The generic Parser implementation.
 */

#ifndef PARSER_H
#define PARSER_H

#include "Service/Api/Response.hpp"
#include "Service/Api/Object/Item.hpp"
#include "Service/Crawler/Queue/ItemQueue.hpp"
#include "Util/List/List.hpp"
#include "Util/String/String.hpp"

class Parser {
public:
typedef ItemQueue::Ptr QueuePtr;
typedef std::shared_ptr<Parser> Ptr;

private:
QueuePtr _queue;

public:
Parser(QueuePtr queue) : _queue(queue) {

}

QueuePtr queue() {
    return _queue;
}

virtual Util::String::string itemsUrl(User::Ptr user) = 0;

virtual int items(Response& resp, User::Ptr user) = 0;
};

#endif
