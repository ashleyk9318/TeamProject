// Team 6
// Neesha B, Daksha D, Viktoriia P, Jane S, Ashley K
// CIS 22C Fall 14

#ifndef _SCHOOL
#define _SCHOOL

#include <iostream>
#include <string>

using namespace std;

class School
{
	private:
		string code; //search key                 
		string name;      
		string city; 
		int apiScore;  

	public:
		// Constructors
		School() {code = ""; name = ""; city = ""; apiScore = 0;} 
		School(string CODE) {code = CODE;} 
		School(string CODE, string NAME, string CITY, int API) 
			{code = CODE; name = NAME; city = CITY; apiScore = API;}

		// Mutators
		string get_Code() const {return code;}
		string get_SchoolName() const  {return name;}
		string get_City() const  {return city;}
		int get_APIscore() const  {return apiScore;}

		bool operator == (const School& right) {return this->code == right.code;}
		bool operator != (const School& right) {return this->code != right.code;}
		friend ostream& operator << (ostream& os, const School& input);

        // Overloaded operators help compare within binary search tree
		bool operator < (const School& right){return this->code < right.code;}
		bool operator > (const School& right){return this->code > right.code;}
};

ostream& operator << (ostream& os, const School& input)
{
	// Might slightly change display format later
	os << input.code << ", " << input.name <<  ", " << input.city	
		<<  ", " << input.apiScore;
	return os;
}

class SchoolPtrContainer
{
    School* school;
public:
    SchoolPtrContainer() { school = 0; };
    SchoolPtrContainer(School* school)
    {
        this->school = school;
    }

    void freeMemory()
    {
        if (school)
        {
            delete school;
            school = 0;
        }
    }

    const School* getSchool() const { return school; };

    bool operator == (const SchoolPtrContainer& right) { return (*school) == (*(right.getSchool())); }
    bool operator != (const SchoolPtrContainer& right) { return (*school) != (*(right.getSchool())); }
     // Overloaded operators help compare within binary search tree
    bool operator < (const SchoolPtrContainer& right){ return (*school) < (*(right.getSchool())); }
	bool operator > (const SchoolPtrContainer& right){ return (*school) > (*(right.getSchool())); }

    friend ostream& operator << (ostream& os, const SchoolPtrContainer& input);
};

ostream& operator << (ostream& os, const SchoolPtrContainer& input)
{
	// Might slightly change display format later
	os << *(input.getSchool());
	return os;
}

#endif
