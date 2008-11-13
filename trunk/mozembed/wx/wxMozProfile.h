#ifndef __WXMOZPROFILE_H__
#define __WXMOZPROFILE_H__

#include <wx/wx.h>

class wxMozProfile
{
public:
    wxMozProfile();
    wxMozProfile(const wxString& profilePath);
    virtual ~wxMozProfile();
    
    wxString GetStringPref(const wxString& key) const;
    void     SetStringPref(const wxString& key, const wxString& value);
    int      GetIntPref(const wxString& key) const;
    void     SetIntPref(const wxString& key, int value);
    bool     GetBoolPref(const wxString& key) const;
    void     SetBoolPref(const wxString& key, bool value);

private:
    class Impl;
    Impl* impl_;
};


#endif /* __WXMOZPROFILE_H__ */
