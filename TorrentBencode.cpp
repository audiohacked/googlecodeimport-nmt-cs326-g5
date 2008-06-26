#include "TorrentBencode.h"

std::string read_until(wxFileInputStream &file, wxDataInputStream &data, char stop);
void read_string(wxFileInputStream &file, wxDataInputStream &data, int len, std::string &ret);

int wx_bdecode(wxFileInputStream &file, wxDataInputStream &data, entry &ret, int depth)
{
	char myByte;
	wxString padding(wxT(""));
	if (depth >= 100)
	{
		return 0;
	}
	if (file.Eof())
	{
		return 0;
	}
	switch(file.Peek())
	{
		case 'i':
			{
				if (file.Peek() == 'i') data.Read8();
				ret = entry(entry::int_t);
				std::string val = read_until(file, data, 'e');
				ret.integer() = boost::lexical_cast<entry::integer_type>(val);
				if (file.Peek() == 'e') data.Read8();
				wxLogMessage(wxT("num: ")+wxString(val.c_str(), wxConvUTF8));
			}
			break;

		case 'l':
			{
				if (file.Peek() == 'l') data.Read8();
				ret = entry(entry::list_t);
				while (file.Peek() != 'e')
				{
					ret.list().push_back(entry());
					entry& list = ret.list().back();
					wx_bdecode(file, data, list, depth + 1);
				}
				if (file.Peek() == 'e') data.Read8();
			}
			break;

		case 'd':
			{
				if (file.Peek() == 'd') data.Read8();
				ret = entry(entry::dictionary_t);
				while (file.Peek() != 'e')
				{
					entry key;
					wx_bdecode(file, data, key, depth + 1);
					if (key.type() != entry::string_t)
					{
						return 0;
					}

					entry dict;
					wx_bdecode(file, data, dict, depth + 1);
					ret.dict().insert(std::pair<std::string, entry>(key.string(), dict));
				}
				if (file.Peek() == 'e')  data.Read8();
			}
			break;

		default:
			if(isdigit(file.Peek()))
			{
				ret = entry(entry::string_t);
				std::string len_s = read_until(file, data, ':');
				if (file.Peek() == ':') data.Read8();
				int len = std::atoi(len_s.c_str());
				read_string(file, data, len, ret.string());
			}
			else
			{
				return 0;
			}
			break;
	}// switch
}

std::string read_until(wxFileInputStream &file, wxDataInputStream &data, char stop)
{
	std::string ret;
	if (file.Eof()) return ret;
	while (file.Peek() != stop)
	{
		ret += file.Peek();
		data.Read8();
		if (file.Eof()) return ret;
	}
	return ret;
}

void read_string(wxFileInputStream &file, wxDataInputStream &data, int len, std::string &ret)
{
	wxString str = wxT("");
	for (int i = 0; i < len; ++i)
	{
		if (file.Eof()) return;
		//str.Append(wxString::FromAscii(file.Peek()));
		ret += file.Peek();
		data.Read8();
	}
	//ret = str.ToAscii();
}

void wx_bencode(wxDataOutputStream &out_data, wxTextOutputStream &out_text, entry e)
{
	switch(e.type())
	{
		case entry::int_t:
			out_data.Write8('i');
			out_text.WriteString( wxString::Format(wxT("%u"), e.integer()) );
			out_data.Write8('e');
			break;

		case entry::string_t:
			out_text.WriteString( wxString::Format(wxT("%u"), e.string().length()) );
			out_data.Write8(':');
			for (int i=0; i<e.string().length(); ++i)
			{
				out_data.Write8( e.string().at(i) );
			}
			break;

		case entry::list_t:
			out_data.Write8('l');
			for (entry::list_type::const_iterator i = e.list().begin(); i != e.list().end(); ++i)
			{
				wx_bencode(out_data, out_text, *i);
			}
			out_data.Write8('e');
			break;

		case entry::dictionary_t:
			out_data.Write8('d');
			for (entry::dictionary_type::const_iterator i = e.dict().begin(); i != e.dict().end(); ++i)
			{
				out_text.WriteString( wxString::Format(wxT("%u"), i->first.length()) );
				out_data.Write8(':');
				for (int j=0; j < i->first.length(); ++j)
				{
					out_data.Write8( i->first.at(j) );
				}
				wx_bencode(out_data, out_text, i->second);
			}
			out_data.Write8('e');
			break;

		default:
			break;
	}
}
