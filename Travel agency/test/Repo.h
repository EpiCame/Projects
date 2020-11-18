#pragma once
#include <vector>
#include <map>
#include <algorithm>
#include "model.h"
#include <assert.h>

using namespace std;

typedef Movie TElem;


class RepoException {
private:
	string msg;

public:

	RepoException(string m) : msg{ m } {};

	string get_msg() const {
		return msg;
	}
};

class Repository {

public:

	Repository() = default;

	Repository(const Repository & rp) = delete;
	/*
	Adauga un element in vector
	*/
	virtual void add(const TElem & elem)  = 0;

	/*
	Modifica un element din vector
	*/
	virtual void modify(const Movie & elem, const Movie & new_elem)= 0;

	/*
	Cauta un element din vector
	*/
	virtual TElem search(const TElem & elem) = 0;

	/*
	Sterge un element din vector
	*/
	virtual TElem erase(const TElem & elem) = 0;


	/*
	returns the elements
	*/
	virtual const vector<TElem>& get_all() = 0;

	virtual ~Repository() = default; 


};

class Repo : public Repository {

private:
	/*
	reprezentare cu std::vector
	*/
	vector<TElem> movies;

public:

	Repo() = default;

	virtual ~Repo() = default;

	Repo(const Repo& rp) = delete;
	/*
	Adauga un element in vector
	*/
	virtual void add(const TElem& elem);

	/*
	Modifica un element din vector
	*/
	virtual void modify(const Movie& elem, const Movie& new_elem);

	/*
	Cauta un element din vector
	*/
	TElem search(const TElem& elem);

	/*
	Sterge un element din vector
	*/
	virtual TElem erase(const TElem& elem);


	/*
	returns the elements
	*/
	const vector<TElem>& get_all();


};

class RepoFile :public Repo {
private:
	string file_name;
	void load_from_file();
	void write_to_file();
public:
	RepoFile(string file_name) :Repo(), file_name{ file_name } {
		load_from_file();
	}
	void add(const TElem& elem) override {
		Repo::add(elem);
		write_to_file();
	}
	TElem erase(const TElem& elem) override {
		auto mv = Repo::erase(elem);
		write_to_file();
		return mv;
	}

	void modify(const Movie& elem, const Movie& new_elem) override {
		Repo::modify(elem, new_elem);
		write_to_file();
	}
};

void test_file_repo();
void test_repo();
