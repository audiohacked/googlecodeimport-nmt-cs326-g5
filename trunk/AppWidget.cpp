#include <QtGui>
#include <QtWebKit>
#include <QtDebug>

#include "TransferManager.h"
#include "BrowserEmbed.h"
#include "SettingsDialog.h"
#include "chat/ChatRoster.h"
#include "AppWidget.h"
#include "config.h"

DDPSFrame::DDPSFrame(QWidget *parent)
	: QWidget(parent)
{
	//log_file = new QFile("./ddps.log");
	//log_file->open(QIODevice::WriteOnly | QIODevice::Append);
	//log = new QDebug(log_file);
	chat = new ChatWindowRoster(this);
	
	tabs = new DDPSTabbed;
	tabs->show();

	News = new QPushButton(QString("&News"));
	News->show();
	Settings = new QPushButton(QString("&Settings"));
	Settings->show();
	Support = new QPushButton(QString("S&upport"));
	Support->show();
	InstaMessenger = new QPushButton(QString("&Chat"));
	InstaMessenger->show();

	connect(News,				SIGNAL(clicked()), this, SLOT(GotoNewsTab())	);
	connect(Settings,			SIGNAL(clicked()), this, SLOT(SettingsDialog())	);
	connect(Support,			SIGNAL(clicked()), this, SLOT(GotoSupport())	);
	connect(InstaMessenger,		SIGNAL(clicked()), this, SLOT(OpenChat())		);

	QHBoxLayout *buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(News);
	buttonLayout->addWidget(Settings);
	buttonLayout->addWidget(Support);
	buttonLayout->addWidget(InstaMessenger);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(tabs);
	mainLayout->addLayout(buttonLayout);

	setLayout(mainLayout);
	setWindowTitle(tr("Digital Distribution and Publishing Service"));
}

DDPSTabbed::DDPSTabbed(QWidget *parent)
	: QTabWidget(parent)
{
#ifdef BUILTIN_BROWSER
	Home = new DDPSBrowser;
	Home->home = QUrl(HOMEPAGE);
	Home->GotoHomepage();
	addTab(Home, tr("Browser"));
#endif

#ifdef COMMUNITY_PORTAL
	Community = new DDPSBrowser;
	Community->home = QUrl(COMMUNITYPAGE);
	Community->GotoHomepage();
	addTab(Community, tr("Community"));
#endif

#ifdef DOWNLOADER
	Downloads = new TransferManager;
	addTab(Downloads, tr("Downloads"));
#endif
}

void DDPSFrame::SettingsDialog()
{
	qDebug() << "Open the Settings Dialog";
	settings_widget = new SettingsWidget;
	settings_widget->exec();
}

void DDPSFrame::OpenChat()
{
	qDebug() << "Open the Chat Dialog";
	chat->show();
}

void DDPSFrame::GotoNewsTab()
{
	qDebug() << "Go To the News Page";
#ifdef BUILTIN_BROWSER
	if ( tabs )
	{
		if (tabs->Home->browser)
		{
			tabs->Home->browser->load(QUrl(NEWSPAGE));
		}
		tabs->setCurrentIndex(0);
	}
#endif
}

void DDPSFrame::GotoSupport()
{
	qDebug("Go to the Support Page");
#ifdef BUILTIN_BROWSER
	if ( tabs )
	{
		if (tabs->Home->browser)
		{
			tabs->Home->browser->load(QUrl(SUPPORTPAGE));
		}
		tabs->setCurrentIndex(0);
	}
#else
	return;
#endif
}

void DDPSFrame::GotoHomepage()
{
	qDebug("Go to the Home page");
#ifdef BUILTIN_BROWSER
	tabs->setCurrentIndex(0);
#endif
}

void DDPSFrame::GotoCommunity()
{
	qDebug("Go to the Community Page");
#ifdef BUILTIN_BROWSER
	tabs->setCurrentIndex(1);
#elif COMMUNITY_PORTAL
	tabs->setCurrentIndex(0);
#endif
}


void DDPSFrame::GotoDownloads()
{
	qDebug("Go to the Downloads Tab");
#ifdef BUILTIN_BROWSER
	tabs->setCurrentIndex(2);
#elif COMMUNITY_PORTAL
	tabs->setCurrentIndex(1);
#else
	tabs->setCurrentIndex(0);
#endif
}
