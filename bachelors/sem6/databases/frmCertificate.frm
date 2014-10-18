VERSION 5.00
Begin VB.Form frmCertificate 
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
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Sun - Microsoft testing Unit"
      Height          =   375
      Left            =   2760
      TabIndex        =   2
      Top             =   5040
      Width           =   6015
   End
   Begin VB.Label lblCourse 
      BackStyle       =   0  'Transparent
      Height          =   495
      Left            =   2160
      TabIndex        =   1
      Top             =   3720
      Width           =   6975
   End
   Begin VB.Label lblName 
      BackStyle       =   0  'Transparent
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.5
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   5280
      TabIndex        =   0
      Top             =   2520
      Width           =   4215
   End
   Begin VB.Image Image1 
      Height          =   9000
      Left            =   0
      Picture         =   "frmCertificate.frx":0000
      Top             =   0
      Width           =   12000
   End
End
Attribute VB_Name = "frmCertificate"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()
    With dbRecordSet
        .Open "select bCompleted BC from Student where cStudentId = '" & studentId & "'", dbConn
        .MoveFirst
        Dim i%, st$, cn$
        i = dbRecordSet!bc
        .Close
        If i = 0 Then
            MsgBox "you have not completed your course and will not get a certificate ", vbCritical, "Baba"
            Unload Me
            Exit Sub
        End If
        .Open "select st.vName STN, c.vName CN from Student st , Course c where st.cCourseId = c.cCourseId and st.cStudentId = '" & studentId & "'", dbConn
        .MoveFirst
        st = dbRecordSet!stn
        cn = dbRecordSet!cn
        .Close
        lblName.Caption = st
        lblCourse.Caption = cn
    End With
End Sub
