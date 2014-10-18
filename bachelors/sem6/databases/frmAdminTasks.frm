VERSION 5.00
Object = "{0ECD9B60-23AA-11D0-B351-00A0C9055D8E}#6.0#0"; "MSHFLXGD.OCX"
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Begin VB.Form frmAdminTasks 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Administrative Tasks"
   ClientHeight    =   7455
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   6945
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   7455
   ScaleWidth      =   6945
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton btnOK 
      Caption         =   "O K "
      Height          =   495
      Left            =   5520
      TabIndex        =   0
      Top             =   6720
      Width           =   1215
   End
   Begin TabDlg.SSTab tsAdmin 
      Height          =   6495
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   6780
      _ExtentX        =   11959
      _ExtentY        =   11456
      _Version        =   393216
      Tabs            =   6
      Tab             =   2
      TabHeight       =   520
      BackColor       =   -2147483638
      ForeColor       =   8388608
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      TabCaption(0)   =   "Scheduled Lecture"
      TabPicture(0)   =   "frmAdminTasks.frx":0000
      Tab(0).ControlEnabled=   0   'False
      Tab(0).Control(0)=   "gridSched"
      Tab(0).Control(1)=   "btnAddSched"
      Tab(0).Control(2)=   "btnDelSched"
      Tab(0).ControlCount=   3
      TabCaption(1)   =   "Subject"
      TabPicture(1)   =   "frmAdminTasks.frx":001C
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "Label5"
      Tab(1).Control(1)=   "Label4(0)"
      Tab(1).Control(2)=   "Label1(2)"
      Tab(1).Control(3)=   "Label1(1)"
      Tab(1).Control(4)=   "Label1(0)"
      Tab(1).Control(5)=   "btnDelSubject"
      Tab(1).Control(6)=   "btnAddSubject"
      Tab(1).Control(7)=   "cmbSub"
      Tab(1).Control(8)=   "txtSubDesc"
      Tab(1).Control(9)=   "txtSubname"
      Tab(1).ControlCount=   10
      TabCaption(2)   =   "Course"
      TabPicture(2)   =   "frmAdminTasks.frx":0038
      Tab(2).ControlEnabled=   -1  'True
      Tab(2).Control(0)=   "Label7"
      Tab(2).Control(0).Enabled=   0   'False
      Tab(2).Control(1)=   "Label6"
      Tab(2).Control(1).Enabled=   0   'False
      Tab(2).Control(2)=   "Label3"
      Tab(2).Control(2).Enabled=   0   'False
      Tab(2).Control(3)=   "Label2(2)"
      Tab(2).Control(3).Enabled=   0   'False
      Tab(2).Control(4)=   "btnDelCourse"
      Tab(2).Control(4).Enabled=   0   'False
      Tab(2).Control(5)=   "btnAddCourse"
      Tab(2).Control(5).Enabled=   0   'False
      Tab(2).Control(6)=   "Label8"
      Tab(2).Control(6).Enabled=   0   'False
      Tab(2).Control(7)=   "Label9"
      Tab(2).Control(7).Enabled=   0   'False
      Tab(2).Control(8)=   "txtCourseDesc"
      Tab(2).Control(8).Enabled=   0   'False
      Tab(2).Control(9)=   "cmbCourses"
      Tab(2).Control(9).Enabled=   0   'False
      Tab(2).Control(10)=   "lstSubjects"
      Tab(2).Control(10).Enabled=   0   'False
      Tab(2).Control(11)=   "txtCourseName"
      Tab(2).Control(11).Enabled=   0   'False
      Tab(2).ControlCount=   12
      TabCaption(3)   =   "Questions"
      TabPicture(3)   =   "frmAdminTasks.frx":0054
      Tab(3).ControlEnabled=   0   'False
      Tab(3).Control(0)=   "Label10"
      Tab(3).Control(0).Enabled=   0   'False
      Tab(3).Control(1)=   "Label11"
      Tab(3).Control(1).Enabled=   0   'False
      Tab(3).Control(2)=   "Label13"
      Tab(3).Control(2).Enabled=   0   'False
      Tab(3).Control(3)=   "btnAddQuestion"
      Tab(3).Control(3).Enabled=   0   'False
      Tab(3).Control(4)=   "Label14"
      Tab(3).Control(4).Enabled=   0   'False
      Tab(3).Control(5)=   "txtQuestion"
      Tab(3).Control(5).Enabled=   0   'False
      Tab(3).Control(6)=   "cmbQSub"
      Tab(3).Control(6).Enabled=   0   'False
      Tab(3).Control(7)=   "op1"
      Tab(3).Control(7).Enabled=   0   'False
      Tab(3).Control(8)=   "op2"
      Tab(3).Control(8).Enabled=   0   'False
      Tab(3).Control(9)=   "op3"
      Tab(3).Control(9).Enabled=   0   'False
      Tab(3).Control(10)=   "op4"
      Tab(3).Control(10).Enabled=   0   'False
      Tab(3).Control(11)=   "frmNew"
      Tab(3).Control(11).Enabled=   0   'False
      Tab(3).ControlCount=   12
      TabCaption(4)   =   "Student"
      TabPicture(4)   =   "frmAdminTasks.frx":0070
      Tab(4).ControlEnabled=   0   'False
      Tab(4).Control(0)=   "gridStudent"
      Tab(4).Control(0).Enabled=   0   'False
      Tab(4).ControlCount=   1
      TabCaption(5)   =   "Lecturer"
      TabPicture(5)   =   "frmAdminTasks.frx":008C
      Tab(5).ControlEnabled=   0   'False
      Tab(5).Control(0)=   "gridLecturer"
      Tab(5).Control(0).Enabled=   0   'False
      Tab(5).ControlCount=   1
      Begin VB.CommandButton btnDelSched 
         Caption         =   "Delete Scheduled Lecture"
         Height          =   615
         Left            =   -70560
         TabIndex        =   39
         Top             =   4800
         Width           =   1935
      End
      Begin VB.CommandButton btnAddSched 
         Caption         =   "Add Scheduled Lecture"
         Height          =   615
         Left            =   -74640
         TabIndex        =   38
         Top             =   4800
         Width           =   1935
      End
      Begin MSHierarchicalFlexGridLib.MSHFlexGrid gridSched 
         Height          =   3015
         Left            =   -74760
         TabIndex        =   37
         Top             =   1080
         Width           =   5895
         _ExtentX        =   10398
         _ExtentY        =   5318
         _Version        =   393216
         Rows            =   20
         Cols            =   6
         SelectionMode   =   1
         AllowUserResizing=   1
         Appearance      =   0
         FormatString    =   "SI|<Lecturer Name  |<Topic ( Subject ) |<Place |< Date |<    Time"
         _NumberOfBands  =   1
         _Band(0).Cols   =   6
      End
      Begin VB.Frame frmNew 
         Height          =   1935
         Left            =   -69240
         TabIndex        =   31
         Top             =   3480
         Width           =   735
         Begin VB.OptionButton Option4 
            Caption         =   "Option4"
            Height          =   255
            Left            =   480
            TabIndex        =   35
            Top             =   1560
            Width           =   255
         End
         Begin VB.OptionButton Option3 
            Caption         =   "Option3"
            Height          =   255
            Left            =   0
            TabIndex        =   34
            Top             =   1080
            Width           =   255
         End
         Begin VB.OptionButton Option2 
            Caption         =   "Option2"
            Height          =   255
            Left            =   480
            TabIndex        =   33
            Top             =   600
            Width           =   255
         End
         Begin VB.OptionButton Option1 
            Caption         =   "Option1"
            Height          =   255
            Left            =   0
            TabIndex        =   32
            Top             =   120
            Value           =   -1  'True
            Width           =   255
         End
      End
      Begin VB.TextBox op4 
         Height          =   375
         Left            =   -73200
         TabIndex        =   30
         Top             =   5040
         Width           =   3735
      End
      Begin VB.TextBox op3 
         Height          =   375
         Left            =   -73200
         TabIndex        =   29
         Top             =   4560
         Width           =   3735
      End
      Begin VB.TextBox op2 
         Height          =   375
         Left            =   -73200
         TabIndex        =   28
         Top             =   4080
         Width           =   3735
      End
      Begin VB.TextBox op1 
         Height          =   375
         Left            =   -73200
         TabIndex        =   27
         Top             =   3600
         Width           =   3735
      End
      Begin VB.ComboBox cmbQSub 
         Appearance      =   0  'Flat
         Height          =   315
         Left            =   -73200
         Style           =   2  'Dropdown List
         TabIndex        =   26
         Top             =   2160
         Width           =   2895
      End
      Begin VB.TextBox txtQuestion 
         Appearance      =   0  'Flat
         Height          =   735
         Left            =   -73200
         MultiLine       =   -1  'True
         ScrollBars      =   2  'Vertical
         TabIndex        =   25
         Top             =   1200
         Width           =   3735
      End
      Begin VB.TextBox txtSubname 
         Appearance      =   0  'Flat
         Height          =   375
         Left            =   -72240
         TabIndex        =   9
         Top             =   1800
         Width           =   2055
      End
      Begin VB.TextBox txtSubDesc 
         Appearance      =   0  'Flat
         Height          =   375
         Left            =   -72240
         TabIndex        =   8
         Top             =   2520
         Width           =   2055
      End
      Begin VB.ComboBox cmbSub 
         Appearance      =   0  'Flat
         Height          =   315
         ItemData        =   "frmAdminTasks.frx":00A8
         Left            =   -72240
         List            =   "frmAdminTasks.frx":00AA
         Style           =   2  'Dropdown List
         TabIndex        =   7
         Top             =   3960
         Width           =   2055
      End
      Begin VB.TextBox txtCourseName 
         Appearance      =   0  'Flat
         Height          =   375
         Left            =   2280
         TabIndex        =   6
         Top             =   1320
         Width           =   2895
      End
      Begin VB.ListBox lstSubjects 
         Appearance      =   0  'Flat
         Height          =   1380
         ItemData        =   "frmAdminTasks.frx":00AC
         Left            =   2280
         List            =   "frmAdminTasks.frx":00AE
         Style           =   1  'Checkbox
         TabIndex        =   5
         Top             =   2640
         Width           =   2895
      End
      Begin VB.ComboBox cmbCourses 
         Height          =   315
         Left            =   2280
         Style           =   2  'Dropdown List
         TabIndex        =   4
         Top             =   5040
         Width           =   2895
      End
      Begin VB.TextBox txtCourseDesc 
         Appearance      =   0  'Flat
         Height          =   615
         Left            =   2280
         MultiLine       =   -1  'True
         ScrollBars      =   2  'Vertical
         TabIndex        =   2
         Top             =   1800
         Width           =   2895
      End
      Begin MSHierarchicalFlexGridLib.MSHFlexGrid gridStudent 
         Height          =   4575
         Left            =   -74880
         TabIndex        =   3
         Top             =   1320
         Width           =   6375
         _ExtentX        =   11245
         _ExtentY        =   8070
         _Version        =   393216
         Rows            =   30
         Cols            =   5
         AllowUserResizing=   3
         BorderStyle     =   0
         Appearance      =   0
         FormatString    =   "^SI |< Student Name  |< Course Name  |<Email Address|<Completed "
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Trebuchet MS"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         _NumberOfBands  =   1
         _Band(0).Cols   =   5
         _Band(0).GridLinesBand=   1
         _Band(0).TextStyleBand=   0
         _Band(0).TextStyleHeader=   0
      End
      Begin MSHierarchicalFlexGridLib.MSHFlexGrid gridLecturer 
         Height          =   4575
         Left            =   -74880
         TabIndex        =   10
         Top             =   1320
         Width           =   6375
         _ExtentX        =   11245
         _ExtentY        =   8070
         _Version        =   393216
         Rows            =   30
         Cols            =   4
         AllowUserResizing=   3
         BorderStyle     =   0
         Appearance      =   0
         FormatString    =   "^SI |< Lecturer  Name  |< Subject Name  |<Email Address"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Trebuchet MS"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         _NumberOfBands  =   1
         _Band(0).Cols   =   4
         _Band(0).GridLinesBand=   1
         _Band(0).TextStyleBand=   0
         _Band(0).TextStyleHeader=   0
      End
      Begin VB.Label Label14 
         Caption         =   "Answer"
         Height          =   255
         Left            =   -69120
         TabIndex        =   36
         Top             =   3120
         Width           =   615
      End
      Begin VB.Image btnAddQuestion 
         Height          =   750
         Left            =   -69480
         Picture         =   "frmAdminTasks.frx":00B0
         Top             =   5520
         Width           =   750
      End
      Begin VB.Label Label13 
         Caption         =   "Options"
         Height          =   255
         Left            =   -74640
         TabIndex        =   24
         Top             =   3600
         Width           =   855
      End
      Begin VB.Label Label11 
         Caption         =   "Subject"
         Height          =   255
         Left            =   -74640
         TabIndex        =   23
         Top             =   2160
         Width           =   855
      End
      Begin VB.Label Label10 
         Caption         =   "Question"
         Height          =   255
         Left            =   -74640
         TabIndex        =   22
         Top             =   1200
         Width           =   1215
      End
      Begin VB.Label Label9 
         Caption         =   "Delete A  Course"
         Height          =   375
         Left            =   240
         TabIndex        =   21
         Top             =   4320
         Width           =   1695
      End
      Begin VB.Label Label8 
         Caption         =   "Add a New Course"
         Height          =   255
         Left            =   360
         TabIndex        =   20
         Top             =   960
         Width           =   1695
      End
      Begin VB.Image btnAddSubject 
         Height          =   750
         Left            =   -69600
         Picture         =   "frmAdminTasks.frx":04EA
         Top             =   1920
         Width           =   750
      End
      Begin VB.Image btnDelSubject 
         Height          =   750
         Left            =   -69600
         Picture         =   "frmAdminTasks.frx":0924
         Top             =   3600
         Width           =   750
      End
      Begin VB.Image btnAddCourse 
         Height          =   750
         Left            =   5520
         Picture         =   "frmAdminTasks.frx":0CA9
         Top             =   1920
         Width           =   750
      End
      Begin VB.Image btnDelCourse 
         Height          =   750
         Left            =   5520
         Picture         =   "frmAdminTasks.frx":10E3
         Top             =   4800
         Width           =   750
      End
      Begin VB.Label Label2 
         Caption         =   "Subjects"
         Height          =   375
         Index           =   2
         Left            =   960
         TabIndex        =   19
         Top             =   2640
         Width           =   855
      End
      Begin VB.Label Label1 
         BackStyle       =   0  'Transparent
         Caption         =   "Subject Name "
         Height          =   255
         Index           =   0
         Left            =   -73680
         TabIndex        =   18
         Top             =   1920
         Width           =   1215
      End
      Begin VB.Label Label1 
         BackStyle       =   0  'Transparent
         Caption         =   "Desciption"
         Height          =   255
         Index           =   1
         Left            =   -73680
         TabIndex        =   17
         Top             =   2520
         Width           =   1215
      End
      Begin VB.Label Label1 
         BackStyle       =   0  'Transparent
         Caption         =   "Subject Name "
         Height          =   255
         Index           =   2
         Left            =   -73680
         TabIndex        =   16
         Top             =   3960
         Width           =   1335
      End
      Begin VB.Label Label3 
         Alignment       =   2  'Center
         BackStyle       =   0  'Transparent
         Caption         =   "Warning -You cannot  delete a course with students enrolled"
         Height          =   375
         Left            =   0
         TabIndex        =   15
         Top             =   5760
         Width           =   6615
      End
      Begin VB.Label Label4 
         Caption         =   "Add a new Subject"
         Height          =   255
         Index           =   0
         Left            =   -74280
         TabIndex        =   14
         Top             =   1320
         Width           =   1695
      End
      Begin VB.Label Label5 
         Caption         =   "Delete a subject"
         Height          =   255
         Left            =   -74280
         TabIndex        =   13
         Top             =   3240
         Width           =   1575
      End
      Begin VB.Label Label6 
         Caption         =   "Course Name"
         Height          =   375
         Left            =   960
         TabIndex        =   12
         Top             =   1440
         Width           =   1095
      End
      Begin VB.Label Label7 
         Caption         =   "Description"
         Height          =   255
         Left            =   960
         TabIndex        =   11
         Top             =   1920
         Width           =   1215
      End
   End
End
Attribute VB_Name = "frmAdminTasks"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim clnSub As Collection
Dim clnCourse As Collection
Dim clnSched As Collection
Private Sub btnAddCourse_Click()
    On Error GoTo ttt
    Dim nm$, cid$, desc$, temp$
    nm = Trim(txtCourseName.Text)
    desc = Trim(txtCourseDesc.Text)
    If nm = "" Or desc = "" Then
        MsgBox "Please Fill up the Values"
        Exit Sub
    End If
    If checkCourse(nm) Then
        MsgBox "Course Already Present", vbCritical, "oops"
        Exit Sub
    End If
    temp = getMaxId("Course", "cCourseId")
    If temp <> "" Then
        cid = getNewId(ByVal temp)
    Else
        cid = "cr0001"
    End If
    dbCommand.CommandText = "insert into Course values ('" & _
        cid & "','" & _
        nm & "','" & _
        desc & "',1)"
    dbCommand.ActiveConnection = dbConn
    dbCommand.Execute
    For i = 0 To (lstSubjects.ListCount - 1)
        If lstSubjects.Selected(i) Then
            dbCommand.CommandText = "insert into CourseSubject values ('" & _
               cid & "','" & _
               clnSub.Item(i + 1) & "')"
            dbCommand.Execute
        End If
    Next i
    MsgBox "Course Added"
    txtCourseDesc.Text = ""
    txtCourseName.Text = ""
    GetCourses
    Exit Sub
ttt:
    MsgBox Err.Description, vbCritical, "Oops"
End Sub

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
    qs.cSubjectId = clnSub.Item(cmbQSub.ListIndex + 1)
    qs.weight = 1
    insertQuestion qs
    txtQuestion.Text = ""
    op1.Text = ""
    op2.Text = ""
    op3.Text = ""
    op4.Text = ""
    MsgBox "Question Inserted"
End Sub

Private Sub btnAddSched_Click()
    frmAddSched.Show vbModal
    getSched
End Sub

Private Sub btnAddSubject_Click()
    On Error GoTo ttt
    Dim sid$, nm$, desc$, id$
    sid = getMaxId("Subject", "cSubjectId")
    If Trim(sid) = "" Then
        id = "sb0001"
    Else
        id = getNewId(ByVal sid)
    End If
    nm = Trim(txtSubname.Text)
    desc = Trim(txtSubDesc.Text)
    If nm = "" Or desc = "" Then
        MsgBox "Please Fill up the Values"
        Exit Sub
    End If
    If checkSubject(nm) Then
        MsgBox "Subject Already Present", vbCritical, "oops"
        Exit Sub
    End If
    dbCommand.CommandText = "insert into Subject values ('" & _
        id & "','" & _
        nm & "','" & _
        desc & "')"
    dbCommand.ActiveConnection = dbConn
    dbCommand.Execute
    txtSubname.Text = ""
    txtSubDesc.Text = ""
    getSubjects
    MsgBox "Subject Added"
    Exit Sub
ttt:
    MsgBox Err.Description
End Sub

Private Sub btnDelCourse_Click()
On Error GoTo park
    Dim ss$
    ss = Trim(cmbCourses)
    dbCommand.CommandText = "delete CourseSubject where cCourseId in ( select cCourseId from Course where vName = '" & ss & "')"
    dbCommand.ActiveConnection = dbConn
    dbCommand.Execute
    dbCommand.CommandText = "delete Course where vName = '" & ss & "'"
    dbCommand.Execute
    GetCourses
    MsgBox "Course Deleted"
    Exit Sub
park:
    setCourseDead (ss)
    MsgBox "You Cannot Delete a Course which has students ", vbCritical, "Tech Tester Pro"
End Sub

Private Sub btnDelSched_Click()
On Error GoTo lll
    idd = clnSched.Item(gridSched.RowSel)
    With dbCommand
        .CommandText = "delete ScheduledLecture where cSLectureId = '" & idd & "'"
        .ActiveConnection = dbConn
        .Execute
    End With
    getSched
lll:
    Exit Sub
End Sub

Private Sub btnDelSubject_Click()
On Error GoTo park
    Dim ss$
    ss = Trim(cmbSub)
    dbCommand.CommandText = "delete Subject where vName = '" & ss & "'"
    dbCommand.ActiveConnection = dbConn
    dbCommand.Execute
    getSubjects
    MsgBox "Subject Deleted"
    Exit Sub
park:
    MsgBox "You Cannot Delete a Subject which is currently in use", vbCritical, "Tech Tester Pro"
End Sub

Private Sub btnOK_Click()
    Unload Me
End Sub

Private Sub Form_Load()
    Set clnSub = New Collection
    Set clnCourse = New Collection
    getSubjects
    GetCourses
    getStudents
    getLecturers
    getSched
End Sub
Private Sub getSubjects()
    Dim ss$, dd$
    cmbSub.Clear
    lstSubjects.Clear
    cmbQSub.Clear
    Set clnSub = New Collection
    Set dbRecordSet = New Recordset
    With dbRecordSet
        .Open "Select vName , cSubjectId from Subject", dbConn
        .MoveFirst
        While Not .BOF And Not .EOF
            ss = dbRecordSet!vName
            dd = dbRecordSet!cSubjectId
            Call cmbSub.AddItem(ss)
            lstSubjects.AddItem ss
            Call clnSub.Add(dd)
            Call cmbQSub.AddItem(ss)
            .MoveNext
        Wend
        .Close
        cmbSub.ListIndex = 0
        cmbQSub.ListIndex = 0
    End With
End Sub
Private Sub GetCourses()
    Dim ss$
    cmbCourses.Clear
    Set clnCourses = New Collection
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

Private Sub getStudents()
    Dim nm$, crs$, eml$, comp%, var%
    var = 1
    gridStudent.Clear
    gridStudent.TextMatrix(0, 0) = "SI"
    gridStudent.TextMatrix(0, 1) = "Student Name"
    gridStudent.TextMatrix(0, 2) = "Course Name"
    gridStudent.TextMatrix(0, 3) = "Email Address"
    gridStudent.TextMatrix(0, 4) = "Completed"
    With dbRecordSet
        .Open "Select s.vName SNAME, c.vName CNAME, vEmailId MAIL , bCompleted CMPL from Student s, Course c where s.cCourseId = c.cCourseId", dbConn
        If .BOF Or .EOF Then
            .Close
            Exit Sub
        End If
        '.MoveFirst
        While Not .BOF And Not .EOF
            nm = dbRecordSet!sname
            crs = dbRecordSet!cname
            eml = dbRecordSet!MAIL
            comp = dbRecordSet!CMPL
            gridStudent.TextMatrix(var, 0) = var
            gridStudent.TextMatrix(var, 1) = nm
            gridStudent.TextMatrix(var, 2) = crs
            gridStudent.TextMatrix(var, 3) = eml
            gridStudent.TextMatrix(var, 4) = "No"
            If comp <> 0 Then
                gridStudent.TextMatrix(var, 4) = "Yes"
            End If
            .MoveNext
            var = var + 1
        Wend
        .Close
    End With
End Sub

Private Sub getLecturers()
    Dim nm$, subj$, eml$, var%
    var = 1
    gridLecturer.Clear
    gridLecturer.TextMatrix(0, 0) = "SI"
    gridLecturer.TextMatrix(0, 1) = "Lecturer Name"
    gridLecturer.TextMatrix(0, 2) = "Subject Name"
    gridLecturer.TextMatrix(0, 3) = "Email Address"
    With dbRecordSet
        .Open "Select s.vName SNAME, c.vName CNAME, vEmailId MAIL from Lecturer s, Subject c where s.cSubjectId = c.cSubjectId", dbConn
        If .BOF Or .EOF Then
            .Close
            Exit Sub
        End If
        '.MoveFirst
        While Not .BOF And Not .EOF
            nm = dbRecordSet!sname
            subj = dbRecordSet!cname
            eml = dbRecordSet!MAIL
            gridLecturer.TextMatrix(var, 0) = var
            gridLecturer.TextMatrix(var, 1) = nm
            gridLecturer.TextMatrix(var, 2) = subj
            gridLecturer.TextMatrix(var, 3) = eml
            .MoveNext
            var = var + 1
        Wend
        .Close
    End With
End Sub

Public Sub setCourseDead(ByVal namb As String)
    With dbCommand
        .ActiveConnection = dbConn
        .CommandText = "update Course set bUsed = 0 where vName = '" & namb & "'"
        .Execute
    End With
End Sub

Public Sub getSched()
    Dim nm$, subj$, eml$, var%
    var = 1
    gridSched.Clear
    Set clnSched = New Collection
    gridSched.TextMatrix(0, 0) = "SI"
    gridSched.TextMatrix(0, 1) = "Lecturer Name"
    gridSched.TextMatrix(0, 2) = "Topic Name"
    gridSched.TextMatrix(0, 3) = "Place"
    gridSched.TextMatrix(0, 4) = "Time"
    With dbRecordSet
        .Open "Select cSLectureId IDD , vName LNAME, vDescription DESR , vPlace PL , dDate DT , tTime TT from ScheduledLecture sl , Lecturer l where sl.cLecturerId = l.cLecturerId", dbConn
        If .BOF Or .EOF Then
            .Close
            Exit Sub
        End If
        .MoveFirst
        While Not .BOF And Not .EOF
            id = dbRecordSet!idd
            nm = dbRecordSet!lname
            subj = dbRecordSet!desr
            eml = dbRecordSet!pl
            dtl = dbRecordSet!dt
            ttl = dbRecordSet!tt
            gridSched.TextMatrix(var, 0) = var
            gridSched.TextMatrix(var, 1) = nm
            gridSched.TextMatrix(var, 2) = subj
            gridSched.TextMatrix(var, 3) = eml
            gridSched.TextMatrix(var, 4) = dtl
            gridSched.TextMatrix(var, 5) = ttl
            clnSched.Add id
            .MoveNext
            var = var + 1
        Wend
        .Close
    End With
End Sub

