#ifndef __APP_FRAME_H
#define __APP_FRAME_H
	#include <QtGui>
	
	class DDPSBrowser;
	class DDPSTabbed;
	class SettingsWidget;
	class TransferManager;
	class ChatWindowRoster;

	class DDPSFrame : public QWidget
	{
		public:
			DDPSFrame(QWidget *parent = 0);
			DDPSTabbed *tabs;
			SettingsWidget *settings_widget;
			ChatWindowRoster *chat;
			//QDebug *log;
			//QFile *log_file;
		public slots:
			void GotoNewsTab();
			void SettingsDialog();
			void GotoSupport();
			void OpenChat();
			void GotoHomepage();
			void GotoCommunity();
			void GotoDownloads();
		private:
			QPushButton *News;
			QPushButton *Settings;
			QPushButton *Support;
			QPushButton *InstaMessenger;
			Q_OBJECT
	};

	class DDPSTabbed : public QTabWidget
	{
		public:
			DDPSTabbed(QWidget *parent = 0);
			DDPSBrowser *Home;
			DDPSBrowser *Community;
			TransferManager *Downloads;
		private:
	};

#endif
