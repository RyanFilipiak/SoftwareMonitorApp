/**
 * @file ProgramDialog.cpp
 * @author Ryan's Server
 */

#include "ProgramDialog.h"
#include "ProgramAction.h"

/**
 * Constructor
 * @param parent Parent window to put this dialog box inside
 * @param machineSystem MachineSystem we are editing
 */
ProgramDialog::ProgramDialog(wxWindow* parent, ProgramAction* program)
    : wxDialog(parent, wxID_ANY, L"Edit Program"), mProgramAction(program)
{

    // Create input fields for editing program properties
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    // Add input field for program name
    wxStaticText* nameLabel = new wxStaticText(this, wxID_ANY, wxT("Change Name:"));
    nameField = new wxTextCtrl(this, wxID_ANY);
    sizer->Add(nameLabel, 0, wxALL | wxEXPAND, 5);
    sizer->Add(nameField, 0, wxALL | wxEXPAND, 5);

    // Add Change button for selecting program path
    changePathButton = new wxButton(this, wxID_ANY, wxT("Change Path"));
    sizer->Add(changePathButton, 0, wxALL | wxEXPAND, 5);

    // Add Change button for selecting program image
    changeImageButton = new wxButton(this, wxID_ANY, wxT("Change Image"));
    sizer->Add(changeImageButton, 0, wxALL | wxEXPAND, 5);

    // Add input fields for program properties
    wxButton* restartButton = new wxButton(this, wxID_ANY, wxT("Restart Program"));
    sizer->Add(restartButton, 0, wxALL | wxEXPAND, 5);



    // Create the remove button with a red background
    wxButton* removeButton = new wxButton(this, wxID_ANY, wxT("Remove Program"));

    // Set button text color and font
    removeButton->SetForegroundColour(*wxWHITE);  // Set text color to white
    wxFont buttonFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);  // Set font to bold
    removeButton->SetFont(buttonFont);

    // Set button background color to red
    removeButton->SetBackgroundColour(*wxRED);

    // Bind events for button hover to maintain red color
    removeButton->Bind(wxEVT_ENTER_WINDOW, [removeButton](wxMouseEvent& event) {
        removeButton->SetBackgroundColour(*wxRED);
        removeButton->Refresh();
    });
    removeButton->Bind(wxEVT_LEAVE_WINDOW, [removeButton](wxMouseEvent& event) {
        removeButton->SetBackgroundColour(wxNullColour);
        removeButton->Refresh();
    });

    // Bind event for mouse leaving button to change color back to red
    removeButton->Bind(wxEVT_LEAVE_WINDOW, [removeButton](wxMouseEvent& event) {
        removeButton->SetBackgroundColour(*wxRED);
        removeButton->Refresh();
    });
//    removeButton->SetWindowStyleFlag(wxNO_BORDER);


    // Bind event for button click to remove program
    removeButton->Bind(wxEVT_BUTTON, &ProgramDialog::OnRemoveProgram, this);
    sizer->Add(removeButton, 0, wxALL | wxEXPAND, 5);

// Add OK and Cancel buttons
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* okButton = new wxButton(this, wxID_OK, wxT("OK"));
    wxButton* cancelButton = new wxButton(this, wxID_CANCEL, wxT("Cancel"));
    buttonSizer->Add(okButton, 0, wxALL, 5);
    buttonSizer->Add(cancelButton, 0, wxALL, 5);

// Add sizers to main sizer
    sizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    SetSizerAndFit(sizer);

// Bind events
    restartButton->Bind(wxEVT_BUTTON, &ProgramDialog::OnRestartProgram, this);
    changePathButton->Bind(wxEVT_BUTTON, &ProgramDialog::OnChangePath, this);
    changeImageButton->Bind(wxEVT_BUTTON, &ProgramDialog::OnChangeImage, this);
    Bind(wxEVT_BUTTON, &ProgramDialog::OnOK, this, wxID_OK);
    Bind(wxEVT_INIT_DIALOG, &ProgramDialog::OnInitDialog, this);

    /// ADD THE REST AND MAKE SURE TO HIDE THEM
    // declare the boxes to save the text
    imageField = new wxTextCtrl(this, wxID_ANY);
    imageField->Hide();
}


/**
 * Handle the OK button press event
 * @param event Button press event
 */
void ProgramDialog::OnOK(wxCommandEvent& event)
{
    if ( Validate() && TransferDataFromWindow() )
    {
        EndModal(wxID_OK);

        wxString newImagePath = imageField->GetValue();
        mProgramAction->SetImage(newImagePath);


        // Retrieve edited values and update program properties
//        newName = nameField->GetValue();
//      newPath = pathField->GetValue();


        /// ADD CONDITIONALS TO SEE IF VALUES CHANGED, IF THEY DID, CHANGE THEM

//
//        mProgramAction->setName(newName);
//        mProgramAction->SetPath(newPath);
//
//        // Close the dialog
//        EndModal(wxID_OK);        wxString newName = nameField->GetValue();
//        wxString newPath = pathField->GetValue();
//        wxString newImagePath = imageField->GetValue();
//
//        mProgramAction->setName(newName);
//        mProgramAction->setPath(newPath);
//        mProgramAction->setImagePath(newImagePath);
            // add the rest
//
//        // Close the dialog
//        EndModal(wxID_OK);

    }
}

/**
 * Initialize dialog event handler.
 *
 * This allows us to preselect the content of the edit control
 * so we don't have to do so manually to change it.
 *
 * @param event EVT_INIT_DIALOG event object
 */
void ProgramDialog::OnInitDialog(wxInitDialogEvent& event)
{
//    TransferDataToWindow();
    // Initialize the text fields with program properties
//    nameField->SetValue(mProgramAction->getName());
//    pathField->SetValue(mProgramAction->getPath());
//    imageField->SetValue(mProgramAction->getImagePath());

// add the rest

}


/**
 * Change the file path
 * @param event
 */
void ProgramDialog::OnChangePath(wxCommandEvent& event) {
    // Create a file dialog
    wxFileDialog openFileDialogPath(this, _("Select a file"), "", "",
                                "Executable files (*.exe)|*.exe",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    // Show the file dialog
    if (openFileDialogPath.ShowModal() == wxID_CANCEL)
        return; // If the user canceled the dialog, return without doing anything

    // Get the selected file path
    wxString filePath = openFileDialogPath.GetPath();

    // Update the path field with the selected file path
//    pathField->SetValue(filePath);
}
/**
 * Change the bitmap/image path
 * @param event
 */
void ProgramDialog::OnChangeImage(wxCommandEvent& event) {
    // Create a file dialog
    wxFileDialog openFileDialogImage(this, _("Select an image file"), "", "",
                                "Image files (*.bmp;*.jpg;*.png)|*.bmp;*.jpg;*.png",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    // Show the file dialog
    if (openFileDialogImage.ShowModal() == wxID_CANCEL)
        return; // If the user canceled the dialog, return without doing anything

    // Get the selected file path
    wxString imagePath = openFileDialogImage.GetPath();

    // Update the image field with the selected image path
    imageField->SetValue(imagePath);

}

/**
 * Restart the program
 * @param event
 */
void ProgramDialog::OnRestartProgram(wxCommandEvent& event)
{
    // Implement the code to restart the program here
    wxMessageBox("Restarting the program...");
}

/**
 * Delete the program
 * @param event
 */
void ProgramDialog::OnRemoveProgram(wxCommandEvent& event)
{

    Close();

    // Implement the code to remove the program here
    mProgramAction->RemoveProgram();
}
