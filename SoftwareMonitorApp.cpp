/**
 * @file SoftwareMonitorApp.cpp
 * @author Ryan's Server
 */

#include "pch.h"
#include "SoftwareMonitorApp.h"

#ifdef WIN32
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#endif

#include <MainFrame.h>

/**
 * Initialize the application.
 * @return
 */
bool SoftwareMonitorApp::OnInit()
{

    if (!wxApp::OnInit())
        return false;


    // Add image type handlers
    wxInitAllImageHandlers();


    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    return true;




}