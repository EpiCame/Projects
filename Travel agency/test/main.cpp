#include "gui_movie.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Repo repo;
	Validator valid;
	auto srv = Movie_service(valid, repo);
	Movie_gui w(srv);
	w.setMinimumHeight(200);
	w.setMinimumWidth(1500);

	w.show();
	return a.exec();
}
