#ifndef __APP_MAIN_H
#define __APP_MAIN_H
	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif

	#include <wx/utils.h>
	#include <wx/choicebk.h>

	#include <wx/notebook.h>
	#include <wx/panel.h>
	
	#include "config.h"

	#include "AppMenu.h"
	#include "BrowserEmbed.h"
	#include "TransferManager.h"
	#include "SettingsDialog.h"

	class sApp : public wxApp
	{
		public:
			virtual bool OnInit();
	};

	class sAppFrame : public wxFrame
	{
		public:
			sAppFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
			void OnExit( wxCommandEvent &event);
			void AboutBox(wxCommandEvent &event);
			void SettingsDialog(wxCommandEvent &event);

			DECLARE_EVENT_TABLE()
	};
	
	class sAppTabbed : public wxNotebook
	{
		public:
			sAppTabbed(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style);
			sAppBrowser *Home;
			sAppBrowser *Community;

			DECLARE_EVENT_TABLE()
	};
	
	class sAppPanel : public wxPanel
	{
		public:
			sAppPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style);

			void GotoNewsTab(wxCommandEvent&);
			void GotoSupport(wxCommandEvent&);
			sAppTabbed *tabs;

			DECLARE_EVENT_TABLE()
	};

	#include <wx/filesys.h>
	#include <wx/fs_inet.h>
	#include <wx/fs_zip.h>
	#include <wx/fs_mem.h>

	#include <wxmozilla/wxMozillaProtocolHandler.h>
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
