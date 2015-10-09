//---------------------------------------------------------------------------

#ifndef VolumeCallbackH
#define VolumeCallbackH
//---------------------------------------------------------------------------

#include <objbase.h>
#include <Endpointvolume.h>

typedef void (__closure *TOnVolumeChange)(GUID EventContext, bool bMuted, float MasterVolume, unsigned NrChannels, float ChannelVolumes[]);

class TVolumeCallback: public IAudioEndpointVolumeCallback
{
public:
  TVolumeCallback(TOnVolumeChange OnVolumeChange);

  // IUnknown
  virtual HRESULT STDMETHODCALLTYPE QueryInterface(const IID &iid, void **ppv);
  virtual ULONG STDMETHODCALLTYPE AddRef();
  virtual ULONG STDMETHODCALLTYPE Release();

  // IAudioEndpointVolumeCallback
  virtual HRESULT STDMETHODCALLTYPE OnNotify(AUDIO_VOLUME_NOTIFICATION_DATA *pNotificationData);

private:
  ULONG m_RefCount;
  TOnVolumeChange m_OnVolumeChange;
};




#endif
