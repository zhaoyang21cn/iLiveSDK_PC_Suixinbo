#include "stdafx.h"
#include "MainWindow.h"

MainWindow* g_pMainWindow = NULL;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	MainWindow w;
	g_pMainWindow = &w;
	w.show();

	return a.exec();
}
