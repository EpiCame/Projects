#pragma once

#include "model.h"
#include "validation.h"
#include "Repo.h"
#include "Cos_rent.h"
#include "Undo.h"
#include <memory>


int typedef (*CompareFunction) (const Movie& mv1, const Movie& mv2);

typedef void (*SortFunction)(vector<Movie>& movs, CompareFunction cmp);

class Movie_service {

private:
	Validator& val;
	Repository& repo;

	Movie_Basket mv_basket;

	vector<unique_ptr<undo_action>> undos;

public:
	Movie_service(Validator& val, Repo& repo) :val{ val }, repo{ repo }, mv_basket{ repo }{
	
	
	};

	/*
	params: strings : t, g ,a
			int : y
	post: validates and adds a movie to repository
	throws: valid errors, repo errors
	*/
	void add_movie(string t, string g, int y, string a);

	/*
	params: strings : t , g , a, new_t, new_g, new_a 
			int : y, new_y
	post: creates the movies, validate them, modify the existing one into the new one 
	*/
	void modify_movie(string t, string g, int y, string a, string new_t, string new_g, int new_y, string new_a);

	/*
	params: strings : t, g ,a
			int : y
	post: validates and deletes a movie from repository
	return: the deleted movie
	throws: valid errors, repo errors
	*/
	Movie delete_movie(string t, string g, int y, string a);

	/*
	*/
	void delete_by_title(string t);

	/*
	params: strings : t, g ,a
			int : y
	post: validates and searches a movie from repository
	throws: valid errors, repo errors
	*/
	Movie search_movie(string t, string g, int y, string a);


	/*
	returns all the movies
	*/
	vector<Movie> get_all();

	/*
	filter movies by a filter (title or price)
	*/
	vector<Movie> filter_movies(CompareFunction cmp, const string& word, const int y);

	/*
	prints the average year of movies
	*/

	float  average_year();

	/*
	sorts by a read criteria + genre
	*/
	vector<Movie> sort_movies( CompareFunction cmp);

	/*
	search a movie with title t in movies then adds it to the basket
	*/
	void add_movie_to_basket(string t);


	/*
	adds a random number of movies to the basket
	*/
	void add_random_to_basket(size_t number);


	/*
	empty the basket
	*/
	void empty_basket();

	/*
	returns the basket list of movies
	*/
	const vector<Movie>& get_all_basket();

	/*
	exports movies from basket to html file
	*/
	void export_basket_html(string f_name);

	/*
	exports movies from basket to cvs file
	*/
	void export_basket_cvs(string f_name);

	/*
	undo
	*/
	void undo();

	/*
	returns a refr to the basket 
	*/
	Movie_Basket& get_basket();

};

void SelectSort(vector<Movie>& movs, CompareFunction cmp);



void export_to_cvs(const string& file_name, const vector<Movie>& movs);


void export_to_HTML(const string& file_name, const vector<Movie>& movs);

void test_export();
void test_service();