//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VolumeCallback.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TVolumeCallback::TVolumeCallback(TOnVolumeChange OnVolumeChange)
  : m_RefCount(0)
  , m_OnVolumeChange(OnVolumeChange)
{
}

HRESULT STDMETHODCALLTYPE TVolumeCallback::QueryInterface(const IID &iid, void **ppv)
{
  if (iid == IID_IUnknown || iid == __uuidof(IAudioEndpointVolumeCallback))
    {
    *ppv = (void*)this;
    AddRef();
    return S_OK;
    }
  else
    {
    *ppv = NULL;
    return E_NOINTERFACE;
    }
}

ULONG STDMETHODCALLTYPE TVolumeCallback::AddRef()
{
  return ++m_RefCount;
}

ULONG STDMETHODCALLTYPE TVolumeCallback::Release()
{
  if ((--m_RefCount) == 0)
    {
    delete this;
    return 0;
    }
  else
    return m_RefCount;
}

HRESULT STDMETHODCALLTYPE TVolumeCallback::OnNotify(AUDIO_VOLUME_NOTIFICATION_DATA *pNotData)
{
  if (m_OnVolumeChange)
    {
    m_OnVolumeChange(
      pNotData->guidEventContext,
      pNotData->bMuted,
      pNotData->fMasterVolume,
      pNotData->nChannels,
      pNotData->afChannelVolumes);
    }

  return S_OK;
}
