#include "ChatRosterData.h"
#include "ChatWindow.h"

ChatWindowChat::ChatWindowChat(ChatContactItemData *id, QWidget *parent)
:QDialog(parent)
{
	qDebug() << "Create Chat Window";
	contact_id = id;
	
	chatText = new QTextEdit;
	//chatText->setReadOnly(true);
	
	sendText = new QLineEdit;
	//connect(sendText, SIGNAL(textChanged(const QString &)), this, SLOT(TextChanged(const QString &)));
	
	sendButton = new QPushButton(tr("Send"));
	connect(sendButton, SIGNAL(clicked()), this, SLOT(SendMsg()));

	QVBoxLayout *mLayout = new QVBoxLayout;
	QGridLayout *sendChat_layout = new QGridLayout;

	sendChat_layout->addWidget(sendText, 0, 0);
	sendChat_layout->addWidget(sendButton, 0, 1);

	mLayout->addWidget(chatText);
	mLayout->addLayout(sendChat_layout);

	setLayout(mLayout);
	contact_id->hasWin = true;
}

ChatWindowChat::~ChatWindowChat()
{	
}

void ChatWindowChat::CreateWin()
{
}

void ChatWindowChat::SendMsg()
{
	if (sendText->text() != tr(""))
	{
		qDebug() << "MsgText:" <<sendText->text();
		contact_id->chatSess->send(sendText->text().toStdString());
		chatText->append(tr("me: ") + sendText->text());
		sendText->setText(tr(""));
	}
	//qDebug() << "acknowledge receiving of a message";
	//m_messageEventFilter->raiseMessageEvent( MessageEventDelivered );
}

void ChatWindowChat::TextChanged(const QString &text)
{
	qDebug() << "user is typing a message";
	//m_messageEventFilter->raiseMessageEvent( MessageEventComposing );
}

void ChatWindowChat::reject()
{
	qDebug() << "close ChatWindowChat??";
	hide();
	done(QDialog::Rejected);
}
