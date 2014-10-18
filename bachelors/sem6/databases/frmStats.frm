VERSION 5.00
Object = "{65E121D4-0C60-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCHRT20.OCX"
Begin VB.Form frmStats 
   Caption         =   "Statistics"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form2"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   WindowState     =   2  'Maximized
   Begin MSChart20Lib.MSChart MSChart1 
      Height          =   6135
      Left            =   5040
      OleObjectBlob   =   "frmStats.frx":0000
      TabIndex        =   18
      Top             =   840
      Width           =   6495
   End
   Begin VB.Frame Frame1 
      Caption         =   "Courses"
      Height          =   2655
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Width           =   4455
      Begin VB.CommandButton btnCourse 
         Caption         =   "View Details"
         Height          =   375
         Left            =   600
         TabIndex        =   19
         Top             =   1080
         Width           =   3255
      End
      Begin VB.TextBox nCoursePas 
         Height          =   375
         Left            =   2880
         TabIndex        =   6
         Top             =   2160
         Width           =   1095
      End
      Begin VB.TextBox nCourseEn 
         Height          =   405
         Left            =   2880
         TabIndex        =   5
         Top             =   1560
         Width           =   1095
      End
      Begin VB.ComboBox cmbCourses 
         Height          =   315
         Left            =   1560
         Style           =   2  'Dropdown List
         TabIndex        =   2
         Top             =   600
         Width           =   2295
      End
      Begin VB.Label Label3 
         Caption         =   "Number Of Students Passed"
         Height          =   375
         Left            =   600
         TabIndex        =   4
         Top             =   2160
         Width           =   2175
      End
      Begin VB.Label Label2 
         Caption         =   "Number Of Students Enrolled"
         Height          =   255
         Index           =   0
         Left            =   600
         TabIndex        =   3
         Top             =   1680
         Width           =   2295
      End
      Begin VB.Label Label1 
         Caption         =   "Course"
         Height          =   255
         Left            =   600
         TabIndex        =   1
         Top             =   600
         Width           =   975
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "Subjects"
      Height          =   4935
      Left            =   120
      TabIndex        =   7
      Top             =   3000
      Width           =   4455
      Begin VB.CommandButton Command2 
         Caption         =   "View Details"
         Height          =   375
         Left            =   600
         TabIndex        =   20
         Top             =   1080
         Width           =   3255
      End
      Begin VB.TextBox nnumLec 
         Height          =   375
         Left            =   2880
         TabIndex        =   17
         Top             =   3600
         Width           =   1095
      End
      Begin VB.TextBox nAvg 
         Height          =   375
         Left            =   2880
         TabIndex        =   16
         Top             =   3000
         Width           =   1215
      End
      Begin VB.TextBox nHigh 
         Height          =   405
         Left            =   2880
         TabIndex        =   15
         Top             =   2400
         Width           =   1215
      End
      Begin VB.TextBox nStud 
         Height          =   375
         Left            =   2880
         TabIndex        =   14
         Top             =   1920
         Width           =   1215
      End
      Begin VB.ComboBox cmbSub 
         Height          =   315
         Left            =   1560
         Style           =   2  'Dropdown List
         TabIndex        =   9
         Top             =   480
         Width           =   2175
      End
      Begin VB.Label Label9 
         Caption         =   "Number Of Lecturers"
         Height          =   255
         Left            =   600
         TabIndex        =   13
         Top             =   3720
         Width           =   1575
      End
      Begin VB.Label Label8 
         Caption         =   "Average Marks"
         Height          =   255
         Left            =   600
         TabIndex        =   12
         Top             =   3000
         Width           =   1095
      End
      Begin VB.Label Label6 
         Caption         =   "Highest Marks "
         Height          =   375
         Left            =   600
         TabIndex        =   11
         Top             =   2400
         Width           =   1455
      End
      Begin VB.Label Label5 
         Caption         =   "Number Of Students Taking Up"
         Height          =   495
         Left            =   600
         TabIndex        =   10
         Top             =   1800
         Width           =   1575
      End
      Begin VB.Label Label4 
         Caption         =   "Subject"
         Height          =   255
         Left            =   600
         TabIndex        =   8
         Top             =   480
         Width           =   855
      End
   End
End
Attribute VB_Name = "frmStats"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub getSubjects()
    Dim ss$, dd$
    cmbSub.Clear
    With dbRecordSet
        .Open "Select vName from Subject", dbConn
        .MoveFirst
        While Not .BOF And Not .EOF
            ss = dbRecordSet!vName
            Call cmbSub.AddItem(ss)
            .MoveNext
        Wend
        .Close
        cmbSub.ListIndex = 0
    End With
End Sub
Private Sub GetCourses()
    Dim ss$
    cmbCourses.Clear
    With dbRecordSet
        .Open "Select vName from Course", dbConn
        .MoveFirst
        While Not .BOF And Not .EOF
            ss = dbRecordSet!vName
            Call cmbCourses.AddItem(ss)
            .MoveNext
        Wend
        .Close
        cmbCourses.ListIndex = 0
    End With
End Sub

Private Sub btnCourse_Click()
    With dbRecordSet
        .Open "Select Count(cStudentId) CNT from Student where cCourseId = ( select cCourseId from Course where vName='" & cmbCourses.List(cmbCourses.ListIndex) & "')", dbConn
        .MoveFirst
        nCourseEn.Text = dbRecordSet!CNT
        .Close
        .Open "Select Count(cStudentId) CNT from Student where bCompleted = 1 and cCourseId = ( select cCourseId from Course where vName='" & cmbCourses.List(cmbCourses.ListIndex) & "')", dbConn
        .MoveFirst
        nCoursePas.Text = dbRecordSet!CNT
        .Close
    End With
End Sub

Private Sub Command2_Click()
    With dbRecordSet
        .Open "Select Count(cStudentId) CNT from Test where cSubjectId = ( select cSubjectId from Subject where vName='" & cmbSub.List(cmbSub.ListIndex) & "')", dbConn
        .MoveFirst
        nStud.Text = dbRecordSet!CNT
        .Close
        .Open "Select Max(nMarks) MX, Avg (nMarks) AV from Test where cSubjectId = ( select cSubjectId from Subject where vName='" & cmbSub.List(cmbSub.ListIndex) & "')", dbConn
        nHigh.Text = "0"
        nAvg.Text = "0"
        If .BOF Then GoTo skip
        .MoveFirst
        nHigh.Text = dbRecordSet!MX
        nAvg.Text = dbRecordSet!AV
skip:
        .Close
        .Open "Select COunt(cLecturerId) CNT from Lecturer where cSubjectId = ( select cSubjectId from Subject where vName='" & cmbSub.List(cmbSub.ListIndex) & "')", dbConn
        .MoveFirst
        nnumLec.Text = dbRecordSet!CNT
        .Close
    End With
End Sub

Private Sub Form_Load()
    getConnection
    getSubjects
    GetCourses
    MSChart1.RowCount = 1
    fillGraph
End Sub


Private Sub fillGraph()
    dbRecordSet.Open "select count( StudentId ) CNT , CourseName ID from Student_Course group by CourseName", dbConn
    dbRecordSet.MoveFirst
    Dim i As Integer
    Dim dd As Double
    Dim ss$
    i = 1
    While Not dbRecordSet.BOF And Not dbRecordSet.EOF
        With MSChart1.DataGrid
            dd = dbRecordSet!CNT
            ss = dbRecordSet!id
            If i > 4 Then .InsertColumns i, 1
            .SetData 1, ByVal i, dd, 0
            .ColumnLabel(i, 1) = ss
            i = i + 1
        End With
        dbRecordSet.MoveNext
    Wend
    dbRecordSet.Close
End Sub

