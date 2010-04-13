#ifndef __PLUGIN_STYLE_H
#define __PLUGIN_STYLE_H

#include <QWindowsStyle>
#include <QDebug>
class QPalette;

class SimpleStyle : public QWindowsStyle
{
	Q_OBJECT

public:
	SimpleStyle() {
		qDebug() << "Loaded Custom DDPS Style";
	};

	void polish(QPalette &palette);
};

#include <QStylePlugin>

class QStringList;
class QStyle;

class DDPSStylePlugin : public QStylePlugin
{
public:
	DDPSStylePlugin() {};
	QStringList keys() const;
	QStyle *create(const QString &key);
};

#endif 