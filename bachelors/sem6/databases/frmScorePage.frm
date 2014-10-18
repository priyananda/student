VERSION 5.00
Object = "{65E121D4-0C60-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCHRT20.OCX"
Begin VB.Form frmScorePage 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Student Test Score"
   ClientHeight    =   4575
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   4710
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4575
   ScaleWidth      =   4710
   StartUpPosition =   3  'Windows Default
   Begin MSChart20Lib.MSChart MSChart1 
      Height          =   3135
      Left            =   360
      OleObjectBlob   =   "frmScorePage.frx":0000
      TabIndex        =   0
      Top             =   0
      Width           =   3975
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      BackStyle       =   0  'Transparent
      Height          =   375
      Left            =   240
      TabIndex        =   1
      Top             =   3360
      Width           =   4095
   End
End
Attribute VB_Name = "frmScorePage"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public score As Integer
Private Sub Form_Load()
    With MSChart1.DataGrid
        .ColumnCount = 2
        .RowCount = 1
        .SetData 1, 1, 10 - score, 0
        .SetData 1, 2, score, 0
        .ColumnLabel(2, 1) = "Correct"
        .RowLabel(1, 1) = "Your Results "
    End With
    Label1.Caption = "Your Score is " & score
End Sub
