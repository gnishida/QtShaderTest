#include "MainWindow.h"
#include <QFileDialog>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags) : QMainWindow(parent, flags) {
	ui.setupUi(this);

	// register the menu's action handlers
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(onFileOpen()));
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));

	// setup the GL widget
	glWidget = new GLWidget3D(this);
	setCentralWidget(glWidget);
}

void MainWindow::onFileOpen()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open OBJ file..."), "", tr("OBJ Files (*.obj)"));
	if (filename.isEmpty()) return;

	glWidget->loadOBJ(filename.toUtf8().data());
	glWidget->updateGL();
}

