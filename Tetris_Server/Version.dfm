object FormVersion: TFormVersion
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'T Server Version'
  ClientHeight = 124
  ClientWidth = 336
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object _pnBase_Version: TPanel
    Left = 0
    Top = 0
    Width = 336
    Height = 124
    Align = alClient
    BevelOuter = bvNone
    Color = clMedGray
    ParentBackground = False
    TabOrder = 0
    object lb_ProgramName: TLabel
      Left = 24
      Top = 16
      Width = 97
      Height = 28
      Caption = 'T Server'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -23
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lb_DeveloperName: TLabel
      Left = 244
      Top = 48
      Width = 70
      Height = 16
      Caption = 'by WAVEM'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lb_Version: TLabel
      Left = 294
      Top = 70
      Width = 20
      Height = 16
      Caption = '1.0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lb_UpdateDate: TLabel
      Left = 80
      Top = 92
      Width = 236
      Height = 16
      Caption = 'Update Date : 2021-01-05 AM 11:30'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lb_Version_Title: TLabel
      Left = 230
      Top = 70
      Width = 58
      Height = 16
      Caption = 'Version :'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
end
