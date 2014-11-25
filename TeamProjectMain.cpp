/*************************************************************

Team Project

Jane Shin, Neesha Bhardwaj, Ashley Kim, Daksha Divakar, Viktoriia Petrusha
Group Number 6? or 11?

**************************************************************/

#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<string>
#include<fstream>
#include <stdio.h>
#include <cstring>
#include <sstream>
#include "SchoolDatabase.h"


using namespace std;

//function protypes

void display_menu();
void build_SchoolDataBase(SchoolDatabase<string> *);/// still incomplete and may need parameters
/// seperate function to write to output file

int main()
{
    SchoolDatabase<string> *schoolList = new SchoolDatabase<string>(); //can rename object later
    int command;

                    cout<<"REMOVE PROCESS INPUT FILE CALL AT TOP OF MAIN LATER!!!!"<<endl;
                    build_SchoolDataBase(schoolList);//temp

    do
    {
        //call display_menu
        display_menu();

        cout<<"\nenter command: ";
        cin>>command;

        //input validation
        while(!(command >= 1 && command <= 10))//while user enters command NOT in range from 1 to 9
        {
            cout<<"\ninvalid command. please enter valid command: ";
            cin>>command;
        }

        switch(command)
        {
            case 1:     //add new data
                break;

            case 2:     //delete data
                break;

            case 3:     //Find and display one element using the primary key
                break;

            case 4:     //List data in hash table sequence
                break;

            case 5:     //List data in key sequence (sorted),
                break;

            case 6:      //Print indented tree
                break;

            case 7:       //Write data to a file
                break;

            case 8:       //hash stats
                break;

            case 9:       //undo delete
                break;
        }//end switch

    }while(command != 10);//end do while


    //save everything to file at end of program

    return 0;
}//end main



///******************************************************
///display_menu()
///this function displays menu of commands
///******************************************************
void display_menu()
{
    //display menu
    cout<<"\n***~***~***~***~***~*** m e n u ***~***~***~***~***~***\n";
    cout<<"(1) - add new data\n";
    cout<<"(2) - delete data\n";
    cout<<"(3) - search and display element by key\n";
    cout<<"(4) - list data in hash table sequence\n";
    cout<<"(5) - list data in key sequence(sorted)\n";
    cout<<"(6) - print indented tree\n";
    cout<<"(7) - write data to file\n";
    cout<<"(8) - hash statistics\n";
    cout<<"(9) - undo delete\n";
    cout<<"(10) - quit\n";
    cout<<  "***~***~***~***~***~***~***~***~***~***~***~***~***~***\n";
}//end display_menu()




///******************************************************
///process_input_file()
/// -add description later-----------
///******************************************************
void build_SchoolDataBase(SchoolDatabase<string> *Sptr)
{
    ifstream infile;
    infile.open("CA_schools.txt");
    string fileData;

    if(!infile)//if file does not open successfully
    {
        cout<<"\nerror opening file!\n";
        return;
    }


        string code;
        string schoolName;
        string cityName;
        string apiScore_string;
        int apiScore_int;


    while(getline(infile, code))
    {
        getline(infile, schoolName);
        getline(infile, cityName);
        getline(infile, apiScore_string);
        apiScore_int = atoi(apiScore_string.c_str());

        cout<<"code:"<<code<<endl;
        cout<<"schoolName:"<<schoolName<<endl;
        cout<<"cityName:"<<cityName<<endl;
        cout<<"apiScore:"<<apiScore_int<<endl;

        Sptr->insert(code, schoolName, cityName, apiScore_int);

    }

    infile.close();
}

