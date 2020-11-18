#include "model.h"
#include <assert.h>
#include <iostream>
/*
Constructor
*/
Movie::Movie(const string& t, const string& g, const int& y, const string& a) :title{ t }, genre{ g }, year{ y }, actor{ a }{
}

/*
Constructor de copiere
*/
Movie::Movie(const Movie& mv) :title{ mv.title }, genre{ mv.genre }, year{ mv.year }, actor{ mv.actor } {
	
}

string Movie::str() const {
	string s = { "" };
	s.append(this->title);
	s.append(", ");
	s.append(this->genre);
	s.append(", ");
	s.append(to_string(this->year));
	s.append(", ");
	s.append(this->actor);
	return s;
}



/*
	Assignment operator =
	*/
Movie& Movie::operator=(const Movie& mv) {
	if (this == &mv)
		return *this;
	this->title = mv.title;
	this->genre = mv.genre;
	this->year = mv.year;
	this->actor = mv.actor;
	return *this;
}

void test_create_movie() {
	Movie mv = Movie("Inception", "action", 2010, "DiCaprio");
	assert(mv.get_title() == "Inception");
	assert(mv.get_genre() == "action");
	assert(mv.get_year() == 2010);
	assert(mv.get_actor() == "DiCaprio");
	mv.set_title("Titanic");
	mv.set_genre("romance");
	mv.set_year(1997);
	assert(mv.get_title() == "Titanic");
	assert(mv.get_genre() == "romance");
	assert(mv.get_year() == 1997);
	Movie cpy_mv = Movie("Titanic", "romance", 1997, "DiCaprio");
	assert(cpy_mv == mv);
	string s;
	s = mv.str();
	assert(s == "Titanic, romance, 1997, DiCaprio");

}

/*
returns:
	0: equality
	1: first lower
	-1: second lower
*/
int cmp_title(const Movie& mv1,  const Movie& mv2) {
	string t1 = mv1.get_title();
	for (int i = 0; i < mv1.get_title().size(); i++)
		t1[i] = tolower(t1[i]);
	string t2 = mv2.get_title();
	for (int i = 0; i < mv2.get_title().size(); i++)
		t2[i] = tolower(t2[i]);
	if (t1 == t2) return 0;
	if (t1 < t2) return 1;
	if (t1 > t2) return -1;
}

/*
returns:
	0: equality
	1: first lower
	-1: second lower
*/
int cmp_genre(const Movie& mv1, const Movie& mv2) {
	string t1 = mv1.get_genre();
	for (int i = 0; i < mv1.get_genre().size(); i++)
		t1[i] = tolower(t1[i]);
	string t2 = mv2.get_genre();
	for (int i = 0; i < mv2.get_genre().size(); i++)
		t2[i] = tolower(t2[i]);
	if (t1 == t2) return 0;
	if (t1 < t2) return 1;
	if (t1 > t2) return -1;
}

/*
returns:
	0: equality
	1: first lower
	-1: second lower
*/
int cmp_year(const Movie& mv1, const Movie& mv2) {
	if (mv1.get_year() == mv2.get_year()) return 0;
	if (mv1.get_year() < mv2.get_year()) return 1;
	if (mv1.get_year() > mv2.get_year()) return -1;
}

/*
returns:
	0: equality
	1: first lower
	-1: second lower
*/
int cmp_actor(const Movie& mv1, const Movie& mv2) {
	string t1 = mv1.get_actor();
	for (int i = 0; i < mv1.get_actor().size(); i++)
		t1[i] = tolower(t1[i]);
	string t2 = mv2.get_actor();
	for (int i = 0; i < mv2.get_actor().size(); i++)
		t2[i] = tolower(t2[i]);
	if (t1 == t2) return 0;
	if (t1 < t2) return 1;
	if (t1 > t2) return -1;
}


void test_cmp_functions() {
	Movie mv{ "Inception", "reaction", 2010, "dicaprio" };
	Movie cpy_mv{ "Inception", "reaction", 2010, "dicaprio" };
	assert(cmp_title(mv, cpy_mv) == 0);
	assert(cmp_genre(mv, cpy_mv) == 0);
	assert(cmp_year(mv, cpy_mv) == 0);
	assert(cmp_actor(mv, cpy_mv) == 0);
	Movie gt_mv{ "a", "a", 2000, "a" };
	assert(cmp_title(gt_mv, mv) == 1);
	assert(cmp_genre(gt_mv, mv) == 1);
	assert(cmp_year(gt_mv, mv) == 1);
	assert(cmp_actor(gt_mv, mv) == 1);
	Movie lt_mv{ "z", "z", 2019, "z" };
	assert(cmp_title(lt_mv, mv) == -1);
	assert(cmp_genre(lt_mv, mv) == -1);
	assert(cmp_year(lt_mv, mv) == -1);
	assert(cmp_actor(lt_mv, mv) == -1);
}
