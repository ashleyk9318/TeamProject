// HashedTable header file
// Jae Eun (Jane) Shin

#ifndef _HASHED_TABLE
#define _HASHED_TABLE

#define HASHTABLESIZE 31 // Required to run program once each with 10 and 31

#include "LinkedList.h"
#include "Film.h"
#include <cmath>
#include <string>

class HashedTable
{
	private:
		LinkedList<Film>* hashTable;
		int getHashIndex(string input);		
	
	public:
		// Constructor, with dynamically allocated hash table
		HashedTable() {hashTable = new LinkedList<Film>[HASHTABLESIZE];}
		// Destructor
		~HashedTable();
		void addToTable(Film& movie); 
		bool findFilm(Film& search, Film& returnFilm);
		void displayList();
		void printHashTable();

		// The statistics functions
		double calcLoadFactor();
		int collisions();
		int amountLinkedLists();
		void longestLinkedList();
		double avgNumNodes();	

};

//*******************************************************
// Destructor											*
//*******************************************************

HashedTable::~HashedTable()
{
	for (int i = 0 ; i < HASHTABLESIZE; i++)
		hashTable[i].clear();  
}

//*******************************************************
// The getHashIndex generates and returns a hash index	*
// for an item based on the key. This specific function	*
// cubes the ASCII value of each character, and then	*
// sums them. Then the function takes the modulus using *
// the defined hash table size, and returns the index.  *
//*******************************************************

int HashedTable::getHashIndex(string input)
{
	int index = 0;
	int cube;

	for (size_t i = 0; i < input.length(); i++)
	{
		cube = static_cast<int>(pow(input[i], 3.0)); 
		index += cube;
	}
	
	if (index >= HASHTABLESIZE)
		index = index % HASHTABLESIZE;

	return index;
}

//*******************************************************
// The addToTable function uses the getHashIndex		*
// function to find which index to add into, and then	*
// calls the insert function from LinkedList.h to insert*
// into linked list.									*
//*******************************************************

void HashedTable::addToTable(Film& movie)
{
	int index;	
	index = getHashIndex(movie.getTitle());
	hashTable[index].insert(movie);
}

//*******************************************************
// The findFilm function calls getEntry function from	*
// LinkedList.h to see if item exists, and then returns *
// the item.											*
//*******************************************************

bool HashedTable::findFilm(Film& search, Film& returnFilm)
{
	return hashTable[getHashIndex(search.getTitle())].getEntry(search, returnFilm);
}

//*******************************************************
// The displayList function displays all of the items   *
// in the list, in the index order and including the	*
// collisions.											*
//*******************************************************

void HashedTable::displayList()
{
	for(int i = 0; i < HASHTABLESIZE; i++)
		hashTable[i].display();
}

//*******************************************************
// The printHashTable function prints all of the items  *
// in the hash table, including the word empty if the	*
// index is empty.										*
//*******************************************************

void HashedTable::printHashTable()
{
	for(int i = 0; i < HASHTABLESIZE; i++)
	{
		cout << "Index " << i << ": ";
		hashTable[i].indentedList();
		cout << endl;
	}
}

//*******************************************************
// The calcLoadFactor function returns the load factor  *
// of the hash table.									*
//*******************************************************

double HashedTable::calcLoadFactor()
{
	int counter = 0;
	double loadFactor;
	for(int i = 0; i < HASHTABLESIZE; i++)
	{
		if(hashTable[i].getItemCount() > 0)
			counter++;
	}
	loadFactor = static_cast<double>(counter) / HASHTABLESIZE * 100;
	return loadFactor;
}

//*******************************************************
// The numCollisions function returns the number of		*
// collisions the hash table experienced while adding	*
// in the the items.									*
//*******************************************************

int HashedTable::collisions()
{
	int numCollisions = 0;
	for(int i = 0; i < HASHTABLESIZE; i++)
	{
		if(hashTable[i].getItemCount() > 0)
			numCollisions += hashTable[i].getItemCount() - 1;
	}
	return numCollisions;
}

//*******************************************************
// The longestLinkedList function prints the linked		*
// lists with the largest amount of nodes.				*
//*******************************************************

void HashedTable::longestLinkedList()
{
	int longest = 0;
	
	for(int i = 0; i < HASHTABLESIZE; i++)
	{
		if(hashTable[i].getItemCount() > longest)
			longest = hashTable[i].getItemCount();
	}
	for(int i = 0; i < HASHTABLESIZE; i++)
	{
		if(hashTable[i].getItemCount() == longest)
		{
			hashTable[i].indentedList();
			cout << endl;
		}
	}
}

//*******************************************************
// The numLinkedLists function returns the number of	*
// linked lists that experienced collisions.			*
//*******************************************************

int HashedTable::amountLinkedLists()
{
	int numLinkedLists = 0;
	
	for(int i = 0; i < HASHTABLESIZE; i++)
	{
		if(hashTable[i].getItemCount() > 1)
			numLinkedLists++;
	}
	return numLinkedLists;
}

//*******************************************************
// The avgNumNodes function returns the average number	*
// of nodes stored in linked lists.						*
//*******************************************************
double HashedTable::avgNumNodes()
{
	return (static_cast<double>(collisions())) / amountLinkedLists();
}

#endif
