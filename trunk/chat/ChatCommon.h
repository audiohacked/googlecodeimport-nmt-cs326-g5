#ifndef __CHAT_COMMON_H
#define __CHAT_COMMON_H

	#include <QtGui>
	#include <string>
	
	#include <client.h>
	#include <gloox.h>
	using namespace gloox;

	QTreeWidgetItem findTreeItem(QTreeWidget* pTreeWidget, const QTreeWidgetItem& root, const QString& text);
#endif
