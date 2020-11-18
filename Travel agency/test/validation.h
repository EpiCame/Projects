#pragma once
#include "model.h"
#include <exception>


class ValidException {
private:
	string msg;

public:

	ValidException(string m) :msg{ m } {
	};

	string get_msg() const {
		return msg;
	}
};

class Validator {
private:
	friend class Movie;

public:
	Validator() = default; 

	Validator(const Validator& val) = delete;
	/*
	Primeste ca parametru un film si il valideaza
	Raise exceptions.
	*/
	int validate_movie(const Movie& mv);

};


void test_validate_movie();






