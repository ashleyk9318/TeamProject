// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by:

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
using namespace std;


template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
 	BinaryTree() {rootPtr = 0; count = 0;}
    BinaryTree(const BinaryTree<ItemType> & tree){}
	virtual ~BinaryTree() { }
	BinaryTree & operator = (const BinaryTree & sourceTree);

	// common functions for all binary trees
 	bool isEmpty() const	{return count == 0;}
	int size() const	    {return count;}
    BinaryNode<ItemType>* root() const {return rootPtr;}
	void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
	void preOrder(void visit(ItemType &)) const {_preorder(visit, rootPtr);}
	void inOrder(void visit(ItemType &)) const  {_inorder(visit, rootPtr);}
	void postOrder(void visit(ItemType &)) const{_postorder(visit, rootPtr);}
    void printIndented() const { _printIndented(rootPtr, 0);}
    void printGreater(const ItemType & target) const {_printGreater(rootPtr, target);}
    void breadthTraversal() const {_breadthTraversal(rootPtr);}

	// abstract functions to be implemented by derived class
	virtual bool insert(const ItemType & newData) = 0;
	virtual bool remove(const ItemType & data) = 0;
	virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem) const = 0;

private:
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
    void _printIndented(BinaryNode<ItemType>* nodePtr, int tabs) const;
    void _printGreater(BinaryNode<ItemType>* nodePtr, const ItemType & target) const;
    void _breadthTraversal(BinaryNode<ItemType>* nodePtr) const;

};

//////////////////////////////////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr)
{
    if (nodePtr != 0) { //if not equal to 0
        insert(nodePtr->getItem()); //putting the item into the tree
        copyTree(nodePtr->getLeftPtr());
        copyTree(nodePtr->getRightPtr());
    }
    return rootPtr;
}

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
    if (nodePtr != 0) { //checking node pointer is not equal to 0
        destroyTree(nodePtr->getLeftPtr());
        destroyTree(nodePtr->getRightPtr());
        delete nodePtr;
    }
}

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item); //printing out the tree in the needed order
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	}
}

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

}

template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
    {
        _postorder(visit, nodePtr->getLeftPtr());
        _postorder(visit, nodePtr->getRightPtr());
        ItemType item = nodePtr->getItem();
        visit(item);
    }

}

template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{
    clear();
    copyTree(sourceTree.root());
    return *this;

}

template<class ItemType>
void BinaryTree<ItemType>::_printIndented(BinaryNode<ItemType>* nodePtr, int tabs) const {
    if (nodePtr != 0) {

        for (int i = 0; i < tabs; i++) {
            cout << "\t";
        }
        cout << tabs + 1 << ". ";
        cout << nodePtr->getItem() << "\n";
        _printIndented(nodePtr->getRightPtr(), tabs + 1); //printing out the requested number
        _printIndented(nodePtr->getLeftPtr(), tabs + 1);
    }
}

template<class ItemType>
void BinaryTree<ItemType>::_printGreater(BinaryNode<ItemType>* nodePtr, const ItemType &target) const {

	if (nodePtr != 0) {
		//getting the item
        if (nodePtr->getItem().substr(0,4) > target) {
            cout << nodePtr->getItem() << " \n";
        }
        _printGreater(nodePtr->getLeftPtr(), target);
        _printGreater(nodePtr->getRightPtr(), target);
    }

}

template<class ItemType>
void BinaryTree<ItemType>::_breadthTraversal(BinaryNode<ItemType> *nodePtr) const {
    int length = 1;
    int counter = 0; //variables to keep track of the counters

    void *arr[20];
    arr[0] = nodePtr;

    while (counter < length) {

        BinaryNode<ItemType> *node = static_cast<BinaryNode<ItemType> *>(arr[counter]);
        std::cout << node->getItem() << "\n";

        //checking if the left pointer is equal to null or not
        if (node->getLeftPtr() != 0) {
            arr[length] = node->getLeftPtr();
            length++;
        }

        //checking the right pointer, if its null
        if (node->getRightPtr() != 0) {
            arr[length] = node->getRightPtr();
            length++;
        }
        counter++; //increment
    }
}


#endif

