#include "gui_movie.h"

using namespace std;


void Movie_gui::init_gui() {

	grid = new QGridLayout;
	setLayout(grid);
	
	QHBoxLayout* main_lay = new QHBoxLayout;
	//setLayout(main_lay);

	//adaugam lista  
	QWidget* wid_list = new QWidget;
	QVBoxLayout* v1 = new QVBoxLayout;
	wid_list->setLayout(v1);
	movie_list = new QListWidget;
	v1->addWidget(movie_list);
	main_lay->addWidget(wid_list);
	// ----- 
	QWidget* wid_right = new QWidget;

	QVBoxLayout* wid_det = new QVBoxLayout;

	QFormLayout* form = new QFormLayout; 
	txt_title = new QLineEdit; 
	form->addRow(new QLabel("Title: "), txt_title);
	txt_genre = new QLineEdit;
	form->addRow(new QLabel("Genre: "), txt_genre);
	txt_year = new QLineEdit;
	form->addRow(new QLabel("Year: "), txt_year);
	txt_actor = new QLineEdit;
	form->addRow(new QLabel("Actor: "), txt_actor);
	//basket 
	QVBoxLayout* basket_ly = new QVBoxLayout;
	//basket_ly->addItem(new QLabel("Basket list"));
	basket_ly->addWidget(new QLabel("Basket list"));
	basket_list = new QListWidget;
	basket_ly->addWidget(basket_list);
	//basket_btns
	QHBoxLayout* basket_btns = new QHBoxLayout;
	btn_add_to_basket = new QPushButton("Add to basket");
	btn_add_random = new QPushButton("Add random");
	btn_clear_basket = new QPushButton("Clear");
	btn_cos_crud = new QPushButton("Basket CRUD");
	btn_cos_paint = new QPushButton("Basket paint");
	number1 = new QLineEdit;
	btn_export_to_cvs = new QPushButton("Export CVS");
	btn_export_to_html = new QPushButton("Export HTML");
	basket_btns->addWidget(btn_add_to_basket);
	basket_btns->addWidget(btn_add_random);
	basket_btns->addWidget(btn_clear_basket);
	basket_btns->addWidget(number1);
	basket_btns->addWidget(btn_export_to_cvs);
	basket_btns->addWidget(btn_export_to_html);
	basket_btns->addWidget(btn_cos_crud);
	basket_btns->addWidget(btn_cos_paint);
	basket_ly->addLayout(basket_btns);


	// layout butoane
	QHBoxLayout* btns = new QHBoxLayout;
	btn_add_movie = new QPushButton("Add movie");
	btn_delete_movie = new QPushButton("Delete movie");
	btn_modify_movie = new QPushButton("Modify movie");
	btn_undo = new QPushButton("Undo");
	btn_sort_movies = new QPushButton("Sort movies by: ");
	txt_sort = new QComboBox; 
	txt_sort->addItem("title");
	txt_sort->addItem("year");
	txt_sort->addItem("actor");
	btn_filter_movies = new QPushButton("Filter movies by: ");
	txt_filter = new QComboBox;
	txt_filter->addItem("title");
	txt_filter->addItem("year");
	btns->addWidget(btn_add_movie);
	btns->addWidget(btn_delete_movie);
	btns->addWidget(btn_modify_movie);
	btns->addWidget(btn_undo);
	QHBoxLayout* btns2 = new QHBoxLayout;
	btns2->addWidget(btn_sort_movies);
	btns2->addWidget(txt_sort);
	btns2->addWidget(btn_filter_movies);
	btns2->addWidget(txt_filter);
	wid_det->addItem(form);
	wid_det->addItem(btns);
	wid_det->addItem(btns2);
	wid_right->setLayout(wid_det);
	main_lay->addWidget(wid_right);
	grid->addLayout(main_lay,0,0);
	grid->addLayout(basket_ly, 0, 1);



}

void Movie_gui::connect_sign_slots() {

	QObject::connect(btn_add_movie, &QPushButton::clicked, this, &Movie_gui::add_new_movie);

	QObject::connect(btn_cos_crud, &QPushButton::clicked, [this]() {
		auto win = new CRUD_basket(srv.get_basket());
		win->show();
		});

	QObject::connect(btn_cos_paint, &QPushButton::clicked, [this]() {
		auto win = new paint_basket(srv.get_basket());
		win->show();
		});

	QObject::connect(btn_undo, &QPushButton::clicked, this, &Movie_gui::undo);

	QObject::connect(btn_sort_movies, &QPushButton::clicked, this, &Movie_gui::sort_movies);

	QObject::connect(btn_clear_basket, &QPushButton::clicked, this, &Movie_gui::clear_basket);

	QObject::connect(btn_delete_movie, &QPushButton::clicked, this, &Movie_gui::delete_movie);

	QObject::connect(btn_modify_movie, &QPushButton::clicked, this, &Movie_gui::modify_movie);

	QObject::connect(btn_filter_movies, &QPushButton::clicked, this, &Movie_gui::filter_movies);

	QObject::connect(btn_add_random, &QPushButton::clicked, this, &Movie_gui::add_random_to_basket);

	QObject::connect(btn_add_to_basket, &QPushButton::clicked, this, &Movie_gui::add_movie_to_basket);

	QObject::connect(btn_export_to_cvs, &QPushButton::clicked, this, &Movie_gui::export_to_cvs);

	QObject::connect(btn_export_to_html, &QPushButton::clicked, this, &Movie_gui::export_to_html);

	QObject::connect(movie_list, &QListWidget::itemSelectionChanged, [&]() {
		if (movie_list->selectedItems().isEmpty()) {
			txt_title->setText("");
			txt_genre->setText("");
			txt_year->setText("");
			txt_actor->setText("");
			return;
		}
		QListWidgetItem* item = movie_list->selectedItems().at(0);
		string movie_line = item->text().toStdString();
		vector<string> infos;
		string info;
		while (movie_line.size()) {
			info.push_back(movie_line[0]);
			movie_line.erase(movie_line.begin());
			if (movie_line[0] == ',')
			{
				infos.push_back(info);
				movie_line.erase(movie_line.begin());
				movie_line.erase(movie_line.begin());
				info.clear();
			}
		}
		infos.push_back(info);
		mv = Movie(infos[0], infos[1], atoi(infos[2].c_str()), infos[3]);
		QString title = QString::fromStdString(infos[0]);
		QString genre = QString::fromStdString(infos[1]);
		QString year = QString::fromStdString(infos[2]);
		QString actor = QString::fromStdString(infos[3]);
		txt_title->setText(title);
		txt_genre->setText(genre);
		txt_year->setText(year);
		txt_actor->setText(actor);
	});

}

void Movie_gui::filter_movies() {
	string crit = txt_filter->currentText().toStdString();
	if (crit == "title") {
		string title = txt_title->text().toStdString();
		Filter_win* filter = new Filter_win;
		filter->reload_filter(srv.filter_movies(cmp_title, title, 0));
		filter->show();
	}
	else {
		int year = txt_year->text().toInt();
		Filter_win* filter = new Filter_win;
		filter->reload_filter(srv.filter_movies(cmp_year, "", year));
		filter->show();
	}
}

void Filter_win::reload_filter(const vector<Movie>& movs) {
	filter_list->clear();
	for (const auto& mv : movs) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(mv.str()), filter_list);
		filter_list->addItem(item);
	}
}

void Movie_gui::export_to_cvs() {
	try {
		srv.export_basket_cvs("movies.cvs");
	}
	catch (RepoException& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
	}
}

void Movie_gui::export_to_html() {
	try {
		srv.export_basket_html("movies.html");
	}
	catch (RepoException& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
	}
}

void clearLayout(QLayout* layout) {
	QLayoutItem* item;
	while ((item = layout->takeAt(0))) {
		if (item->layout()) {
			clearLayout(item->layout());
			delete item->layout();
		}
		if (item->widget()) {
			delete item->widget();
		}
		delete item;
	}
}

void Movie_gui::add_dyn_btns() {
	clearLayout(btns_ly);
	btns_ly = new QHBoxLayout;
	for (int i = 0; i < movie_list->count(); i++) {
		QListWidgetItem* it = movie_list->item(i);
		string movie_line = it->text().toStdString();
		vector<string> infos;
		string info;
		while (movie_line.size()) {
			info.push_back(movie_line[0]);
			movie_line.erase(movie_line.begin());
			if (movie_line[0] == ',')
			{
				infos.push_back(info);
				movie_line.erase(movie_line.begin());
				movie_line.erase(movie_line.begin());
				info.clear();
			}
		}
		infos.push_back(info);
		QPushButton* bt = new QPushButton(QString::fromStdString(infos[0]));
		
		btns_ly->addWidget(bt);
		QObject::connect(bt, &QPushButton::clicked, [&, bt]() {
			//qDebug() << bt->text();
			srv.delete_by_title(bt->text().toStdString());
			reload_list(srv.get_all());
			});
	}
	//dy_btns->setLayout(btns_ly);
	grid->addLayout(btns_ly, 0, 2);
}


void Movie_gui::add_random_to_basket() {
	int nr = number1->text().toInt();
	number1->setText("");
	try { srv.add_random_to_basket(nr); 
	reload_basket(srv.get_all_basket());
	}
	catch (BasketException& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
	}
}


void Movie_gui::clear_basket() {
	srv.empty_basket();
	reload_basket(srv.get_all_basket());
}

void Movie_gui::reload_basket(const vector<Movie>& movs) {
	basket_list->clear();
	for (const auto& mv : movs) {
		basket_list->addItem(QString::fromStdString(mv.str()));
	}
}

void Movie_gui::add_movie_to_basket() {
	try {
		srv.add_movie_to_basket(mv.get_title());
		txt_title->setText("");
		txt_genre->setText("");
		txt_year->setText("");
		txt_actor->setText("");
		reload_basket(srv.get_all_basket());
	}
	catch (BasketException& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
	}
}

void Movie_gui::undo() {
	try {
		srv.undo();
		reload_list(srv.get_all());

	}
	catch (RepoException& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
	}
}

void Movie_gui::sort_movies() {
	QString crt = txt_sort->currentText();
	if (crt == "title")
		reload_list(srv.sort_movies(cmp_title));
	else if (crt == "year")
		reload_list(srv.sort_movies(cmp_year));
	else if (crt == "actor")
		reload_list(srv.sort_movies(cmp_actor));
	else
		QMessageBox::warning(this, "Warning", "Invalid sort criteria!");
}

void Movie_gui::modify_movie() {
	
	string title = txt_title->text().toStdString();
	int year = txt_year->text().toInt();
	string genre = txt_genre->text().toStdString();
	string actor = txt_actor->text().toStdString();
	try {
		
		txt_title->setText("");
		txt_genre->setText("");
		txt_year->setText("");
		txt_actor->setText("");
		srv.modify_movie(mv.get_title(), mv.get_genre(), mv.get_year(), mv.get_actor(), title, genre, year, actor);
		reload_list(srv.get_all());
	}
	catch (RepoException& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
	}
	catch (ValidException& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
	}


}

void Movie_gui::delete_movie() {
	txt_title->setText("");
	txt_genre->setText("");
	txt_year->setText("");
	txt_actor->setText("");
	try {
		srv.delete_movie(mv.get_title(), mv.get_genre(), mv.get_year(), mv.get_actor());
		reload_list(srv.get_all());
	}
	catch (RepoException& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
	}
	catch (ValidException& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
	}


}

void Movie_gui::add_new_movie() {
	string title = txt_title->text().toStdString();
	int year = txt_year->text().toInt();
	string genre = txt_genre->text().toStdString();
	string actor = txt_actor->text().toStdString();
	txt_title->setText("");
	txt_genre->setText("");
	txt_year->setText("");
	txt_actor->setText("");
	try {
		srv.add_movie(title,genre,year,actor);
		reload_list(srv.get_all());
	}
	catch (RepoException& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
	}
	catch (ValidException& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
	}
}

void Movie_gui::reload_list(const vector<Movie>& movs){
	movie_list->clear();
	for (const auto& mv : movs) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(mv.str()), movie_list);
		movie_list->addItem(item);
	}
	add_dyn_btns();
}

// 
void CRUD_basket::init_gui() {
	table = new QTableWidget;
	QVBoxLayout* ly = new QVBoxLayout;
	ly->addWidget(table);
	btn_add = new QPushButton("Add random: ");
	add_number = new QLineEdit;
	btn_golire = new QPushButton("Clear");
	ly->addWidget(btn_add);
	ly->addWidget(add_number);
	ly->addWidget(btn_golire);
	setLayout(ly);
}

void CRUD_basket::connect_sign_slots() {

	cos.addObserver(this);
	QObject::connect(btn_add, &QPushButton::clicked, [&]() {
		auto number = add_number->text().toInt();
		add_number->setText("");
		cos.add_random(number);
		});

	QObject::connect(btn_golire, &QPushButton::clicked, [&]() {
		cos.empty_basket();
		});



}

void CRUD_basket::reload_table(const vector<Movie>& movs) {
	table->clear();
	table->setRowCount(movs.size());
	table->setColumnCount(4);
	for (int i = 0; i < movs.size(); i++) {
		table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(movs[i].get_title())));
		table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(movs[i].get_genre())));
		table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(to_string(movs[i].get_year()))));
		table->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(movs[i].get_actor())));
	}
}

CRUD_basket::~CRUD_basket() {
	cos.removeObserver(this);
}


void paint_basket::paintEvent(QPaintEvent* ev) {
	QPainter p{ this };
	for (int i = 0; i < cos.basket_size(); i++) {
		auto r = QRect(i * 50, i * 50, 50, 50);
		p.drawImage(r, QImage("try.png"));
	}
	//p.drawImage(0, 0, QImage("movie.jpg"), 0 , 0 , -1 , -1);
}

void paint_basket::update() {

	const QRect rct(0, 0, width(), height());
	QPaintEvent* ev = new QPaintEvent(rct);
	this->paintEvent(ev);
}
