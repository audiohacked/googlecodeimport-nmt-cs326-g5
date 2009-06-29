#ifndef __BROWSER_EMBED_H
#define __BROWSER_EMBED_H
	#include <QtWebKit>

	class DDPSBrowserView;
	class DDPSTabbed;
	class TransferManager;
	class DDPSBrowser : public QWidget
	{
		Q_OBJECT
		public:
			DDPSBrowser(DDPSTabbed *f, QWidget *parent = 0);
			void GotoHomepage();
			QUrl home;
			DDPSBrowserView *browser;
			DDPSTabbed *frame;
		public slots:
			void OnPrev();
			void OnNext();
			void OnStop();
			void OnRefresh();
			void OnHome();
		private:
			//void linkClicked(const QUrl &url);
			//void loadStarted();
	};

	class DDPSBrowserView : public QWebView
	{
		Q_OBJECT
		public:
			DDPSBrowserView(DDPSTabbed *f, QWidget *parent =0);
			DDPSBrowser *browserWidget;
			DDPSTabbed *frame;
		public slots:
			void myProtocol(const QUrl &url);
		signals:
			void linkClicked(const QUrl &url);
		private:
			QUrl myurl;
	};

#endif


