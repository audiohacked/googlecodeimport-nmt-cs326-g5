#include <QtGui>

#include "AppConfig.h"
#include "AppLogin.h"
#include "AppWidget.h"
#include "BrowserEmbed.h"
#include "chat/ChatRoster.h"
#include "SettingsDialog.h"

#include "AppMain.h"
#include "config.h"

void LogOutput(QtMsgType type, const char *msg);

int main(int argc, char *argv[])
{
	qInstallMsgHandler(LogOutput);
	QApplication app(argc, argv);

	app.setApplicationName("DDPS");
	app.setOrganizationName("Audiohacked");

	MainAppWindow *win = new MainAppWindow;
	AppLoginWindow *login = new AppLoginWindow;
	if (login->exec())
	{
		win->show();
		return app.exec();
	}
	return 0;
}

MainAppWindow::MainAppWindow()
{
	/* QSplashScreen */
	createActions();
	createMenus();
	frame = new DDPSFrame;
	setCentralWidget(frame);
	setStatusBar(new QStatusBar);
	statusBar()->showMessage(tr("Ready"));
}

void MainAppWindow::createActions()
{
	FileLogoutAct = new QAction(tr("&Logout..."), this);
	FileLogoutAct->setStatusTip(tr("Logout/Login or Change users.."));
	connect(FileLogoutAct, SIGNAL(triggered()), this, SLOT(logout()));

	FileUpdateAct = new QAction(tr("Check for App Updates"), this);
	FileUpdateAct->setStatusTip(tr("Check online for latest version.."));
	connect(FileUpdateAct, SIGNAL(triggered()), this, SLOT(update_app()));

	FileSettingsAct = new QAction(tr("Settings"), this);
	FileSettingsAct->setStatusTip(tr("View Application Settings"));
	connect(FileSettingsAct, SIGNAL(triggered()), this, SLOT(app_settings()));

	FileQuitAct = new QAction(tr("E&xit"), this);
	FileQuitAct->setShortcut(tr("Ctrl+Q"));
	FileQuitAct->setStatusTip(tr("Exit.."));
	connect(FileQuitAct, SIGNAL(triggered()), this, SLOT(close()));

	ViewNewsAct = new QAction(tr("News"), this);
	ViewNewsAct->setStatusTip(tr("Go to News page"));
	connect(ViewNewsAct, SIGNAL(triggered()), this, SLOT(news()));

	ViewSupportAct = new QAction(tr("Support"), this);
	ViewSupportAct->setStatusTip(tr("Go to Support page"));
	connect(ViewSupportAct, SIGNAL(triggered()), this, SLOT(support()));

	ViewForumsAct = new QAction(tr("Forums"), this);
	ViewForumsAct->setStatusTip(tr("Go to Forums page"));
	connect(ViewForumsAct, SIGNAL(triggered()), this, SLOT(forums()));

	ViewBandwidthAct = new QAction(tr("Bandwidth monitor"), this);
	ViewBandwidthAct->setStatusTip(tr("View Bandwidth Usage/Speed"));
	connect(ViewBandwidthAct, SIGNAL(triggered()), this, SLOT(bandwidth()));

	ViewSettingsAct = new QAction(tr("Settings"), this);
	ViewSettingsAct->setStatusTip(tr("View Application Settings"));
	connect(ViewSettingsAct, SIGNAL(triggered()), this, SLOT(app_settings()));

	ViewHomeAct = new QAction(tr("Home"), this);
	ViewHomeAct->setStatusTip(tr("Go to Homepage"));
	connect(ViewHomeAct, SIGNAL(triggered()), this, SLOT(home()));

	ViewCommunityAct = new QAction(tr("Community Portal"), this);
	ViewCommunityAct->setStatusTip(tr("View Profile"));
	connect(ViewCommunityAct, SIGNAL(triggered()), this, SLOT(community()));

	ViewDownloadsAct = new QAction(tr("Downloads"), this);
	ViewDownloadsAct->setStatusTip(tr("View Downloads Manager"));
	connect(ViewDownloadsAct, SIGNAL(triggered()), this, SLOT(downloads()));

	HelpSupportAct = new QAction(tr("Support"), this);
	HelpSupportAct->setStatusTip(tr("Go to Support page"));
	connect(HelpSupportAct, SIGNAL(triggered()), this, SLOT(support()));

	HelpAboutAct = new QAction(tr("&About DDPS"), this);
	HelpAboutAct->setStatusTip(tr("About DDPS"));
	connect(HelpAboutAct, SIGNAL(triggered()), this, SLOT(about()));

	ViewMessengerAct = new QAction(tr("InstaMessenger"), this);
	connect(ViewMessengerAct, SIGNAL(triggered()), this, SLOT(open_chat()));
}

void MainAppWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(FileLogoutAct);
	fileMenu->addAction(FileUpdateAct);
	fileMenu->addSeparator();
	fileMenu->addAction(FileSettingsAct);
	//fileMenu->addSeparator();
	fileMenu->addAction(FileQuitAct);
	menuBar()->addSeparator();

	viewMenu = menuBar()->addMenu(tr("&View"));
	//viewMenu->addAction(ViewMiniModeAct);
	//viewMenu->addSeparator();
	viewMenu->addAction(ViewNewsAct);
	viewMenu->addAction(ViewMessengerAct);
	viewMenu->addAction(ViewSettingsAct);
	viewMenu->addAction(ViewSupportAct);
	viewMenu->addAction(ViewForumsAct);
	viewMenu->addSeparator();
	viewMenu->addAction(ViewBandwidthAct);
	viewMenu->addSeparator();
	viewMenu->addAction(ViewHomeAct);
	viewMenu->addAction(ViewCommunityAct);
	viewMenu->addAction(ViewDownloadsAct);
	menuBar()->addSeparator();

	//gameMenu = menuBar()->addMenu(tr("&Games"));
	//menuBar()->addSeparator();

	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(HelpSupportAct);
	helpMenu->addAction(HelpAboutAct);
}

void MainAppWindow::about()
{
	QMessageBox::about(this, tr("About DDPS"),
			tr("DDPS 1.0-Qt Beta\n"
			"This Program is a Digital Content Distribution and Publishing System.\n"
			"Written Spring 2008 for CS326: Software Engineering.\n"
			"(C) 2009 Sean Nelson <snelson@nmt.edu>\n"
			"(C) 2008 Josha Barron <jbarron@nmt.edu>\n"
			"(C) 2008 Corey Brown <coreyb42@gmail.com>\n"
			"(C) 2008 Adam Troemne <atroemne@nmt.edu>"));
}

void MainAppWindow::home()
{
	frame->tabs->setCurrentIndex(0);
}

void MainAppWindow::community()
{
	frame->tabs->setCurrentIndex(1);
}

void MainAppWindow::downloads()
{
	frame->tabs->setCurrentIndex(2);
}

void MainAppWindow::logout()
{
	return;
}

void MainAppWindow::update_app()
{
	return;
}

void MainAppWindow::support()
{
	frame->tabs->Home->browser->load(QUrl(SUPPORTPAGE));
	frame->tabs->setCurrentIndex(0);
}

void MainAppWindow::bandwidth()
{
	return;
}

void MainAppWindow::news()
{	
	frame->tabs->Home->browser->load(QUrl(NEWSPAGE));
	frame->tabs->setCurrentIndex(0);
}

void MainAppWindow::forums()
{
	frame->tabs->Home->browser->load(QUrl(SUPPORTPAGE));
	frame->tabs->setCurrentIndex(0);
}

void MainAppWindow::app_settings()
{
	settings_widget = new SettingsWidget;
	settings_widget->exec();
}

void MainAppWindow::open_chat()
{
	frame->chat->show();
}

void LogOutput(QtMsgType type, const char *msg)
{
	QFile log_file("./ddps.log");
	log_file.open(QIODevice::WriteOnly | QIODevice::Append);
	switch(type)
	{
	case QtDebugMsg:
		log_file.write("Debug: ");
		log_file.write(msg);
		log_file.write("\n");
		break;
	case QtWarningMsg:
		log_file.write("Warning: ");
		log_file.write(msg);
		log_file.write("\n");
		break;
	case QtCriticalMsg:
		log_file.write("Critical: ");
		log_file.write(msg);
		log_file.write("\n");
		break;
	case QtFatalMsg:
		log_file.write("Fatal: ");
		log_file.write(msg);
		log_file.write("\n");
		abort();
	}
	log_file.close();

}
