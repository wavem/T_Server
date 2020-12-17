//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include "cxClasses.hpp"
#include "cxControls.hpp"
#include "cxGraphics.hpp"
#include "cxLookAndFeelPainters.hpp"
#include "cxLookAndFeels.hpp"
#include "dxBar.hpp"
#include "dxRibbon.hpp"
#include "dxRibbonCustomizationForm.hpp"
#include "dxRibbonSkins.hpp"
#include "dxSkinBlack.hpp"
#include "dxSkinBlue.hpp"
#include "dxSkinBlueprint.hpp"
#include "dxSkinCaramel.hpp"
#include "dxSkinCoffee.hpp"
#include "dxSkinDarkRoom.hpp"
#include "dxSkinDarkSide.hpp"
#include "dxSkinDevExpressDarkStyle.hpp"
#include "dxSkinDevExpressStyle.hpp"
#include "dxSkinFoggy.hpp"
#include "dxSkinGlassOceans.hpp"
#include "dxSkinHighContrast.hpp"
#include "dxSkiniMaginary.hpp"
#include "dxSkinLilian.hpp"
#include "dxSkinLiquidSky.hpp"
#include "dxSkinLondonLiquidSky.hpp"
#include "dxSkinMcSkin.hpp"
#include "dxSkinMetropolis.hpp"
#include "dxSkinMetropolisDark.hpp"
#include "dxSkinMoneyTwins.hpp"
#include "dxSkinOffice2007Black.hpp"
#include "dxSkinOffice2007Blue.hpp"
#include "dxSkinOffice2007Green.hpp"
#include "dxSkinOffice2007Pink.hpp"
#include "dxSkinOffice2007Silver.hpp"
#include "dxSkinOffice2010Black.hpp"
#include "dxSkinOffice2010Blue.hpp"
#include "dxSkinOffice2010Silver.hpp"
#include "dxSkinOffice2013DarkGray.hpp"
#include "dxSkinOffice2013LightGray.hpp"
#include "dxSkinOffice2013White.hpp"
#include "dxSkinPumpkin.hpp"
#include "dxSkinsCore.hpp"
#include "dxSkinsDefaultPainters.hpp"
#include "dxSkinsdxBarPainter.hpp"
#include "dxSkinsdxRibbonPainter.hpp"
#include "dxSkinSeven.hpp"
#include "dxSkinSevenClassic.hpp"
#include "dxSkinSharp.hpp"
#include "dxSkinSharpPlus.hpp"
#include "dxSkinSilver.hpp"
#include "dxSkinSpringTime.hpp"
#include "dxSkinStardust.hpp"
#include "dxSkinSummer2008.hpp"
#include "dxSkinTheAsphaltWorld.hpp"
#include "dxSkinValentine.hpp"
#include "dxSkinVisualStudio2013Blue.hpp"
#include "dxSkinVisualStudio2013Dark.hpp"
#include "dxSkinVisualStudio2013Light.hpp"
#include "dxSkinVS2010.hpp"
#include "dxSkinWhiteprint.hpp"
#include "dxSkinXmas2008Blue.hpp"
#include "AdvSmoothButton.hpp"
#include "AdvMemo.hpp"
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "BaseGrid.hpp"
#include <Vcl.Grids.hpp>
#include <Vcl.ImgList.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <Vcl.DBGrids.hpp>
#include "AdvEdit.hpp"
#include "cxContainer.hpp"
#include "cxEdit.hpp"
#include "cxMemo.hpp"
#include "cxTextEdit.hpp"
//---------------------------------------------------------------------------

#include <queue>
#include <algorithm>

#include "Define.h"
#include "DataSenderThread.h"
#include "TCPListenThread.h"
#include "ClientThread.h"
#include "Password.h"
#include "Version.h"
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "BaseGrid.hpp"
#include <Vcl.Grids.hpp>
#include <Vcl.ImgList.hpp>

//---------------------------------------------------------------------------
class CTCPListenThread;
class ClientThread;
class DataSenderThread;

class TFormMain : public TForm
{
__published:	// IDE-managed Components
	TTrayIcon *TrayIcon;
	TPopupMenu *PopupMenu;
	TMenuItem *Exit1;
	TPanel *__pnBase;
	TNotebook *Notebook_Main;
	TPanel *_pnBase_01_Status;
	TdxRibbonTab *RibbonMenuTab_Main;
	TdxRibbon *RibbonMenu;
	TdxBarManager *BarMgr;
	TdxBar *BarMgrBar;
	TdxBarLargeButton *MenuBtn_Status;
	TdxBarLargeButton *MenuBtn_Setting;
	TdxBarLargeButton *MenuBtn_Version;
	TPanel *_pnBase_02_Setting;
	TAdvSmoothButton *btn_Hide;
	TdxBarLargeButton *MenuBtn_Lock;
	TAdvStringGrid *grid;
	TImageList *ImgList;
	TAdvMemo *memo;
	TAdvSmoothButton *btn_Test;
	TAdvSmoothButton *btn_Listen;
	TAdvSmoothButton *btn_Stop;
	TAdvSmoothButton *btn_Resume;
	TAdvSmoothButton *btn_Terminate;
	TAdvSmoothButton *btn_GetRunningTime;
	TTimer *tm_FindClient;
	TTimer *tm_DeleteClient;
	TPanel *_pnBase_03_UserInfo;
	TDBGrid *DBGrid_User;
	TAdvSmoothButton *btn_UserInfo;
	TAdvSmoothButton *btn_Count;
	TADOConnection *ADOConnection;
	TADOTable *Table_User;
	TADOQuery *Query_USER;
	TDataSource *DataSource_USER;
	TAdvSmoothButton *btn_AddDB;
	TAdvSmoothButton *btn_DelDB;
	TLabel *lb_Title_SignUp_ID;
	TLabel *lb_Title_SignUp_PW;
	TLabel *lb_Title_SignUp_UserName;
	TAdvEdit *ed_PW;
	TAdvEdit *ed_UserName;
	TAdvEdit *ed_ID;
	TcxMemo *memo_log;
	TAdvStringGrid *grid_LobbyList;
	TLabel *lb_Title_PlayerList_No;
	TLabel *lb_Title_PlayerList_ID;
	TLabel *lb_Title_PlayerList_Grade;
	TAdvSmoothButton *btn_RoomList;
	TPanel *_pnBase_04_RoomList;
	TAdvStringGrid *grid_Room;
	TLabel *lb_Lobby_1;
	TLabel *lb_Lobby_2;
	TLabel *lb_Lobby_3;
	TLabel *lb_Lobby_4;
	TLabel *lb_Lobby_5;
	TLabel *lb_Lobby_6;
	TLabel *lb_Lobby_7;
	TLabel *lb_Lobby_8;
	TLabel *lb_Lobby_9;
	void __fastcall Exit1Click(TObject *Sender);
	void __fastcall TrayIconDblClick(TObject *Sender);
	void __fastcall MenuBtn_StatusClick(TObject *Sender);
	void __fastcall MenuBtn_SettingClick(TObject *Sender);
	void __fastcall btn_HideClick(TObject *Sender);
	void __fastcall btn_TestClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btn_ListenClick(TObject *Sender);
	void __fastcall btn_StopClick(TObject *Sender);
	void __fastcall btn_TerminateClick(TObject *Sender);
	void __fastcall btn_ResumeClick(TObject *Sender);
	void __fastcall btn_GetRunningTimeClick(TObject *Sender);
	void __fastcall tm_FindClientTimer(TObject *Sender);
	void __fastcall tm_DeleteClientTimer(TObject *Sender);
	void __fastcall MenuBtn_VersionClick(TObject *Sender);
	void __fastcall btn_UserInfoClick(TObject *Sender);
	void __fastcall btn_CountClick(TObject *Sender);
	void __fastcall btn_AddDBClick(TObject *Sender);
	void __fastcall btn_DelDBClick(TObject *Sender);
	void __fastcall btn_RoomListClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormMain(TComponent* Owner);

// START TETRIS SERVER
public: // Member
	CTCPListenThread* m_TCPListenThread;
	SOCKET m_TCPListenSocket;
	ClientThread* m_Client[MAX_TCP_CLIENT_USER_COUNT];
	SOCKET m_ClientSocket[MAX_TCP_CLIENT_USER_COUNT];
	int m_ClientCnt;
	DataSenderThread* m_SenderThread[MAX_SENDER_THREAD_COUNT];
	int m_SenderThreadWorkCount[MAX_SENDER_THREAD_COUNT];
	std::vector<int> m_LobbyPlayerVector;


public: // BASIC FUNCTIONS
	void __fastcall InitProgram();
	void __fastcall ExitProgram();
	void __fastcall PrintMsg(UnicodeString _str);
	void __fastcall PrintLog(UnicodeString _str);
	void __fastcall InitGrid();
	void __fastcall InitDB();
	void __fastcall GetClientInfoFromDB();
	BYTE __fastcall GetGradeLevelValue(UnicodeString _gradeStr);
	void __fastcall PushLobbyPlayer(int _Idx);
	void __fastcall EraseLobbyPlayer(int _Idx);

public: // SOCKET FUNCTIONS
	bool __fastcall CreateTCPListenSocket();

public: // ETC UI FUNCTIONS
	void __fastcall RefreshClientInfoGrid();
	void __fastcall RefreshLobbyListGrid();

public: // Received Message Queue
	HANDLE m_Mutex;
	std::queue<SERVERMSG> m_ServerMsgQ;

public: // USER DB ROUTINE
	bool __fastcall FindUserID(UnicodeString _ID);
	bool __fastcall AddUserID(UnicodeString _ID, UnicodeString _PW, UnicodeString _USERNAME);
	bool __fastcall DeleteUserID(UnicodeString _ID);
	BYTE __fastcall Login(UnicodeString _ID, UnicodeString _PW);

public: // CALCULATION AND SEND FUNCTIONS
	void __fastcall SendLobbyStatus();
	void __fastcall SendRoomStatus();
	void __fastcall SendLobbyPlayerList();

public: // Client Message Handler
	void __fastcall ClientMsg_SIGN_UP(CLIENTMSG _ClientMsg, SERVERMSG* _pServerMsg);
	void __fastcall ClientMsg_SIGN_IN(CLIENTMSG _ClientMsg, SERVERMSG* _pServerMsg);
	void __fastcall ClientMsg_LOBBY_CHATTING(CLIENTMSG _ClientMsg, SERVERMSG* _pServerMsg);

public: // Thread Message Handler
	void __fastcall PrintThreadMessage(TMessage &_msg);
	void __fastcall AddClient(TMessage &_msg);
	void __fastcall ReceiveClientMessage(TMessage &_msg);


BEGIN_MESSAGE_MAP
	MESSAGE_HANDLER(MSG_MEMO, TMessage, PrintThreadMessage)
	MESSAGE_HANDLER(MSG_NEW_CONNECTION, TMessage, AddClient)
	MESSAGE_HANDLER(MSG_CLIENT_MESSAGE, TMessage, ReceiveClientMessage)
END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
