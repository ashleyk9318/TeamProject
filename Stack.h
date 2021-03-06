// Team 6
// Neesha B, Daksha D, Viktoriia P, Jane S, Ashley K
// CIS 22C Fall 14

/**~*~*
   Stack template
*~**/
#ifndef DYNAMICSTACK_H
#define DYNAMICSTACK_H
#include <iostream>
#include "School.h"

using namespace std;

template <class ItemType>
class Stack
{
private:
   // Structure for the stack nodes
   struct StackNode
   {
      ItemType value;          // Value in the node
      StackNode *next;  // Pointer to next node
   };

   StackNode *top;     // Pointer to the stack top
   int count;

public:
   //Constructor
   Stack(){top = NULL; count = 0;}

   // Destructor
   ~Stack();

   // Stack operations
   bool push(ItemType);
   bool pop(ItemType &);
   bool isEmpty();
   int getCount();
   ItemType getTop();
};

/**~*~*
   Destructor
*~**/
template <class ItemType>
Stack<ItemType>::~Stack()
{
   StackNode *currNode, *nextNode;

   // Position nodePtr at the top of the stack.
   currNode = top;

   // Traverse the list deleting each node.
   while (currNode) //while (currNode != NULL)
   {
      nextNode = currNode->next;
      delete currNode;
      currNode = nextNode;
   }
}

/**~*~*
  Member function push pushes the argument onto
  the stack.
*~**/
template <class ItemType>
bool Stack<ItemType>::push(ItemType item)
{
   StackNode *newNode; // Pointer to a new node

   // Allocate a new node and store num there.
   newNode = new StackNode;
   if (!newNode)
       return false;
   newNode->value = item;

   // Update links and counter
   newNode->next = top;
   top = newNode;
   count++;

   return true;
}

/**~*~*
  Member function pop pops the value at the top
  of the stack off, and copies it into the variable
  passed as an argument.
*~**/
template <class ItemType>
bool Stack<ItemType>::pop(ItemType &item)
{
   StackNode *temp; // Temporary pointer

   // empty stack
   if (count == 0)
       return false;

   // pop value off top of stack
   item = top->value;
   temp = top->next;
   delete top;
   top = temp;
   count--;

   return true;
}

/**~*~*
  Member function isEmpty returns true if the stack
  is empty, or false otherwise.
*~**/
template <class ItemType>
bool Stack<ItemType>::isEmpty()
{
   return count == 0;
}

//==================================================
// getCount member function returns the number of
// elements currently in the stack that is stored
// in member variable count
//==================================================
template<class ItemType>
int Stack<ItemType>::getCount()
{
    return count;
}

//==================================================
// getTop function returns the top value of the
// stack as long as there are greater than zero
// element in the stack
//==================================================
template<class ItemType>
ItemType Stack<ItemType>::getTop()
{
    //empty stack
    if(count == 0)
        return false;

    return top->value;//return value of the top node
}
#endif
