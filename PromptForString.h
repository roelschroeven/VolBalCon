//---------------------------------------------------------------------------

#ifndef PromptForStringH
#define PromptForStringH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
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

private:	// User declarations

public:		// User declarations
  __fastcall TFormPromptForString(TComponent* Owner);

  void Set(const String &Prompt, const String &Value);
  String GetValue();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPromptForString *FormPromptForString;
//---------------------------------------------------------------------------
#endif
