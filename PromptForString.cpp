//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <RsUtil.h>

#include "PromptForString.h"
#include "Util.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormPromptForString *FormPromptForString;
//---------------------------------------------------------------------------

bool PromptForString(const String &Prompt, String &Value)
{
  std::auto_ptr<TFormPromptForString> Form = rsutil::CreateVclForm<TFormPromptForString>();
  Form->Set(Prompt, Value);
  if (Form->ShowModal() != mrOk)
    return false;
  Value = Form->GetValue();
  return true;
}
//---------------------------------------------------------------------------

__fastcall TFormPromptForString::TFormPromptForString(TComponent* Owner)
  : TForm(Owner)
  , m_bFirstIdle(true)
{
}
//---------------------------------------------------------------------------

void TFormPromptForString::Set(const String &Prompt, const String &Value)
{
  Caption = Prompt;
  LabelPrompt->Caption = Prompt + L":";
  EditValue->Text = Value;
}
//---------------------------------------------------------------------------

String TFormPromptForString::GetValue()
{
  return EditValue->Text;
}
//---------------------------------------------------------------------------

void __fastcall TFormPromptForString::ApplicationEventsIdle(TObject *Sender, bool &Done)
{
  if (m_bFirstIdle)
    {
    m_bFirstIdle = false;
    EnsureOnScreen(this);
    }
}
//---------------------------------------------------------------------------

