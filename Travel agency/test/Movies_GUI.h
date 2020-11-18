#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Movies_GUI.h"

class Movies_GUI : public QMainWindow
{
	Q_OBJECT

public:
	Movies_GUI(QWidget *parent = Q_NULLPTR);

private:
	Ui::Movies_GUIClass ui;
};
