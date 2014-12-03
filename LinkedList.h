// Team 6
// Neesha B, Daksha D, Viktoriia P, Jane S, Ashley K
// CIS 22C Fall 14

#ifndef _LINKED_LIST
#define _LINKED_LIST

#include "Node.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

template <class ItemType>
class LinkedList
{
	private:
		Node<ItemType>* head;
		int itemCount; // Count of items in list

	public:
		// Constructor
		LinkedList() {head = NULL; itemCount = 0;} 
		// Destructor
		~LinkedList() {clear();} 
		void clear();
		int getItemCount() {return itemCount;}
		bool insert(const ItemType& newEntry);
        bool remove(const ItemType& removedEntry);
		bool getEntry(const ItemType& target, ItemType& returnedEntry) const;
		bool getEntry(int index, ItemType& returnedEntry);
		void display() const;
		string indentedList() const;

};

//*******************************************************
// The insert function receives an item newEntry		*
// and inserts it into a node of the linked list.		*
// It returns true if the item is inserted successfully.*
//*******************************************************

template <class ItemType>
bool LinkedList<ItemType>::insert(const ItemType& newEntry)
{		
	Node<ItemType>* nodePtr;
	Node<ItemType>* newNode = new Node<ItemType>(newEntry); 
	newNode->next = NULL;

	if(!head) // if list is empty
	{
		head = newNode;
		itemCount++;
		return true;
	}
	else
	{
		nodePtr = head;
		while(nodePtr->next)
			nodePtr = nodePtr->next;
		nodePtr->next = newNode;
		itemCount++;
		return true;
	}
}

template <class ItemType>
bool LinkedList<ItemType>::remove(const ItemType& removedEntry)
{
    if (head->getItem() == removedEntry)
    {
        Node<ItemType>* deletePtr = head;
        head = head->next;
        delete deletePtr;
        itemCount--;
        return true;
    } else {
        Node<ItemType>* nodePtr = head;

	    // Traverses until it reaches end of list or finds target
	    while(nodePtr->next != 0 && nodePtr->next->getItem() != removedEntry)
		    nodePtr = nodePtr->next;

	    if(nodePtr->next != 0 )
	    {
		    Node<ItemType>* deletePtr = nodePtr->next;
            nodePtr->next = nodePtr->next->next;
            delete deletePtr;
            itemCount--;
            return true;
	    }
    }

    return false;
}

//*******************************************************
// The clear function removes all nodes from the list.	*
//*******************************************************

template <class ItemType>
void LinkedList<ItemType>::clear() 
{
	Node<ItemType>* deletePtr;

	for(int i = 0; i < itemCount; i++) 
	{
		deletePtr = head;			
		head = head->next;	
		delete deletePtr;				
	}
	itemCount = 0;
} 

//*******************************************************
// The getEntry function looks to see if there is an    *
// Item on the given index. The found item is returned  *
//*******************************************************

template<class ItemType>
bool LinkedList<ItemType>::getEntry(int index, ItemType& returnedEntry)
{
	//if (index < itemCount || index >= itemCount)
    if (index < 0 || index >= itemCount)
		return false;

	Node<ItemType>* current = head;

	for (int i = 0; i < index; i++)
		current = current->next;

	returnedEntry = current->getItem();
	return true;
}

//*******************************************************
// The getEntry function looks to see if a node matches *
// an item in one of the nodes of the linked list, and  *
// returns true if it is found.							*
//*******************************************************

template <class ItemType>
bool LinkedList<ItemType>::getEntry(const ItemType& target, ItemType& returnedEntry) const
{
	bool found = false;
	Node<ItemType>* nodePtr = head;

	// Traverses until it reaches end of list or finds target
	while(nodePtr != 0 && nodePtr->getItem() != target)
		nodePtr = nodePtr->next;

	if(nodePtr != 0 && nodePtr->getItem() == target)
	{
		returnedEntry = nodePtr->getItem();
		found = true;
	}
	
	return found;
}

//*******************************************************
// The display function traverses the linked list and   *
// displays each node's	contents						*
//*******************************************************
template <class ItemType>
void LinkedList<ItemType>::display() const
{
	Node<ItemType>* nodePtr = head;

	// While traversing, it displays each node's item
	while(nodePtr)
	{
		cout << nodePtr->getItem() << endl;
		nodePtr = nodePtr->next;
	}
}

//*******************************************************
// The indentedList function first checks the linked	*
// list to see if it is empty. If it is, it prints		*
// "// Empty". If it does contain nodes, the function	*
// prints the first node's content normally, and then   *
// indents the rest of the nodes.						*
//*******************************************************

template <class ItemType>
string LinkedList<ItemType>::indentedList() const
{
	Node<ItemType>* nodePtr = head;
	
	stringstream ss;

	if(nodePtr == 0)
	{
		ss << "// Empty" << endl;
	}
	else
	{
		ss << nodePtr->getItem() << endl;
		nodePtr = nodePtr->next;
		while(nodePtr)
		{
			ss << "\t\t" << nodePtr->getItem() << endl;
			nodePtr = nodePtr->next;
		}
	}

	return ss.str();
}

#endif
