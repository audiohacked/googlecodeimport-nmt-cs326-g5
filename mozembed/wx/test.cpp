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
#include <wx/wx.h>

class MyFrame : public wxFrame
{
public:
    MyFrame(int width, int height);
    void LoadURI(wxString& uri);
protected:
    void Go(wxCommandEvent&);
    void TitleChanged(wxCommandEvent&);
    void StatusChanged(wxCommandEvent&);
    void LocationChanged(wxCommandEvent&);

    wxMozView* browser;
    wxTextCtrl* txtLocation_;
    wxButton* btnGo_;

    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_COMMAND(wxID_ANY, wxEVT_MOZVIEW_TITLE_CHANGED, MyFrame::TitleChanged)
EVT_COMMAND(wxID_ANY, wxEVT_MOZVIEW_LOCATION_CHANGED, MyFrame::LocationChanged)
EVT_COMMAND(wxID_ANY, wxEVT_MOZVIEW_STATUS_CHANGED, MyFrame::StatusChanged)
END_EVENT_TABLE()

MyFrame::MyFrame(int w, int h)
    : wxFrame(0, -1, wxString("wx_mozembed Test", wxConvUTF8), wxDefaultPosition, wxDefaultSize)
{
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
    this->txtLocation_ = new wxTextCtrl(this, -1, wxString("http://", wxConvUTF8), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    this->txtLocation_->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(MyFrame::Go), 0, this);

    this->btnGo_ = new wxButton(this, -1, wxString("Go", wxConvUTF8));
    this->btnGo_->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::Go), 0, this);

    hbox->Add(txtLocation_, 1, wxEXPAND|wxRIGHT, 5);
    hbox->Add(btnGo_);

    vbox->Add(hbox, 0, wxEXPAND, 5);

    browser = new wxMozView(this, w, h);

    vbox->Add(browser, 1, wxEXPAND|wxALL, 5);

    this->SetSizer(vbox);
    this->CreateStatusBar();
}

void MyFrame::LoadURI(wxString& uri)
{
    browser->LoadURI(uri);
}

void MyFrame::Go(wxCommandEvent&)
{
    browser->LoadURI(this->txtLocation_->GetValue());
}

void MyFrame::TitleChanged(wxCommandEvent& event)
{
    this->SetTitle(event.GetString());
}

void MyFrame::StatusChanged(wxCommandEvent& event)
{
    this->SetStatusText(event.GetString());
}

void MyFrame::LocationChanged(wxCommandEvent& event)
{
    this->txtLocation_->SetValue(event.GetString());
}


class TestApp : public wxApp
{
public:
    virtual bool OnInit();
};

bool TestApp::OnInit()
{
    MyFrame* frame = new MyFrame(1024, 768);
    frame->Show();
    wxString uri = wxString("http://google.com", wxConvUTF8);
    frame->LoadURI(uri);
    SetTopWindow(frame);
    return true;
}

IMPLEMENT_APP(TestApp)

