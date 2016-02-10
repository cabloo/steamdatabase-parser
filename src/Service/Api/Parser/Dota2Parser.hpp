#ifndef DOTA2_PARSER_H
#define DOTA2_PARSER_H

#include "IEconItemsParser.hpp"

class Dota2Parser : public IEconItemsParser {
public:
Dota2Parser(ItemQueue::Ptr queue) : IEconItemsParser(queue) {}
protected:
int econId();
};

#endif
