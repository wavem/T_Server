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
//---------------------------------------------------------------------------

#include "Define.h"
#define MYMSG	40000
//---------------------------------------------------------------------------
class CTCPListenThread;
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
	TAdvMemo *memo;
	TAdvSmoothButton *btn_Test;
	TAdvSmoothButton *btn_Listen;
	TAdvSmoothButton *btn_Stop;
	TAdvSmoothButton *btn_Terminate;
	TAdvSmoothButton *btn_Resume;
	TAdvSmoothButton *btn_GetRunningTime;
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
private:	// User declarations
public:		// User declarations
	__fastcall TFormMain(TComponent* Owner);


public: // Member
	CTCPListenThread *m_TCPListenThread;

public: // Routine
	void __fastcall InitProgram();
	void __fastcall ExitProgram();
	void __fastcall PrintMsg(UnicodeString _str);


	void __fastcall DoMsg(TMessage &_msg);


BEGIN_MESSAGE_MAP
	MESSAGE_HANDLER(MYMSG, TMessage, DoMsg)
END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
