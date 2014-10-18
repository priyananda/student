VERSION 5.00
Object = "{0ECD9B60-23AA-11D0-B351-00A0C9055D8E}#6.0#0"; "MSHFLXGD.OCX"
Begin VB.Form frmAboutCourses 
   AutoRedraw      =   -1  'True
   BorderStyle     =   1  'Fixed Single
   Caption         =   "About the Courses"
   ClientHeight    =   6345
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7770
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6345
   ScaleWidth      =   7770
   StartUpPosition =   3  'Windows Default
   Begin MSHierarchicalFlexGridLib.MSHFlexGrid gridCourses 
      Height          =   2775
      Left            =   3360
      TabIndex        =   7
      Top             =   3360
      Width           =   4335
      _ExtentX        =   7646
      _ExtentY        =   4895
      _Version        =   393216
      Rows            =   10
      Cols            =   3
      MergeCells      =   2
      AllowUserResizing=   3
      FormatString    =   "^SI |<Subject  |< Description"
      BandDisplay     =   1
      RowSizingMode   =   1
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      _NumberOfBands  =   1
      _Band(0).BandIndent=   5
      _Band(0).Cols   =   3
      _Band(0).GridLinesBand=   1
      _Band(0).TextStyleBand=   0
      _Band(0).TextStyleHeader=   2
   End
   Begin VB.CommandButton Command1 
      Caption         =   "O  K "
      Height          =   495
      Left            =   360
      TabIndex        =   6
      Top             =   5520
      Width           =   1815
   End
   Begin VB.CommandButton btnView 
      Caption         =   "View Syllabus"
      Height          =   735
      Left            =   2880
      TabIndex        =   5
      Top             =   6600
      Width           =   2295
   End
   Begin VB.TextBox txtDescription 
      Appearance      =   0  'Flat
      Enabled         =   0   'False
      ForeColor       =   &H00000000&
      Height          =   1335
      Left            =   3360
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   4
      Top             =   1680
      Width           =   3015
   End
   Begin VB.ListBox lstCourse 
      Appearance      =   0  'Flat
      BackColor       =   &H80000014&
      Height          =   2370
      Left            =   360
      TabIndex        =   2
      Top             =   1680
      Width           =   1815
   End
   Begin VB.Label Label2 
      BackStyle       =   0  'Transparent
      Caption         =   "Description"
      Height          =   255
      Index           =   1
      Left            =   3360
      TabIndex        =   3
      Top             =   1440
      Width           =   1095
   End
   Begin VB.Label Label1 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "Courses"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   360
      TabIndex        =   1
      Top             =   1440
      Width           =   1455
   End
   Begin VB.Label lab1 
      Alignment       =   2  'Center
      BackStyle       =   0  'Transparent
      Caption         =   "Take a look at all courses"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   0
      TabIndex        =   0
      Top             =   360
      Width           =   7695
   End
   Begin VB.Image Image1 
      Height          =   8655
      Left            =   0
      Picture         =   "frmAboutCourses.frx":0000
      Stretch         =   -1  'True
      Top             =   0
      Width           =   12015
   End
End
Attribute VB_Name = "frmAboutCourses"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim clnCourses As Collection
Private Sub Command1_Click()
    Me.Hide
    Unload Me
End Sub

Private Sub Form_Load()
    Set clnCourses = New Collection
    GetCourses
    gridCourses.ColWidth(2) = 5000
End Sub

Private Sub lstCourse_Click()
    On Error Resume Next
    Dim var%
    Dim nm$, vd$
    var% = 1
    i = lstCourse.ListIndex
    txtDescription.Text = clnCourses.Item(i + 1)
    gridCourses.Clear
    gridCourses.TextMatrix(0, 0) = "SI"
    gridCourses.TextMatrix(0, 1) = "Subject"
    gridCourses.TextMatrix(0, 2) = "Description"
    dbRecordSet.Open "select vName , vDescription from Subject where cSubjectId IN ( select cSubjectId from CourseSubject where cCourseId = ( select cCourseId from Course where vName = '" & _
        lstCourse.List(i) & _
        "' ) )", dbConn
    dbRecordSet.MoveFirst
    While Not dbRecordSet.EOF And Not dbRecordSet.BOF
        nm = dbRecordSet!vName
        vd = dbRecordSet!vDescription
        gridCourses.TextMatrix(var, 0) = var
        gridCourses.TextMatrix(var, 1) = nm
        gridCourses.TextMatrix(var, 2) = vd
        dbRecordSet.MoveNext
        var = var + 1
    Wend
ffend:
    dbRecordSet.Close
End Sub

Private Sub GetCourses()
    On Error GoTo pend
    Set dbRecordSet = New Recordset
    Set dbCommand = New Command
    dbCommand.CommandText = "select vName,vDescription from Course"
    dbCommand.ActiveConnection = dbConn
    Set dbRecordSet = dbCommand.Execute
    dbRecordSet.MoveFirst
    While Not dbRecordSet.EOF And Not dbRecordSet.BOF
        Dim ss$, baba$
        ss = dbRecordSet!vName
        baba = dbRecordSet!vDescription
        lstCourse.AddItem ss
        clnCourses.Add baba
        dbRecordSet.MoveNext
    Wend
    dbRecordSet.Close
    Exit Sub
pend:
    ErrorHandler
End Sub

Private Sub ErrorHandler()
    MsgBox Err.Description
End Sub
