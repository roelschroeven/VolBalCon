//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <RsUtil.h>

#include "PresetsForm.h"
#include "PromptForString.h"
#include "Util.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormPresets *FormPresets;
//---------------------------------------------------------------------------

using rsutil::CreateVclForm;
using rsutil::PrintF;

void ShowPresets(TPresets &Presets, const TPreset &CurrentSetting, TOnPreset OnPreset)
{
  std::auto_ptr<TFormPresets> Form = CreateVclForm<TFormPresets>();
  Form->Set(Presets, CurrentSetting, OnPreset);
  Form->ShowModal();
}
//---------------------------------------------------------------------------

__fastcall TFormPresets::TFormPresets(TComponent* Owner)
  : TForm(Owner)
  , m_bFirstIdle(true)
  , m_pPresets(NULL)
{
}
//---------------------------------------------------------------------------

void TFormPresets::Set(TPresets &Presets, const TPreset &CurrentSetting, TOnPreset OnPreset_)
{
  m_pPresets = &Presets;
  m_CurrentSetting = CurrentSetting;
  OnPreset = OnPreset_;

  FillList();
}
//---------------------------------------------------------------------------

void TFormPresets::FillList()
{
  if (!m_pPresets)
    return;

  ListBoxPresets->Items->BeginUpdate();
  ListBoxPresets->Items->Clear();

  for (std::map<String, TPreset>::const_iterator it = m_pPresets->Presets.begin(); it != m_pPresets->Presets.end(); ++it)
    ListBoxPresets->Items->Append(it->first);

  ListBoxPresets->Items->EndUpdate();
  ListBoxPresets->ItemIndex = 0;

  ButtonLoad->Enabled = ListBoxPresets->ItemIndex >= 0;
  ButtonDelete->Enabled = ListBoxPresets->ItemIndex >= 0;
}
//---------------------------------------------------------------------------

void __fastcall TFormPresets::ListBoxPresetsClick(TObject *Sender)
{
  ButtonLoad->Enabled = true;
  ButtonDelete->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormPresets::ButtonLoadClick(TObject *Sender)
{
  if (ListBoxPresets->ItemIndex < 0)
    return;
  String Name = ListBoxPresets->Items->Strings[ListBoxPresets->ItemIndex];
  std::map<String, TPreset>::const_iterator it = m_pPresets->Presets.find(Name);
  if (it == m_pPresets->Presets.end())
    return;
  m_CurrentSetting = it->second;
  OnPreset(it->second);
}
//---------------------------------------------------------------------------

void __fastcall TFormPresets::ButtonSaveClick(TObject *Sender)
{
  String Name = L"";
  if (ListBoxPresets->ItemIndex >= 0)
    Name = ListBoxPresets->Items->Strings[ListBoxPresets->ItemIndex];

  while (true)
    {
    if (!PromptForString(L"Preset name", Name))
      return;
    if (ListBoxPresets->Items->IndexOf(Name) < 0)
      break;
    int rv = MessageDlg(
      PrintF(L"Going to overwrite preset '%ls'; are you sure?", Name.c_str()),
        mtConfirmation,
        TMsgDlgButtons() << mbYes << mbNo << mbCancel,
        0);
    if (rv == mrCancel)
      return;
    else if (rv == mrYes)
      break;
    else if (rv == mrNo)
      continue;
    }

  m_pPresets->Presets[Name] = m_CurrentSetting;
  m_pPresets->Save();
  FillList();
  ListBoxPresets->ItemIndex = ListBoxPresets->Items->IndexOf(Name);

  ButtonLoad->Enabled = ListBoxPresets->ItemIndex >= 0;
  ButtonDelete->Enabled = ListBoxPresets->ItemIndex >= 0;
}
//---------------------------------------------------------------------------

void __fastcall TFormPresets::ButtonDeleteClick(TObject *Sender)
{
  if (ListBoxPresets->ItemIndex < 0)
    return;
  String Name = ListBoxPresets->Items->Strings[ListBoxPresets->ItemIndex];
  int rv = MessageDlg(
    PrintF(L"Going to delete preset '%ls'; are you sure?", Name.c_str()),
      mtConfirmation,
      TMsgDlgButtons() << mbYes << mbNo,
      0);
  if (rv != mrYes)
    return;
  m_pPresets->Presets.erase(Name);
  m_pPresets->Save();
  ListBoxPresets->Items->Delete(ListBoxPresets->ItemIndex);
  ListBoxPresets->ItemIndex = -1;
  FillList();
}
//---------------------------------------------------------------------------

void __fastcall TFormPresets::ApplicationEventsIdle(TObject *Sender, bool &Done)
{
  if (m_bFirstIdle)
    {
    m_bFirstIdle = false;
    EnsureOnScreen(this);
    }
}
//---------------------------------------------------------------------------

