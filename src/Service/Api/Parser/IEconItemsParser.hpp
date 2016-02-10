#ifndef IECON_ITEMS_PARSER_H
#define IECON_ITEMS_PARSER_H

#include "Parser.hpp"

class IEconItemsParser : public Parser {
public:
IEconItemsParser(ItemQueue::Ptr queue) : Parser(queue) {}

Util::String::string itemsUrl(User::Ptr user);

int items(Response& resp, User::Ptr user);

protected:
virtual int econId() = 0;
};

#endif
