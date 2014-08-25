#include "MainWindow.h"
#include <QFileDialog>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags) : QMainWindow(parent, flags) {
	ui.setupUi(this);

	// register the menu's action handlers
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));

	// setup the GL widget
	glWidget = new GLWidget3D(this);
	setCentralWidget(glWidget);
}

MainWindow::~MainWindow() {
}

void MainWindow::keyPressEvent(QKeyEvent* e) {
	glWidget->keyPressEvent(e);
}

void MainWindow::keyReleaseEvent(QKeyEvent* e) {
	glWidget->keyReleaseEvent(e);
}


