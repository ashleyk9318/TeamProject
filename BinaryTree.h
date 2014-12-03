// Team 6
// Neesha B, Daksha D, Viktoriia P, Jane S, Ashley K
// CIS 22C Fall 14

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
 	BinaryTree() {rootPtr = 0; count = 0;}
	BinaryTree(const BinaryTree<ItemType> & tree){rootPtr = copyTree(tree.rootPtr);}
	virtual ~BinaryTree() {destroyTree(rootPtr); rootPtr = 0; count = 0;} 
	BinaryTree & operator = (const BinaryTree & sourceTree);
   
	// common functions for all binary trees
 	bool isEmpty() const	{return count == 0;}
	int size() const	    {return count;}
	void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
	void inOrder(void visit(ItemType &)) const  {_inorder(visit, rootPtr);} //~*~*~*~ADDED*~*~*~*~*~//

	// abstract functions to be implemented by derived class
	virtual bool insert(const ItemType & newData) = 0; 
	virtual bool remove(const ItemType & data) = 0; 

private:   
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);
   
	// internal traverse
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const; //~*~*~*~ADDED*~*~*~*~*~//

}; 

//////////////////////////////////////////////////////////////////////////

//**************************************************
// The copyTree function copies the tree's nodes   *
// by preorder traversal, using nodePtr.           *
//**************************************************
template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr) 
{
	BinaryNode<ItemType>* newNodePtr = 0;
	
	// Copy tree nodes during a preorder traversal
	if (nodePtr != 0)
	{
		newNodePtr = new BinaryNode<ItemType>(nodePtr->getItem());
		newNodePtr->setLeftPtr(copyTree(nodePtr->getLeftPtr()));
		newNodePtr->setRightPtr(copyTree(nodePtr->getRightPtr()));
	} 
	// Else tree is empty (newNodePtr is 0)

    return newNodePtr;
}  

//**************************************************
// The destroyTree deletes the existing tree by    *
// using nodePtr to traverse the tree.             *
//**************************************************

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr != 0)
	{
		destroyTree(nodePtr->getLeftPtr());
		destroyTree(nodePtr->getRightPtr());
		delete nodePtr;
	}
}  

//**************************************************
// The _inorder function takes void visit and      *
// nodePtr from inOrder function, and traverses    *
// the tree in in-order using recursion.           *
//**************************************************

template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		_inorder(visit, nodePtr->getLeftPtr());
		ItemType item = nodePtr->getItem();
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}  //~*~*~*~ADDED ENTIRE FUNCTION*~*~*~*~*~//

//**************************************************
// The overloaded assignment function.	           *
//**************************************************

template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{
	if(this != &sourceTree)
	{
		this->clear();
        rootPtr=copyTree(sourceTree.rootPtr);
        count=sourceTree.count;
    }
    return *this;
}  

#endif

