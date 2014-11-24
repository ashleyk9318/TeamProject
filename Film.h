#ifndef _FILM
#define _FILM

#include <iostream>
#include <string>

using namespace std;

class Film
{
	private:
		int year;
		string title;

	public:
		// Constructors
		Film() {year = 0; title = "";} 
		Film(string filmTitle) {title = filmTitle;} 
		Film(int filmYear, string filmTitle) {year = filmYear; title = filmTitle;} 

		// Mutators
		int getYear() {return year;}
		string getTitle() {return title;}

		bool operator == (const Film& right) {return this->title == right.title;}
		bool operator != (const Film& right) {return this->title != right.title;}
		friend ostream& operator << (ostream& os, const Film& input);
};

ostream& operator << (ostream& os, const Film& input)
{
	os << input.year << ", " << input.title;
	return os;
}

#endif
