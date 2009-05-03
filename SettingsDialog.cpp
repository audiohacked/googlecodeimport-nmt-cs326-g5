#include <QtGui>
#include "AppConfig.h"
#include "SettingsDialog.h"

//constructor for the settings frame
SettingsWidget::SettingsWidget(QWidget *parent) 
: QDialog(parent)
{
	settings_cfg = new DDPSConfig;

	//define ok and cancel buttons
	QPushButton *Ok_Button = new QPushButton(tr("Accept"), this);
	connect(Ok_Button, SIGNAL(clicked()), this, SLOT(accept()));

	QPushButton *Cancel_Button = new QPushButton(tr("Cancel"), this);
	connect(Cancel_Button, SIGNAL(clicked()), this, SLOT(reject()));

	//define download directory label and control
	downloadLocation = new QLineEdit(settings_cfg->cfg_download_location, this);
	QLabel* downloadLocationLabel = new QLabel ( tr("Download Location:"), this );

	//download/upload speed label and control
	downloadSpeed = new QSpinBox(this);
	downloadSpeed->setValue(settings_cfg->cfg_download_speed);
	downloadSpeed->setRange( -1, 5000);
	QLabel* downloadSpeedLabel = new QLabel ( tr("Max Download Speed (KBytes/s):"), this );

	uploadSpeed = new QSpinBox ( this );
	uploadSpeed->setValue(settings_cfg->cfg_upload_speed);
	uploadSpeed->setRange(-1, 5000);
	QLabel* uploadSpeedLabel = new QLabel ( tr("Max Upload Speed (KBytes/s):"), this );
	
	//number of peers label and control
	numPeers = new QSpinBox ( this );
	numPeers->setValue(settings_cfg->cfg_max_peers);
	numPeers->setRange(-1, 5000);
	QLabel* numPeersLabel = new QLabel ( tr("Max Number of Peers:"), this );	

	QVBoxLayout *mLayout = new QVBoxLayout;
	QVBoxLayout *sLayout = new QVBoxLayout;
	QHBoxLayout *bLayout = new QHBoxLayout;

	bLayout->addWidget(Ok_Button);
	bLayout->addWidget(Cancel_Button);

	sLayout->addWidget(downloadLocationLabel); 
	sLayout->addWidget(downloadLocation);
	sLayout->addWidget(downloadSpeedLabel); 
	sLayout->addWidget(downloadSpeed);
	sLayout->addWidget(uploadSpeedLabel); 
	sLayout->addWidget(uploadSpeed);
	sLayout->addWidget(numPeersLabel); 
	sLayout->addWidget(numPeers);

	mLayout->addLayout(sLayout);
	mLayout->addLayout(bLayout);

	setLayout(mLayout);
}

void SettingsWidget::SaveSettings()
{
	settings_cfg->cfg_download_location = downloadLocation->text();
	settings_cfg->cfg_download_speed = downloadSpeed->value();
	settings_cfg->cfg_upload_speed = uploadSpeed->value();
	settings_cfg->cfg_max_peers = numPeers->value();
	settings_cfg->Save();
}

void SettingsWidget::accept()
{
	SaveSettings();
	done(QDialog::Accepted);
}