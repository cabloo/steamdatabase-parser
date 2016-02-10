#include "Service/Database/Dispatcher.hpp"
#include <iostream>

void DatabaseDispatcher::query(const char* query)
{
	std::cout << query << "\n";
}
