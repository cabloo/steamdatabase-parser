#ifndef RESPONSE_H
#define RESPONSE_H

#include <sstream>
#include <memory>
#include <json/json.h>
#include "Util/Log/Log.hpp"

class Response {
public:
typedef std::stringstream Stream;
typedef Json::Value JsonValue;
typedef std::shared_ptr< JsonValue > JsonValuePtr;

private:
typedef std::unique_ptr< Util::Log > LogPtr;

/**
 * Stream: Holds the raw string stream Response.
 */
Stream* stream;

/**
 * Root: Holds a cached version of the JSON tree.
 */
JsonValuePtr root;

/**
 * Log: Logs debug messages and errors that occur.
 */
LogPtr log;

public:
Response() : stream(new Stream), root(nullptr), log(new Util::Log)
{

}

Response(Response const & other)
{
    Response();
}

/**
 * Access pointer to stream (for reading or writing).
 *
 * @return raw access to the Response's output stream.
 */
Stream* getStream()
{
	return stream;
}

/**
 * Access stream as JSON.
 */
JsonValuePtr json()
{
    if (!root) {
        root = std::make_shared<JsonValue>();
        Json::CharReaderBuilder rbuilder;
        std::string err;
        Stream& input = *getStream();
        if (!Json::parseFromStream(rbuilder, input, root.get(), &err)) {
            root = nullptr;
            log->error("Failed to parse JSON Response.");
            log->error(err);
            log->debug(input.str());
        }
    }
    return root;
}
};

#endif
