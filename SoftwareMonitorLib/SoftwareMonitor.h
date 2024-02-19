/**
 * @file SoftwareMonitor.h
 * @author Ryan's Server
 *
 *
 */

#ifndef SOFTWAREMONITORPROJECT_SOFTWAREMONITORLIB_SOFTWAREMONITOR_H
#define SOFTWAREMONITORPROJECT_SOFTWAREMONITORLIB_SOFTWAREMONITOR_H

#include "Program.h"
#include <vector>
#include <wx/dcbuffer.h>

/**
 * The class for our software monitor app (the like foundation for it all)
 */
class SoftwareMonitor
{
private:

    /// All of the programs we are monitoring
    std::vector<std::shared_ptr<Program>> mPrograms;

    /// Program that is clicked on
    std::shared_ptr<Program> mClickedOn = nullptr;

    bool NoDuplicatePrograms(std::shared_ptr<Program> program);

public:
    SoftwareMonitor();
    void OnDraw(std::shared_ptr<wxGraphicsContext> gc, wxDC *dc, int width, int height);
    void AddProgram(std::shared_ptr<Program> program);
    int CalcMaxUnits(int windowWidth, int boxWidth, int horizontalSpacing);
    int Available(int vecSize, int &itemsUsed, int maxUnits);
    int GetEdgeDistance(int windowWidth, int boxWidth, int horizontalSpacing, int freeUnits);
    void OnLeftDown(int x, int y);
    void OnDoubleClick(int x, int y, wxWindow *window);
    std::shared_ptr<Program> HitTest(int x, int y);
    void RemoveProgram(Program *program);


};

#endif //SOFTWAREMONITORPROJECT_SOFTWAREMONITORLIB_SOFTWAREMONITOR_H
