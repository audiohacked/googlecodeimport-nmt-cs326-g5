#ifndef __BROWSER_EMBED_H
#define __BROWSER_EMBED_H
	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif
	
	#include <wx/filesys.h>
	#include <wx/fs_inet.h>
	#include <wx/fs_zip.h>
	#include <wx/fs_mem.h>

	#include <wxmozilla/wxMozillaBrowser.h>
	#include <wxmozilla/wxMozillaProtocolHandler.h>

	class sAppBrowser : public wxPanel
	{
		public:
			sAppBrowser(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size);
			wxMozillaBrowser *browser;
			wxString home;
			void GotoHomepage(void);
			
		private:
			void OnPrev(wxCommandEvent& event);
			void OnNext(wxCommandEvent& event);
			void OnStop(wxCommandEvent& event);
			void OnRefresh(wxCommandEvent& event);
			void OnHome(wxCommandEvent& event);
			
			DECLARE_EVENT_TABLE()
			
	};


	class ddpsProtocolHandler : public wxFSProtocolHandler
	{
		public:
			ddpsProtocolHandler(const wxString scheme) : wxFSProtocolHandler(scheme)
			{}
			
			~ddpsProtocolHandler()
			{}
			
			static wxProtocolHandler* Create(const wxString scheme)
			{
				return new ddpsProtocolHandler(scheme);
			}
			
			const wxString NewURI(const wxString spec, const wxString base)
			{

				if(base.IsEmpty()||spec.StartsWith(wxT("ddps://")))
					return spec;

				wxString mutable_base = base;
				const int slash_position = base.Find(wxT('/'), TRUE);

				if(slash_position>7)
					if(!((base[slash_position-1]=='/')&&(base[slash_position-2]==':')))
						mutable_base = base.Mid(0,slash_position);
					else
						mutable_base = base;
				else
					mutable_base = base;

				if (!spec.StartsWith(wxT("/")))
					mutable_base=mutable_base+wxT('/');

				return mutable_base+spec;
			}

			wxProtocolChannel* OpenChannel(const wxString uri)
			{    
				wxString after;
				uri.StartsWith(wxT("ddps://"), &after); 

				return wxFSProtocolHandler::OpenChannel(after);
			}

		protected:
			wxFileSystem mFileSystem;

	};

#endif


