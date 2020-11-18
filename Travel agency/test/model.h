#pragma once
#include <string>

using namespace std;

class Movie {
private:
	string title;
	string genre;
	int year;
	string actor;

public:

	/*
	Defaault constructor
	*/
	Movie() = default;
	/*
	Constructor
	*/
	Movie(const string& t, const string& g, const int& y, const string& a);
	/*
	Constructor de copiere
	*/
	Movie(const Movie& mv);
	
	/*
	Assignment operator =
	*/
	Movie& operator=(const Movie& mv);


	/*
	Equality operator == 
	*/
	bool operator==(const Movie& mv)  const{
		return (this->title == mv.title && this->genre == mv.genre && this->year == mv.year && this->actor == mv.actor);
	}

	string str() const;

	string get_title() const{
		return this->title;
	}

	string get_genre() const{
		return this->genre;
	}

	int get_year() const{
		return this->year;
	}

	string get_actor() const{
		return this->actor;
	}

	void set_title(string t) {
		this->title = t;
	}

	void set_genre( string g) {
		this->genre = g;
	}

	void set_year(int y) {
		this->year = y;
	}

	void set_actor(string a) {
		this->actor = a;
	}

};

/*
returns:
	0: equality 
	1: first bigger 
	-1: second bigger
*/
int cmp_title(const Movie& mv1, const Movie& mv2);

/*
returns:
	0: equality
	1: first bigger
	-1: second bigger
*/
int cmp_genre(const Movie& mv1, const Movie& mv2);

/*
returns:
	0: equality
	1: first bigger
	-1: second bigger
*/
int cmp_year(const Movie& mv1, const Movie& mv2);

/*
returns:
	0: equality
	1: first bigger
	-1: second bigger
*/
int cmp_actor(const Movie& mv1, const Movie& mv2);

void test_create_movie();
void test_cmp_functions();
