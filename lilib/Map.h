#ifndef LILIB_MAP_H
#define LILIB_MAP_H
#include "List.h"
#include "Pair.h"

template <typename F, typename S>
class liMap : public liList<liPair<F, S>> {
public:
	int FindIndex(F key);
	S& operator[](F key);
};

template<typename F, typename S>
inline int liMap<F, S>::FindIndex(F key) {
	for (size_t i = 0; i < Size(); i++) {
		if (data[i].first == key)
			return i;
	}
	return 0;
}

template<typename F, typename S>
inline S& liMap<F, S>::operator[](F key) {
	return data[FindIndex(key)].second;
}

#endif