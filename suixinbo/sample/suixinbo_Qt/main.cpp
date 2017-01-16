#include "stdafx.h"
#include "MainWindow.h"

MainWindow* g_pMainWindow = NULL;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	g_pMainWindow = MainWindow::getInstance();
	g_pMainWindow->show();
	return a.exec();
}
