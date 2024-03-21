#ifndef LILIB_LILIB_H
#define LILIB_LILIB_H
#include "EngineDefs.h"

template <typename T>
struct linkedlist_node_t {
	T data;
	linkedlist_node_t* prev;
	linkedlist_node_t* next;
};

template <typename T>
class liLinkedList {
private:
	linkedlist_node_t<T>* root;
public:
};

#endif