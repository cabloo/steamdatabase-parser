/**
 * Parser Status
 * =====
 * Responsibilities:
 *  - Store the Status of the parser
 *  - Describe the Status of the parser
 */
#ifndef STATUS_H
#define STATUS_H

class ParserStatus {
private:
	int status;

public:
	static const int UNKNOWN = 0;
	static const int CONFIG_REQ = 1;
	static const int SETUP_REQ = 2;
	static const int EMPTY_QUEUE = 3;
	static const int RUNNING = 4;
	static const int PAUSED = 5;

	ParserStatus() { status = UNKNOWN; }
	ParserStatus(int status) : status(status) {}

	const char* describe() {
		switch (status) {
			case CONFIG_REQ: return "Not Configured";
			case SETUP_REQ: return "Not Setup";
			case EMPTY_QUEUE: return "Queue Empty";
			case RUNNING: return "Running";
			case PAUSED: return "Paused";
			default: return "Unknown";
		}
	}

	/**
	 * Determine if this status is equal to the given one by numeric value.
	 * @param  eq the status to check against (e.g. ParserStatus::SETUP_REQ)
	 * @return true if status is the same
	 */
	bool equals(const int eq) const {
		return status == eq;
	}
};

#endif
