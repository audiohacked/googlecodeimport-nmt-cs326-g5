#ifndef __DDPS_PROTOCOL_H
#define __DDPS_PROTOCOL_H

	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif

	#include <wxmozilla/wxMozillaProtocolHandler.h>

	#include <wx/filesys.h>
	#include <wx/fs_inet.h>
	#include <wx/fs_zip.h>
	#include <wx/fs_mem.h>
	
	class ddpsProtocolHandler : public wxFSProtocolHandler
	{
		public:
			ddpsProtocolHandler(const wxString scheme);
			~ddpsProtocolHandler();
			
			const wxString NewURI(const wxString spec, const wxString base);
			wxProtocolChannel* OpenChannel(const wxString uri);
			static wxProtocolHandler* Create(const wxString scheme);
			
		protected:
			wxFileSystem mFileSystem;

	};
#endif