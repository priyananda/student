VERSION 5.00
Begin VB.Form Form1 
   BorderStyle     =   0  'None
   Caption         =   "Welcome to Tech Tester Pro"
   ClientHeight    =   3195
   ClientLeft      =   300
   ClientTop       =   1725
   ClientWidth     =   4605
   Icon            =   "Form1.frx":0000
   LinkTopic       =   "Form1"
   MousePointer    =   4  'Icon
   ScaleHeight     =   3195
   ScaleWidth      =   4605
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   WindowState     =   2  'Maximized
   Begin VB.Label Label3 
      BackStyle       =   0  'Transparent
      Caption         =   "Exit"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   10320
      TabIndex        =   8
      Top             =   840
      Width           =   495
   End
   Begin VB.Image Image2 
      Height          =   375
      Left            =   10920
      Picture         =   "Form1.frx":0982
      Stretch         =   -1  'True
      Top             =   840
      Width           =   375
   End
   Begin VB.Label Label2 
      BackStyle       =   0  'Transparent
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   11.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0000FFFF&
      Height          =   3135
      Left            =   8400
      TabIndex        =   7
      Top             =   4080
      Width           =   1815
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      BackStyle       =   0  'Transparent
      Caption         =   "About Us"
      Height          =   735
      Index           =   6
      Left            =   2520
      MousePointer    =   99  'Custom
      TabIndex        =   6
      ToolTipText     =   "General Enquiry about IICT and Tect Tester Pro"
      Top             =   7320
      Width           =   3255
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      BackStyle       =   0  'Transparent
      Caption         =   "This Lecture Schedule"
      Height          =   735
      Index           =   5
      Left            =   3000
      MousePointer    =   99  'Custom
      TabIndex        =   5
      ToolTipText     =   "Take a look at whats up this week"
      Top             =   6360
      Width           =   3255
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      BackStyle       =   0  'Transparent
      Caption         =   "Admin Login"
      Height          =   615
      Index           =   4
      Left            =   3240
      MousePointer    =   99  'Custom
      TabIndex        =   4
      ToolTipText     =   "Administrator Login"
      Top             =   5400
      Width           =   3255
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      BackStyle       =   0  'Transparent
      Caption         =   "Lecturer Login"
      Height          =   735
      Index           =   3
      Left            =   3360
      MousePointer    =   99  'Custom
      TabIndex        =   3
      ToolTipText     =   "All registered lecturers login here"
      Top             =   4320
      Width           =   3255
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      BackStyle       =   0  'Transparent
      Caption         =   "Student Login"
      Height          =   615
      Index           =   2
      Left            =   3360
      MousePointer    =   99  'Custom
      TabIndex        =   2
      ToolTipText     =   "All registered students login here"
      Top             =   3120
      Width           =   3255
      WordWrap        =   -1  'True
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      BackStyle       =   0  'Transparent
      Caption         =   "Lecturer Registration"
      Height          =   615
      Index           =   1
      Left            =   3120
      MousePointer    =   99  'Custom
      TabIndex        =   1
      ToolTipText     =   "All Lecturers Of IICT Click here "
      Top             =   2040
      Width           =   3255
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      BackStyle       =   0  'Transparent
      Caption         =   "Student Registration"
      Height          =   615
      Index           =   0
      Left            =   2760
      MouseIcon       =   "Form1.frx":2ED1
      MousePointer    =   99  'Custom
      TabIndex        =   0
      ToolTipText     =   "Click Here to register for our courses"
      Top             =   1200
      Width           =   3255
   End
   Begin VB.Image Image1 
      Height          =   9000
      Left            =   0
      Picture         =   "Form1.frx":379B
      Stretch         =   -1  'True
      Top             =   0
      Width           =   12105
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub btnAbout()
    frmAbout.Show (vbModal)
End Sub
Private Sub btnAdmin()
    frmAdminLogin.Show (vbModal)
End Sub

Private Sub btnRecLogin()
    frmRecLogin.Show (vbModal)
End Sub

Private Sub btnEnquiry()
    frmEnquiry.Show (vbModal)
End Sub

Private Sub btnExit_Click()
End
End Sub

Private Sub btnLogin()
    frmLogin.Show (vbModal)
End Sub

Private Sub btnRecRegn()
    Load frmRecRegn
    frmRecRegn.Show
    Unload Me
End Sub

Private Sub btnRegister()
    Load frmStudentRegn
    frmStudentRegn.Show
    Unload Me
End Sub

Private Sub Form_Load()
    For Each x In Label1
        x.Caption = vbCrLf & x.Caption
        x.MousePointer = 99
        x.MouseIcon = Label1(0).MouseIcon
    Next x
    getConnection
End Sub
Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
    If UnloadMode = 0 Then
        End
    End If
End Sub

Private Sub Image2_Click()
    End
End Sub

Private Sub Label1_Click(Index As Integer)
    Select Case Index
        Case 0
            btnRegister
        Case 1
            btnRecRegn
        Case 2
            btnLogin
        Case 3
            btnRecLogin
        Case 4
            btnAdmin
        Case 6
            frmAbout.Show (vbModal)
        Case 5
            frmSched.Show (vbModal)
    End Select
End Sub

Private Sub Label1_MouseMove(Index As Integer, Button As Integer, Shift As Integer, x As Single, Y As Single)
    Select Case Index
        Case 0
            Label2 = "All new students can register here and discover " & _
                    " a new paradigm in CBT "
        Case 1
            Label2 = "All the esteemed lecturers of our institution " & _
                    " can register here and avail all the benefits "
        Case 2
            Label2 = "The registered students of our institution " & _
                    " can login here "
        Case 3
             Label2 = "The registered lecturers of our institution " & _
                    " can login here "
        Case 4
            Label2 = " Login For administrators "
        Case 6
            Label2 = "Want to know more about our institution ? " & _
                    "Then click here to discover a whole new world "
    End Select
End Sub



Private Sub Label5_Click()
    MsgBox "Ha Ha Ha , There is no such thing called Privacy " & vbCrLf & _
            "We will post all your sensitive data on Hackers Website"
End Sub

