object Form1: TForm1
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  ClientHeight = 106
  ClientWidth = 507
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Panel2: TPanel
    Left = 8
    Top = 8
    Width = 489
    Height = 57
    Caption = 'Original Pairs game'
    TabOrder = 1
    object Button1: TButton
      Left = 16
      Top = 17
      Width = 75
      Height = 25
      Caption = 'Pairs'
      TabOrder = 0
      OnClick = Button1Click
    end
    object Button3: TButton
      Left = 136
      Top = 23
      Width = 97
      Height = 34
      Caption = 'Symbol Digits'
      TabOrder = 1
      OnClick = Button3Click
    end
    object Button2: TButton
      Left = 16
      Top = 23
      Width = 97
      Height = 34
      Caption = 'Trails'
      TabOrder = 2
      OnClick = Button2Click
    end
  end
  object Panel1: TPanel
    Left = 10
    Top = 8
    Width = 489
    Height = 90
    TabOrder = 0
    object Label1: TLabel
      Left = 16
      Top = 8
      Width = 86
      Height = 13
      Caption = 'Click to view tests'
    end
    object Button4: TButton
      Left = 117
      Top = 29
      Width = 97
      Height = 34
      Caption = 'Hoop'
      TabOrder = 0
      OnClick = Button4Click
    end
    object Button5: TButton
      Left = 272
      Top = 29
      Width = 97
      Height = 34
      Caption = 'Matrix'
      TabOrder = 1
      OnClick = Button5Click
    end
  end
end
