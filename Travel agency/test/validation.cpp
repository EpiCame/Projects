#include "validation.h"
#include <assert.h>

/*
	Primeste ca parametru un film si il valideaza
	Raise exceptions.
	0 - film valid.
*/
int Validator::validate_movie(const Movie& mv) {

	string err = { "" };
	if (mv.get_title().length() == 0)
		err.append("Invalid title!\n");
	if (mv.get_genre().length() == 0)
		err.append("Invalid genre!\n");
	if (mv.get_year() < 1900)
		err.append("Invalid year!\n");
	if (mv.get_actor().length() == 0)
		err.append("Invalid actor!\n");
	if (err.length() != 0) {
		throw ValidException(err);
	}
	return 0;

}


void test_validate_movie() {
	Validator valid;
	Movie mv_invalid = Movie("", "comedy", 345, "");
	try {
		const int error = valid.validate_movie(mv_invalid);
		assert(false);
	}
	catch (const ValidException& e) {
		assert(e.get_msg()=="Invalid title!\nInvalid year!\nInvalid actor!\n");
	}
	Movie mv = Movie("Inception", "action", 2010, "DiCaprio");
	assert(valid.validate_movie(mv) == 0);
}