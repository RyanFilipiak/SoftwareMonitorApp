/**
 * @file MainFrame.cpp
 * @author Ryan's Server
 */

#include "pch.h"
#include "MainFrame.h"

#include "SoftwareMonitorView.h"


/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Software Monitor", wxDefaultPosition,  wxSize( 1000,800 ));

    // Create a sizer that will lay out child windows vertically
    // one above each other
    auto sizer = new wxBoxSizer( wxVERTICAL );

    // Create the view class object as a child of MainFrame
    auto softwareView = new SoftwareMonitorView();
    softwareView->Initialize(this);

    // set the object
    mSoftwareView = softwareView;

    // Add it to the sizer
    sizer->Add(mSoftwareView,1, wxEXPAND | wxALL );

    // Set the sizer for this frame
    SetSizer( sizer );

    // Layout (place) the child windows.
    Layout();

    // create the menu
    auto menuBar = new wxMenuBar( );
    SetMenuBar( menuBar );
    CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

    // create the options on the menu
    auto programMenu = new wxMenu();
    auto helpMenu = new wxMenu();

    // label the new options
    menuBar->Append(programMenu, L"&Program Options" );
    menuBar->Append(helpMenu, L"&Help");

    // add sub-options (in drop down)
    programMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");
    programMenu->Append(wxID_REFRESH, "&Refresh", "Refresh Status of Programs");
    programMenu->Append(wxID_ADD, "&Add Program", "Add A Program");

    // bind specific functions with their sub-menu options
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnRefresh, this, wxID_REFRESH);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAdd, this, wxID_ADD);

}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * Refresh status of all programs added in interface
 * @param event
 */
void MainFrame::OnRefresh(wxCommandEvent& event)
{
    // iterate over all items in mPrograms vector from mProgramMain
    mSoftwareView->RefreshStatus();
    Refresh();
}

/**
 * Add a program to the list of programs
 * @param event
 */
void MainFrame::OnAdd(wxCommandEvent& event)
{
    // we need to way to prompt the user for a path

    // Create a file dialog
    wxFileDialog openFileDialog(this, _("Select a file"), "", "",
                                "Executable files (*.exe)|*.exe",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    // Show the file dialog
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return; // If the user canceled the dialog, return without doing anything

    // Get the selected file path
    wxString filePath = openFileDialog.GetPath();

    // Now you have the filePath, you can add it to your list of programs
    mSoftwareView->AddProgram(filePath);

    Refresh();
}




