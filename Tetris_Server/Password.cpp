//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Password.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvEdit"
#pragma resource "*.dfm"
TFormPassword *FormPassword;
//---------------------------------------------------------------------------
__fastcall TFormPassword::TFormPassword(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

__fastcall TFormPassword::TFormPassword(TComponent* Owner, UnicodeString *_str)
	: TForm(Owner)
{
	m_password = _str;
}
//---------------------------------------------------------------------------
void __fastcall TFormPassword::ed_pwKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == VK_RETURN) {
		*m_password = ed_pw->Text;
		this->Close();
	}
}
//---------------------------------------------------------------------------
