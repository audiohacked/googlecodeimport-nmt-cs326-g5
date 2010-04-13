#include <QtGui>
#include <QtWebKit>
#include "downloader/TransferManager.h"
#include "AppWidget.h"
#include "BrowserEmbed.h"
#include "config.h"

DDPSBrowser::DDPSBrowser(DDPSTabbed *f, QWidget *parent) 
: QWidget(parent)
{
	frame = f;
	browser = new DDPSBrowserView(f, parent);
	
	QPushButton *back, *forward, *refresh, *stop, *home;
	
	back 	= new QPushButton(tr("Back"));
	back->show();
	
	forward = new QPushButton(tr("Forward"));
	forward->show();
	
	refresh = new QPushButton(tr("Refresh"));
	refresh->show();
	
	stop 	= new QPushButton(tr("Stop"));
	stop->show();
	
	home 	= new QPushButton(tr("Home"));
	home->show();

	connect(back,		SIGNAL(clicked()), this, SLOT(OnPrev())		);
	connect(forward,	SIGNAL(clicked()), this, SLOT(OnNext())		);
	connect(refresh,	SIGNAL(clicked()), this, SLOT(OnRefresh())	);
	connect(stop,		SIGNAL(clicked()), this, SLOT(OnStop())		);
	connect(home,		SIGNAL(clicked()), this, SLOT(OnHome())		);
	
	QVBoxLayout *mainLayout = new QVBoxLayout;
	QHBoxLayout *buttonLayout = new QHBoxLayout;

	buttonLayout->addWidget(back);
	buttonLayout->addWidget(forward);
	buttonLayout->addWidget(refresh);
	buttonLayout->addWidget(stop);
	buttonLayout->addWidget(home);

	mainLayout->addLayout(buttonLayout);
	mainLayout->addWidget(browser);
	setLayout(mainLayout);
	browser->show();
}

DDPSBrowserView::DDPSBrowserView(DDPSTabbed *f, QWidget *parent)
	:QWebView(parent)
{
	frame = f;
	page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
	connect(page(), SIGNAL(linkClicked(const QUrl &)), this, SLOT(myProtocol(const QUrl &)) );
	page()->settings()->setAttribute(QWebSettings::AutoLoadImages, true);
	page()->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
	page()->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
}

void DDPSBrowser::OnPrev()
{
	if (browser->history()->canGoBack())
	{
		browser->back();		
	}
}
void DDPSBrowser::OnNext()
{
	if ( browser->history()->canGoForward() )
	{
		browser->forward();
	}
}
void DDPSBrowser::OnStop()
{
	browser->stop();
}
void DDPSBrowser::OnRefresh()
{
	browser->reload();
}

void DDPSBrowser::OnHome()
{
	browser->load(home);
}

void DDPSBrowser::GotoHomepage()
{
	browser->load(home);	
}

void DDPSBrowserView::myProtocol(const QUrl &url)
{
	QUrl newurl = url;
	if (url.scheme() == tr("ddps"))
	{
		if (url.host() == tr("browser"))
		{
			/*
			QString str = QString("browser: http:/")+url.path();
			QMessageBox msgBox;
			msgBox.setText(str);
			msgBox.setStandardButtons(QMessageBox::Ok);
			msgBox.setDefaultButton(QMessageBox::Ok);
			msgBox.exec();
			*/
			newurl = QUrl(tr("http:/")+url.path());
		}
		else if (url.host() == tr("torrentdownload"))
		{
			QString tracker;
			QString hash;
			QRegExp regex("(\\w+)@(.*)$");

			if (regex.indexIn(url.path()) != -1)
			{
				tracker = regex.cap(2);
				hash = regex.cap(1);
			}

			QString str = QString("torrent tracker: ")+tracker+QString("\n hash: ")+hash;
			//frame->Downloads->add_item_tor();
			/*QMessageBox msgBox;
			msgBox.setText(str);
			msgBox.setStandardButtons(QMessageBox::Ok);
			msgBox.setDefaultButton(QMessageBox::Ok);
			msgBox.exec();*/
			return;
		}
		else if (url.host() == tr("httpdownload"))
		{
			QString str = QString("http download: http:/")+url.path();
			QUrl newurl = QUrl(tr("http:/")+url.path());
			/*QMessageBox msgBox;
			msgBox.setText(str);
			msgBox.setStandardButtons(QMessageBox::Ok);
			msgBox.setDefaultButton(QMessageBox::Ok);
			msgBox.exec();*/
			frame->Downloads->add_item_http(frame->Downloads->media_installed, newurl);
			return;
		}
	}
	setUrl(newurl);
	emit linkClicked(newurl);
}
/*
void DDPSBrowser::BeforeLoad(wxCommandEvent &event)
{
	wxURL url(event.GetURL());
	if (url.GetScheme() == wxString("ddps", wxConvUTF8))
	{
		event.Cancel();
		wxLogDebug(wxString("DDPS Protocol Intercepted -- ", wxConvUTF8) + event.GetURL());
		if (url.GetServer() == wxString("browser", wxConvUTF8))
		{
			//wxLogDebug(wxT("http:/")+url.GetPath());
			browser->LoadURL( wxT("http:/")+url.GetPath() );
		} 
		else if (url.GetServer() == wxString("torrentDownload", wxConvUTF8))
		{
			wxString hash = url.GetPath().AfterFirst(wxChar('/')).BeforeFirst(wxChar('@'));
			wxString tracker = url.GetPath().AfterFirst(wxChar('@'));
			//wxLogDebug(wxT("DDPS Protocol Torrent Hash -- ") + hash);
			//wxLogDebug(wxT("DDPS Protocol Torrent Tracker -- ") + tracker);
			wxGetApp().frame->panel->tabs->Downloads->listDownloads->AddTorrentDownload( hash.mb_str(), tracker.mb_str(), hash.mb_str() );
			//wxGetApp().frame->panel->tabs->Downloads->listDownloads->AddTorrentFileDownload("original.torrent");
		}
		else if (url.GetServer() == wxString("httpDownload", wxConvUTF8))
		{
			wxString addr = wxString("http:/", wxConvUTF8)+url.GetPath();
			//wxGetApp().frame->panel->tabs->Downloads->listDownloads->httpDownloads->AddDownload( addr );
		}
	}
}
*/
