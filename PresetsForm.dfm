object FormPresets: TFormPresets
  Left = 0
  Top = 0
  Caption = 'Presets'
  ClientHeight = 104
  ClientWidth = 296
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  DesignSize = (
    296
    104)
  PixelsPerInch = 96
  TextHeight = 13
  object ListBoxPresets: TListBox
    Left = 8
    Top = 8
    Width = 185
    Height = 87
    Anchors = [akLeft, akTop, akRight, akBottom]
    ItemHeight = 13
    TabOrder = 0
    OnClick = ListBoxPresetsClick
  end
  object ButtonLoad: TButton
    Left = 199
    Top = 8
    Width = 90
    Height = 25
    Anchors = [akTop, akRight]
    Caption = 'Load'
    Enabled = False
    TabOrder = 1
    OnClick = ButtonLoadClick
  end
  object ButtonSave: TButton
    Left = 199
    Top = 39
    Width = 90
    Height = 25
    Anchors = [akTop, akRight]
    Caption = 'Save'
    TabOrder = 2
    OnClick = ButtonSaveClick
  end
  object ButtonDelete: TButton
    Left = 199
    Top = 70
    Width = 90
    Height = 25
    Anchors = [akTop, akRight]
    Caption = 'Delete'
    Enabled = False
    TabOrder = 3
    OnClick = ButtonDeleteClick
  end
  object ApplicationEvents: TApplicationEvents
    OnIdle = ApplicationEventsIdle
    Left = 8
    Top = 8
  end
end
