// Team 6
// Neesha B, Daksha D, Viktoriia P, Jane S, Ashley K
// CIS 22C Fall 14

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"
#include <queue>
static int level = 0;

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{   
private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);
   
	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);
   
	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);
   
	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);
   
	// prints the existing tree in indented form
	void _indentedTree(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const;


public:  
	// insert a node at the correct location
    bool insert(const ItemType & newEntry);
	// remove a node if found
	bool remove(const ItemType & anEntry);
	// public function indentedTree needed since rootPtr cannot be accessed by HW_4.cpp 
	void indentedTree(void visit(ItemType&)) const {_indentedTree(visit, rootPtr);}
};


///////////////////////// public function definitions ///////////////////////////

//**************************************************
// The insert function inserts newEntry as a node  *
// into the correct location.					   *
//**************************************************

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	rootPtr = _insert(rootPtr, newNodePtr);  
	count++;
	return true;
}  

//**************************************************
// The remove function deletes a node from the tree*
// if found.									   *
//**************************************************

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target)
{
	bool isSuccessful = false;
	rootPtr = _remove(rootPtr, target, isSuccessful);
	count--;
	return isSuccessful; 
}  

//////////////////////////// private functions ////////////////////////////////////////////

//**************************************************
// The _insert function internally inserts newNode *
// into the nodePtr subtree.					   *
//**************************************************

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr)
{
	if (nodePtr == 0)
		return newNodePtr;
	else if (nodePtr->getItem() > newNodePtr->getItem())
		nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr));
	else
		nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr));

	return nodePtr;
}  

//**************************************************
// The _remove function internally removes node by *
// locating and deleting the target node under	   *
// nodePtr subtree.								   *
//**************************************************

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
                                                          const ItemType target,
                                                          bool & success)

{
	if (nodePtr == 0)                   
	{
		success = false;
		return 0;
	}
	if (nodePtr->getItem() > target)		 
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (nodePtr->getItem() < target)	 
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else		
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}      
	return nodePtr;   
}  

//**************************************************
// The deleteNode function deletes target node from*
// the tree. It is called by the internal remove   *
// node.										   *
//**************************************************

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())				
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)  
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0) 
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;      
	}
	else                                  
	{
		ItemType newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}  
}  

//**************************************************
// The removeLeftmostNode function removes the	   *
// leftmost node in the left subtree of nodePtr.   *
//**************************************************

template<class ItemType> 
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else 
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}       
}

//**************************************************
// The _indentedTree function prints the tree in   *
// indented form by using recursion.			   *
//**************************************************

template<class ItemType>
void BinarySearchTree<ItemType>::_indentedTree(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const
{
	if(treePtr != 0)
	{
		level++;
		for(int i = 0; i < (level-1); i++)
			cout << "\t";
		 cout << level << ". ";

		 ItemType item = treePtr->getItem();
		 visit(item);

		_indentedTree(visit, treePtr->getLeftPtr());
        _indentedTree(visit, treePtr->getRightPtr());
        level--;
	}
}

#endif
