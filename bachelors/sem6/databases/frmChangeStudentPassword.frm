VERSION 5.00
Begin VB.Form frmChangeStudentPassword 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Change Student Password "
   ClientHeight    =   1545
   ClientLeft      =   2835
   ClientTop       =   3480
   ClientWidth     =   3750
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   912.837
   ScaleMode       =   0  'User
   ScaleWidth      =   3521.047
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.TextBox txtUserName 
      Height          =   345
      IMEMode         =   3  'DISABLE
      Left            =   1290
      PasswordChar    =   "!"
      TabIndex        =   1
      Top             =   135
      Width           =   2325
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   390
      Left            =   495
      TabIndex        =   4
      Top             =   1020
      Width           =   1140
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   390
      Left            =   2100
      TabIndex        =   5
      Top             =   1020
      Width           =   1140
   End
   Begin VB.TextBox txtPassword 
      Height          =   345
      IMEMode         =   3  'DISABLE
      Left            =   1290
      PasswordChar    =   "*"
      TabIndex        =   3
      Top             =   525
      Width           =   2325
   End
   Begin VB.Label lblLabels 
      Caption         =   "Old Password"
      Height          =   270
      Index           =   0
      Left            =   105
      TabIndex        =   0
      Top             =   150
      Width           =   1080
   End
   Begin VB.Label lblLabels 
      Caption         =   "New Password:"
      Height          =   270
      Index           =   1
      Left            =   105
      TabIndex        =   2
      Top             =   540
      Width           =   1200
   End
End
Attribute VB_Name = "frmChangeStudentPassword"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub cmdCancel_Click()
    Me.Hide
End Sub

Private Sub cmdOK_Click()
    If confirmStudentPassword(studentId, txtUserName.Text) Then
        changePassword (txtPassword.Text)
        Me.Hide
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
Private Sub changePassword(pass As String)
    With dbCommand
        .CommandText = "update Student set vPassword = '" & pass & "' where cStudentId = '" & studentId & "'"
        .ActiveConnection = dbConn
        .Execute
    End With
    MsgBox "Password Changed"
End Sub



