#ifndef TF2_PARSER_H
#define TF2_PARSER_H

#include "IEconItemsParser.hpp"
#include "Service/Crawler/Queue/ItemQueueGame.hpp"

class TF2Parser : public IEconItemsParser, public ItemQueueGame {
protected:
int econId();
public:
TF2Parser(ItemQueue::Ptr queue) : IEconItemsParser(queue) {}
};

#endif
