//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#pragma message "End of auto-included header files"
//---------------------------------------------------------------------------

#include <vector>
#include <Endpointvolume.h>

#include "ComPtr.h"
#include "VolumeCallback.h"

class TFormMain : public TForm
{
__published:	// IDE-managed Components
  TGroupBox *GroupBoxMaster;
  TTrackBar *TrackBarMaster;
  TGroupBox *GroupBoxChannels;
  TTrackBar *TrackBarChannel0;
  void __fastcall TrackBarMasterChange(TObject *Sender);
  void __fastcall TrackBarChannelChange(TObject *Sender);

private:	// User declarations
  TComPtr<IAudioEndpointVolume> m_VolumeControl;
  TComPtr<IAudioEndpointVolumeCallback> m_VolumeCallback;
  void OnVolumeChange(GUID EventContext, bool bMuted, float MasterVolume, unsigned NrChannels, float ChannelVolumes[]);

  std::vector<TTrackBar*> m_ChannelSliders;
  void CreateChannelControls();
  void InitControlPositions();
  void PositionWindow();

  float GetMasterVolume();
  void SetMasterVolume(float Volume);
  float GetChannelVolume(UINT Channel);
  void SetChannelVolume(UINT Channel, float Volume);

public:		// User declarations
  __fastcall TFormMain(TComponent* Owner);
  __fastcall ~TFormMain();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
