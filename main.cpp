// Team 6
// Neesha B, Daksha D, Viktoriia P, Jane S, Ashley K
// CIS 22C Fall 14

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

#include "School.h"
#include "HashedTable.h"
#include "BinarySearchTree.h"
#include "Stack.h"

void deleteSchool(SchoolPtrContainer& schoolPtr)
{
    schoolPtr.freeMemory();
}

void printSchool(SchoolPtrContainer& schoolPtr)
{
    cout << schoolPtr << endl;
}

void writeSchoolToFile(SchoolPtrContainer& schoolPtr, ofstream& os)
{
    os << schoolPtr.getSchool()->get_Code() << "\t";
    os << schoolPtr.getSchool()->get_SchoolName() << "\t";
    os << schoolPtr.getSchool()->get_City() << "\t";
    os << schoolPtr.getSchool()->get_APIscore() << endl;    
}

class SchoolDataStorage
{
    HashedTable* pHash;
    BinarySearchTree<SchoolPtrContainer>* pTree;
    Stack<SchoolPtrContainer>* pStack;

    void clearStack();
public:
    SchoolDataStorage();
    ~SchoolDataStorage();

    void readFromFile(const char* fileName);  
    void writeToFile(const char* fileName);

    void addNewData();
    void removeData();
    void findAndDisplay();
    void printHashedData();
    void printSortedData();    
    void printIntendedTree();    
    void printHashStatistic();
    void undoDelete();
};

SchoolDataStorage::SchoolDataStorage()
{
    pTree = new BinarySearchTree<SchoolPtrContainer>();
    pHash = new HashedTable(20);
    pStack = new Stack<SchoolPtrContainer>();
}

void SchoolDataStorage::clearStack()
{
    while(!pStack->isEmpty())
    {
        SchoolPtrContainer school;
        pStack->pop(school);
        deleteSchool(school);
    }
}

SchoolDataStorage::~SchoolDataStorage()
{
    delete pHash;

    clearStack();
    // remove school in SchoolPtrContainer objects
    pTree->inOrder(deleteSchool);    
    delete pTree;
    delete pStack;
}

// read file and build both tree and hash
void SchoolDataStorage::readFromFile(const char* fileName)
{
    //vector<SchoolPtrContainer> schools;
    ifstream inputfile(fileName);

    if (inputfile)
    {
        string code; //search key                 
		string name;      
		string city; 
		int apiScore;  

        while(!inputfile.eof())
        {
            inputfile >> code; //search key                 
            inputfile.ignore(1);
		    getline(inputfile, name);
		    getline(inputfile, city);
		    if (inputfile >> apiScore)
            {
                School* readSchool = new School(code, name, city, apiScore);
                //schools.push_back(SchoolPtrContainer(readSchool));
                pTree->insert(SchoolPtrContainer(readSchool));
                pHash->addToTable(SchoolPtrContainer(readSchool));
            }            
        }
        inputfile.close();
    }
}

void SchoolDataStorage::addNewData()
{
    string key;
    cout << "Enter code of new school: ";
    cin >> key;
    School findThis(key);
    SchoolPtrContainer foundSchool;
    
    if (pHash->findSchool(SchoolPtrContainer(&findThis), foundSchool))
    {
        cout << "This kay is already used. " << endl;
        cout << "  " << foundSchool << endl;
        cout << "Try to use another key" << endl;
    } else {                
	    string name;      
	    string city; 
	    int apiScore;  
    
        cin.ignore(1);
        cout << "Enter name of new school: ";
	    getline(cin, name);
        cout << "Enter city of new school: ";
	    getline(cin, city);
        cout << "Enter api score of new school: ";
	    cin >> apiScore;

        School* readSchool = new School(key, name, city, apiScore);        
        pTree->insert(SchoolPtrContainer(readSchool));
        pHash->addToTable(SchoolPtrContainer(readSchool));
    }
    cout << endl;
}

void SchoolDataStorage::findAndDisplay()
{
    string key;
    cout << "Enter key to remove: ";
    cin >> key;
    School findThis(key);
    SchoolPtrContainer foundSchool;
    
    if (pHash->findSchool(SchoolPtrContainer(&findThis), foundSchool))
    {
        cout << "Found " << endl;
        cout << "  " << foundSchool << endl;
    } else {
        cout << "Not Found" << endl;
    }
    cout << endl;
}

void SchoolDataStorage::removeData()
{
    string key;
    cout << "Enter key to find: ";
    cin >> key;
    School findThis(key);
    SchoolPtrContainer foundSchool;
    
    if (pHash->findSchool(SchoolPtrContainer(&findThis), foundSchool))
    {
        pStack->push(foundSchool);
        pTree->remove(foundSchool);
        pHash->removeSchool(foundSchool);
        cout << "Removed " << endl;        
    } else {
        cout << "Not Found" << endl;
    }
    cout << endl;
}

void SchoolDataStorage::printHashedData()
{
    cout << endl << "Hashed Data: " << endl;;
    pHash->printHashTable();
    cout << endl;
}

void SchoolDataStorage::printSortedData()
{
    cout << endl << "Sorted List: " << endl;;
    pTree->inOrder(printSchool);
    cout << endl;
}

void SchoolDataStorage::printIntendedTree()
{
    cout << endl << "Tree: " << endl;;
    pTree->indentedTree(printSchool);
    cout << endl;
}

void SchoolDataStorage::printHashStatistic()
{
    cout << endl << "Hash Statistic: " << endl;;
    cout << "Elements in Hash table : " << pHash->getTableSize() << endl;
    cout << "Load factor : " << pHash->calcLoadFactor() << endl;
    cout << "Collisions in Hash table : " << pHash->collisions() << endl;
    cout << "Linked Lists in Hash table : " << pHash->amountLinkedLists() << endl;    
    cout << "Average Size of Linked List in Hash table : " << pHash->avgNumNodes() << endl;   
    cout << "Longest Linked List in Hash table : " << endl;
    cout << "\t\t";
    pHash->longestLinkedList();
    cout << endl;
}

void SchoolDataStorage::writeToFile(const char* fileName)
{
    ofstream outputfile(fileName);
    if (outputfile)
    {        
        pHash->writeHashTable(outputfile, writeSchoolToFile);
        outputfile.close();
        cout << endl << "Saved into " << fileName << " file " << endl << endl;
        clearStack();
    } else {
        cout << endl << "Cannot save data" << endl << endl;
    }
}

void SchoolDataStorage::undoDelete()
{
    if (!pStack->isEmpty())
    {        
        SchoolPtrContainer school;
        pStack->pop(school);
        
        // add again...
        pTree->insert(school);
        pHash->addToTable(school);        
        cout << endl << "Restored" << endl;
        cout << "  " << school << endl << endl;

    } else {
        cout << endl << "There is no deleted school" << endl << endl;
    }
}

int main(void)
{
    SchoolDataStorage schools;
    schools.readFromFile("CA_schools.txt");

    char choice;
    do
    {
        cout << "Main Menu" << endl;
        cout << "(A). Add new data" << endl;
        cout << "(D). Delete data" << endl;
        cout << "(S). Search and display one element using the primary key" << endl;
        cout << "(H). List data in hash table sequence" << endl;
        cout << "(L). List data in key sequence (sorted)" << endl;
        cout << "(T). Print indented tree" << endl;
        cout << "(W). Write data to a file" << endl;
        cout << "(S). Hash statistics" << endl;
        cout << "(U). Undo Delete" << endl;
        cout << "(Q). Quit" << endl;
        cout << endl << "Your choice: ";
        cin >> choice;
        
        switch(toupper(choice))
        {
            case 1:
                schools.addNewData();
                break;
            case 2:
                schools.removeData();
                break;
            case 3:                
                schools.findAndDisplay();
                break;
            case 4:
                schools.printHashedData();
                break;
            case 5:
                schools.printSortedData();
                break;
            case 6:
                schools.printIntendedTree();
                break;
            case 7:
                schools.writeToFile("CA_schools_output.txt");
                break;
            case 8:
                schools.printHashStatistic();
                break;
            case 9:
                schools.undoDelete();
                break;
            case 0:
                // exit
                cout << endl << "Bye!" << endl;
                break;            
            default:
                cout << "Invalid option is chosen. Please, try again" << endl;
                break;            
        }
    }while(choice!='Q');

    return 0;
}
