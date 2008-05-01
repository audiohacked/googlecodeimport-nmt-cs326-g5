#ifndef __WX_MOZILLA_BROWSER_H__
#define __WX_MOZILLA_BROWSER_H__
/*
 * wxWindows Mozilla Component
 * Copyright 2001 (c) Jeremiah Cornelius McCarthy. All Rights Reserved.
 * 
 * Author: Jeremiah Cornelius McCarthy
 * Created: January 24th, 2001
 * Licence: wxWindows License
 */

/* wxwindow includes */
#include "wx/defs.h"
#include "wx/window.h"
#ifdef __WXMAC__
#include <Carbon/Carbon.h>
#endif

// forward declarations
class wxMozillaBrowserChrome;
struct wxMozillaBrowserInterface;
class wxMozillaDialogs;
class nsIHTMLEditor;
class nsIDOMDocument;
class nsIAppShell;

//macros for testing wxMozilla version
#define wxMOZ_MAJOR_VERSION    0
#define wxMOZ_MINOR_VERSION    5
#define wxMOZ_RELEASE_NUMBER   6

/*  check if the current version is at least major.minor.release */
#define wxMOZILLA_CHECK_VERSION(major,minor,release) \
    (wxMOZ_MAJOR_VERSION > (major) || \
    (wxMOZ_MAJOR_VERSION == (major) && wxMOZ_MINOR_VERSION > (minor)) || \
    (wxMOZ_MAJOR_VERSION == (major) && wxMOZ_MINOR_VERSION == (minor) \
     && wxMOZ_RELEASE_NUMBER >= (release)))


//forward declaration of function needed by wxPython
void wxMozillaInitResourceModule();

extern const wxChar *wxMozillaBrowserNameStr;
/**
 * wxWindows Mozilla browser component
 */
class wxMozillaBrowser: public wxWindow
{
	friend class wxMozillaDialogs;
	friend class wxMozillaBrowserChrome;

private:
	DECLARE_DYNAMIC_CLASS(wxMozillaBrowser)
protected:
	class wxMozillaBrowserChrome *Chrome;

    wxMozillaBrowserInterface *m_Mozilla;

	static int gNumInstances;

	//Mozilla events
	void OnLocationChange();
	void OnStatusChange();
	void OnRightClick();

    WXWidget m_macControl;
    bool m_needParent;
    bool m_acceptsFocus;
	wxString m_status;
	bool m_isEditable;
	bool m_isBusy;
    wxString m_title;

    // private wxMozilla functions:
    static bool IsEmbeddingInitialized();
    static bool EnsureEmbedding();

    friend class wxMozillaSettings;

public:

	wxMozillaBrowser();
	wxMozillaBrowser(wxWindow *parent, wxWindowID id,
		const wxPoint &pos = wxDefaultPosition,
		const wxSize &size = wxDefaultSize,
		long style = 0,
        	const wxString &name = wxMozillaBrowserNameStr);

	virtual ~wxMozillaBrowser();

	bool Create(wxWindow *parent, wxWindowID id,
		const wxPoint &pos = wxDefaultPosition,
		const wxSize &size = wxDefaultSize,
		long style = 0,
	       	const wxString &name = wxMozillaBrowserNameStr);

	virtual bool LoadURL(const wxString &location);
	wxString GetURL();

	bool SavePage(const wxString &filename, bool saveFiles=TRUE);
	bool IsBusy();
	bool GoBack();
	bool CanGoBack();
	bool GoForward();
	bool CanGoForward();
	bool Stop();
	bool Reload();
	bool Find(const wxString &searchString, bool matchCase = FALSE, bool matchWholeWord = FALSE, bool wrapAround = TRUE, bool searchBackwards = FALSE);
	bool FindNext();
	wxString GetStatus();
	wxString GetSelection();

    #ifdef __WXGTK__
    virtual void SetFocus();
    #endif
    
	void OnSize(wxSizeEvent &event);
	void OnActivate(wxActivateEvent &event);
	void OnIdle(wxIdleEvent &event);
    #ifdef __WXMAC__
        virtual void MacRedraw(WXHRGN updatergnr , long time, bool erase);
        virtual void MacEnabledStateChanged() ;
        virtual void MacSuperChangedPosition() ;
        virtual void MacVisibilityChanged() ;
        void OnPaint(wxPaintEvent &event);
        void OnMove(wxMoveEvent &event);
        void OnMouseEvent(wxMouseEvent &event);
        void OnLeftDown(wxMouseEvent &event);
        void OnSetFocus(wxFocusEvent &pEvent);
        void OnKillFocus(wxFocusEvent &pEvent);

    #endif
	wxString GetLinkMessage();
	wxString GetJSStatus();

    bool SetPage(const wxString &data);
    wxString GetPage();

    // override wxWindow's empty implementation:
    void SetTitle(const wxString &title) { m_title = title; }
    wxString GetTitle() const { return m_title; }

	//spell checker
	void StartSpellCheck();
	wxString GetNextMisspelledWord();
	wxString GetSuggestedWord();
	void ReplaceWord(wxString misspelledWord, wxString replacement, bool allOccurrences);
	void StopSpellChecker();

	DECLARE_EVENT_TABLE()

public:
	/**
		* @author David Teller <Yoric@users.sourceforge.net>
		* Sets the zoom level
		*/
        bool SetZoom(float level);
	/**
	 * @author David Teller <Yoric@users.sourceforge.net>
	 *
	 * Returns a pointer to the current document
   * @warning behaviour is non-specified if the current document is not fully loaded !
   */
        bool GetDOMDocument(nsIDOMDocument** aDocument);

#ifdef __WXMSW__
/**
 * @author Zhang Yue <zhangyue99@tsinghua.org.cn>
 * we need to override wx set focus method here
 */
void wxMozillaBrowser::SetFocus();
#endif


};

#endif
