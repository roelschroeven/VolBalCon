//---------------------------------------------------------------------------

#ifndef PresetsH
#define PresetsH
//---------------------------------------------------------------------------

#include <map>
#include <vector>

struct TPreset
{
  float Master;
  typedef std::vector<float> TChannels;
  TChannels Channels;
};

class TPresets
{
public:
  TPresets() { Load(); }
  void Load();
  void Save();

  std::map<String, TPreset> Presets;
};

#endif
