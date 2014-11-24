// Team #6
// Jane Shin, Neesha Bhardwaj, Ashley Kim, Daksha Divakar, Viktoriia Petrusha
// Created by Viktoriia Petrusha

//***********************************************************************************************************
#include "hashTable.h"
template<typename ItemType>  // // template class name is a subject to change according to the class name in our program
//***********************************************************************************************************
// Constructor
//***********************************************************************************************************
HashedTable<ItemType>::HashTable(int hashSize, unsigned int hash(const ItemType &))
{
    // Dynamically allocate heap array
    h = hash;
	hashSize = size;
	hashedLists = new LinkedList<ItemType>[size]; // since we have to use linked list I change this constructor
}// End constructor

//***********************************************************************************************************
// Destructor
//***********************************************************************************************************
HashedTable<ItemType>::~HashTable()
{
    destroyHash();

}// End destructor

//***********************************************************************************************************
// Definition of destroyHash
//
// This function deletes all of the school pointers stored in the hash array.
//***********************************************************************************************************
HashedTable<ItemType>::destroyHash()
{
    string tempName = "";
    int tempNum;

    for (int i = 0; i < hashSize; i++)
    {
        // check if there are schools in table
        if (hashArrPtr[i].numSchools > 0)
        {
            // check if there is only one school
            if (hashArrPtr[i].numSchools == 1)
            {
                delete hashArrPtr[i].aSchool;
                hashArrPtr[i].aSchool = nullptr;
            }
            else
            {
                delete hashArrPtr[i].aSchool;
                hashArrPtr[i].aSchool = nullptr;

                hashArrPtr[i].numSchools--;

            }// End if

        }// End if

    }// End for

    delete [] hashArrPtr;

}// End destroyHash

//I'm not sure if this long destroy hash function(above) I made is needed or
//we can just use simple destructor like the one below

template<typename ItemType>
HashedTable<ItemType>::~HashedTable()
{
	delete[] hashArrPtr;
}

// Destroy BST function
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
