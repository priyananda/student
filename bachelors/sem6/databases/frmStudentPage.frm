VERSION 5.00
Object = "{0ECD9B60-23AA-11D0-B351-00A0C9055D8E}#6.0#0"; "MSHFLXGD.OCX"
Begin VB.Form frmStudentPage 
   Caption         =   "Form2"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "frmStudentPage"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   WindowState     =   2  'Maximized
   Begin VB.CommandButton Command3 
      Caption         =   "Open"
      Height          =   375
      Left            =   9720
      TabIndex        =   24
      Top             =   3600
      Width           =   1815
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Get Certificate"
      Height          =   375
      Left            =   9720
      TabIndex        =   23
      Top             =   6360
      Width           =   1815
   End
   Begin VB.CommandButton btnLogout 
      Caption         =   "Logout"
      Height          =   375
      Left            =   9720
      TabIndex        =   22
      Top             =   7920
      Width           =   1815
   End
   Begin VB.CommandButton btnUpdate 
      Caption         =   "Update Details"
      Height          =   375
      Left            =   5760
      TabIndex        =   21
      Top             =   7920
      Width           =   2535
   End
   Begin VB.TextBox txtCreditCardNo 
      Height          =   375
      Left            =   5760
      TabIndex        =   18
      Top             =   7200
      Width           =   2535
   End
   Begin VB.TextBox txtEmail 
      Height          =   375
      Left            =   5760
      TabIndex        =   17
      Top             =   6600
      Width           =   2535
   End
   Begin VB.TextBox txtAddress 
      Height          =   975
      Left            =   5760
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   16
      Top             =   5400
      Width           =   2535
   End
   Begin VB.OptionButton radSearchBy 
      BackColor       =   &H00FF8080&
      Caption         =   "Author"
      Height          =   255
      Index           =   0
      Left            =   4560
      TabIndex        =   14
      Top             =   600
      Width           =   855
   End
   Begin VB.OptionButton radSearchBy 
      BackColor       =   &H00FF8080&
      Caption         =   "Subject"
      Height          =   255
      Index           =   1
      Left            =   5520
      TabIndex        =   13
      Top             =   600
      Width           =   855
   End
   Begin VB.OptionButton radSearchBy 
      BackColor       =   &H00FF8080&
      Caption         =   "Keyword"
      Height          =   255
      Index           =   2
      Left            =   6480
      TabIndex        =   12
      Top             =   600
      Width           =   975
   End
   Begin VB.CommandButton btnGo 
      Caption         =   "Go !!"
      Height          =   375
      Left            =   10920
      TabIndex        =   11
      Top             =   600
      Width           =   615
   End
   Begin VB.TextBox Text1 
      Height          =   285
      Left            =   7680
      TabIndex        =   10
      Top             =   600
      Width           =   3015
   End
   Begin VB.CommandButton btnCourse 
      Caption         =   "Check Out the courses"
      Height          =   375
      Left            =   1080
      TabIndex        =   8
      Top             =   7080
      Width           =   2000
   End
   Begin VB.CommandButton Command2 
      Caption         =   "View Stats"
      Height          =   375
      Left            =   1080
      TabIndex        =   7
      Top             =   6240
      Width           =   2000
   End
   Begin VB.ListBox lstSubject 
      Appearance      =   0  'Flat
      Height          =   1395
      Left            =   1080
      TabIndex        =   6
      Top             =   1080
      Width           =   2000
   End
   Begin VB.CommandButton btnScore 
      Caption         =   "See Scores"
      Height          =   375
      Left            =   1080
      TabIndex        =   5
      Top             =   5400
      Width           =   2000
   End
   Begin VB.CommandButton cmdSampTest 
      Caption         =   "Take a Sample Test"
      Height          =   375
      Left            =   1080
      TabIndex        =   4
      Top             =   3480
      Width           =   2000
   End
   Begin VB.CommandButton cmdTest 
      Caption         =   "Take a Test"
      Height          =   375
      Left            =   1080
      TabIndex        =   1
      Top             =   2760
      Width           =   2000
   End
   Begin VB.CommandButton btnChange 
      Caption         =   "Change Password "
      Height          =   375
      Left            =   9720
      TabIndex        =   0
      Top             =   7080
      Width           =   1815
   End
   Begin MSHierarchicalFlexGridLib.MSHFlexGrid gridOutput 
      Height          =   2175
      Left            =   4560
      TabIndex        =   9
      Top             =   1320
      Visible         =   0   'False
      Width           =   6975
      _ExtentX        =   12303
      _ExtentY        =   3836
      _Version        =   393216
      Rows            =   30
      Cols            =   4
      SelectionMode   =   1
      AllowUserResizing=   1
      RowSizingMode   =   1
      _NumberOfBands  =   1
      _Band(0).Cols   =   4
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Credit Card Number"
      Height          =   375
      Index           =   4
      Left            =   4320
      TabIndex        =   20
      Top             =   7200
      Width           =   1335
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Address"
      Height          =   255
      Index           =   3
      Left            =   4320
      TabIndex        =   19
      Top             =   5520
      Width           =   1335
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Search On : "
      Height          =   375
      Index           =   2
      Left            =   4080
      TabIndex        =   15
      Top             =   360
      Width           =   1335
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Email Id"
      Height          =   255
      Index           =   1
      Left            =   4320
      TabIndex        =   3
      Top             =   6720
      Width           =   1335
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Choose Subject"
      Height          =   255
      Index           =   0
      Left            =   360
      TabIndex        =   2
      Top             =   720
      Width           =   1335
   End
   Begin VB.Image Image1 
      Height          =   9000
      Left            =   0
      Picture         =   "frmStudentPage.frx":0000
      Top             =   0
      Width           =   12000
   End
End
Attribute VB_Name = "frmStudentPage"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub btnChange_Click()
    frmChangeStudentPassword.Show vbModal
End Sub

Private Sub btnCourse_Click()
    frmAboutCourses.Show
End Sub
Private Sub btnGo_Click()
On Error GoTo ErrSx
    Dim zz$
    Dim scStr(0 To 2) As String
    zz$ = Trim(Text1.Text)
    If zz = "" Then Exit Sub
    gridOutput.Clear
    scStr(0) = "select * from OnlineLecture where cLecturerId IN ( select cLecturerId from Lecturer where vName like '%" & zz & "%')"
    scStr(1) = "select * from OnlineLecture ol, Lecturer l where l.cLecturerId = ol.cLecturerId and l.cSubjectId = ( select cSubjectId from Subject where vName = '" & zz & "')"
    scStr(2) = "select * from OnlineLecture where vkeyword like '%" & zz & "%'"
    For temp = 0 To 2
        If radSearchBy(temp).Value = True Then
            ans = temp
        End If
    Next temp
    gridOutput.TextMatrix(0, 0) = "SI"
    gridOutput.TextMatrix(0, 1) = "Description"
    gridOutput.TextMatrix(0, 2) = "Keyword"
    gridOutput.TextMatrix(0, 3) = "Path"
    temp = 1
    With dbRecordSet
        .Open scStr(ans), dbConn
        If .BOF Or .EOF Then
            MsgBox "Sorry , No Match for your query"
            .Close
            Exit Sub
        End If
        '.MoveFirst
        While Not .EOF And Not .BOF
            zz = dbRecordSet!vDescription
            kw = dbRecordSet!vKeyword
            pt = dbRecordSet!vPath
            gridOutput.TextMatrix(temp, 0) = temp
            gridOutput.TextMatrix(temp, 1) = zz
            gridOutput.TextMatrix(temp, 2) = kw
            gridOutput.TextMatrix(temp, 3) = pt
            temp = temp + 1
            .MoveNext
        Wend
        .Close
    End With
    gridOutput.Visible = True
    Exit Sub
ErrSx:
    MsgBox Err.Description
End Sub

Private Sub btnLogout_Click()
    Unload Me
End Sub

Private Sub btnScore_Click()
    frmPrevScore.Show vbModal
End Sub

Private Sub btnUpdate_Click()
    setDetails
End Sub

Private Sub cmdSampTest_Click()
On Error Resume Next
    If lstSubject.ListIndex = -1 Then Exit Sub
    frmSampleTest.subject = lstSubject.List(lstSubject.ListIndex)
    frmSampleTest.Show vbModal
End Sub

Private Sub cmdTest_Click()
On Error Resume Next
    If lstSubject.ListIndex = -1 Then Exit Sub
    frmTestEngine.subject = lstSubject.List(lstSubject.ListIndex)
    frmTestEngine.Show
End Sub

Private Sub Command1_Click()
On Error Resume Next
    frmCertificate.Show vbModal
End Sub

Private Sub Command2_Click()
    frmStats.Show vbModal
End Sub

Private Sub Command3_Click()
    If Trim(gridOutput.TextMatrix(gridOutput.RowSel, 3)) <> "" Then
        ShellExecute Me.hWnd, _
                "open", _
                gridOutput.TextMatrix(gridOutput.RowSel, 3), _
                " ", _
                " ", _
                1
    End If
End Sub

Private Sub Form_Load()
    getSubjects
    getDetails
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Form1.Show
End Sub

Private Sub getSubjects()
    Dim ss$, dd$
    lstSubject.Clear
    With dbRecordSet
        .Open "Select vName from Subject where cSubjectId IN ( select cSubjectId from CourseSubject where cCourseId = ( select cCourseId from Student where cStudentId = '" & studentId & "' ))", dbConn
        .MoveFirst
        While Not .BOF And Not .EOF
            ss = dbRecordSet!vName
            lstSubject.AddItem (ss)
            .MoveNext
        Wend
        .Close
    End With
End Sub

Private Sub getDetails()
    With dbRecordSet
        .Open "Select vAddress , vEmailId , cCCNumber from Student where cStudentId = '" & studentId & "'", dbConn
        .MoveFirst
        txtAddress.Text = dbRecordSet!vAddress
        txtEmail.Text = dbRecordSet!vEmailId
        txtCreditCardNo.Text = dbRecordSet!cCCNumber
        .Close
    End With
End Sub
Private Sub setDetails()
    With dbCommand
        .CommandText = "Update Student Set vAddress = '" & txtAddress.Text & "'" & _
            ",vEmailId = '" & txtEmail.Text & "', cCCNumber = '" & txtCreditCardNo.Text & "' where cStudentId = '" & studentId & "'"
        .ActiveConnection = dbConn
        .Execute
    End With
    MsgBox "Updated"
End Sub


