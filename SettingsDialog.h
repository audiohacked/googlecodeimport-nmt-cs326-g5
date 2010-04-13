#ifndef __SETTINGS_DIALOG_H
#define __SETTINGS_DIALOG_H
	#include <QtGui>

class DDPSConfig;

class SettingsWidget : public QDialog
{	
	public:
		SettingsWidget(QWidget *parent = 0);
		~SettingsWidget();
	public slots:
		virtual void accept();
		void GetSkinListing();
		//virtual void reject();
		//void SaveSettings();
	private:
		DDPSConfig *settings_cfg;
		QLineEdit *downloadLocation;
		QSpinBox *downloadSpeed;
		QSpinBox *uploadSpeed;
		QSpinBox *numPeers;
		QComboBox *skinSelect;
		Q_OBJECT
};

#endif
