#ifndef UTIL_LOG_H
#define UTIL_LOG_H

#include <exception>
#include "Util/String/String.hpp"

namespace Util
{
class Log
{
public:
Log() {

}

void error(Util::String::string msg);

void debug(Util::String::string msg);

void handle(std::exception &e);

};
}

#endif
