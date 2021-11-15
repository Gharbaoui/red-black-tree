#ifndef MAIN_HPP
#define MAIN_HPP
#include <iostream>
#include <memory>
#include <vector>

template <typename T>
struct node{
	node(T i) : item(i), color(true), left(nullptr), right(nullptr){}
	T		item;
	bool	color; // false =>black true =>red
	node	*left;
	node	*right;
	node	*parent;
};

#endif
