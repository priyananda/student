VERSION 5.00
Object = "{65E121D4-0C60-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCHRT20.OCX"
Begin VB.Form frmPrevScore 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Dialog Caption"
   ClientHeight    =   5265
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   7050
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5265
   ScaleWidth      =   7050
   ShowInTaskbar   =   0   'False
   Begin MSChart20Lib.MSChart MSChart1 
      Height          =   5295
      Left            =   0
      OleObjectBlob   =   "frmPrevScore.frx":0000
      TabIndex        =   0
      Top             =   0
      Width           =   7095
   End
End
Attribute VB_Name = "frmPrevScore"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private Sub Form_Load()
    Dim i%, mk$, idd$
    i = 1
    With dbRecordSet
        .Open "Select vName IDD , nMarks MK from Test t , subject s where t.csubjectId = s.cSubjectId and cStudentId = '" & studentId & "'"
        If .BOF Then GoTo endfi
        '.MoveFirst
        While Not .BOF And Not .EOF
            mk = dbRecordSet!mk
            idd = dbRecordSet!idd
            MSChart1.DataGrid.InsertColumns i, 1
            MSChart1.DataGrid.SetData 1, i, mk, 0
            MSChart1.DataGrid.ColumnLabel(i, 1) = idd
            .MoveNext
            i = i + 1
        Wend
        MSChart1.DataGrid.InsertColumns i, 1
        MSChart1.DataGrid.SetData 1, i, 10, 0
        MSChart1.DataGrid.ColumnLabel(i, 1) = "Maximum"
        .Close
    End With
    Exit Sub
endfi:
    MsgBox "You have Not passed any previous tests"
    dbRecordSet.Close
End Sub
