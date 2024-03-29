/**
 * @file Program.h
 * @author Ryan's Server
 *
 * File that represents a program or file
 */

#ifndef SOFTWAREMONITORPROJECT_SOFTWAREMONITORLIB_PROGRAM_H
#define SOFTWAREMONITORPROJECT_SOFTWAREMONITORLIB_PROGRAM_H

#include <wx/graphics.h>

class SoftwareMonitor;

/**
 * Base class for any program
 */
class Program
{
private:
    /// The exe this item is contained in (its parent)
    SoftwareMonitor *mSoftwareMonitor = nullptr;

    /// The string of the path
    wxString mFilePath;

    /// File Name
    wxString mFileName;

    /// Image path
    wxString mImagePath;

    /// Programs location on the screen
    double  mX = 0;     ///< X location for the center of the item
    double  mY = 0;     ///< Y location for the center of the item

    /// Programs area
    double mArea = 0;

    /// Program's dimensions
    double mWidth = 0;
    double mHeight = 0;

    /// The program image
    std::shared_ptr<wxImage> mProgramImage = nullptr;

    /// Bit map display for the item
    wxGraphicsBitmap mProgramBitmap;

public:

    /// Default constructor (disabled)
    Program() = delete;

    /// Copy constructor (disabled)
    Program(const Program &) = delete;

    /// Assignment operator
    void operator=(const Program &) = delete;

    Program(SoftwareMonitor *monitor, wxString filePath);
    void Draw(std::shared_ptr<wxGraphicsContext> gc, wxDC *dc, int x, int y, int boxWidth, int boxHeight);
    void OnMouseClick(wxMouseEvent &event);
    bool HitTest(double x, double y);
    void Click(double x, double y);
    void DoubleClick(double x, double y, wxWindow *window);
    void Program::RemoveProgram(Program *);
    void SetImage(wxString filepath);
    void DrawImage(std::shared_ptr<wxGraphicsContext> gc, wxDC *dc, int x, int y, int boxWidth, int boxHeight);

    /**
     * Get the File name
     * @return: file name
     */
     wxString Program::GetFileName() { return mFileName; }

    /**
    * Get the files path
     * @return: file path
    */
    wxString Program::GetPath() { return mFilePath; }


    wxString Program::GetImage() { return mImagePath; }

};

#endif //SOFTWAREMONITORPROJECT_SOFTWAREMONITORLIB_PROGRAM_H
