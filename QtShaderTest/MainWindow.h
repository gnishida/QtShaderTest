#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <GL/glew.h>
#include <QtGui/QMainWindow>
#include "ui_MainWindow.h"
#include "GLWidget3D.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	static enum { MODE_DEFAULT = 0, MODE_PLACETYPE, MODE_BLOCK, MODE_PARCEL };

public:
	Ui::MainWindow ui;
	GLWidget3D* glWidget;

public:
	MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainWindow();

protected:
	void keyPressEvent(QKeyEvent* e);
	void keyReleaseEvent(QKeyEvent* e);

public slots:
};

#endif // MAINWINDOW_H
