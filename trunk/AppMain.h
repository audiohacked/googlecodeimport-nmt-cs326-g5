#ifndef __APP_MAIN_H
#define __APP_MAIN_H

#include <QtGui>

class DDPSConfig;
class DDPSFrame;
class SettingsWidget;

class MainAppWindow : public QMainWindow
{
public:
	MainAppWindow();
public slots:
	void logout();
	void update_app();
	void bandwidth();
	void home();
	void community();
	void downloads();
	void support();
	void app_settings();
	void about();
	void news();
	void forums();
	void open_chat();
private slots:
private:
	DDPSFrame *frame;
	SettingsWidget *settings_widget;
	QMenu *fileMenu;
	QMenu *viewMenu;
	QMenu *gameMenu;
	QMenu *helpMenu;
	QAction *FileLogoutAct;
	QAction *FileUpdateAct;
	QAction *FileSettingsAct;
	QAction *FileQuitAct;
	QAction *ViewMessengerAct;
	QAction *ViewNewsAct;
	QAction *ViewSupportAct;
	QAction *ViewForumsAct;
	QAction *ViewSettingsAct;
	QAction *ViewBandwidthAct;
	QAction *ViewHomeAct;
	QAction *ViewCommunityAct;
	QAction *ViewDownloadsAct;
	QAction *HelpSupportAct;
	QAction *HelpAboutAct;
	void createActions();
	void createMenus();
	Q_OBJECT
};

#endif
