#include <iostream>
#include "Util/String/String.hpp"
#include "Util/Log/Log.hpp"

using Util::String::string;

void Util::Log::error(string msg)
{
    std::cerr << msg << std::endl;
}

/**
 * TODO: add a way to enable/disable debug mode via the compiler.
 */
void Util::Log::debug(string msg)
{
    std::cout << msg << std::endl;
}

void Util::Log::handle(std::exception &e)
{
    error(e.what());
}
