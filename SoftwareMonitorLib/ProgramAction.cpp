/**
 * @file ProgramAction.cpp
 * @author Ryan's Server
 */

#include "ProgramAction.h"
#include "pch.h"
#include "ProgramDialog.h"
#include "Program.h"

void ProgramAction::SetParent(Program *program)
{
    mProgram = program;
}

void ProgramAction::EditProgram(wxWindow* window)
{

    ProgramDialog dlg(window, this);
    if(dlg.ShowModal() == wxID_OK)
    {
        // box is pulled up through double-clicking
    }

// use project 2 of cse 335 machine dialogue class to understand what to add
}


/**
  * Remove the program from the vector
  * @return Program to be removed
  */
void ProgramAction::RemoveProgram()
{
    mProgram->RemoveProgram(mProgram);
}


/**
  * Set the new path for image
  * @param newImagePath path to new iamge
  */
void ProgramAction::SetImage(wxString newImagePath)
{
    mProgram->SetImage(newImagePath);
}