object FormPromptForString: TFormPromptForString
  Left = 0
  Top = 0
  Caption = 'FormPromptForString'
  ClientHeight = 116
  ClientWidth = 497
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 497
    Height = 75
    Align = alClient
    ShowCaption = False
    TabOrder = 0
    ExplicitLeft = 224
    ExplicitTop = 32
    ExplicitWidth = 225
    ExplicitHeight = 73
    DesignSize = (
      497
      75)
    object LabelPrompt: TLabel
      Left = 7
      Top = 16
      Width = 38
      Height = 13
      Caption = 'Prompt:'
    end
    object EditValue: TEdit
      Left = 7
      Top = 35
      Width = 484
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 0
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 75
    Width = 497
    Height = 41
    Align = alBottom
    ShowCaption = False
    TabOrder = 1
    ExplicitLeft = 320
    ExplicitTop = 120
    ExplicitWidth = 185
    DesignSize = (
      497
      41)
    object ButtonOk: TButton
      Left = 335
      Top = 8
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'OK'
      Default = True
      ModalResult = 1
      TabOrder = 0
      ExplicitLeft = 351
    end
    object ButtonCancel: TButton
      Left = 416
      Top = 8
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Cancel = True
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 1
      ExplicitLeft = 432
    end
  end
end
