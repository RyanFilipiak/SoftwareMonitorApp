/**
 * @file MainFrame.h
 * @author Ryan's Server
 *
 * The top level (main) frame of the application
 */

#ifndef SOFTWAREMONITORPROJECT_SOFTWAREMONITORLIB_MAINFRAME_H
#define SOFTWAREMONITORPROJECT_SOFTWAREMONITORLIB_MAINFRAME_H

class SoftwareMonitorView;

/**
 * The top-level (main) frame of the application
 */
class MainFrame: public wxFrame
{
private:
    /// View class for the program
    SoftwareMonitorView *mSoftwareView;

    void OnExit(wxCommandEvent &event);
    void OnRefresh(wxCommandEvent &event);
    void OnAdd(wxCommandEvent &event);

public:

    void Initialize();
};

#endif //SOFTWAREMONITORPROJECT_SOFTWAREMONITORLIB_MAINFRAME_H
