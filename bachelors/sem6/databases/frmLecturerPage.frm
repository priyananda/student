VERSION 5.00
Begin VB.Form frmLecturerPage 
   Caption         =   "Form2"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form2"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   WindowState     =   2  'Maximized
   Begin VB.CommandButton Command2 
      Caption         =   "Logout"
      Height          =   375
      Left            =   10200
      TabIndex        =   23
      Top             =   240
      Width           =   1575
   End
   Begin VB.TextBox Text4 
      Height          =   375
      Left            =   1920
      TabIndex        =   21
      Top             =   4680
      Width           =   3135
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Add Material"
      Height          =   615
      Left            =   2880
      TabIndex        =   16
      Top             =   5280
      Width           =   2175
   End
   Begin VB.TextBox Text3 
      Height          =   375
      Left            =   1920
      TabIndex        =   15
      Top             =   3960
      Width           =   3135
   End
   Begin VB.TextBox Text2 
      Height          =   375
      Left            =   1920
      TabIndex        =   14
      Top             =   3240
      Width           =   3135
   End
   Begin VB.TextBox Text1 
      Height          =   975
      Left            =   1920
      TabIndex        =   13
      Top             =   1800
      Width           =   3135
   End
   Begin VB.TextBox txtQuestion 
      Appearance      =   0  'Flat
      Height          =   735
      Left            =   6840
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   9
      Top             =   3360
      Width           =   3735
   End
   Begin VB.TextBox op1 
      Height          =   375
      Left            =   6840
      TabIndex        =   8
      Top             =   5760
      Width           =   3735
   End
   Begin VB.TextBox op2 
      Height          =   375
      Left            =   6840
      TabIndex        =   7
      Top             =   6240
      Width           =   3735
   End
   Begin VB.TextBox op3 
      Height          =   375
      Left            =   6840
      TabIndex        =   6
      Top             =   6720
      Width           =   3735
   End
   Begin VB.TextBox op4 
      Height          =   375
      Left            =   6840
      TabIndex        =   5
      Top             =   7200
      Width           =   3735
   End
   Begin VB.Frame frmNew 
      BackColor       =   &H8000000A&
      Height          =   1815
      Left            =   10560
      TabIndex        =   0
      Top             =   5760
      Width           =   735
      Begin VB.OptionButton Option1 
         Caption         =   "Option1"
         Height          =   255
         Left            =   0
         TabIndex        =   4
         Top             =   120
         Value           =   -1  'True
         Width           =   255
      End
      Begin VB.OptionButton Option2 
         Caption         =   "Option2"
         Height          =   255
         Left            =   480
         TabIndex        =   3
         Top             =   600
         Width           =   255
      End
      Begin VB.OptionButton Option3 
         Caption         =   "Option3"
         Height          =   255
         Left            =   0
         TabIndex        =   2
         Top             =   1080
         Width           =   255
      End
      Begin VB.OptionButton Option4 
         Caption         =   "Option4"
         Height          =   255
         Left            =   480
         TabIndex        =   1
         Top             =   1560
         Width           =   255
      End
   End
   Begin VB.Label Label10 
      BackStyle       =   0  'Transparent
      Caption         =   "Keyword"
      ForeColor       =   &H0080FFFF&
      Height          =   375
      Index           =   4
      Left            =   120
      TabIndex        =   22
      Top             =   4800
      Width           =   1215
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Add Questions"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.5
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0080C0FF&
      Height          =   615
      Index           =   1
      Left            =   6960
      TabIndex        =   20
      Top             =   2280
      Width           =   4455
   End
   Begin VB.Label Label10 
      BackStyle       =   0  'Transparent
      Caption         =   "Path"
      ForeColor       =   &H0080FFFF&
      Height          =   375
      Index           =   3
      Left            =   120
      TabIndex        =   19
      Top             =   3960
      Width           =   1215
   End
   Begin VB.Label Label10 
      BackStyle       =   0  'Transparent
      Caption         =   "Type"
      ForeColor       =   &H0080FFFF&
      Height          =   375
      Index           =   2
      Left            =   120
      TabIndex        =   18
      Top             =   3240
      Width           =   1215
   End
   Begin VB.Label Label10 
      BackStyle       =   0  'Transparent
      Caption         =   "Description"
      ForeColor       =   &H0080FFFF&
      Height          =   375
      Index           =   1
      Left            =   120
      TabIndex        =   17
      Top             =   1920
      Width           =   1215
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Add Online Lecture material "
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.5
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0080C0FF&
      Height          =   615
      Index           =   0
      Left            =   480
      TabIndex        =   12
      Top             =   1200
      Width           =   4455
   End
   Begin VB.Label Label10 
      BackStyle       =   0  'Transparent
      Caption         =   "Question"
      ForeColor       =   &H0080FFFF&
      Height          =   255
      Index           =   0
      Left            =   5400
      TabIndex        =   11
      Top             =   3360
      Width           =   1215
   End
   Begin VB.Label Label13 
      BackStyle       =   0  'Transparent
      Caption         =   "Options"
      ForeColor       =   &H0080FFFF&
      Height          =   255
      Left            =   5400
      TabIndex        =   10
      Top             =   5760
      Width           =   855
   End
   Begin VB.Image btnAddQuestion 
      Height          =   750
      Left            =   10560
      Picture         =   "frmLecturerPage.frx":0000
      Top             =   7680
      Width           =   750
   End
   Begin VB.Image Image1 
      Height          =   8655
      Left            =   0
      Picture         =   "frmLecturerPage.frx":043A
      Stretch         =   -1  'True
      Top             =   0
      Width           =   11895
   End
End
Attribute VB_Name = "frmLecturerPage"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim lsid As String
Private Sub btnAddQuestion_Click()
    Dim qs As Question
    qs.vQuestion = Trim(txtQuestion.Text)
    qs.vOption1 = Trim(op1.Text)
    qs.vOption2 = Trim(op2.Text)
    qs.vOption3 = Trim(op3.Text)
    qs.vOption4 = Trim(op4.Text)
    If qs.vQuestion = "" Or qs.vOption1 = "" Or qs.vOption2 = "" Or qs.vOption3 = "" Or qs.vOption4 = "" Then
        MsgBox "Please Fill up the Values"
        Exit Sub
    End If
    If Option1.Value Then
        qs.correct = 1
    End If
    If Option2.Value Then
        qs.correct = 2
    End If
    If Option3.Value Then
        qs.correct = 3
    End If
    If Option4.Value Then
        qs.correct = 4
    End If
    qs.cSubjectId = lsid
    qs.weight = 1
    insertQuestion qs
    op1.Text = ""
    op2.Text = ""
    op3.Text = ""
    op4.Text = ""
    MsgBox "Question added"
End Sub

Private Sub Command1_Click()
On Error GoTo EeW
    If Text1.Text = "" Or Text2.Text = "" Or Text3.Text = "" Or Text4.Text = "" Then
        MsgBox "Please Fill up the Values"
        Exit Sub
    End If
    olid = "ol0001"
    temp = getMaxId("OnlineLecture", "cOLectureId")
    If temp <> "" Then olid = getNewId(temp)
    With dbCommand
        .ActiveConnection = dbConn
        .CommandText = "insert into OnlineLecture values('" & olid & "','" & lecturerId & "','" & Text1.Text & "','" & _
            Text2.Text & "','" & Text3.Text & "','" & Text4.Text & "')"
        .Execute
    End With
    Text1.Text = ""
    Text2.Text = ""
    Text3.Text = ""
    Text4.Text = ""
    MsgBox "Online Lecture Added"
    Exit Sub
EeW:
    MsgBox "Oops Error"
End Sub
Private Sub Command2_Click()
    Unload Me
End Sub

Private Sub Form_Load()
    getLecSubj
End Sub

Private Sub getLecSubj()
    With dbRecordSet
        .Open "select cSubjectId from Lecturer where cLecturerId = '" & lecturerId & "'", dbConn
        .MoveFirst
        lsid = dbRecordSet!cSubjectId
        .Close
    End With
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Form1.Show
End Sub

