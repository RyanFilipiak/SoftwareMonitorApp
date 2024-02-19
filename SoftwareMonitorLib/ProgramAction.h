/**
 * @file ProgramAction.h
 * @author Ryan's Server
 *
 * Main class that represents the action a class can take
 */

#ifndef SOFTWAREMONITORPROJECT_SOFTWAREMONITORLIB_PROGRAMACTION_H
#define SOFTWAREMONITORPROJECT_SOFTWAREMONITORLIB_PROGRAMACTION_H

class Program;

/**
 * Class that represents actions for program
 */
class ProgramAction
{
private:
    /// The exe this item is contained in (its parent)
    Program *mProgram = nullptr;

public:
    void SetParent(Program * program);
    void EditProgram(wxWindow* window);
    void RemoveProgram();
    void SetImage(wxString newImagePath);
};

#endif //SOFTWAREMONITORPROJECT_SOFTWAREMONITORLIB_PROGRAMACTION_H
