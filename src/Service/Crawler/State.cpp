/**
 * State
 * Author: Zane Hooper <zanehooper.com>
 * Authorized use only. Please email zanehoop@gmail.com to request access.
 * Do not use, share, or sell this code without authorization!
 * =====
 * Handles the state of the Crawler.
 */

#include "State.hpp"
#include "Util/String/String.hpp"
#include <iostream>

State::State()
{
	start = time();
}

int State::time()
{
	return 1;
}

int State::startTime()
{
	return start;
}

void State::info(std::string message)
{
	std::cout << message << EOL;
}

void State::debug(std::string message)
{
	if (mode != 0) return;

	std::cout << message << EOL;
}
