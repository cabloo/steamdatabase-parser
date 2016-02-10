#include "Parser.hpp"

struct Opts {
	// The numbers here define precedence in menu.
	// Highest numbered items are shown last in the list.
	static const int DbSetup = 1;
	static const int StartQueueWorker = 5;
	static const int StartExpiredWorker = 6;
	static const int Exit = 10;
};

const char * HEADER = "Steam Database Crawler";
const char * STATUS = "Crawler Status: %s";
const char * NUM_WORKERS = "How many %s Workers would you like to start?";
const char * STARTING_WORKER = "Starting %s Worker...";
const char * START_QUEUE_WORKER = "Start Queue Worker(s)";
const char * START_EXPIRED_WORKER = "Start Expired Worker(s)";
const char * QUEUE = "Queue";
const char * EXPIRED = "Expired";
const char * EXIT = "Exit (does not stop workers)";

Parser::Parser(int argv, char **& argc)
{
	// TODO: use args
	cli.outputHeader(HEADER);

	showMenu();
}

void Parser::showMenu()
{
	// Get and show the current parser status.
	Parser::Status state = status();
	cli.output(STATUS, state.describe());

	if (state.equals(Parser::Status::CONFIG_REQ)) {
		cli.output(NOT_CONFIGURED, DBConfig.fileName().c_str());
		return;
	}

	Util::CliOptions opts = options(state);

	switch (int opt = cli.options(opts)) {
	case Opts::Exit:
		return;

	case Opts::StartQueueWorker:
	case Opts::StartExpiredWorker:
		bool isQueue = opt == Opts::StartQueueWorker;
		const char * type = isQueue ? QUEUE : EXPIRED;

		// Get number of workers to start
		cli.output(NUM_WORKERS, type);
		int n = cli.in();

		// TODO: maybe ask for verification if n > 9?

		// Start workers
		for (int i = 0; i < n; i++) {
			cli.output(STARTING_WORKER, type);
			isQueue ? workers.startQueue() : workers.startExpired();
		}
		break;
	}

	showMenu();
}

Util::CliOptions Parser::options(Parser::Status& state)
{
	Util::CliOptions opts;

	/*if (state.equals(Parser::Status::SETUP_REQ)) {
		opts.add(Opts::DbSetup, "Run Database Setup");
		return opts;
	}*/

	// TODO: display number of running queue/expired workers
	opts.add(Opts::StartQueueWorker, START_QUEUE_WORKER);
	opts.add(Opts::StartExpiredWorker, START_EXPIRED_WORKER);
	opts.add(Opts::Exit, EXIT);

	return opts;
}

Parser::Status Parser::status()
{
	if (DBConfig.incomplete())
		return Parser::Status(Parser::Status::CONFIG_REQ);

	// if (setup.required())
	// 	return Parser::Status(Parser::Status::SETUP_REQ);

	return Parser::Status(Parser::Status::RUNNING);
}
