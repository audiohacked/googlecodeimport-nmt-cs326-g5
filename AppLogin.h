#ifndef __APP_LOGIN_DLG_H
#define __APP_LOGIN_DLG_H

#include <QtGui>
#if CRYPTO
#include <QtCrypto>
#endif

class DDPSConfig;

class AppLoginWindow : public QDialog
{
public:
	AppLoginWindow(QWidget *parent = 0);
	QString GetUsername() { return user; }
	QString GetPassword() { return pass; }

public slots:
	virtual void accept();
	//virtual void reject();
	void create_account();
	void fetch_account();
private:
	DDPSConfig *login_cfg;
	QLineEdit *username;
	QLineEdit *password;
	QCheckBox *remember;
	QString user;
	QString pass;
	Q_OBJECT
};

#endif //__APP_LOGIN_DLG_H
