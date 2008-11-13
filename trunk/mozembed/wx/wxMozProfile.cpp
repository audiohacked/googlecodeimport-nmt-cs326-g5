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
 *   Krishnakumar V <v.krishnakumar@gmail.com>
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

#include "wxMozProfile.h"
#include "embed.h"
#include <stdlib.h>

class wxMozProfile::Impl
{
public:
    Impl(const char* profilePath = 0)
        : mozapp(profilePath)
        {
        }
    MozApp mozapp;
};

wxMozProfile::wxMozProfile()
{
    impl_ = new Impl();
}

wxMozProfile::wxMozProfile(const wxString& path)
{
    impl_ = new Impl(path.mb_str(wxConvUTF8));
}

wxMozProfile::~wxMozProfile()
{
    delete impl_;
}

wxString wxMozProfile::GetStringPref(const wxString& key) const
{
    char* value = 0;
    nsresult rv = impl_->mozapp.GetCharPref(key.mb_str(wxConvUTF8), &value);
    if (value)
    {
        wxString result = wxString(value, wxConvUTF8);
        free(value);
        return result;
    }
    return wxEmptyString;
}

void wxMozProfile::SetStringPref(const wxString& key, const wxString& value)
{
    nsresult rv = impl_->mozapp.SetCharPref(key.mb_str(wxConvUTF8), value.mb_str(wxConvUTF8));
}

int wxMozProfile::GetIntPref(const wxString& key) const
{
    int result = 0;
    nsresult rv = impl_->mozapp.GetIntPref(key.mb_str(wxConvUTF8), &result);
    return result;
}

void wxMozProfile::SetIntPref(const wxString& key, int value)
{
    nsresult rv = impl_->mozapp.SetIntPref(key.mb_str(wxConvUTF8), value);
}

bool wxMozProfile::GetBoolPref(const wxString& key) const
{
    PRBool result = 0;
    nsresult rv = impl_->mozapp.GetBoolPref(key.mb_str(wxConvUTF8), &result);
    return result;
}

void wxMozProfile::SetBoolPref(const wxString& key, bool value)
{
    nsresult rv = impl_->mozapp.SetBoolPref(key.mb_str(wxConvUTF8), value);
}
