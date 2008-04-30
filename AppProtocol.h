#ifndef __DDPS_PROTOCOL_H
#define __DDPS_PROTOCOL_H

	//#include <wxmozilla/wxMozillaProtocolHandler.h>

	#ifdef __WX_MOZILLA_PROTOCOLS_H__
	
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
#endif