/**
 * @file Program.cpp
 * @author Ryan's Server
 */

#include "Program.h"
#include "pch.h"
#include <wx/filename.h>
#include <wx/graphics.h>
#include "SoftwareMonitor.h"
#include "ProgramDialog.h"


/**
 * Constructor
 * @param monitor The software monitor this program is a member of
 * @param filePath the path of the file
 */
Program::Program(SoftwareMonitor *monitor, wxString filePath) : mSoftwareMonitor(monitor), mFilePath(filePath)
{
    wxFileName fileName(mFilePath);
    mFileName = fileName.GetFullName(); // Get the full file name with extension
}
/**
 * Draw the iamge of the program
 * @param gc graphics
 * @param dc drawing plane
 * @param x starting coordinates
 * @param y starting coordinates
 * @param boxWidth box width
 * @param boxHeight box height
 */
void Program::DrawImage(std::shared_ptr<wxGraphicsContext> gc, wxDC* dc, int x, int y, int boxWidth, int boxHeight)
{

    x = x + (boxWidth/2);
    y = y + (boxHeight/2);

    double wid = mProgramImage->GetWidth();
    double hit = mProgramImage->GetHeight();

    // Calculate the scaling factor to fit the image inside the box
    double scaleFactor = std::min(boxWidth / wid, boxHeight / hit);

    // Calculate the new width and height of the image after scaling
    int newWidth = static_cast<int>(wid * scaleFactor);
    int newHeight = static_cast<int>(hit * scaleFactor);

    // Crop and resize the image to fit the box
    wxImage croppedImage = mProgramImage->Rescale(newWidth, newHeight);

    // Draw the cropped image
    gc->DrawBitmap(croppedImage, x - newWidth / 2, y - newHeight / 2, newWidth, newHeight);
}

/**
 * Display the program
 * @param gc graphics
 * @param dc drawing plane
 * @param x starting coordinates
 * @param y starting coordinates
 * @param boxWidth box width
 * @param boxHeight box height
 */
void Program::Draw(std::shared_ptr<wxGraphicsContext> gc, wxDC* dc, int x, int y, int boxWidth, int boxHeight)
{

    // check if the bitmap is empty and the program image is NOT empty
    if (mProgramBitmap.IsNull() && (mProgramImage != nullptr))
    {
        mProgramBitmap = gc->CreateBitmapFromImage(*mProgramImage);

        // draw the image
        DrawImage(gc, dc, x, y, boxWidth, boxHeight);

    }
    // we draw the image of the
    else if ((mProgramBitmap.IsNull() != true) && (mProgramImage != nullptr))
    {
        DrawImage(gc, dc, x, y, boxWidth, boxHeight);
    }

    // draw a black box as a placeholder
    else
    {
        // Draw the box at the specified position
        dc->SetBrush(*wxBLACK_BRUSH);  // Set the brush color to black
        dc->DrawRectangle(x, y, boxWidth, boxHeight);
    }

    // set values based on window resizing
    mX = x;
    mY = y;
    mArea = boxWidth*boxHeight;
    mWidth = boxWidth;
    mHeight = boxHeight;
}


/**
 * Hit test x,y to see if they are clicking on this program.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @return true if clicked on program
 */
bool Program::HitTest(double x, double y)
{
    // Check if (x, y) falls within the boundaries of the box
    return x >= mX && x <= (mX + mWidth) && y >= mY && y <= (mY + mHeight);
}


/**
 * Handle a click on an program
 * @param x X location in the game of the click
 * @param y Y location in the game of the click
 */
void Program::Click(double x, double y) { }


/**
 * Handle a double click on an item
 * @param x X location in the game of the click
 * @param y Y location in the game of the click
* @param window pointer to GameView window
 */
void Program::DoubleClick(double x, double y, wxWindow* window)
{
    ProgramDialog dlg(window, this);
    if(dlg.ShowModal() == wxID_OK)
    {
        // box is pulled up through double-clicking
    }
}


/**
 * Remove the program from the vector
 */
void Program::RemoveProgram(Program * program)
{
    mSoftwareMonitor->RemoveProgram(this);
}
/**
 * Set the image
 * @param filepath path to the image
 */
void Program::SetImage(wxString filepath)
{

    if (!filepath.empty()) {
//         Create a temporary wxImage object
        wxImage tempImage;
        mImagePath = filepath;

//         Load the image from the file path
        if (tempImage.LoadFile(filepath, wxBITMAP_TYPE_ANY)) {
            // Assign the loaded image to mProgramImage
            mProgramImage = std::make_shared<wxImage>(tempImage);
        }
    }


}


