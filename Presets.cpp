//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <Registry.hpp>
#include <RsUtil.h>

#include "Presets.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

const String BaseKey = "\\Software\\Roel Schroeven\\VolBalCon";
const String PresetsKey = "\\Software\\Roel Schroeven\\VolBalCon\\Presets";

using rsutil::JoinPaths;
using rsutil::PrintF;

void TPresets::Load()
{
  std::auto_ptr<TRegistry> Registry(new TRegistry);
  Registry->RootKey = HKEY_CURRENT_USER;
  if (!Registry->OpenKeyReadOnly(PresetsKey))
    return;
  std::auto_ptr<TStrings> PresetNames(new TStringList);
  Registry->GetKeyNames(PresetNames.get());
  for (int i = 0; i < PresetNames->Count; ++i)
    {
    String Name = PresetNames->Strings[i];
    if (!Registry->OpenKeyReadOnly(JoinPaths(PresetsKey, Name)))
      continue;
    TPreset Preset;
    Preset.Master = 0.01 * Registry->ReadInteger("Master");
    int ChannelIndex = 0;
    while (true)
      {
      String ValueName = PrintF(L"Channel%d", ChannelIndex);
      if (!Registry->ValueExists(ValueName))
        break;
      float ChannelVolume = 0.0;
      try { ChannelVolume = 0.01 * Registry->ReadInteger(ValueName); }
      catch (Exception &E) {  }
      Preset.Channels.push_back(ChannelVolume);
      ChannelIndex += 1;
      }
    Presets[Name] = Preset;
    }
}

static void DeletePresetsFromRegistry(TRegistry *Registry, const String &PresetsKey)
{
  if (!Registry->OpenKey(PresetsKey, false))
    return;
  std::auto_ptr<TStrings> PresetNames(new TStringList);
  Registry->GetKeyNames(PresetNames.get());
  for (int i = 0; i < PresetNames->Count; ++i)
    Registry->DeleteKey(JoinPaths(PresetsKey, PresetNames->Strings[i]));
}

void TPresets::Save()
{
  std::auto_ptr<TRegistry> Registry(new TRegistry);
  Registry->RootKey = HKEY_CURRENT_USER;

  // First remove all presets to start from a clean slate
  DeletePresetsFromRegistry(Registry.get(), PresetsKey);

  // Write presets
  for (std::map<String, TPreset>::const_iterator it = Presets.begin(); it != Presets.end(); ++it)
    {
    const String &PresetName = it->first;
    const TPreset &Preset = it->second;
    if (!Registry->OpenKey(JoinPaths(PresetsKey, PresetName), true))
      continue;
    Registry->WriteInteger(L"Master", 100 * Preset.Master);
    for (unsigned i = 0; i < Preset.Channels.size(); ++i)
      Registry->WriteInteger(PrintF(L"Channel%d", i), 100 * Preset.Channels[i]);
    }
}

