// Team #6
// Jane Shin, Neesha Bhardwaj, Ashley Kim, Daksha Divakar, Viktoriia Petrusha
// Created by Viktoriia Petrusha

//I created .h file with functions that count number of lines in file
//and based on number of lines calculate the hash size using the formula that our professor provided
//We might need to move this functions to the main file

#ifndef HashSize_h
#define HashSize_h
#define FILE_NAME "inputFile.txt" // need to change to our file name
#include <iostream>
#include <string>
//#include "SchoolDatabase.h" // not sure if needed

using namespace std;

class DataFile {
private:
    int lineCount;

public:

    DataFile() {numSchool = 0;} // numSchool is the number of lines in a file
    bool readData();
    bool numPrime (int);
    int hashSize();

bool DataFile::readData()
{
    ifstream inFile (FILE_NAME); // file name defined
    string item;
    if (!inFile){
            cout << "File not found.\n" ;
    return 0;
    }

    while (getline(inFile , item))
    {
        lineCount++;
    }

}

//****************
// Calculate hash size
//****************
int DataFile::hashSize(int numSchool)
{
    int hashSize = numSchool * 2;
    for (hashSize+1; !numPrime(hashSize) ; hashSize++ ) {}

    return hashSize;
}


//****************
// Checks if a number is prime
//****************
bool DataFile::numPrime (int num)
{
    if (num <= 1)
        return false;

    else if (num == 2)
        return true;

    else if (num % 2 == 0)
        return false;


    else
    {
        for (int i = 3; i < sqrt(num); i++)
            if (num % i == 0)
                return false;

        return true;
    }
  }
};

#endif

