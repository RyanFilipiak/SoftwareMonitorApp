/**
 * @file ProgramDialog.h
 * @author Ryan's Server
 *
 *
 */

#ifndef SOFTWAREMONITORPROJECT_SOFTWAREMONITORLIB_PROGRAMDIALOG_H
#define SOFTWAREMONITORPROJECT_SOFTWAREMONITORLIB_PROGRAMDIALOG_H

class Program;


class ProgramDialog : public wxDialog
{
private:
    void OnOK(wxCommandEvent& event);
    void OnInitDialog(wxInitDialogEvent& event);

    /// Program we are editing
    Program *mProgram = nullptr;

    /// Change program aspects
    wxTextCtrl* nameField; // The programs name
    wxTextCtrl* imageField; // change path to new image/bitmap
    wxTextCtrl* pathField; // the program's path

    /// dialog buttons
    wxButton* changePathButton; // change path button
    wxButton* changeImageButton; // change image button


public:
    ProgramDialog(wxWindow *parent, Program * program);
    void OnChangePath(wxCommandEvent &event);
    void OnChangeImage(wxCommandEvent &event);
    void OnRestartProgram(wxCommandEvent &event);
    void OnRemoveProgram(wxCommandEvent &event);
};

#endif //SOFTWAREMONITORPROJECT_SOFTWAREMONITORLIB_PROGRAMDIALOG_H
