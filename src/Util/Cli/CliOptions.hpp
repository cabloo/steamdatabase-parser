namespace Util
{
#include <map>

class CliOptions {
public:
// Stored Types
typedef const char * Value;
typedef int Key;

// Derived types
typedef std::map<Key, Value> Options;
typedef std::pair<Key, Value> Pair;
typedef Options::iterator Iterator;

void add(Key key, Value val)
{
	options.insert(Pair(key, val));
}

Iterator begin()
{
	return options.begin();
}

Iterator end()
{
	return options.end();
}

private:
Options options;
};
}
