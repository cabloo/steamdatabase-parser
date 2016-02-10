/**
 * API Key
 * =====
 * An object version of an API Key.
 */

#ifndef APIKEY_H
#define APIKEY_H

#include <string>

class ApiKey {
private:
    const std::string key;

public:
    /**
     * @param key the API Key
     */
    ApiKey(std::string key) : key(key) {}

    const std::string value() {
        return key;
    }
};

#endif
