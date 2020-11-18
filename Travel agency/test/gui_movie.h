#pragma once

#include <qwidget.h>
#include <qpainter.h>
#include <QPaintEvent>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qboxlayout.h>
#include <qformlayout.h>
#include <qcombobox.h>
#include <qmessagebox.h>
#include "service.h"
#include "Model.h"
#include <vector>
#include <qlabel.h>
#include <qmenu.h>
#include <qdebug.h>
#include "Observer.h"
#include <qtablewidget.h>

using namespace std; 

class Filter_win : public QWidget {

private:

	QListWidget* filter_list;
	QHBoxLayout* filter_ly;
public:
	Filter_win() {
		filter_list = new QListWidget;
		filter_ly = new QHBoxLayout;
		filter_ly->addWidget(filter_list);
		this->setLayout(filter_ly);
	}
	void reload_filter(const vector<Movie>& movs);
};

class Movie_gui : public QWidget {
private:
	//service 
	Movie_service& srv;
	Movie mv;
	QGridLayout* grid;

	//QWidget* dy_btns = new QWidget;
	QHBoxLayout* btns_ly = new QHBoxLayout;

	QListWidget* movie_list;
	QListWidget* basket_list;
	QPushButton* btn_add_movie;
	QPushButton* btn_delete_movie;
	QPushButton* btn_modify_movie;
	QPushButton* btn_sort_movies;
	QPushButton* btn_filter_movies;
	QPushButton* btn_undo;
	//
	QPushButton* btn_add_to_basket;
	QPushButton* btn_add_random;
	QLineEdit* number1;
	QPushButton* btn_clear_basket;
	QPushButton* btn_export_to_cvs;
	QPushButton* btn_export_to_html;
	//
	QPushButton* btn_cos_crud;
	QPushButton* btn_cos_paint;
	//
	QComboBox* txt_sort;
	QComboBox* txt_filter;
	QLineEdit* txt_title;
	QLineEdit* txt_genre;
	QLineEdit* txt_year;
	QLineEdit* txt_actor;
	void init_gui();
	void connect_sign_slots();
	void reload_list(const vector<Movie>& movs);
	void reload_basket(const vector<Movie>& movs);
	//adds a movie
	void add_new_movie();
	//deletes a movie
	void delete_movie();
	//modifies a movie
	void modify_movie();
	//sorts the movie list 
	void sort_movies();
	//filter by title or year
	void filter_movies();
	//undo
	void undo();
	//adds a movie to the basket
	void add_movie_to_basket();
	
	//clears the basket
	void clear_basket();
	//adds movies random to basket
	void add_random_to_basket();
	//
	void export_to_cvs();
	//
	void export_to_html();
	//
	void add_dyn_btns();

public:
	//constructor 
	Movie_gui(Movie_service& service) :srv{service} {
		init_gui();
		connect_sign_slots();
		reload_list(srv.get_all());
	}

};

//implementam clasa pentru fereastra Cos GUI CRUD

class CRUD_basket : public QWidget, public Observer {

private:
	Movie_Basket& cos;
	QTableWidget* table; 
	QPushButton* btn_golire;
	QPushButton* btn_add;
	QLineEdit* add_number;

	//
	void init_gui();

	void connect_sign_slots();

	void reload_table(const vector<Movie>& movs);

public:

	CRUD_basket(Movie_Basket& cos) :cos{ cos } {
		init_gui();
		connect_sign_slots();
		reload_table(cos.basket_list());
	};
	
	void update() override {
		reload_table(cos.basket_list());
	};

	~CRUD_basket();


};

class paint_basket : public QWidget, public Observer {
private:

	Movie_Basket& cos;

public:
	paint_basket(Movie_Basket& cos) :cos{ cos } {
		setAttribute(Qt::WA_DeleteOnClose); //daca vreau sa se distruga fereastra imediat dupa inchidere
		cos.addObserver(this);
		update();
	}
	void update();


	void paintEvent(QPaintEvent* ev) override;

	~paint_basket() {
		cos.removeObserver(this);
	}

};