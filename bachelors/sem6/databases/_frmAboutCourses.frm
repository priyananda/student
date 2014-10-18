VERSION 5.00
Object = "{0ECD9B60-23AA-11D0-B351-00A0C9055D8E}#6.0#0"; "MSHFLXGD.OCX"
Begin VB.Form frmAboutCourses 
   AutoRedraw      =   -1  'True
   BorderStyle     =   1  'Fixed Single
   Caption         =   "About the Coursese"
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
      Sorted          =   -1  'True
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
    Unload Me
End Sub

Private Sub Form_Load()
    GetCourses
    gridCourses.TextMatrix(1, 0) = "1"
    gridCourses.TextMatrix(1, 1) = "Hello"
    gridCourses.TextMatrix(1, 2) = "This course will definitely get you a plum job"
    gridCourses.ColWidth(2) = 5000
End Sub

Private Sub lstCourse_Click()
    i = lstCourse.ListIndex
    txtDescription.Text = lstCourse & " is a Great Course"
    gridCourses.TextMatrix(1, 0) = Str(i)
    gridCourses.TextMatrix(1, 1) = "Hello"
    gridCourses.TextMatrix(1, 2) = "This course will definitely get you a plum job"
End Sub

Private Sub GetCourses()
    lstCourse.AddItem "MCSE"
    lstCourse.AddItem "CCNA"
    lstCourse.AddItem "MCSD"
    lstCourse.AddItem "SCP"
    lstCourse.AddItem "SCA"
    lstCourse.AddItem "CCIE"
End Sub

