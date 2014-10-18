VERSION 5.00
Begin VB.Form frmAddSched 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Dialog Caption"
   ClientHeight    =   4380
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   6045
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4380
   ScaleWidth      =   6045
   ShowInTaskbar   =   0   'False
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   1680
      TabIndex        =   11
      Tag             =   "Time"
      Top             =   2760
      Width           =   2415
   End
   Begin VB.ComboBox Combo1 
      Height          =   315
      Left            =   1680
      Style           =   2  'Dropdown List
      TabIndex        =   9
      Top             =   360
      Width           =   2415
   End
   Begin VB.TextBox Text4 
      Height          =   375
      Left            =   1680
      TabIndex        =   8
      Tag             =   "Date"
      Top             =   2160
      Width           =   2415
   End
   Begin VB.TextBox Text3 
      Height          =   375
      Left            =   1680
      TabIndex        =   7
      Tag             =   "Place"
      Top             =   1560
      Width           =   2415
   End
   Begin VB.TextBox Text2 
      Height          =   375
      Left            =   1680
      TabIndex        =   6
      Tag             =   "Topic"
      Top             =   960
      Width           =   2415
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   4680
      TabIndex        =   1
      Top             =   1920
      Width           =   1215
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "Add"
      Height          =   375
      Left            =   4680
      TabIndex        =   0
      Top             =   1320
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "Date"
      Height          =   375
      Index           =   4
      Left            =   240
      TabIndex        =   10
      Top             =   2160
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "Time "
      Height          =   375
      Index           =   3
      Left            =   240
      TabIndex        =   5
      Top             =   2760
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "Place "
      Height          =   375
      Index           =   2
      Left            =   240
      TabIndex        =   4
      Top             =   1560
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "Topic"
      Height          =   375
      Index           =   1
      Left            =   240
      TabIndex        =   3
      Top             =   960
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "Lecturer "
      Height          =   375
      Index           =   0
      Left            =   240
      TabIndex        =   2
      Top             =   360
      Width           =   1215
   End
End
Attribute VB_Name = "frmAddSched"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub getLecturers()
    Dim nm$, subj$, eml$, var%
    Combo1.Clear
    With dbRecordSet
        .Open "Select vName SNAME  from Lecturer", dbConn
        .MoveFirst
        While Not .BOF And Not .EOF
            nm = dbRecordSet!sname
            Combo1.AddItem nm
            .MoveNext
            var = var + 1
        Wend
        .Close
    End With
    Combo1.ListIndex = 0
End Sub

Private Sub CancelButton_Click()
    Unload Me
End Sub

Private Sub Form_Load()
    getLecturers
End Sub

Private Sub OKButton_Click()
    Validate
End Sub

Public Sub Validate()
    For Each cntl In Me.Controls
        If TypeOf cntl Is TextBox Then
            If cntl.Text = "" And Trim(cntl.Tag) <> "Other Skills" Then
                MsgBox "You left " & _
                        cntl.Tag & _
                        " Empty "
                Exit Sub
            End If
        End If
    Next cntl
    insertSched
End Sub

Public Sub insertSched()
    Dim lname As String
    id = "sl0001"
    temp = getMaxId("ScheduledLecture", "cSLectureId")
    If temp <> "" Then id = getNewId(ByVal temp)
    lname = Combo1.List(Combo1.ListIndex)
    lid = getLecId(ByVal lname)
    desc = Text2.Text
    place = Text3.Text
    ddate = Text4.Text
    ttime = Text1.Text
    With dbCommand
        .ActiveConnection = dbConn
        .CommandText = "insert into ScheduledLecture values ( '" & _
            id & "','" & lid & "','" & desc & "','" & _
            place & "','" & ddate & "','" & ttime & "')"
        .Execute
    End With
    MsgBox "Scheduled Lecture added"
    For Each cntl In Me.Controls
        If TypeOf cntl Is TextBox Then
            cntl.Text = ""
        End If
    Next cntl
End Sub
Public Function getLecId(ByVal lname As String)
    With dbRecordSet
        .Open "select cLecturerId ID from Lecturer where vName = '" & lname & "'", dbConn
        .MoveFirst
        getLecId = dbRecordSet!id
        .Close
    End With
End Function



