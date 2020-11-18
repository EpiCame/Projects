#include "ui.h"
#include <iostream>

using namespace std;


void Console::add_movie() {
	string t;
	string g;
	int y;
	string a;
	cout << "Title: ";
	getline(cin , t);
	cout << "Genre: ";
	getline(cin, g);
	cout << "Year: ";
	cin >> y;
	cout << "Actor: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, a);
	srv.add_movie(t, g, y, a);
	cout << "Movie added!\n";
}

void Console::delete_movie() {
	string t;
	string g;
	int y;
	string a;
	cout << "Title: ";
	getline(cin, t);
	cout << "Genre: ";
	getline(cin, g);
	cout << "Year: ";
	cin >> y;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Actor: ";
	getline(cin, a);
	srv.delete_movie(t, g, y, a);
	cout << "Movie deleted!\n";
}

void Console::search_movie() {
	string t;
	string g;
	int y;
	string a;
	cout << "Title: ";
	getline(cin, t);
	cout << "Genre: ";
	getline(cin, g);
	cout << "Year: ";
	cin >> y;
	cout << "Actor: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, a);
	Movie mv = srv.search_movie(t, g, y, a);
	cout << mv.str();
}


void Console::sort_movies() {
	//first read the criteria
	string crit;
	cout << "Read the criteria: ";
	cin >> crit;
	if (crit != "title" && crit != "year" && crit!="actor")
	{
		cout << "You can sort by title, year or actor!\n";
	}
	else if (crit == "title") {
		vector<Movie> movs = srv.sort_movies(cmp_title);
		if (movs.size() == 0) cout << "There are no movies!\n";
		else
		{
			for (const Movie& mv : movs)
				cout << mv.str() << endl;
		}
	}
	else if (crit == "year") {
		vector<Movie> movs = srv.sort_movies(cmp_year);
		if (movs.size() == 0) cout << "There are no movies!\n";
		else
		{
			for (const Movie& mv : movs)
				cout << mv.str() << endl;
		}
	}
	else if (crit == "actor") {
		vector<Movie> movs = srv.sort_movies(cmp_actor);
		if (movs.size() == 0) cout << "There are no movies!\n";
		else
		{
			for (const Movie& mv : movs)
				cout << mv.str() << endl;
		}
	}
}

void Console::filter_movies() {
	//first read the criteria
	string crit;
	cout << "Read the criteria: ";
	cin >> crit;
	if (crit != "title" && crit != "year")
	{
		cout << "You can filter by title or year!\n";
	}
	else if (crit == "title") {
		cout << "Read a title: ";
		string t;
		cin >> t;
		vector<Movie> movs = srv.filter_movies(cmp_title, t, 0);
		if (movs.size() == 0) cout << "There are no movies with this criteria!\n";
		else
		{
			for (const Movie& mv : movs)
				cout << mv.str() << endl;
		}
	}
	else if (crit == "year") {
		cout << "Read an year: ";
		int y;
		cin >> y;
		vector<Movie> movs = srv.filter_movies(cmp_year, "", y);
		if (movs.size() == 0) cout << "There are no movies with this criteria!\n";
		else
		{
			for (const Movie& mv : movs)
				cout << mv.str() << endl;
		}
	}
}

void Console::modify_movie() {
	string t, new_t , new_g ,new_a;
	string g;
	int y, new_y;
	string a;
	cout << "First movie:\n";
	cout << "Title: ";
	getline(cin, t);
	cout << "Genre: ";
	getline(cin, g);
	cout << "Year: ";
	cin >> y;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Actor: ";
	getline(cin, a);
	cout << "New movie:\n";
	cout << "Title: ";
	getline(cin, new_t);
	cout << "Genre: ";
	getline(cin, new_g);
	cout << "Year: ";
	cin >> new_y;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Actor: ";
	getline(cin, new_a);
	srv.modify_movie(t, g, y, a, new_t, new_g, new_y,new_a);
	cout << "Movie modified!\n";
}

void Console::print_movies() {
	vector<Movie> movs = srv.get_all();
	Movie mv;
	if (movs.size() == 0) cout << "There are no movies added!\n";
	else {
		for (const auto& mv : movs) {
			cout << mv.str() << endl;
		}
	}
}

void Console::add_one_movie() {
	string t;
	cout << "Title: ";
	getline(cin, t);
	srv.add_movie_to_basket(t);
	cout << "Movie added!\n";
}

void Console::add_random_movies() {
	unsigned int number;
	cout << "Number of movies: ";
	cin >> number;
	srv.add_random_to_basket(number);
	cout << "Movies added!\n";
}

void Console::empty_basket() {
	srv.empty_basket();
	cout << "Basket is empty!\n";
}

void Console::print_basket() {

	vector<Movie> movs = srv.get_all_basket();
	if (movs.size() == 0) cout << "There are no movies added in the basket!\n";
	else {
		for (const auto& mv : movs) {
			cout << mv.str() << endl;
		}
	}
}

void Console::export_basket_cvs(){
	string f_name;
	getline(cin, f_name);
	srv.export_basket_cvs(f_name);
}

void Console::export_basket_HTML() {
	string f_name;
	getline(cin, f_name);
	srv.export_basket_html(f_name);
}

void Console::undo_movies() {
	srv.undo();
}
void Console::avg_year() {
	
	cout << srv.average_year() << endl;
}


void Console::run() {
	string commands = { "1- Add a new movie\n2- Modify an existing movie\n3- Delete an existing movie\n4- Search an existing movie\n5- Print all movies\n6- Filter movies\n7- Sort movies\n8- Add a movie in the basket\n9- Add random movies to basket\n10- Empty the basket\n11- Print movies from the basket\n12- Export bascket to CVS\n13- Export basket to HTML\n14- Undo\n15- Average year\n0-Exit the program\nCommand: " };
	int cmd;
	while (true) {
		cout << commands;
		cin >> cmd;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (cmd == 0)
			break;
		try {
			if (cmd == 1)
				add_movie();
			if (cmd == 2)
				modify_movie();
			if (cmd == 3)
				delete_movie();
			if (cmd == 4)
				search_movie();
			if (cmd == 5)
				print_movies();
			if (cmd == 6)
				filter_movies();
			if (cmd == 7)
				sort_movies();
			if (cmd == 8)
				add_one_movie();
			if (cmd == 9)
				add_random_movies();
			if (cmd == 10)
				empty_basket();
			if (cmd == 11)
				print_basket();
			if (cmd == 12)
				export_basket_cvs();
			if (cmd == 13)
				export_basket_HTML();
			if (cmd == 14)
				undo_movies();
			if (cmd == 15)
				avg_year();
		}
		catch (const ValidException& e) { cout << e.get_msg(); }
		catch (const RepoException& e) { cout << e.get_msg(); }
		catch (const BasketException& e) { cout << e.get_msg(); }
		
	}
}






void test_all() {
	test_create_movie();
	test_validate_movie();
	test_repo();
	test_export();
	test_file_repo();
	test_service();
	test_cmp_functions();
}