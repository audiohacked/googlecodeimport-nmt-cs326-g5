#ifndef __APP_TASKBAR_BALLOON_H
#define __APP_TASKBAR_BALLOON_H

	#include <wx/frame.h>
	#include <wx/string.h>
	#include <wx/timer.h>

class TaskBarBaloon : public wxFrame
{
    public:
        TaskBarBaloon(wxString sTitle, wxString sMessage);
        virtual ~TaskBarBaloon() { delete timer; }
 
        /** painting bg */
        void OnPaint(wxPaintEvent& event);
        /** timer to close window */
        void OnTimerTick(wxTimerEvent & event);
        /** click on the baloon */
        void OnClick(wxMouseEvent & event);
 
        /** display the baloon and run the timer */
        void showBaloon(unsigned int iTimeout);
    private:
        wxTimer * timer;
 
        DECLARE_EVENT_TABLE();
 
};

#endif
