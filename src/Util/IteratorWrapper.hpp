template<class Iter, class Val>
class IteratorWrapper {
	Iter cur;
	const Iter last;
public:
	IteratorWrapper() {}

	IteratorWrapper(Iter first, Iter last)
	: cur(first), last(last)
	{}

	Val value() {
		return *cur;
	}

	void next() {
		++cur;
	}

	bool end() {
		return cur == last;
	}
};
