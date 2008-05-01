
#include <wx/wxprec.h>
#include <wx/filename.h>

#include "wxMozillaSettings.h"
#include "wxMozillaBrowser.h"

#include "nsString.h"
#include "nsCOMPtr.h"
#include "nsIProfile.h"
#include "nsProfileDirServiceProvider.h"
#include "nsIPrefService.h"
#include "nsIPrefBranch.h"

class wxMozillaSettingsData
{
public:
    ~wxMozillaSettingsData();

#ifndef __WXMAC__
//There seems to be some extra library needed on OS X - until then skip OS X.
    nsCOMPtr<nsProfileDirServiceProvider> m_profileDirServiceProvider;
#endif
    nsCOMPtr<nsIPrefService> m_prefService;
    nsCOMPtr<nsIPrefBranch> m_prefBranch;
};

wxMozillaSettingsData::~wxMozillaSettingsData()
{
#ifndef __WXMAC__
    if (m_profileDirServiceProvider)
    {
        m_profileDirServiceProvider->Shutdown();
        m_profileDirServiceProvider = nsnull;
    }
#endif
}


wxString wxMozillaSettings::ms_profilePath;
wxString wxMozillaSettings::ms_mozillaPath;
wxMozillaSettingsData *wxMozillaSettings::ms_data = NULL;


void wxMozillaSettings::SetMozillaPath(const wxString &path)
{
    wxASSERT_MSG( !wxMozillaBrowser::IsEmbeddingInitialized(),
                  _T("You must call SetMozillaPath before creating wxMozillaBrowser instance!") );

    wxFileName fn(path);
    fn.MakeAbsolute();
    ms_mozillaPath = fn.GetFullPath();
}


bool wxMozillaSettings::SetProfilePath(const wxString &path)
{
//TODO: figure out what needs added on OS X to get this to compile!
#ifndef __WXMAC__
    wxFileName fn(path);
    fn.MakeAbsolute();
    ms_profilePath = fn.GetFullPath();

    // If Mozilla wasn't loaded yet, postpone setting profile path:
    if (!wxMozillaBrowser::IsEmbeddingInitialized())
        return TRUE;

    if (ms_data == NULL)
        ms_data = new wxMozillaSettingsData();
    
    nsresult rv;
    nsCOMPtr<nsILocalFile> dir;
    NS_NewNativeLocalFile(nsDependentCString(ms_profilePath.mb_str(wxConvFile)),
                          PR_TRUE,
                          getter_AddRefs(dir));
    if (!dir)
        return FALSE;    
    if (!ms_data->m_profileDirServiceProvider)
    {
        nsresult rv;

        nsCOMPtr<nsIServiceManager> servMgr;
        rv = NS_GetServiceManager(getter_AddRefs(servMgr));
        if (NS_FAILED(rv))
            return FALSE;

        rv = servMgr->GetServiceByContractID
                      (
                        NS_PROFILE_CONTRACTID,
                        NS_GET_IID(nsIProfile),
                        getter_AddRefs(ms_data->m_profileDirServiceProvider)
                      );
        if (NS_FAILED(rv))
            return FALSE;
        if (!ms_data->m_profileDirServiceProvider)
            return FALSE;
        rv = ms_data->m_profileDirServiceProvider->Register();
        if (NS_FAILED(rv))
            return FALSE;
    }
    rv = ms_data->m_profileDirServiceProvider->SetProfileDir(dir);
    if (NS_FAILED(rv))
        return FALSE;
    return TRUE;
#endif
}

static NS_DEFINE_CID(kPrefServiceCID, NS_PREFSERVICE_CID);
 
/// Return nsIPrefBranch object and create it if we don't have it yet
nsIPrefBranch *wxMozillaSettings::GetPrefBranch()
{
    if (!wxMozillaBrowser::EnsureEmbedding())
        return NULL;

    if (ms_data == NULL)
        ms_data = new wxMozillaSettingsData();
    if (!ms_data->m_prefBranch)
    {
        ms_data->m_prefService = do_GetService(kPrefServiceCID);
        ms_data->m_prefBranch = do_QueryInterface(ms_data->m_prefService);
        // read default prefs files (prefs.js, user.js):
        ms_data->m_prefService->ReadUserPrefs(nsnull);
    }
    wxASSERT_MSG( ms_data->m_prefBranch, _T("failed to get nsIPrefBranch") );
    return ms_data->m_prefBranch;
}

#ifdef __WXDEBUG__
    #define CHECK_PREF_TYPE(pref, name, type, msg) \
        PRInt32 ptype; \
        pref->GetPrefType(name.ToAscii(), &ptype); \
        wxASSERT_MSG( ptype == nsIPrefBranch::type, msg );       
#else
    #define CHECK_PREF_TYPE(pref, name, type, msg)
#endif

void wxMozillaSettings::SetBoolPref(const wxString& name, bool value)
{
    nsIPrefBranch *p = GetPrefBranch();
    CHECK_PREF_TYPE(p, name, PREF_BOOL, _T("preference not bool"))
    p->SetBoolPref(name.ToAscii(), value);
}

void wxMozillaSettings::SetStrPref(const wxString& name, const wxString& value)
{
    nsIPrefBranch *p = GetPrefBranch();
    CHECK_PREF_TYPE(p, name, PREF_STRING, _T("preference not string"))
    p->SetCharPref(name.ToAscii(), value.ToAscii());
}

void wxMozillaSettings::SetIntPref(const wxString& name, int value)
{
    nsIPrefBranch *p = GetPrefBranch();
    CHECK_PREF_TYPE(p, name, PREF_INT, _T("preference not integer"))
    p->SetIntPref(name.ToAscii(), value);
}

bool wxMozillaSettings::GetBoolPref(const wxString& name)
{
    nsIPrefBranch *p = GetPrefBranch();
    CHECK_PREF_TYPE(p, name, PREF_BOOL, _T("preference not bool"))
    PRBool val;
    p->GetBoolPref(name.ToAscii(), &val);
    return val;
}

wxString wxMozillaSettings::GetStrPref(const wxString& name)
{
    nsIPrefBranch *p = GetPrefBranch();
    CHECK_PREF_TYPE(p, name, PREF_STRING, _T("preference not string"))
    char *val;
    p->GetCharPref(name.ToAscii(), &val);
    return wxString::FromAscii(val);
}

int wxMozillaSettings::GetIntPref(const wxString& name)
{
    nsIPrefBranch *p = GetPrefBranch();
    CHECK_PREF_TYPE(p, name, PREF_INT, _T("preference not integer"))
    int val;
    p->GetIntPref(name.ToAscii(), &val);
    return val;
}
    
void wxMozillaSettings::SavePrefs()
{
    if (ms_data && ms_data->m_prefService)
    {
        ms_data->m_prefService->SavePrefFile(nsnull);
    }
}
        
void wxMozillaSettings::CleanUp()
{
    delete wxMozillaSettings::ms_data;
    wxMozillaSettings::ms_data = NULL;
}
