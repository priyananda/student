VERSION 5.00
Begin VB.Form frmLogin 
   BorderStyle     =   0  'None
   Caption         =   "Student Login"
   ClientHeight    =   2910
   ClientLeft      =   2790
   ClientTop       =   3150
   ClientWidth     =   6225
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   Picture         =   "frmLogin.frx":0000
   ScaleHeight     =   1719.324
   ScaleMode       =   0  'User
   ScaleWidth      =   5844.938
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.TextBox txtUserName 
      Appearance      =   0  'Flat
      Height          =   345
      Left            =   480
      TabIndex        =   1
      Top             =   360
      Width           =   2325
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   390
      Left            =   240
      TabIndex        =   4
      Top             =   2040
      Width           =   1140
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   390
      Left            =   4920
      TabIndex        =   5
      Top             =   2040
      Width           =   1140
   End
   Begin VB.TextBox txtPassword 
      Appearance      =   0  'Flat
      Height          =   345
      IMEMode         =   3  'DISABLE
      Left            =   3480
      PasswordChar    =   "*"
      TabIndex        =   3
      Top             =   360
      Width           =   2325
   End
   Begin VB.Label lblLabels 
      BackStyle       =   0  'Transparent
      Caption         =   "&User Name:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   0
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1185
   End
   Begin VB.Label lblLabels 
      BackStyle       =   0  'Transparent
      Caption         =   "&Password:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   1
      Left            =   5280
      TabIndex        =   2
      Top             =   120
      Width           =   840
   End
End
Attribute VB_Name = "frmLogin"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Public LoginSucceeded As Boolean
Private Sub cmdCancel_Click()
    LoginSucceeded = False
    Me.Hide
End Sub

Private Sub cmdOK_Click()
    studentId = txtUserName.Text
    If confirmStudentPassword(txtUserName, txtPassword) Then
        Me.Hide
        Unload Me
        Unload Form1
        Load frmStudentPage
        frmStudentPage.Show
    Else
        MsgBox "Invalid Password, try again!", , "Login"
        txtPassword.SetFocus
        SendKeys "{Home}+{End}"
    End If
End Sub

Private Function confirmStudentPassword(user As String, pass As String) As Boolean
    confirmStudentPassword = False
    Set dbRecordSet = New Recordset
    dbRecordSet.Open "Select count(*) PCOUNT from Student where cStudentId = '" & _
                    Trim(user) & _
                    "'and  vPassword = '" & _
                    Trim(pass) & _
                    "'", dbConn
    dbRecordSet.MoveFirst
    Dim v%
    v = dbRecordSet!PCOUNT
    If v <> 0 Then
        confirmStudentPassword = True
    End If
    dbRecordSet.Close
End Function

