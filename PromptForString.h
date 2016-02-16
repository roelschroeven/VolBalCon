//---------------------------------------------------------------------------

#ifndef PromptForStringH
#define PromptForStringH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <AppEvnts.hpp>
#pragma message "End of auto-included headers"
//---------------------------------------------------------------------------

bool PromptForString(const String &Prompt, String &Value);
//---------------------------------------------------------------------------

class TFormPromptForString : public TForm
{
__published:	// IDE-managed Components
  TPanel *Panel1;
  TPanel *Panel2;
  TLabel *LabelPrompt;
  TButton *ButtonOk;
  TButton *ButtonCancel;
  TEdit *EditValue;
  TApplicationEvents *ApplicationEvents;
  void __fastcall ApplicationEventsIdle(TObject *Sender, bool &Done);

private:	// User declarations
  bool m_bFirstIdle;

public:		// User declarations
  __fastcall TFormPromptForString(TComponent* Owner);

  void Set(const String &Prompt, const String &Value);
  String GetValue();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPromptForString *FormPromptForString;
//---------------------------------------------------------------------------
#endif
