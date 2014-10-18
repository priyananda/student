VERSION 5.00
Begin VB.Form frmRecLogin 
   BorderStyle     =   0  'None
   Caption         =   "Lecturer Login"
   ClientHeight    =   3300
   ClientLeft      =   2790
   ClientTop       =   3150
   ClientWidth     =   5790
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   Picture         =   "frmRecLogin.frx":0000
   ScaleHeight     =   1949.75
   ScaleMode       =   0  'User
   ScaleWidth      =   5436.497
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.TextBox txtUserName 
      Appearance      =   0  'Flat
      Height          =   345
      Left            =   2640
      TabIndex        =   0
      Top             =   720
      Width           =   2325
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   390
      Left            =   360
      TabIndex        =   2
      Top             =   2520
      Width           =   1140
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   390
      Left            =   4320
      TabIndex        =   3
      Top             =   2520
      Width           =   1140
   End
   Begin VB.TextBox txtPassword 
      Appearance      =   0  'Flat
      Height          =   345
      IMEMode         =   3  'DISABLE
      Left            =   2640
      PasswordChar    =   "*"
      TabIndex        =   1
      Top             =   1200
      Width           =   2325
   End
End
Attribute VB_Name = "frmRecLogin"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public LoginSucceeded As Boolean
Private Sub cmdCancel_Click()
    'set the global var to false
    'to denote a failed login
    LoginSucceeded = False
    Me.Hide
End Sub

Private Sub cmdOK_Click()
    lecturerId = txtUserName.Text
    If confirmLecPassword(txtUserName.Text, txtPassword.Text) Then
        'place code to here to pass the
        'success to the calling sub
        'setting a global var is the easiest
        Me.Hide
        Unload Me
        Unload Form1
        Load frmLecturerPage
        frmLecturerPage.Show
    Else
        MsgBox "Invalid Password, try again!", , "Login"
        txtPassword.SetFocus
        SendKeys "{Home}+{End}"
    End If
End Sub

Private Function confirmLecPassword(user As String, pass As String) As Boolean
    confirmLecPassword = False
    Set dbRecordSet = New Recordset
    Dim ss$
    ss = "Select count(*) PCOUNT from Lecturer where cLecturerId = '" & _
                    Trim(user) & _
                    "' and  vPassword = '" & _
                    Trim(pass) & _
                    "'"
    dbRecordSet.Open ss, dbConn
    dbRecordSet.MoveFirst
    Dim v%
    v = dbRecordSet!PCOUNT
    If v <> 0 Then
        confirmLecPassword = True
    End If
    dbRecordSet.Close
End Function

