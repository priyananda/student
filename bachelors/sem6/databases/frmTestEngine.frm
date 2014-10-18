VERSION 5.00
Begin VB.Form frmTestEngine 
   BorderStyle     =   0  'None
   Caption         =   "Test Engine"
   ClientHeight    =   6555
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   6840
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6555
   ScaleWidth      =   6840
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command1 
      Caption         =   "Help"
      Height          =   495
      Left            =   5040
      TabIndex        =   16
      Top             =   5640
      Width           =   1575
   End
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   900
      Left            =   480
      Top             =   4920
   End
   Begin VB.OptionButton radAnswer 
      Caption         =   "Option 3"
      Height          =   255
      Index           =   4
      Left            =   2160
      TabIndex        =   15
      Top             =   4200
      Width           =   3015
   End
   Begin VB.OptionButton radAnswer 
      Caption         =   "Option 4"
      Height          =   255
      Index           =   3
      Left            =   2160
      TabIndex        =   14
      Top             =   3840
      Width           =   4455
   End
   Begin VB.OptionButton radAnswer 
      Caption         =   "Option 2"
      Height          =   255
      Index           =   2
      Left            =   2160
      TabIndex        =   13
      Top             =   3480
      Width           =   4455
   End
   Begin VB.OptionButton radAnswer 
      Caption         =   "Option1"
      Height          =   255
      Index           =   1
      Left            =   2160
      TabIndex        =   12
      Top             =   3120
      Width           =   4455
   End
   Begin VB.Frame Frame1 
      BackColor       =   &H8000000B&
      Height          =   1815
      Left            =   1920
      TabIndex        =   11
      Top             =   2880
      Width           =   4815
   End
   Begin VB.TextBox Text4 
      Appearance      =   0  'Flat
      Height          =   615
      Left            =   1920
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   10
      Top             =   2040
      Width           =   4815
   End
   Begin VB.TextBox Text3 
      Appearance      =   0  'Flat
      Height          =   375
      Left            =   1920
      TabIndex        =   9
      Top             =   1440
      Width           =   1215
   End
   Begin VB.TextBox Text2 
      Appearance      =   0  'Flat
      Height          =   375
      Left            =   1920
      TabIndex        =   8
      Top             =   840
      Width           =   2175
   End
   Begin VB.TextBox Text1 
      Appearance      =   0  'Flat
      Enabled         =   0   'False
      Height          =   375
      Left            =   1920
      TabIndex        =   7
      Top             =   240
      Width           =   1215
   End
   Begin VB.CommandButton btnComplete 
      Caption         =   "End Test "
      Height          =   495
      Left            =   240
      TabIndex        =   6
      Top             =   5760
      Width           =   1935
   End
   Begin VB.CommandButton btnNext 
      Appearance      =   0  'Flat
      Height          =   615
      Left            =   2880
      Picture         =   "frmTestEngine.frx":0000
      Style           =   1  'Graphical
      TabIndex        =   5
      Top             =   4920
      Width           =   735
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Answers"
      Height          =   375
      Index           =   4
      Left            =   240
      TabIndex        =   4
      Top             =   3120
      Width           =   1575
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Question"
      Height          =   375
      Index           =   3
      Left            =   240
      TabIndex        =   3
      Top             =   2160
      Width           =   1575
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Question Number"
      Height          =   375
      Index           =   2
      Left            =   240
      TabIndex        =   2
      Top             =   1440
      Width           =   1455
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Subject"
      Height          =   255
      Index           =   1
      Left            =   240
      TabIndex        =   1
      Top             =   840
      Width           =   1575
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Time Remaining :"
      Height          =   375
      Index           =   0
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   1575
   End
End
Attribute VB_Name = "frmTestEngine"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public subject As String
Public subjectId As String
Dim arrQues(30) As Question
Dim numQ As Integer
Dim currQ As Integer
Dim corr As Integer
Dim secs As Integer
Dim score As Integer
Private Sub btnComplete_Click()
    If MsgBox("Do You Really Want to End the Test", vbOKCancel, "Tech Tester Pro") = vbCancel Then Exit Sub
    endTest
End Sub

Private Sub btnNext_Click()
    'If MsgBox("Do You Really Want to Confirm the question", vbOKCancel, "Tech Tester Pro") = vbCancel Then Exit Sub
    currQ = currQ + 1
    If currQ = 11 Then
        endTest
        Exit Sub
    End If
    Dim temp%, ans%
    For temp = 1 To 4
        If radAnswer(temp).Value = True Then
            ans = temp
        End If
    Next temp
    If corr = ans Then score = score + 1
    putQues
End Sub

Private Sub Form_Load()
    secs = 10 * 60 '10 minutes
    Text1.Text = "10:00"
    Timer1.Enabled = True
    Text1.Enabled = False
    Text2.Enabled = False
    Text3.Enabled = False
    Text4.Enabled = False
    Text2.Text = subject '
    currQ = 1
    score = 0
    getQues
    If numQ < 10 Then
        MsgBox "Sorry , Not Enough Questions for you to take a test", vbCritical, "Tech Tester Pro"
        Timer1.Enabled = False
        Me.Hide
        Unload Me
        Exit Sub
    End If
    putQues
    Me.Show
End Sub

Private Sub Timer1_Timer()
    secs = secs - 1
    If secs = 0 Then
        endTest
    End If
    Min = Int(secs / 60)
    psecs = secs - Int(secs / 60) * 60
    Text1.Text = Min & ":" & psecs
End Sub
Private Sub endTest()
    Timer1.Enabled = False
    insertTestRecord
    frmScorePage.score = score
    frmScorePage.Show
    Me.Hide
    Unload Me
End Sub
Private Sub getQues()
    Dim i%
    i = 0
    With dbCommand
        .CommandText = "Select cSubjectId , vQuestion ,vOption1 ,vOption2 ,vOption3 ,vOption4,nWeightage,nAnswer from Question where cSubjectId = ( select cSubjectId from Subject where vName = '" & subject & "')"
        .ActiveConnection = dbConn
        Set dbRecordSet = .Execute
    End With
        If dbRecordSet.BOF Then GoTo fend
        'dbRecordSet.MoveFirst
        While Not dbRecordSet.BOF And Not dbRecordSet.EOF
            arrQues(i).vQuestion = dbRecordSet!vQuestion
            arrQues(i).vOption1 = dbRecordSet!vOption1
            arrQues(i).vOption2 = dbRecordSet!vOption2
            arrQues(i).vOption3 = dbRecordSet!vOption3
            arrQues(i).vOption4 = dbRecordSet!vOption4
            arrQues(i).correct = dbRecordSet!nAnswer
            i = i + 1
            dbRecordSet.MoveNext
        Wend
        dbRecordSet.Close
    numQ = i
    Exit Sub
fend:
    numQ = 0
    dbRecordSet.Close
End Sub

Private Function getRandQuestion() As Integer
    Randomize
    While Rnd() * Rnd() <= Rnd() * 1.23
        Randomize
    Wend
    getRandQuestion = (Int(Rnd() * 100) * numQ) / 100
End Function
Private Sub putQues()
    Dim x As Question
    rndQno = getRandQuestion()
    x = arrQues(rndQno)
    While Trim(x.vQuestion) = ""
        x = arrQues(getRandQuestion())
    Wend
    Text4.Text = x.vQuestion
    Text3.Text = currQ
    radAnswer(1).Caption = x.vOption1
    radAnswer(2).Caption = x.vOption2
    radAnswer(3).Caption = x.vOption3
    radAnswer(4).Caption = x.vOption4
    radAnswer(1).Value = True
    arrQues(rndQno).vQuestion = ""
    corr = x.correct
End Sub
Private Sub insertTestRecord()
    If score < 5 Then
        MsgBox "You have Failed in the Exam ", vbCritical
        Exit Sub
    End If
On Error Resume Next
    With dbCommand
        .ActiveConnection = dbConn
        .CommandText = "delete Test where cStudentId = '" & studentId & "' and cSubjectId = ( select cSubjectId from Subject where vName = '" & subject & "')"
        .Execute
        Dim id$, subj$, stud$
        id = "ts0001"
        subj = getSubjectId(subject)
        stud = studentId
        temp = getMaxId("Test", "cTestId")
        If temp <> "" Then id = getNewId(temp)
        .CommandText = "insert into Test values ( '" & id & "','" & subj & "','" & stud & "'," & score & ")"
        .Execute
        checkForCompleteNess
    End With
End Sub


Private Function getSubjectId(sname As String) As String
    With dbRecordSet
        .Open "select cSubjectId from Subject where vName = '" & sname & "'", dbConn
        .MoveFirst
        getSubjectId = dbRecordSet!cSubjectId
        .Close
    End With
End Function

Private Sub checkForCompleteNess()
    Dim total%, don%
    With dbRecordSet
        .Open "select count(cSubjectId) CNT from CourseSubject where cCourseId = ( select cCourseId from Student where cStudentId = '" & studentId & "')", dbConn
        .MoveFirst
        total = dbRecordSet!CNT
        .Close
        .Open "select count(cSubjectId) CNT from Test where cStudentId = '" & studentId & "'"
        don = dbRecordSet!CNT
        .Close
    End With
    If total = don Then
        With dbCommand
            .ActiveConnection = dbConn
            .CommandText = "update Student set bCompleted = 1 where cStudentId = '" & studentId & "'"
            .Execute
        End With
    End If
End Sub
