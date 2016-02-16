//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Util.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

void EnsureOnScreen(TForm *Form)
{
  HMONITOR hMonitor = MonitorFromWindow(Form->Handle, MONITOR_DEFAULTTONEAREST);
  MONITORINFO MonitorInfo;
  memset(&MonitorInfo, 0, sizeof(MonitorInfo));
  MonitorInfo.cbSize = sizeof(MonitorInfo);
  GetMonitorInfo(hMonitor, &MonitorInfo);
  TRect WorkArea = MonitorInfo.rcWork;

  if (Form->Left + Form->Width > WorkArea.Right)
    Form->Left = WorkArea.Right - Form->Width;
  if (Form->Top + Form->Height > WorkArea.Bottom)
    Form->Top = WorkArea.Bottom - Form->Height;
  if (Form->Left < WorkArea.Left)
    Form->Left = WorkArea.Left;
  if (Form->Top < WorkArea.Top)
    Form->Top = WorkArea.Top;
  /*
  Left = PrimMonitorRect.Right - Width - GetSystemMetrics(SM_CXSIZEFRAME);
  Top = PrimMonitorRect.Bottom - Height - GetSystemMetrics(SM_CYSIZEFRAME);
  */
}

