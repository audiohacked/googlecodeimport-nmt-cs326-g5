#include "TransferCommon.h"

template <class T>
void call_destructor(T* o)
{
	o->~T();
}

void download_list::construct(handle_list_type t)
{
	switch(t)
	{
		case torrent_list_t:
			new(data) torrent_list_type;
			break;
		case http_list_t:
			new(data) http_list_type;
			break;
		default:
			break;
	}
	m_type = t;
}

void download_list::copy(download_list const& l)
{
	switch (l.type())
	{
		case torrent_list_t:
			new(data) torrent_list_type(l.torrent_list());
			break;
		case http_list_t:
			new(data) http_list_type(l.http_list());
			break;
		default:
			break;
	}
	m_type = l.type();
}

void download_list::destruct()
{
	switch(m_type)
	{
		case torrent_list_t:
			call_destructor(reinterpret_cast<torrent_list_type*>(data));
			break;
		case http_list_t:
			call_destructor(reinterpret_cast<http_list_type*>(data));
			break;
		default:
			break;
	}
	m_type = undefined_t;
}

download_list::handle_list_type download_list::type() const
{
	return m_type;
}

download_list::torrent_list_type& download_list::torrent_list()
{
	if (m_type == undefined_t) construct(torrent_list_t);
	return *reinterpret_cast<torrent_list_type*>(data);
}

download_list::torrent_list_type const& download_list::torrent_list() const
{
	return *reinterpret_cast<const torrent_list_type*>(data);
}

download_list::http_list_type& download_list::http_list()
{
	if (m_type == undefined_t) construct(http_list_t);
	return *reinterpret_cast<http_list_type*>(data);
}

download_list::http_list_type const& download_list::http_list() const
{
	return *reinterpret_cast<const http_list_type*>(data);
}

download_list::download_list() : m_type(undefined_t)
{
	
}

download_list::download_list(handle_list_type t) : m_type(undefined_t)
{
	construct(t);
}

download_list::download_list(download_list const& l) : m_type(undefined_t)
{
	copy(l);
}

download_list::download_list(torrent_list_type const& v) : m_type(undefined_t)
{
	new(data) torrent_list_type(v);
	m_type = torrent_list_t;
}

download_list::download_list(http_list_type const& v) : m_type(undefined_t)
{
	new(data) http_list_type(v);
	m_type = http_list_t;
}

download_list::~download_list()
{
	destruct(); 
}

/*bool download_list::operator==(download_list const& l) const
{
	if (m_type != l.m_type) return false;

	switch(m_type)
	{
		case torrent_list_t:
			return torrent_list() == l.torrent_list();
		case http_list_t:
			return http_list() == l.http_list();
		default:
			return true;
	}
}*/

void download_list::operator=(const torrent_list_type& l)
{
	destruct();
	copy(l);
}

void download_list::operator=(const http_list_type& l)
{
	destruct();
	copy(l);
}

