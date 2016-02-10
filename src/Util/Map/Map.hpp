#ifndef MAP_H
#define MAP_H

#include <map>

template<typename T1, typename T2>
struct Map : public std::map<T1, T2> {
	typedef std::pair<T1, T2> Pair;
};

#endif
