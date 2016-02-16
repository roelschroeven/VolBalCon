//---------------------------------------------------------------------------

#ifndef PresetsFormH
#define PresetsFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <AppEvnts.hpp>
#pragma message "End of auto-included header files"
//---------------------------------------------------------------------------

#include "Presets.h"

typedef void (__closure *TOnPreset)(const TPreset &Preset);

void ShowPresets(TPresets &Presets, const TPreset &CurrentSetting, TOnPreset OnPreset);

//---------------------------------------------------------------------------

class TFormPresets : public TForm
{
__published:	// IDE-managed Components
  TListBox *ListBoxPresets;
  TButton *ButtonLoad;
  TButton *ButtonSave;
  TButton *ButtonDelete;
  TApplicationEvents *ApplicationEvents;
  void __fastcall ButtonSaveClick(TObject *Sender);
  void __fastcall ListBoxPresetsClick(TObject *Sender);
  void __fastcall ButtonLoadClick(TObject *Sender);
  void __fastcall ButtonDeleteClick(TObject *Sender);
  void __fastcall ApplicationEventsIdle(TObject *Sender, bool &Done);

private:	// User declarations
  bool m_bFirstIdle;
  TPresets *m_pPresets;
  TPreset m_CurrentSetting;
  TOnPreset OnPreset;

  void FillList();

public:		// User declarations
  __fastcall TFormPresets(TComponent* Owner);

  void Set(TPresets &Presets, const TPreset &CurrentSetting, TOnPreset OnPreset);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPresets *FormPresets;
//---------------------------------------------------------------------------
#endif
