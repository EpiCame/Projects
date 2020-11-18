#include "Repo.h"
#include <iostream>
#include <fstream>


/*
	Adauga un element in vector
*/
void Repo::add(const TElem& elem) {

	for (const Movie& mv : movies) {
		if (mv == elem)
			throw RepoException("Movie already exists!\n");
	}
	movies.push_back(elem);
}

/*
	Modifica un element din vector
*/
void Repo::modify(const Movie& elem, const Movie& new_elem) {

	bool found = false;
	for (Movie& mv : movies) {
		if (mv.str() == elem.str()) {
			mv = new_elem;
			found = true;
		}
	}
	if (!found)
		throw RepoException("Movie does not exist to be modified!\n");
}

/*
	Sterge un element din vector
*/
TElem Repo::erase(const TElem& elem) {

	auto it = movies.begin();
	while (it != movies.end()) {
		if (*it == elem) {
			movies.erase(it);
			return elem;
		}
		it++;
	}
	throw RepoException("The movie does not exist!\n");
}

/*
	returns the elements
*/
const vector<TElem>& Repo::get_all() {
	return this->movies;
}


/*
Cauta un element din vector
*/
TElem Repo::search(const TElem& elem) {

	auto it = movies.begin();
	while (it != movies.end()) {
		if (*it == elem)
			return elem;
		it++;
	}
	throw RepoException("The movie does not exist!\n");
}

void RepoFile::load_from_file() {
	ifstream fin(file_name);
	if (!fin.is_open()) { //verify if the stream is opened		
		throw RepoException("Unable to open file:" + file_name);
	}
	while (!fin.eof()) {
		string title;
		fin >> title;
		string genre;
		fin >> genre;
		int year;
		fin >> year;
		string actor;
		fin >> actor;
		if (fin.eof()) {	
			break;
		}
		Movie mv{ title, genre, year, actor };
		Repo::add(mv);
	}
	fin.close();
}

void RepoFile::write_to_file() {
	ofstream fout(file_name, ios::trunc);
	if (!fout.is_open()) { 
		string msg("Unable to open file:");
		throw RepoException(msg);
	}
	for (auto& mv : get_all()) {
		fout << mv.get_title();
		fout << endl;
		fout << mv.get_genre();
		fout << endl;
		fout << mv.get_year();
		fout << endl;
		fout << mv.get_actor();
		fout << endl;
	}
	fout.close();
}

void test_file_repo() {
	ofstream fout("test_movies.txt", ios::trunc);
	fout.close();
	RepoFile repo_file{ "test_movies.txt" };
	repo_file.add(Movie{ "test","test",1999, "test" });

	RepoFile repo_file2{ "test_movies.txt" };
	Movie mv1 = Movie{ "test","test",1999, "test" };
	Movie mv2 = Movie{ "test2","test2",1999, "test2" };
	auto mv = repo_file2.search(mv1);
	assert(mv.get_year() == 1999);
	try {
		repo_file2.search(mv2);
		assert(false);
	}
	catch (RepoException&) {
	}
	repo_file2.erase(mv1);
	assert(repo_file2.get_all().size() == 0);
	try {
		repo_file2.erase(mv2);
		assert(false);
	}
	catch (RepoException&) {
	}

	RepoFile repo_file3{ "test_movies.txt" };
	assert(repo_file3.get_all().size() == 0);
	try {
		RepoFile repo_file4{ "movies.txt" };
		assert(false);
	}
	catch (RepoException&) {
	}
}

void test_repo() {

	Repo repo;
	Movie mv{ "Titanic", "romance", 1997, "DiCaprio" };
	repo.add(mv);
	vector<Movie> movs = repo.get_all();
	assert(movs.size() == 1);
	Movie cpy_mv{ "Titanic", "romance", 1997, "DiCaprio" };
	try {
		repo.add(cpy_mv);
		assert(false);}
	catch (const RepoException& ) {
		assert(true);
	}
	Movie mv1{ "Inception", "action", 2010, "DiCaprio" };
	try {
		repo.modify(mv1, mv);
		assert(false);}
	catch (const RepoException& e) {
		assert(true);
	}
	repo.modify(mv, mv1);
	movs = repo.get_all();
	assert(movs[0] == mv1);
	try {
		repo.search(mv);
		assert(false);}
	catch (const RepoException& e) {
		assert(true);
	}
	assert(repo.search(mv1) == mv1);
	try {
		repo.erase(mv);
		assert(false);}
	catch (const RepoException& e) {
		assert(true);
	}
	Movie mv2 = repo.erase(mv1);
	assert(mv2 == mv1);
	movs = repo.get_all();
	assert(movs.size() == 0);

}