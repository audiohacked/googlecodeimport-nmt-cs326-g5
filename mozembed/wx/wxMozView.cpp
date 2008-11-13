/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is
 * Mozilla Corporation.
 * Portions created by the Initial Developer are Copyright (C) 2008
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Krishnakumar V (v.krishnakumar@gmail.com)
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#include "wxMozView.h"
#include "embed.h"

using namespace std;

DEFINE_EVENT_TYPE(wxEVT_MOZVIEW_TITLE_CHANGED)
DEFINE_EVENT_TYPE(wxEVT_MOZVIEW_STATUS_CHANGED)
DEFINE_EVENT_TYPE(wxEVT_MOZVIEW_LOCATION_CHANGED)

class wxMozViewListener : public MozViewListener
{
public:
    wxMozViewListener(wxMozView* view)
        : wxmozview_(view) 
        {
        }
    virtual ~wxMozViewListener() 
        {
        }
    
    void SetTitle(const char* title);
    void StatusChanged(const char* status, PRUint32 statusType);
    void LocationChanged(const char* location);
    MozView* OpenWindow(PRUint32 flags);
    void SizeTo(PRUint32 width, PRUint32 height);
    void StartModal();
    void ExitModal(nsresult result);

private:
    wxMozView* wxmozview_;
};

class wxMozView::Impl
{
public:
    Impl(wxMozView* wxmozview)
        : listener(wxmozview)
        {
            mozview.SetListener(&listener);
        }
    MozView mozview;
    wxMozViewListener listener;
    wxSize preferredSize;
};

void wxMozViewListener::SetTitle(const char* title)
{
    wxCommandEvent event(wxEVT_MOZVIEW_TITLE_CHANGED, this->wxmozview_->GetId());
    event.SetEventObject(this->wxmozview_);
    event.SetString(wxString(title, wxConvUTF8));
    this->wxmozview_->AddPendingEvent(event);
}

void wxMozViewListener::StatusChanged(const char* status, PRUint32 statusType)
{
    wxCommandEvent event(wxEVT_MOZVIEW_STATUS_CHANGED, this->wxmozview_->GetId());
    event.SetEventObject(this->wxmozview_);
    event.SetString(wxString(status, wxConvUTF8));
    event.SetInt(statusType);
    this->wxmozview_->AddPendingEvent(event);
}

void wxMozViewListener::LocationChanged(const char* location)
{
    wxCommandEvent event(wxEVT_MOZVIEW_LOCATION_CHANGED, this->wxmozview_->GetId());
    event.SetEventObject(this->wxmozview_);
    event.SetString(wxString(location, wxConvUTF8));
    this->wxmozview_->AddPendingEvent(event);
}

MozView* wxMozViewListener::OpenWindow(PRUint32 flags)
{
    wxMozView* view = wxmozview_->OpenWindow(flags);
    if (!view)
        return 0;
    return &(view->impl_->mozview);
}

void wxMozViewListener::SizeTo(PRUint32 width, PRUint32 height)
{
    std::cout << "SizeTo called! - " << width << " " << height << std::endl;
    wxmozview_->impl_->preferredSize = wxSize(width, height);
    wxmozview_->SetSize(width, height);
    //FIXME: notify parent about the size change?
}

void wxMozViewListener::StartModal()
{
    std::cout << "StartModal called!\n";
}

void wxMozViewListener::ExitModal(nsresult result)
{
    std::cout << "ExitModal called!\n";
}

IMPLEMENT_DYNAMIC_CLASS(wxMozView, wxPanel)

BEGIN_EVENT_TABLE(wxMozView, wxPanel)
EVT_SIZE(wxMozView::OnResize)
END_EVENT_TABLE()

wxMozView::wxMozView(wxWindow* parent,
                     wxWindowID id,
                     unsigned int mozflags,
                     const wxPoint& pos,
                     const wxSize& size,
                     long style,
                     const wxValidator& validator)
: wxPanel(parent, id), flags_(mozflags)
{
    Init();
    Create(parent, id, pos, size, style, validator);
}

wxMozView::~wxMozView()
{
    delete impl_;
}

void wxMozView::Init()
{
    impl_ = new Impl(this);
    //TODO: initialize the notifier here
}

bool wxMozView::Create(wxWindow* parent,
                       wxWindowID id,
                       const wxPoint& pos,
                       const wxSize& size,
                       long style,
                       const wxValidator& validator)
{
    Init();
    if (!PreCreation(parent, pos, size) ||
        !CreateBase(parent, id, pos, size, style, validator))
    {
        wxFAIL_MSG(wxT("wxMozView creation failed"));
        return false;
    }
    CreateBrowser();
    PostCreation();
    return true;
}

void wxMozView::CreateBrowser()
{
    const wxSize& size = GetSize();
#ifdef __WXGTK__
    impl_->mozview.CreateBrowser(m_wxwindow, 0, 0, size.GetWidth(), size.GetHeight(), flags_);
#endif

#ifdef WIN32
    impl_->mozview.CreateBrowser((void*)GetHandle(), 0, 0, size.GetWidth(), size.GetHeight(), flags_);
#endif
}

bool wxMozView::Show(bool state)
{
    state ? impl_->mozview.Show() : impl_->mozview.Hide();
    wxPanel::Show(state);
    return state;
}

void wxMozView::OnResize(wxSizeEvent& event)
{
    std::cout << "resizing..." << std::endl;
    const wxSize& size = event.GetSize();
    impl_->mozview.SetPositionAndSize(0, 0, size.GetWidth(), size.GetHeight());
    wxPanel::SetSize(size);
}

void wxMozView::LoadURI(const wxString& uri)
{
    impl_->mozview.LoadURI(uri.mb_str(wxConvUTF8));
}

void wxMozView::LoadURI(const char* uri)
{
    impl_->mozview.LoadURI(uri);
}

void wxMozView::GetInterfaceRequestor(nsIInterfaceRequestor** requestor)
{
    *requestor = 0;
    impl_->mozview.GetInterfaceRequestor(requestor);
}

wxString wxMozView::EvaluateJavaScript(const wxString& script)
{
    return wxString(impl_->mozview.EvaluateJavaScript(script.mb_str(wxConvUTF8)), wxConvUTF8);
}

wxMozView* wxMozView::OpenWindow(unsigned int flags)
{
    return 0;
}
