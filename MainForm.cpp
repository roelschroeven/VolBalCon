//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#pragma link "TrescoUtilLib.lib"

#include <TrescoUtilLib.h>

#include "MainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------

GUID OUR_VOLUME_CHANGE_CONTEXT = { 0xfbf3e7b5, 0x601, 0x4a33, { 0xb2, 0x89, 0x4d, 0x85, 0x07, 0x3ba, 0xfb6 } };

__fastcall TFormMain::TFormMain(TComponent* Owner)
  : TForm(Owner)
{
  TComPtr<IMMDeviceEnumerator> Enumerator(uuidof<MMDeviceEnumerator>(), uuidof<IMMDeviceEnumerator>());

  IMMDevice *pDev;
  COM_CHECKED(Enumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDev));
  TComPtr<IMMDevice> DefaultDevice(pDev);

  IAudioEndpointVolume *pVol;
  COM_CHECKED(DefaultDevice->Activate(uuidof<IAudioEndpointVolume>(), CLSCTX_ALL, NULL, (void**)&pVol));
  m_VolumeControl = pVol;

  m_VolumeCallback = new TVolumeCallback(&OnVolumeChange);
  m_VolumeControl->RegisterControlChangeNotify(m_VolumeCallback.get());

  CreateChannelControls();
  InitControlPositions();
}
//---------------------------------------------------------------------------

__fastcall TFormMain::~TFormMain()
{
  m_VolumeControl->UnregisterControlChangeNotify(m_VolumeCallback.get());
}
//---------------------------------------------------------------------------

void TFormMain::CreateChannelControls()
{
  UINT NrChannels;
  COM_CHECKED(m_VolumeControl->GetChannelCount(&NrChannels));
  if (NrChannels < 1)
    NrChannels = 1;

  if (m_ChannelSliders.empty())
    m_ChannelSliders.push_back(TrackBarChannel0);

  if (NrChannels < m_ChannelSliders.size())
    {
    for (unsigned i = NrChannels; i < m_ChannelSliders.size(); ++i)
      delete m_ChannelSliders[i];
    m_ChannelSliders.resize(NrChannels);
    }
  else if (NrChannels > m_ChannelSliders.size())
    {
    for (unsigned i = m_ChannelSliders.size(); i < NrChannels; ++i)
      {
      TTrackBar *pTrackBar = new TTrackBar(this);
      pTrackBar->Parent = TrackBarChannel0->Parent;
      pTrackBar->Orientation = TrackBarChannel0->Orientation;
      pTrackBar->Width = TrackBarChannel0->Width;
      pTrackBar->Height = TrackBarChannel0->Height;
      pTrackBar->OnChange = TrackBarChannel0->OnChange;
      pTrackBar->Min = TrackBarChannel0->Min;
      pTrackBar->Max = TrackBarChannel0->Max;
      pTrackBar->Frequency = TrackBarChannel0->Frequency;
      pTrackBar->PageSize = TrackBarChannel0->PageSize;
      pTrackBar->ThumbLength = TrackBarChannel0->ThumbLength;
      pTrackBar->TickMarks = TrackBarChannel0->TickMarks;
      pTrackBar->TickStyle = TrackBarChannel0->TickStyle;

      pTrackBar->Top = TrackBarChannel0->Top;
      pTrackBar->Left = TrackBarChannel0->Left + i * TrackBarChannel0->Width;
      pTrackBar->Tag = i;

      m_ChannelSliders.push_back(pTrackBar);
      }
    }

  GroupBoxChannels->Width = 2 * TrackBarChannel0->Left + NrChannels * TrackBarChannel0->Width;
  ClientWidth = GroupBoxChannels->Left + GroupBoxChannels->Width + GroupBoxMaster->Left;
}
//---------------------------------------------------------------------------

void TFormMain::InitControlPositions()
{
  TrackBarMaster->Position = 100 - GetMasterVolume() * 100;
  for (UINT i = 0; i < m_ChannelSliders.size(); ++i)
    m_ChannelSliders[i]->Position = 100 - GetChannelVolume(i) * 100;
}
//---------------------------------------------------------------------------

void TFormMain::OnVolumeChange(GUID EventContext, bool bMuted, float MasterVolume, unsigned NrChannels, float ChannelVolumes[])
{
  if (EventContext == OUR_VOLUME_CHANGE_CONTEXT)
    return;

  if (std::max(NrChannels, 1U) != m_ChannelSliders.size())
    CreateChannelControls();

  TrackBarMaster->Position = 100 - 100 * MasterVolume;
  for (unsigned i = 0; i < NrChannels; ++i)
    {
    if (i < m_ChannelSliders.size())
      m_ChannelSliders[i]->Position = 100 - 100 * ChannelVolumes[i];
    }
}
//---------------------------------------------------------------------------

float TFormMain::GetMasterVolume()
{
  float Volume;
  COM_CHECKED(m_VolumeControl->GetMasterVolumeLevelScalar(&Volume));
  return Volume;
}

void TFormMain::SetMasterVolume(float Volume)
{
  COM_CHECKED(m_VolumeControl->SetMasterVolumeLevelScalar(Volume, &OUR_VOLUME_CHANGE_CONTEXT));
}

float TFormMain::GetChannelVolume(UINT Channel)
{
  float Volume;
  COM_CHECKED(m_VolumeControl->GetChannelVolumeLevelScalar(Channel, &Volume));
  return Volume;
}

void TFormMain::SetChannelVolume(UINT Channel, float Volume)
{
  COM_CHECKED(m_VolumeControl->SetChannelVolumeLevelScalar(Channel, Volume, &OUR_VOLUME_CHANGE_CONTEXT));
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TrackBarMasterChange(TObject *Sender)
{
  SetMasterVolume(0.01 * (100 - TrackBarMaster->Position));
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TrackBarChannelChange(TObject *Sender)
{
  TTrackBar *TrackBar = dynamic_cast<TTrackBar*>(Sender);
  if (!TrackBar)
    return;

  unsigned Channel = TrackBar->Tag;
  SetChannelVolume(Channel, 0.01 * (100 - TrackBar->Position));
}
//---------------------------------------------------------------------------

