#ifndef LILIB_PAIR_H
#define LILIB_PAIR_H

template<typename F, typename S>
struct liPair {
	F first;
	S second;

	liPair() {}
	liPair(F first, S second);
	void DeleteBoth();
};

template<typename F, typename S>
inline liPair<F, S>::liPair(F first, S second)
{
	this->first = first;
	this->second = second;
}

template<typename F, typename S>
inline void liPair<F, S>::DeleteBoth()
{
	delete first;
	delete second;
}

#endif