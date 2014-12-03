// Team 6
// Neesha B, Daksha D, Viktoriia P, Jane S, Ashley K
// CIS 22C Fall 14

#ifndef _NODE
#define _NODE

#include <iostream>

template <class ItemType>
class Node
{
	private:
		ItemType item;

	public:
		// Constructors
		Node() {next = NULL;} 
		Node(const ItemType& anItem) {item = anItem; next = NULL;}

		Node<ItemType>* next;

		void setItem(const ItemType& anItem) {item = anItem;}
		ItemType getItem() const {return item;}
};

#endif
