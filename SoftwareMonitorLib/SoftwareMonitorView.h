/**
 * @file SoftwareMonitorView.h
 * @author Ryan's Server
 *
 *
 */

#ifndef SOFTWAREMONITORPROJECT_SOFTWAREMONITORLIB_SOFTWAREMONITORVIEW_H
#define SOFTWAREMONITORPROJECT_SOFTWAREMONITORLIB_SOFTWAREMONITORVIEW_H

#include "SoftwareMonitor.h"
#include <wx/dcbuffer.h>



/**
 * View class for our window
 */
class SoftwareMonitorView : public wxWindow
{
private:

    /// The program we are viewing
    SoftwareMonitor mSoftwareMonitor;

    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent &event);


public:
    void Initialize(wxFrame *parent);
    void RefreshStatus();
    void AddProgram(wxString filePath);
    void OnLeftDown(wxMouseEvent &event);
    void OnDoubleClick(wxMouseEvent &event);
};

#endif //SOFTWAREMONITORPROJECT_SOFTWAREMONITORLIB_SOFTWAREMONITORVIEW_H
