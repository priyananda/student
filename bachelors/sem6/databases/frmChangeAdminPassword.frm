VERSION 5.00
Begin VB.Form frmChangeAdminPassword 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Change Admin Password"
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
      PasswordChar    =   "*"
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
      Caption         =   "New Password "
      Height          =   270
      Index           =   1
      Left            =   105
      TabIndex        =   2
      Top             =   540
      Width           =   1080
   End
End
Attribute VB_Name = "frmChangeAdminPassword"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private Sub cmdCancel_Click()
    Unload Me
    Me.Hide
End Sub

Private Sub cmdOK_Click()
    If confirmAdminPassword(Trim(txtUserName.Text)) Then
       changeAdminPass (Trim(txtPassword))
       Me.Hide
       Unload Me
    Else
        MsgBox "Invalid Password, try again!", vbCritical, "Change Admin Password"
    End If
End Sub
Private Function confirmAdminPassword(pass As String) As Boolean
    confirmAdminPassword = False
    dbRecordSet.Open "Select count(*) PCOUNT from admin_pass where vPassword='" & _
                    pass & _
                    "'", dbConn
    dbRecordSet.MoveFirst
    Dim v%
    v = dbRecordSet!PCOUNT
    If v <> 0 Then
        confirmAdminPassword = True
    End If
    dbRecordSet.Close
End Function

Private Sub changeAdminPass(pass As String)
    With dbCommand
        .CommandText = "update admin_pass set vPassword = '" & pass & "'"
        .ActiveConnection = dbConn
        .Execute
    End With
    MsgBox "Password Changed"
End Sub
