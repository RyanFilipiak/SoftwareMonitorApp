/**
 * @file SoftwareMonitor.cpp
 * @author Ryan's Server
 */

#include "SoftwareMonitor.h"
#include "pch.h"
#include <algorithm>

using namespace std;

/**
 * SoftwareMonitor Constructor
 */
SoftwareMonitor::SoftwareMonitor()
{
    // eventually come through here and all save processes here
}

/**
 * Calculate max number of boxes per row
 * @param windowWidth window width
 * @param boxWidth box width
 * @param horizontalSpacing horizontal spacing
 * @return max number of boxes
 */
int SoftwareMonitor::CalcMaxUnits(int windowWidth, int boxWidth, int horizontalSpacing)
{
    return floor(windowWidth / (boxWidth + horizontalSpacing));
}

/**
 * Find how many units are free to use per row
 * @param vecSize size of the vector
 * @param itemsUsed items used
 * @param maxUnits total units per row
 * @return return the total units free
 */
int SoftwareMonitor::Available(int vecSize, int &itemsUsed, int maxUnits)
{
    int units = 0;
    if ((vecSize - itemsUsed) > maxUnits)
    {
        units = maxUnits;
        itemsUsed = itemsUsed + maxUnits;
    }
    else
    {
        units = vecSize - itemsUsed;
        itemsUsed = itemsUsed + (vecSize - itemsUsed);
    }

    return units;
}

/**
 * Get the edge distance b
 * @param windowWidth window width
 * @param boxWidth box width
 * @param horizontalSpacing horizontal spacing
 * @param freeUnits units available for this row
 * @return distance between edges
 */
int SoftwareMonitor::GetEdgeDistance(int windowWidth, int boxWidth, int horizontalSpacing, int freeUnits)
{
    // calculate the edge distance here
    int maxSpacing = windowWidth - (((boxWidth + horizontalSpacing) * freeUnits) - horizontalSpacing);
    return maxSpacing/2;;
}

/**
 * Draw the software
 * @param dc The device context to draw on
 * @param gc graphics
 * @param width width of window
 * @param height height of the window
 */
void SoftwareMonitor::OnDraw(std::shared_ptr<wxGraphicsContext> gc, wxDC *dc, int width, int height)
{
    wxString widthText = wxString::Format(wxT("Width: %d"), width);
    wxString heightText = wxString::Format(wxT("Height: %d"), height);

    dc->SetTextForeground(*wxBLACK);
    dc->DrawText(widthText, 10, 10); // Adjust the position as needed
    dc->DrawText(heightText, 10, 30); // Adjust the position as needed


    // Define the dimensions of each box
    int boxWidth = 100;
    int boxHeight = 100;

    // Define the horizontal and vertical spacing between boxes
    int horizontalSpacing = 175;
    int verticalSpacing = 175;


    // initialize helper variables
    int currBoxNum = 0;
    int itemsUsed = 0; // total number of boxes printed out of the total
    int vecSize = mPrograms.size(); // size of the vector
    int maxUnits = CalcMaxUnits(width, boxWidth, horizontalSpacing);

    if (maxUnits == 0) { return; }


    // Define the initial position for the first box
    int freeUnits = Available(vecSize, itemsUsed, maxUnits);
    int x = GetEdgeDistance(width, boxWidth, horizontalSpacing, freeUnits);
    int y = 50;

    // remove everything below this line
    int temp = x;
    wxString maxItemsInRow = wxString::Format(wxT("Item in row: %d"), maxUnits);
    dc->DrawText(maxItemsInRow, 10, 50); // Adjust the position as needed

    wxString tempUsed = wxString::Format(wxT("Edge Distance: %d"), temp);
    dc->DrawText(tempUsed, 10, 70); // Adjust the position as needed


    for (auto& program : mPrograms)
    {
        if ((currBoxNum % maxUnits == 0) && (currBoxNum != 0))
        {
            // new row means we need to update some things:
            // - y the value
            // - restart the x spacing value
            // - given the current size of all the programs, how many can be drawn in this row
            y = y + verticalSpacing;

            // we now need to reset x
            // to fix the issue we need to pass in different variables that we will calculate before
            freeUnits = Available(vecSize, itemsUsed, maxUnits);
            x = GetEdgeDistance(width, boxWidth, horizontalSpacing, freeUnits);

        }

        // Draw the program at the current position
        program->Draw(gc, dc, x, y, boxWidth, boxHeight);

        // update the x value
        x = x + boxWidth + horizontalSpacing;

        currBoxNum++;
    }


}



/**
 * Add a program to the vector of existing programs
 * @param program the shared pointer of the program object
 */
void SoftwareMonitor::AddProgram(std::shared_ptr<Program> program)
{
    if (NoDuplicatePrograms(program) == false)
    {
        mPrograms.push_back(program);
    }

}

/**
 * Verify current program isn't in the vector; avoids duplicates
 * @param program the shared pointer of the program object
 */
bool SoftwareMonitor::NoDuplicatePrograms(std::shared_ptr<Program> newProgram)
{
    for (auto program : mPrograms)
    {
        if ((newProgram->GetFileName() == program->GetFileName()) && (newProgram->GetPath() == program->GetPath()))
        {
            return false;
            /// make sure this is set to true
        }
    }
    return false;
}



/**
 * Test an x,y click location to see if it clicked
 * on some item in the game.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<Program> SoftwareMonitor::HitTest(int x, int y)
{
    for (auto i = mPrograms.rbegin(); i != mPrograms.rend();  i++)
    {
        if ((*i)->HitTest(x, y))
        {
            return *i;
        }
    }

    return  nullptr;
}


/**
 * Handle a mouse click
 * @param x X location clicked on
 * @param y Y location clicked on
 */
void SoftwareMonitor::OnLeftDown(int x, int y)
{

    mClickedOn = HitTest(x, y);
    if (mClickedOn != nullptr)
    {
        mClickedOn->Click(x, y);
    }
}

/**
 * Handle a double mouse click
 * @param x X location clicked on
 * @param y Y location clicked on
 * @param window pointer to GameView
 */
void SoftwareMonitor::OnDoubleClick(int x, int y, wxWindow* window)
{
    mClickedOn = HitTest(x, y);
    if (mClickedOn != nullptr)
    {
        mClickedOn->DoubleClick(x, y, window);
    }
}

/**
 * Remove program from vector
 * @param program
 */
void SoftwareMonitor::RemoveProgram(Program * program)
{
    std::shared_ptr<Program> toRemove = nullptr;

    for (auto programToFind : mPrograms)
    {
        if ((programToFind->GetFileName() == program->GetFileName()) && (programToFind->GetPath() == program->GetPath()))
        {
            toRemove = programToFind;
        }
    }


    if (toRemove == nullptr) { return; }

    auto loc = find(std::begin(mPrograms), std::end(mPrograms), toRemove);
    if (loc != std::end(mPrograms))
    {
        mPrograms.erase(loc);
    }

}



