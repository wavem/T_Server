//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Version.h"
#include "Define.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormVersion *FormVersion;
//---------------------------------------------------------------------------
__fastcall TFormVersion::TFormVersion(TComponent* Owner)
	: TForm(Owner)
{
	UnicodeString tempStr = L"";
	tempStr.sprintf(L"%d.%d", VERSION_MAJOR, VERSION_MINOR);
	lb_Version->Caption = tempStr;
}
//---------------------------------------------------------------------------
