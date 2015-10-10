object FormMain: TFormMain
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = 'VolBalCon'
  ClientHeight = 201
  ClientWidth = 171
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBoxMaster: TGroupBox
    Left = 8
    Top = 8
    Width = 65
    Height = 185
    Caption = ' Master '
    TabOrder = 0
    object TrackBarMaster: TTrackBar
      Left = 16
      Top = 24
      Width = 45
      Height = 145
      Max = 100
      Orientation = trVertical
      PageSize = 10
      Frequency = 10
      TabOrder = 0
      OnChange = TrackBarMasterChange
    end
  end
  object GroupBoxChannels: TGroupBox
    Left = 79
    Top = 8
    Width = 82
    Height = 185
    Caption = ' Channels '
    TabOrder = 1
    object TrackBarChannel0: TTrackBar
      Left = 16
      Top = 24
      Width = 45
      Height = 145
      Max = 100
      Orientation = trVertical
      PageSize = 10
      Frequency = 10
      TabOrder = 0
      OnChange = TrackBarChannelChange
    end
  end
end
