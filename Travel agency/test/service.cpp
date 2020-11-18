#include "service.h"
#include <iostream>
#include <numeric>
#include <fstream>



/*
Sorts a vector of movies with cmp function
*/
void SelectSort(vector<Movie>& movs, CompareFunction cmp) {

	//sorteaza dupa criteriul citit
	for(int i = 0 ;i<int(movs.size())-1;i++)
		for(int j=i+1;j<int(movs.size());j++)
			if (cmp(movs[i], movs[j]) == -1) {
				Movie aux = movs[i];
				movs[i] = movs[j];
				movs[j] = aux;
			}
	//sorteaza dupa gen
	for (int i = 0; i < int(movs.size()) - 1; i++)
		for (int j = i+1; j < int(movs.size()); j++)
			if (cmp(movs[i], movs[j]) == 0 && cmp_genre(movs[i], movs[j]) == -1) {
				Movie aux = movs[i];
				movs[i] = movs[j];
				movs[j] = aux;
			}
}

/*
params: strings : t, g , y ,a
post: validates and adds a movie to repository 
throws: valid errors, repo errors
*/
void Movie_service::add_movie(string t, string g, int y, string a) {
	Movie mv{ t, g, y, a };
	const int err = val.validate_movie(mv);
	if (err == 0)
		repo.add(mv);
	undos.push_back(make_unique<undo_add>(repo, mv));
}

/*
params: strings : t , g , a, new_t, new_g, new_a
		int : y, new_y
post: creates the movies, validate them, modify the existing one into the new one
*/
void Movie_service::modify_movie(string t, string g, int y, string a, string new_t, string new_g, int new_y, string new_a) {

	Movie mv{ t,g,y,a };
	Movie new_mv{ new_t, new_g, new_y, new_a };
	if (!val.validate_movie(mv) && !val.validate_movie(new_mv))
		repo.modify(mv, new_mv);
	undos.push_back(make_unique<undo_modify>(repo, mv, new_mv));
}


/*
params: strings : t, g ,a
		int : y
post: validates and deletes a movie from repository
throws: valid errors, repo errors
*/
Movie Movie_service::delete_movie(string t, string g, int y, string a) {

	Movie mv{ t,g, y,a };
	if (!val.validate_movie(mv))
			repo.erase(mv);
	undos.push_back(make_unique<undo_erase>(repo, mv));
	return mv; 
}

void Movie_service::undo() {
	if (undos.empty()) {
		throw RepoException{"There are 0 operation left!\n"};
	}
	undos.back()->make_undo();
	undos.pop_back();
}

/*
returns all movies
*/
vector<Movie> Movie_service::get_all() {
	return repo.get_all();
}

/*
params: strings : t, g ,a
		int : y
post: validates and searches a movie from repository
throws: valid errors, repo errors
*/
Movie Movie_service::search_movie(string t, string g, int y, string a) {
	
	Movie mv{ t,g,y,a };
	if (!val.validate_movie(mv))
		return repo.search(mv);	
	throw std::exception();
}

/*
	prints the average year of movies
*/
float Movie_service::average_year() {
	auto movs = repo.get_all();
	vector<int> years; 
	for (const auto& mv : movs)
		years.push_back(mv.get_year());
	int sum = accumulate(years.begin(), years.end(), 0); 
	return sum/movs.size();
}

/*
filter movies by a filter (title or price)
*/
vector<Movie> Movie_service::filter_movies(CompareFunction cmp, const string& word, const int y) {
	// folosim copy_if ... 
	vector<Movie> movs;
	Movie mv{ word,word,y,word };
	auto all = repo.get_all(); 
	copy_if(all.begin(), all.end(), back_inserter(movs), [&mv, cmp](const Movie& m) {return (cmp(mv, m) == 0); });
	return movs;
}
/*

*/
void Movie_service::delete_by_title(string t) {
	vector<Movie> movs = repo.get_all();
	Movie mv2;
	for (const auto& mv : movs) {
		if (mv.get_title() == t)
		{
			mv2 = mv;
			break;
		}
	}
	repo.erase(mv2);
	undos.push_back(make_unique<undo_erase>(repo, mv2));
}

/*
	sorts by a read criteria + genre
*/
vector<Movie> Movie_service::sort_movies(CompareFunction cmp) {
	vector<Movie> movs = repo.get_all();
	sort(movs.begin(), movs.end(), [cmp](const Movie& mv1, const Movie& mv2) {return (cmp(mv1, mv2) == 1); });
	return movs;
}


/*
	search a movie with title t in movies then adds it to the basket
*/
void Movie_service::add_movie_to_basket(string t) {

	vector<Movie> movs = filter_movies(cmp_title, t, 2000);
	if (movs.size() == 0)
		throw BasketException("There is no movie with that title!\n");
	if (movs.size() == 1)
		mv_basket.add_to_basket(movs[0]);
}


void Movie_service::add_random_to_basket(size_t number) {
	if (number > repo.get_all().size())
		number = repo.get_all().size();
	if(number <= 0)
		throw BasketException("Invalid number!\n");
	mv_basket.add_random(number);
}


void Movie_service::empty_basket() {
	mv_basket.empty_basket();
}

const vector<Movie>& Movie_service::get_all_basket() {
	return mv_basket.basket_list();
}

void export_to_cvs(const string& file_name, const vector<Movie>& movs) {
	ofstream fout(file_name, ios::trunc);
	if (!fout.is_open()) {
		throw RepoException("Unable to open file:" + file_name);
	}
	for (const auto& mv : movs) {
		fout << mv.get_title() << ",";
		fout << mv.get_genre() << ",";
		fout << mv.get_year() << ",";
		fout << mv.get_actor() << endl;
	}
	fout.close();
}

void export_to_HTML(const string& file_name, const vector<Movie>& movs) {
	ofstream fout(file_name, ios::trunc);
	if (!fout.is_open()) {
		throw RepoException("Unable to open file:" + file_name);
	}
	fout << "<html><body>" << endl;
	fout << "<table border=\"1\" style=\"width:100 % \">" << endl;
	for (const auto& mv : movs) {
		fout << "<tr>" << endl;
		fout << "<td>" << mv.get_title() << "</td>" << endl;
		fout << "<td>" << mv.get_genre() << "</td>" << endl;
		fout << "<td>" << mv.get_year() << "</td>" << endl;
		fout << "<td>" << mv.get_actor() << "</td>" << endl;
		fout << "</tr>" << endl;
	}
	fout << "</table>" << endl;
	fout << "</body></html>" << endl;
	fout.close();
}

Movie_Basket& Movie_service::get_basket() {
	return mv_basket;
}


void Movie_service::export_basket_html(string f_name) {
	export_to_HTML(f_name, get_all_basket());
}

void Movie_service::export_basket_cvs(string f_name) {
	export_to_cvs(f_name, get_all_basket());
}


void test_export() {
	Repo repo;
	Validator val;
	Movie_service srv{ val, repo };
	srv.add_movie("t1", "t1", 2000, "t1");
	srv.add_movie("t2", "t2", 2001, "t2");
	srv.add_movie("t3", "t3", 2002, "t3");
	srv.add_random_to_basket(3);
	srv.export_basket_cvs("test_export.cvs");
	ifstream fin("test_export.cvs");
	assert(fin.is_open());
	int count_lines = 0;
	while (!fin.eof()) {
		string line;
		fin >> line;
		count_lines++;
	}
	fin.close();
	assert(count_lines == 4);
	srv.export_basket_html("test_export.html");
	fin.open("test_export.html");
	assert(fin.is_open());

	
	try {
		srv.export_basket_cvs("test/Export.cvs");
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
	try {
		srv.export_basket_html("a/b/c/Export.html");
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
}

void test_service() {
	Validator val;
	Repo repo; 
	Movie_service srv(val, repo);
	srv.add_movie("Inception", "action", 2010, "DiCaprio");
	srv.undo();
	assert(srv.get_all().size() == 0);
	srv.add_movie("Inception", "action", 2010, "DiCaprio");
	try {
		srv.add_movie("", "", 2016, "ram");
		assert(false);}
	catch (ValidException& ) {
		assert(true);
	}
	try {
		srv.add_movie("Inception", "action", 2010, "DiCaprio");
		assert(false);}
	catch (const RepoException& ) {
		assert(true);
	}
	//modify
	try {
		srv.modify_movie("Inception", "action", 2010, "DiCaprio", "", "", 1901, "fasf");
		assert(false);}
	catch (const ValidException& ) {
		assert(true);
	}
	try {
		srv.modify_movie("Inception", "action", 2010, "Tom Hanks", "test", "test", 1901, "test");
		assert(false);}
	catch (RepoException& ) {
		assert(true);
	}
	srv.modify_movie("Inception", "action", 2010, "DiCaprio", "The Great Gatsby", "drama", 2014, "DiCaprio");
	//search 
	try {
		srv.search_movie("Inception", "action", 2010, "Tom Hanks");
		assert(false);}
	catch (const RepoException& e) {
		assert(true);
	}
	Movie mv = srv.search_movie("The Great Gatsby", "drama", 2014, "DiCaprio"); 
	assert(mv.str() == "The Great Gatsby, drama, 2014, DiCaprio");
	//delete        
	try {
		srv.delete_movie("Inception", "action", 2010, "Tom Hanks");
		assert(false);}
	catch (const RepoException& e) {
		assert(true);
	}
	assert(srv.delete_movie("The Great Gatsby", "drama", 2014, "DiCaprio").str() == "The Great Gatsby, drama, 2014, DiCaprio");
	//get_all 
	vector<Movie> movs = srv.get_all();
	assert(movs.size() == 0);
	srv.add_movie("The Great Gatsby", "drama", 2014, "DiCaprio");
	movs = srv.get_all();
	assert(movs.size() == 1);
	movs = srv.filter_movies(cmp_title, "The Great Gatsby", 0); 
	assert(movs.size() == 1);
	movs = srv.filter_movies(cmp_year, "", 2014);
	assert(movs.size() == 1);
	//test sort
	srv.add_movie("Inception", "action", 2014, "DiCaprio");
	movs = srv.sort_movies(cmp_title);
	assert(movs[0].get_title() == "Inception");
	srv.add_movie("Anception", "action", 2014, "DiCaprio");
	movs = srv.sort_movies(cmp_title);
	assert(movs[0].get_title() == "Anception");
	
	////test movie basket

	movs = srv.get_all_basket();
	assert(movs.size() == 0);
	srv.add_movie_to_basket("Inception");
	movs = srv.get_all_basket();
	assert(movs.size() == 1);
	try {
		srv.add_movie_to_basket("Assassin's Creed");
		assert(false);
	}
	catch (BasketException& e) {
		assert(e.get_msg() == "There is no movie with that title!\n");
		assert(true);
	}
	srv.add_random_to_basket(4);
	movs = srv.get_all_basket();
	assert(movs.size() == 3);
	srv.add_random_to_basket(2);
	movs = srv.get_all_basket();
	assert(movs.size() == 3);
	srv.empty_basket();
	movs = srv.get_all_basket();
	assert(movs.size() == 0);
	srv.delete_movie("Inception", "action", 2014, "DiCaprio");
	srv.delete_movie("Anception", "action", 2014, "DiCaprio");
	srv.delete_movie("The Great Gatsby", "drama", 2014, "DiCaprio");
	try {
		srv.add_random_to_basket(2);
		assert(false);
	}
	catch (BasketException&) {
		assert(true);
	}



}