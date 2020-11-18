#pragma once
#include <vector>
#include <algorithm>
#include <random>    
#include <chrono>   
#include "Observer.h"

#include "model.h"
using std::vector;


class BasketException {
private:
	string msg;

public:

	BasketException(string m) : msg{ m } {};

	string get_msg() const {
		return msg;
	}
};

class Movie_Basket : public Observable {

	vector<Movie> basket;
	Repo& repo;
public:
	

	Movie_Basket(Repo& repo) : repo{ repo } {
	};

	void add_to_basket(const Movie& mv) {
		basket.push_back(mv);
		notify();
	}
	void empty_basket() {
		basket.clear();
		notify();
	}
	/*
	Umple cosul aleator
	*/
	void add_random(size_t number) {
		auto all = this->repo.get_all();
		std::shuffle(all.begin(), all.end(), std::default_random_engine(std::random_device{}())); //amesteca vectorul v
		while (number && all.size() > 0) {
			number--;
			basket.push_back(all.back());
			all.pop_back();
		}
		notify();
	}

	const vector<Movie>& basket_list() const {
		return basket;
	}

	const int basket_size() const {
		return basket.size();
	}
};

