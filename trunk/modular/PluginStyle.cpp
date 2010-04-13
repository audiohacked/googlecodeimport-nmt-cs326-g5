/* 
QApplication::setStyle(new CustomStyle);
*/
#include <QtGui>
#include "PluginStyle.h"

void SimpleStyle::polish(QPalette &palette)
{
    palette.setBrush(QPalette::Button, Qt::red);
}

QStringList DDPSStylePlugin::keys() const
{
	return QStringList() << "DDPS";
}

QStyle *DDPSStylePlugin::create(const QString &key)
{
	if (key.toLower() == "ddps")
		return new SimpleStyle;
	return 0;
}

Q_EXPORT_PLUGIN2(ddpsstyleplugin, DDPSStylePlugin)