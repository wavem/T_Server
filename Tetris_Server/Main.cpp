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
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "BaseGrid"
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
	m_ClientCnt = 0;
	m_TCPListenThread = NULL;
	for(int i = 0 ; i < MAX_TCP_CLIENT_USER_COUNT ; i++) {
		m_ClientSocket[i] = INVALID_SOCKET;
		m_Client[i] = NULL;
	}

	// Init Grid
	InitGrid();

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

	// Delete TCP Listen Socket
	if(m_TCPListenSocket != INVALID_SOCKET) {
		closesocket(m_TCPListenSocket);
		m_TCPListenSocket = INVALID_SOCKET;
	}

	// Turn Off TCP Listen Thread Routine
	if(m_TCPListenThread) {
		m_TCPListenThread->DoTerminate();
		m_TCPListenThread->Terminate();
		delete m_TCPListenThread;
		m_TCPListenThread = NULL;
	}

	// Delete Client Socket
	for(int i = 0 ; i < MAX_TCP_CLIENT_USER_COUNT ; i++) {
		if(m_ClientSocket[i] != INVALID_SOCKET) {
			closesocket(m_ClientSocket[i]);
			m_ClientSocket[i] = INVALID_SOCKET;
		}
	}

	// Delete Client Thread
	for(int i = 0 ; i < MAX_TCP_CLIENT_USER_COUNT ; i++) {
		if(m_Client[i]) {
			m_Client[i]->Terminate();
			delete m_Client[i];
		}
	}

	// Socket Clean Up
	WSACleanup();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::InitGrid() {
	// Common
	UnicodeString tempStr = L"";

	// Load Images
	TBitmap* t_bmp = new TBitmap;
	t_bmp->LoadFromFile(L".\\Images\\green.bmp");
	ImgList->Add(t_bmp, t_bmp);
	t_bmp->FreeImage();

	t_bmp->LoadFromFile(L".\\Images\\gray.bmp");
	ImgList->Add(t_bmp, t_bmp);
	t_bmp->FreeImage();

	delete t_bmp;

	// Setting
	grid->ControlLook->NoDisabledButtonLook = true;

	// Init Grid
	int t_RowCnt = grid->RowCount;
	for(int i = 1 ; i < t_RowCnt ; i++) {
		grid->Cells[0][i] = i; // Idx
		grid->AddImageIdx(1, i, 1, haCenter, Advgrid::vaCenter); // State
		//grid->Cells[2][i] = L"basslover7022"; // ID
		//grid->Cells[3][i] = L"192.168.220.201"; // IP
		//grid->Cells[4][i] = L"65535"; // Port
		//grid->Cells[5][i] = L"Lobby"; // Status
		grid->AddButton(6, i, 70, 24, L"View", haCenter, Advgrid::vaCenter); // View
		//grid->Cells[7][i] = L"07"; // Last Message
		//grid->Cells[8][i] = L"2020-08-04 14:22:33"; // Connection Time
		//grid->Cells[9][i] = L"2020-08-04 14:22:33"; // Disconnection Time
	}
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
		PrintMsg(L"Server is already listening...");
		return;
	}

	if(CreateTCPListenSocket() == false) return;
	PrintMsg(L"Success to create Listening Socket");

	// Create TCP Listen Thread
	m_TCPListenThread = new CTCPListenThread(&m_TCPListenSocket, m_ClientSocket, &m_ClientCnt);
	PrintMsg(L"TCP Listen Thread Start...");
}
//---------------------------------------------------------------------------

bool __fastcall TFormMain::CreateTCPListenSocket() {

	// Common
	UnicodeString tempStr = L"";

	// Create Listen Socket
	m_TCPListenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(m_TCPListenSocket == INVALID_SOCKET) {
		tempStr = L"Socket create fail";
		PrintMsg(tempStr);
		return false;
	}

	struct sockaddr_in	t_sockaddr_in;
	memset(&t_sockaddr_in, 0, sizeof(t_sockaddr_in));
	t_sockaddr_in.sin_family = AF_INET;
	t_sockaddr_in.sin_addr.s_addr = htonl(INADDR_ANY);
	t_sockaddr_in.sin_port = htons(TCP_SERVER_PORT);

	// Set Socket Option : REUSE
	int t_SockOpt = 1;
	setsockopt(m_TCPListenSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&t_SockOpt, sizeof(t_SockOpt));

	// Bind Socket
	if(bind(m_TCPListenSocket, (struct sockaddr*)&t_sockaddr_in, sizeof(t_sockaddr_in)) < 0) {
		tempStr = L"Socket bind fail";
		PrintMsg(tempStr);
		return false;
	}

	// Listen Socket
	if(listen(m_TCPListenSocket, MAX_TCP_CLIENT_LISTENING_COUNT) < 0) {
		tempStr = L"Socket Listen Fail";
		PrintMsg(tempStr);
		return false;
	}

	tempStr = L"Socket is ready";
	PrintMsg(tempStr);
	return true;
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
	//t_StartTime = m_TCPListenThread->GetStartTime();
	//t_CurrentTime = m_TCPListenThread->GetCurrentTime();
	PrintMsg(L"Start : " + t_StartTime.TimeString() + L" ");
	PrintMsg(L"Current : " + t_CurrentTime.TimeString() + L" ");
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PrintMsg(UnicodeString _str) {
	int t_Idx = memo->Lines->Add(_str);
	memo->SetCursor(0, t_Idx);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PrintLog(UnicodeString _str) {
	int t_Idx = memo_log->Lines->Add(_str);
	memo_log->SetCursor(0, t_Idx);
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

void __fastcall TFormMain::PrintThreadMessage(TMessage &_msg) {
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

void __fastcall TFormMain::tm_FindClientTimer(TObject *Sender)
{
	// Common
	UnicodeString tempStr = L"";

	BYTE t_Buffer[5] = {0, };
	t_Buffer[0] = 0x01;
	t_Buffer[1] = 0x02;
	t_Buffer[2] = 0x03;
	t_Buffer[3] = 0x04;
	t_Buffer[4] = 0x05;

	int t_rst = 0;

	for(int i = 0 ; i < MAX_TCP_CLIENT_USER_COUNT ; i++) {
		if(m_ClientSocket[i] != INVALID_SOCKET) {
			t_rst = send(m_ClientSocket[i], t_Buffer, 5, 0);
			//tempStr.sprintf(L"Socket[%d] -> Send Result : %d", i, t_rst);
			//PrintLog(tempStr);
			t_rst = 0;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AddClient(TMessage &_msg) {

	// Common
	UnicodeString tempStr = L"";
	UnicodeString t_IPStr = L"";
	UnicodeString t_DateTimeStr = L"";
	unsigned int t_wParam = _msg.WParam;
	CLIENTINFO* p_ClientInfo;
	CLIENTINFO t_ClientInfo;
	memset(&t_ClientInfo, 0, sizeof(t_ClientInfo));
	int t_Port = 0;
	int t_ClientIdx = 0;
	TDateTime t_DateTime;

	// Receive Client Info
	p_ClientInfo = (CLIENTINFO*)t_wParam;
	t_ClientInfo = *p_ClientInfo;

	// Extract Client Index
	t_ClientIdx = t_ClientInfo.ClientIndex;

	// Create Client Thread
	m_Client[t_ClientIdx] = new ClientThread(&(m_ClientSocket[t_ClientIdx]) ,t_ClientInfo);

	// Refresh Client Info Grid
	RefreshClientInfoGrid();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::RefreshClientInfoGrid() {

	// Common
	UnicodeString tempStr = L"";
	int t_FixedIdx = 0;
	UnicodeString t_IPStr = L"";
	UnicodeString t_DateTimeStr = L"";
	int t_Port = 0;
	int t_ClientIdx = 0;
	TDateTime t_DateTime;

	// Refresh Routine
	for(int i = 0 ; i < MAX_TCP_CLIENT_USER_COUNT ; i++) {
		// Fix Index Number for Grid
		t_FixedIdx = i + 1;

		// Check if Thread is NULL, Reset Grid Row
		if(m_Client[i] == NULL) {
			grid->RemoveImageIdx(1, t_FixedIdx);
			grid->Cells[2][t_FixedIdx] = L""; // Client ID
			grid->Cells[3][t_FixedIdx] = L""; // Client IP
			grid->Cells[4][t_FixedIdx] = L""; // Client Port
			grid->Cells[5][t_FixedIdx] = L""; // Status
			grid->Cells[8][t_FixedIdx] = L""; // Connected Date Time
			continue;
		}

		// Parsing from Client Thread (For Test)
		t_IPStr = inet_ntoa(m_Client[i]->info.ClientSockAddrIn.sin_addr);
		t_Port = ntohs(m_Client[i]->info.ClientSockAddrIn.sin_port);
		t_DateTime = m_Client[i]->info.ConnectionDateTime;
		t_ClientIdx = m_Client[i]->info.ClientIndex; // Re-Parsing(Re-Extracting)

		// Set Date Format String
		t_DateTimeStr = t_DateTime.FormatString(L"yyyy-mm-dd, hh:mm:ss");

		// Re Draw Grid
		grid->RemoveImageIdx(1, t_FixedIdx);
		grid->AddImageIdx(1, t_FixedIdx, 0, haCenter, Advgrid::vaCenter); // Set Green Icon
		tempStr.sprintf(L"Client[%02X]", t_ClientIdx); // Temporary Creating Client ID
		grid->Cells[2][t_FixedIdx] = tempStr; // Client ID
		grid->Cells[3][t_FixedIdx] = t_IPStr; // Client IP
		grid->Cells[4][t_FixedIdx] = t_Port; // Client Port
		grid->Cells[5][t_FixedIdx] = L"Connected"; // Status
		grid->Cells[8][t_FixedIdx] = t_DateTimeStr; // Connected Date Time
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::tm_DeleteClientTimer(TObject *Sender)
{
	for(int i = 0 ; i < MAX_TCP_CLIENT_USER_COUNT ; i++) {
		if(m_Client[i] == NULL) continue;
		if(m_Client[i]->GetThreadStatus() == THREAD_TERMINATED) {
        	// Close Socket
			if(m_ClientSocket[i]) {
				closesocket(m_ClientSocket[i]);
				m_ClientSocket[i] = INVALID_SOCKET;
			}

			// Delete Client Thread
			if(m_Client[i]) {
				m_Client[i]->DoTerminate();
				m_Client[i]->Terminate();
				delete m_Client[i];
				m_Client[i] = NULL;
			}

			// Refresh Client Info Grid
			RefreshClientInfoGrid();
		}
	}
}
//---------------------------------------------------------------------------

