/**
 * Queue Worker
 * Author: Zane Hooper <zanehooper.com>
 * Authorized use only. Please email zanehoop@gmail.com to request access.
 * Do not use, share, or sell this code without authorization!
 * =====
 * Takes queued users and uses the Steam API to store their backpack and friend information.
 */

#include "Service/Crawler/Crawler.hpp"
#include "Service/Config/Config.hpp"
#include "Util/Worker.hpp"

const char * END_OF_QUEUE = "Hit end of Queue, waiting %d seconds then trying again.";

class QueueWorker : public Worker
{
private:
Config config = Config("crawler");
Crawler crawler = Crawler();

protected:
bool work()
{
	// Start scanning.
	bool worked = crawler.start();

	// At the end of the queue pause,
	// hoping something will be added after the pause.
	crawler.state.debug(END_OF_QUEUE, getWaitTime());

	// Reset the wait time if work was done.
    return worked;
}

public:
/**
 * Initialize the Queued worker instance.
 */
QueueWorker()
{
	// Enable debug mode.
	crawler.state.debug();

	// Save relevant configs.
	setWaitTime(config.integer("wait_on_queue"));

	// Start crawling.
	start();
}
};

/**
 * Initialize the Queued worker instance.
 */
int main()
{
	QueueWorker();
	return 0;
}
