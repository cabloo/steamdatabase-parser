#include <vector>
#include "Util/IteratorWrapper.hpp"

template <class Class>
struct Vector {
	typedef typename std::vector<Class, std::allocator<Class> > vector;
	typedef typename vector::iterator iterator;
};

template <class Class>
class ListIterator : public IteratorWrapper<typename Vector<Class>::iterator, Class> {
	typedef typename Vector<Class>::iterator Iter;
public:
	ListIterator(Iter first, Iter last)
	: IteratorWrapper<Iter, Class>(first, last)
	{}
};
