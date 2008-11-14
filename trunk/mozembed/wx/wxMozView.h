#ifndef __WXMOZVIEW_H__
#define __WXMOZVIEW_H__

#include <wx/wx.h>
#include <wx/validate.h>

class wxMozViewListener;
class nsIInterfaceRequestor;

DECLARE_EVENT_TYPE(wxEVT_MOZVIEW_TITLE_CHANGED, -1)
DECLARE_EVENT_TYPE(wxEVT_MOZVIEW_STATUS_CHANGED, -1)
DECLARE_EVENT_TYPE(wxEVT_MOZVIEW_LOCATION_CHANGED, -1)

class WXDLLEXPORT wxMozView : public wxPanel
{
public:
    wxMozView(wxWindow* parent = 0, 
              wxWindowID id = wxID_ANY,
              unsigned int flags = 0,
              const wxPoint& pos = wxDefaultPosition,
              const wxSize& size = wxDefaultSize,
              long style = 0,
              const wxValidator& validator = wxDefaultValidator);
    
    virtual ~wxMozView();
    
    void Init();
    
    bool Create(wxWindow* parent = 0, 
                wxWindowID id = wxID_ANY,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = 0,
                const wxValidator& validator = wxDefaultValidator);
    virtual bool Show(bool state = true);
    void LoadURI(const wxString& uri);
    void LoadURI(const char* uri);
    void GetInterfaceRequestor(nsIInterfaceRequestor** requestor);
    wxString EvaluateJavaScript(const wxString& script);
protected:
    void CreateBrowser();
    void OnResize(wxSizeEvent& event);
    virtual wxMozView* OpenWindow(unsigned int flags);
    
    unsigned int flags_;
    
    class Impl;
    Impl* impl_;
    
    friend class wxMozViewListener;

    DECLARE_DYNAMIC_CLASS(wxMozView)
    DECLARE_NO_COPY_CLASS(wxMozView)
    DECLARE_EVENT_TABLE()
};

#endif /* __WXMOZVIEW_H__ */
