#include <QtGui>
#include "AppConfig.h"
#include "AppLogin.h"


AppLoginWindow::AppLoginWindow(QWidget *parent)
: QDialog(parent)
{
	QLabel *userText = new QLabel(tr("Account name:"), this);
	QLabel *passText = new QLabel(tr("Password: "), this);
	QLabel *fetchText = new QLabel(tr("Forgot your login info?"), this);
	QLabel *createText = new QLabel(tr("Don't have an account?"), this);
	QPushButton *Ok_button = new QPushButton(tr("Login"), this);
	QPushButton *Cancel_button = new QPushButton(tr("Cancel"), this);
	QPushButton *FetchAccount_button = new QPushButton(tr("Create a new account..."), this);
	QPushButton *CreateAccount_button = new QPushButton(tr("Fetch my lost account..."), this);
	remember = new QCheckBox(tr("Remember my password"), this);

	connect(Ok_button, SIGNAL(clicked()), this, SLOT(accept()));
	connect(Cancel_button, SIGNAL(clicked()), this, SLOT(reject()));
	connect(CreateAccount_button, SIGNAL(clicked()), this, SLOT(create_account()));
	connect(FetchAccount_button, SIGNAL(clicked()), this, SLOT(fetch_account()));

	username = new QLineEdit;
	password = new QLineEdit;
	password->setEchoMode(QLineEdit::Password);

	QHBoxLayout *uLayout = new QHBoxLayout;
	QHBoxLayout *pLayout = new QHBoxLayout;
	QHBoxLayout *bLayout = new QHBoxLayout;
	QHBoxLayout *o1Layout = new QHBoxLayout;
	QHBoxLayout *o2Layout = new QHBoxLayout;
	QVBoxLayout *mainLayout = new QVBoxLayout;

	uLayout->addWidget(userText);
	uLayout->addWidget(username);
	pLayout->addWidget(passText);
	pLayout->addWidget(password);

	bLayout->addWidget(Ok_button);
	bLayout->addWidget(Cancel_button);

	o1Layout->addWidget(createText);
	o1Layout->addWidget(CreateAccount_button);
	o2Layout->addWidget(fetchText);
	o2Layout->addWidget(FetchAccount_button);

	mainLayout->addLayout(uLayout);
	mainLayout->addLayout(pLayout);
	mainLayout->addWidget(remember);
	mainLayout->addLayout(bLayout);
	mainLayout->addSpacing(1);
	mainLayout->addLayout(o1Layout);
	mainLayout->addLayout(o2Layout);

	setLayout(mainLayout);

	login_cfg = new DDPSConfig;
	if (login_cfg->cfg_RememberLogin)
	{
		username->setText(login_cfg->cfg_LoginUsername);
		password->setText(login_cfg->cfg_LoginPassword);
		remember->setChecked(login_cfg->cfg_RememberLogin);
	}

}
void AppLoginWindow::create_account()
{
	return;
}

void AppLoginWindow::fetch_account()
{
	return;
}

void AppLoginWindow::accept()
{
	user = username->text();
	pass = password->text();
	if(remember->isChecked())
	{
			login_cfg->cfg_LoginUsername = user;
			login_cfg->cfg_LoginPassword = pass;
			login_cfg->cfg_RememberLogin = true;
	}
	login_cfg->Save();
	done(QDialog::Accepted);
}
