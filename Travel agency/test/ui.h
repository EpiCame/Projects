#pragma once
#include "model.h"
#include "service.h"
#include "validation.h"


void test_all();

class Console {

private:

	Movie_service& srv;

public:

	Console(Movie_service& srv) :srv{ srv } {};

	/*
	reads a movie and adds it
	*/
	void add_movie();

	/*
	reads 2 movies and movdifies the first with the second
	*/
	void modify_movie();

	/*
	reads and deletes a movie
	*/
	void delete_movie();

	/*
	reads and search a movie 
	*/
	void search_movie();

	/*
	prints all the movies 
	*/
	void print_movies();

	/*
	filter the movies by title or year
	*/
	void filter_movies();

	/*
	sort the movies by tilte, actor or year +genre
	*/
	void sort_movies();

	/*
	reads a title and adds a movie to the basket
	*/
	void add_one_movie();

	/*
	reads an number of movies then adds random movies from the repository
	*/
	void add_random_movies();

	/*
	empty the basket
	*/
	void empty_basket();

	/*
	prints all the movies from the basket
	*/
	void print_basket();

	/*
	exports movie from the basket in cvs file
	*/
	void export_basket_cvs();

	/*
	exports movie from the basket in html file
	*/
	void export_basket_HTML();

	void avg_year();

	void undo_movies();

	void run();

};

