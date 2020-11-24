//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cxClasses"
#pragma link "cxControls"
#pragma link "cxGraphics"
#pragma link "cxLookAndFeelPainters"
#pragma link "cxLookAndFeels"
#pragma link "dxBar"
#pragma link "dxRibbon"
#pragma link "dxRibbonCustomizationForm"
#pragma link "dxRibbonSkins"
#pragma link "dxSkinBlack"
#pragma link "dxSkinBlue"
#pragma link "dxSkinBlueprint"
#pragma link "dxSkinCaramel"
#pragma link "dxSkinCoffee"
#pragma link "dxSkinDarkRoom"
#pragma link "dxSkinDarkSide"
#pragma link "dxSkinDevExpressDarkStyle"
#pragma link "dxSkinDevExpressStyle"
#pragma link "dxSkinFoggy"
#pragma link "dxSkinGlassOceans"
#pragma link "dxSkinHighContrast"
#pragma link "dxSkiniMaginary"
#pragma link "dxSkinLilian"
#pragma link "dxSkinLiquidSky"
#pragma link "dxSkinLondonLiquidSky"
#pragma link "dxSkinMcSkin"
#pragma link "dxSkinMetropolis"
#pragma link "dxSkinMetropolisDark"
#pragma link "dxSkinMoneyTwins"
#pragma link "dxSkinOffice2007Black"
#pragma link "dxSkinOffice2007Blue"
#pragma link "dxSkinOffice2007Green"
#pragma link "dxSkinOffice2007Pink"
#pragma link "dxSkinOffice2007Silver"
#pragma link "dxSkinOffice2010Black"
#pragma link "dxSkinOffice2010Blue"
#pragma link "dxSkinOffice2010Silver"
#pragma link "dxSkinOffice2013DarkGray"
#pragma link "dxSkinOffice2013LightGray"
#pragma link "dxSkinOffice2013White"
#pragma link "dxSkinPumpkin"
#pragma link "dxSkinsCore"
#pragma link "dxSkinsDefaultPainters"
#pragma link "dxSkinsdxBarPainter"
#pragma link "dxSkinsdxRibbonPainter"
#pragma link "dxSkinSeven"
#pragma link "dxSkinSevenClassic"
#pragma link "dxSkinSharp"
#pragma link "dxSkinSharpPlus"
#pragma link "dxSkinSilver"
#pragma link "dxSkinSpringTime"
#pragma link "dxSkinStardust"
#pragma link "dxSkinSummer2008"
#pragma link "dxSkinTheAsphaltWorld"
#pragma link "dxSkinValentine"
#pragma link "dxSkinVisualStudio2013Blue"
#pragma link "dxSkinVisualStudio2013Dark"
#pragma link "dxSkinVisualStudio2013Light"
#pragma link "dxSkinVS2010"
#pragma link "dxSkinWhiteprint"
#pragma link "dxSkinXmas2008Blue"
#pragma link "AdvSmoothButton"
#pragma link "AdvMemo"
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
	: TForm(Owner)
{
	InitProgram();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormClose(TObject *Sender, TCloseAction &Action)
{
	ExitProgram();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::InitProgram() {

	// Common
	UnicodeString t_Str = L"";

	// Set First Notebook Page
	Notebook_Main->PageIndex = 0; // Status

	// Set TrayIcon
	TrayIcon->ShowBalloonHint();

	// Init
	m_TCPListenThread = NULL;

	// Socket
	WSADATA data;
	WORD version;
	int ret = 0;

	version = MAKEWORD(2, 2);
	ret = WSAStartup(version, &data);
	if(ret != 0) {
		ret = WSAGetLastError();
		if(ret == WSANOTINITIALISED) {
			t_Str.sprintf(L"Socket not initialised (error code : %d)", ret);
			PrintMsg(t_Str);
		} else {
			t_Str.sprintf(L"Socket error (error code : %d)", ret);
			PrintMsg(t_Str);
		}
	} else {
		PrintMsg(L"Socket init success");
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ExitProgram() {

	// Turn Off TCP Listen Thread Routine
	if(m_TCPListenThread) {
		m_TCPListenThread->DoTerminate();
		m_TCPListenThread->Terminate();
		delete m_TCPListenThread;
		m_TCPListenThread = NULL;
	}

	// Socket
	WSACleanup();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::btn_TestClick(TObject *Sender)
{
	PrintMsg(L"TEST BUTTON CLICKED");
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::btn_ListenClick(TObject *Sender)
{
	if(m_TCPListenThread) {
		PrintMsg(L"TCP Listen Thread Already Running...");
		return;
	}
	m_TCPListenThread = new CTCPListenThread;
	PrintMsg(m_TCPListenThread->m_msg);
	if(m_TCPListenThread->GetThreadStatus() == THREAD_TERMINATED) {
		PrintMsg(L"TCP Listen Thread Fail...");

		// Delete Thread
		m_TCPListenThread->Terminate();
		delete m_TCPListenThread;
		m_TCPListenThread = NULL;
		PrintMsg(L"TCP Listen Thread Terminated");
		return;
	}
	PrintMsg(L"TCP Listen Thread Start...");
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::btn_StopClick(TObject *Sender)
{
	if(!m_TCPListenThread) {
		PrintMsg(L"There is no TCP Listen Thread");
		return;
	}
	m_TCPListenThread->Stop();
	PrintMsg(L"TCP Listen Thread Stoped");
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::btn_ResumeClick(TObject *Sender)
{
	if(!m_TCPListenThread) {
		PrintMsg(L"There is no TCP Listen Thread");
		return;
	}
	m_TCPListenThread->Resume();
	PrintMsg(L"TCP Listen Thread Resume");
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::btn_TerminateClick(TObject *Sender)
{
	if(!m_TCPListenThread) {
		PrintMsg(L"There is no TCP Listen Thread");
		return;
	}
	m_TCPListenThread->DoTerminate();
	PrintMsg(m_TCPListenThread->m_msg);
	if(m_TCPListenThread->GetThreadStatus() == THREAD_TERMINATED) {
		m_TCPListenThread->Terminate();
		delete m_TCPListenThread;
		m_TCPListenThread = NULL;
		PrintMsg(L"TCP Listen Thread Terminated");
	} else {
		PrintMsg(L"TCP Listen Thread is not Terminated");
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::btn_GetRunningTimeClick(TObject *Sender)
{
	if(!m_TCPListenThread) {
		PrintMsg(L"There is no TCP Listen Thread");
		return;
	}
	TTime t_StartTime, t_CurrentTime;
	t_StartTime = m_TCPListenThread->GetStartTime();
	t_CurrentTime = m_TCPListenThread->GetCurrentTime();
	PrintMsg(L"Start : " + t_StartTime.TimeString() + L" ");
	PrintMsg(L"Current : " + t_CurrentTime.TimeString() + L" ");
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PrintMsg(UnicodeString _str) {
	int t_Idx = memo->Lines->Add(_str);
	memo->SetCursor(0, t_Idx);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Exit1Click(TObject *Sender)
{
	//FormMain->Close();
	// Terminate 를 하면 Form Close() 로 접근하는 일은 없다.
	// 하지만, Application 자체를 Terminate() 해도 문제 되는건 없는 것 같다.
	// 따라서 이 내용을 걍 메모만 해 두겠음.
	Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TrayIconDblClick(TObject *Sender)
{
	UnicodeString t_strPW = L"";
	TFormPassword *dlg = new TFormPassword(NULL, &t_strPW);
	dlg->ShowModal();
	delete dlg;

	if(t_strPW == L"1212") {
		FormMain->Show();
	} else if(t_strPW == L"") {
		// Do Nothing
	} else {
		ShowMessage(L"PASSWORD INCORRECT");
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MenuBtn_StatusClick(TObject *Sender)
{
	Notebook_Main->PageIndex = 0; // Status
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MenuBtn_SettingClick(TObject *Sender)
{
	Notebook_Main->PageIndex = 1; // Setting
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::btn_HideClick(TObject *Sender)
{
	FormMain->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::DoMsg(TMessage &_msg) {
	unsigned int t_wParam = _msg.WParam;
	int t_lParam = _msg.LParam;

	UnicodeString tempStr = L"";
	UnicodeString *p = NULL;
	p = (UnicodeString*)t_wParam;
	tempStr = *p;
	//tempStr.sprintf(L"W : %08x, L : %08x", t_wParam, t_lParam);
	int t_Idx = memo->Lines->Add(tempStr);
	memo->SetCursor(0, t_Idx);
}
//---------------------------------------------------------------------------
