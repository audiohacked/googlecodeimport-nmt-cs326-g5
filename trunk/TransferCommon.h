#ifndef __TRANSFER_COMMON_H
#define __TRANSFER_COMMON_H
	#include <wx/wxprec.h>

	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif

	#include <wx/progdlg.h>
	
#ifdef HTTP_DOWNLOADER
	#include <wx/curl/dialog.h>
#endif

#ifdef TORRENT_DOWNLOADER
	#include <libtorrent/config.hpp>
	#include <libtorrent/session.hpp>
#endif

	#include <map>
	#include <utility>

	typedef struct {
		wxProgressDialog *dlg;
#ifdef TORRENT_DOWNLOADER
		libtorrent::torrent_handle handle;
#endif
	} torrent_data_t;

	typedef struct {
#ifdef HTTP_DOWNLOADER
		wxCurlDownloadDialog *dlg;
#endif
		long i;
	} http_data_t;
	template<int v1, int v2>
	struct max2 { enum { value = v1>v2?v1:v2 }; };

	class download_list
	{
		public:
			typedef torrent_data_t torrent_list_type;
			typedef http_data_t http_list_type;
	
			enum handle_list_type
			{
				torrent_list_t,
				http_list_t,
				undefined_t
			};
	
			handle_list_type type() const;
			
			download_list(torrent_list_type const&);
			download_list(http_list_type const&);

			download_list();
			download_list(handle_list_type t);
			download_list(download_list const& l);
			~download_list();
			
			//bool operator==(download_list const& l) const;
			
			void operator=(torrent_list_type const&);
			void operator=(http_list_type const&);
			
			torrent_list_type& torrent_list();
			const torrent_list_type& torrent_list() const;
			http_list_type& http_list();
			const http_list_type& http_list() const;

		protected:

			void construct(handle_list_type t);
			void copy(const download_list& l);
			void destruct();
		
		private:
			handle_list_type m_type;
			
			union
			{
				char data[max2<sizeof(torrent_list_type)
					, sizeof(http_list_type)>::value];
				int dummy_aligner;
			};
	};

	typedef std::map<long, download_list> download_handles_t;
	
#endif
