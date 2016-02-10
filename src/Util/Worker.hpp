#include <unistd.h>

class Worker
{
private:
int queuePause;
int currPause;
int maxPause;

protected:
/**
 * Wait the Current Pause interval.
 */
void wait()
{
	sleep(currPause);
}

public:
/**
 * Process all available worker jobs.
 * @return true if current wait time should be reset.
 */
virtual bool work() = 0;

/**
 * Recursively crawl through the Queue.
 */
void start()
{
	// Process all available jobs for the worker.
	bool reset = work();

	// Wait the Current Pause interval, then increment it.
	wait(); increaseWaitTime();

	// Reset the wait time if the worker actually got something done.
	if (reset)
		resetWaitTime();

	// Diligently continue working.
	start();
}

/**
 * Set the wait time (time to wait after empty queue before retrying).
 * @param seconds number of seconds to wait
 */
void setWaitTime(int seconds)
{
	currPause = queuePause = seconds;
	// TODO: should maxPause be configurable?
	maxPause = queuePause * 10;
}

/**
 * Get the Current Pause interval.
 * @return number of seconds to wait
 */
int getWaitTime()
{
	return currPause;
}

/**
 * Increase the Current Pause interval.
 */
void increaseWaitTime()
{
	currPause = std::min(currPause + queuePause, maxPause);
}

void resetWaitTime()
{
	currPause = queuePause;
}
};
