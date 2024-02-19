/**
 * @file SoftwareMonitorView.cpp
 * @author Ryan's Server
 */

#include "pch.h"
#include "SoftwareMonitorView.h"
#include "Program.h"

/**
 * Initialize the aquarium view class.
 * @param parent The parent window for this class
 */
void SoftwareMonitorView::Initialize(wxFrame* parent)
{
    Create(parent, wxID_ANY);
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &SoftwareMonitorView::OnPaint, this);
    Bind(wxEVT_SIZE, &SoftwareMonitorView::OnSize, this);

    Bind(wxEVT_LEFT_DOWN, &SoftwareMonitorView::OnLeftDown, this);
    Bind(wxEVT_LEFT_DCLICK, &SoftwareMonitorView::OnDoubleClick, this);
}

// Size event handler
void SoftwareMonitorView::OnSize(wxSizeEvent& event)
{
    Refresh();  // Trigger repaint when size changes
    event.Skip();  // Allow default processing
}



/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void SoftwareMonitorView::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto gc = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    wxRect rect = GetRect();
    mSoftwareMonitor.OnDraw(gc, &dc, rect.GetWidth(), rect.GetHeight());
}

/**
 * Refresh the status of all programs
 */
void SoftwareMonitorView::RefreshStatus()
{
//    mSoftwareMonitor.CallRefresh();
    Refresh();
}


/**
 * Refresh the status of all programs
 * @param filePath path to the executable
 */
void SoftwareMonitorView::AddProgram(wxString filePath)
{
    std::shared_ptr<Program> program;
    program = std::make_shared<Program>(&mSoftwareMonitor, filePath);

    if (program != nullptr)
    {
        mSoftwareMonitor.AddProgram(program);
    }
    Refresh();
}

/**
 * Handle the left mouse button down event
 * @param event The mouse click event
 */
void SoftwareMonitorView::OnLeftDown(wxMouseEvent& event)
{
    mSoftwareMonitor.OnLeftDown(event.GetX(), event.GetY());
//    Refresh();
}


/**
 * Handle the left mouse button down event
 * @param event The mouse click event
 */
void SoftwareMonitorView::OnDoubleClick(wxMouseEvent& event)
{
    mSoftwareMonitor.OnDoubleClick(event.GetX(), event.GetY(), this);
    Refresh();
}