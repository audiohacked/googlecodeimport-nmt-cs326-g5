#include <QtGui>

#include <boost/lexical_cast.hpp>

#include <libtorrent/session.hpp>

#include "TorrentProperties.h"

TorrentProperties::TorrentProperties(QString const& title, libtorrent::torrent_handle &h, QWidget *parent)
	: QDialog(parent), i(h.get_torrent_info()), handle(h)
{
	s = h.status();
	
	TorrentInformation();
	TorrentCreator();

	QVBoxLayout *mLayout = new QVBoxLayout;
	QGridLayout *iLayout = new QGridLayout;
	QGridLayout *cLayout = new QGridLayout;
	

	iLayout->addWidget(tor_name_label, 		0, 0);
	iLayout->addWidget(tor_name, 			0, 1);
	iLayout->addWidget(tor_size_label, 		1, 0);
	iLayout->addWidget(tor_size, 			1, 1);
	iLayout->addWidget(tor_tracker_label, 	2, 0);
	iLayout->addWidget(tor_tracker, 		2, 1);
	iLayout->addWidget(tor_hash_label, 		3, 0);
	iLayout->addWidget(tor_hash, 			3, 1);
	iLayout->addWidget(tor_secure_label, 	4, 0);
	iLayout->addWidget(tor_secure, 			4, 1);
	iLayout->addWidget(tor_comment_label, 	5, 0);
	iLayout->addWidget(tor_comment, 		5, 1);

	cLayout->addWidget(tor_creator_label, 	0, 0);
	cLayout->addWidget(tor_creator, 		0, 1);
	cLayout->addWidget(tor_date_label, 		1, 0);
	cLayout->addWidget(tor_date, 			1, 1);

	mLayout->addWidget(tor_header_info);
	mLayout->addWidget(iLayout);
	mLayout->addWidget(tor_header_creator);
	mLayout->addWidget(cLayout);

	setLayout(mLayout);
}

TorrentProperties::~TorrentProperties()
{
	
}

void TorrentProperties::TorrentInformation()
{
	tor_header_info = new QLabel(tr("Torrent Information"));
	tor_name_label = new QLabel(tr("Name: "));
	tor_name = new QLabel(tr(handle.name().c_str()));


	tor_size_label = new QLabel(tr("Size: "));
	tor_size = new QLabel(tr(""));
	if (i.total_size() > 1000)
		if (i.total_size() > 1000000)
			if (i.total_size() > 1000000000) 
				tor_size->setText(QString::sprintf("%i Files, %d GBytes", i.num_files(), i.total_size()/1000000000));
			else tor_size->setText(wxString::sprintf("%i Files, %d MBytes", i.num_files(), i.total_size()/1000000));
		else tor_size->setText(wxString::sprintf("%i Files, %d KBytes", i.num_files(), i.total_size()/1000));
	else tor_size->setText(wxString::sprintf("%i Files, %d Bytes", i.num_files(), i.total_size()));


	tor_tracker_label = new QLabel(tr("Trackers: "));
	tor_tracker = new QLineEdit(tr(""));
	QString tracker_str("");
	for (std::vector<libtorrent::announce_entry>::const_iterator j=i.trackers().begin(); j < i.trackers().end(); ++j)
	{
		tracker_str += QString((*j).url.c_str()) + tr("\n");
	}
	tor_tracker->setText(tracker_str);


	tor_hash_label = new QLabel(tr("Hash: "));
	tor_hash = new QLabel(QString(boost::lexical_cast<std::string>(i.info_hash()).c_str()));


	tor_secure_label = new QLabel(tr("Secure: "));
	tor_secure = new QLabel(tr(""));
	if (i.priv())
		tor_secure->setText(tr("Private Torrent"));
	else
		tor_secure->setText(tr("Public Torrent"));


	tor_comment_label = new QLabel(tr("Comment: "));
	tor_comment = new QLineEdit(QString(i.comment().c_str()));
}

//#include <boost/date_time/gregorian/gregorian.hpp>
//#include <boost/date_time/posix_time/posix_time.hpp>
//#include <iostream>
void TorrentProperties::TorrentCreator()
{
	tor_header_creator = new QLabel(tr("Created By"));
	tor_creator_label = new QLabel(tr("Creator: "));
	tor_creator = new QLabel(tr("N/A"));
	//QString(i.creator().c_str(), wxConvUTF8)
	
	tor_date_label = new QLabel(tr("Date: "));
	tor_date = new QLabel(tr(""));
	//std::string date_str = to_simple_string(i.creation_date().get());
	//tor_date.setText( QString(date_str.c_str()) );
}
