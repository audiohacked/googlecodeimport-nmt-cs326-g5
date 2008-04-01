#ifndef __WX_MOZILLA_SETTINGS_H__
#define __WX_MOZILLA_SETTINGS_H__

/* wxwindow includes */
#include "wx/defs.h"
#include "wx/string.h"

class wxMozillaSettingsData;
class wxMozillaBrowser;
class nsIPrefBranch;

class wxMozillaSettings
{
public:
    /*
     * Sets the profile path for the browser.
     *
     * Profilepath is directory where Mozilla stores its settings. You should
     * call this function as soon as possible and set the path to directory
     * specific to your application. If you don't call this function:
     *
     *     1. Settings, cookies, etc. are discarded when the application exits
     *     2. The SSL handler will crash as soon as you try to visit an HTTPS
     *        site
     *
     * @param path
     *     Path in which to store profile information.
     *
     * @return
     *     true on success, false on failure.
     */
    static bool SetProfilePath(const wxString &path);
    static wxString GetProfilePath() { return ms_profilePath; }
    
    /**
     * Sets the path to Mozilla runtime directory. Must be called before
     * first instance of wxMozillaBrowser is created. By default, current directory
     * is used on Windows and the directory where Mozilla was during compilation
     * on Unix.
     *
     * @param path
     * 	Path to Mozilla runtime
     */
	static void SetMozillaPath(const wxString &path);
    static wxString GetMozillaPath() { return ms_mozillaPath; }

    static void SetBoolPref(const wxString& name, bool value);
    static bool GetBoolPref(const wxString& name);
    static void SetStrPref(const wxString& name, const wxString& value);
    static wxString GetStrPref(const wxString& name);
    static void SetIntPref(const wxString& name, int value);
    static int GetIntPref(const wxString& name);

    static void SavePrefs();

private:
    static nsIPrefBranch *GetPrefBranch();
    static void CleanUp();
    
    friend void wxMozillaShutdown();
    
    static wxMozillaSettingsData *ms_data;
    static wxString ms_profilePath, ms_mozillaPath;
};

#endif
