//---------------------------------------------------------------------------

#ifndef PasswordH
#define PasswordH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "AdvEdit.hpp"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormPassword : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TAdvEdit *ed_pw;
	void __fastcall ed_pwKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
public:		// User declarations
	__fastcall TFormPassword(TComponent* Owner);
	__fastcall TFormPassword(TComponent* Owner, UnicodeString *_str);

public: // MJW
	UnicodeString *m_password;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPassword *FormPassword;
//---------------------------------------------------------------------------
#endif
