VERSION 5.00
Begin VB.Form frmAdminLogin 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Admin Login"
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
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   390
      Left            =   495
      TabIndex        =   3
      Top             =   1020
      Width           =   1140
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   390
      Left            =   2100
      TabIndex        =   4
      Top             =   1020
      Width           =   1140
   End
   Begin VB.TextBox txtPassword 
      Height          =   345
      IMEMode         =   3  'DISABLE
      Left            =   1320
      PasswordChar    =   "*"
      TabIndex        =   2
      Top             =   525
      Width           =   2325
   End
   Begin VB.Label Label1 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Admin"
      Height          =   375
      Left            =   1320
      TabIndex        =   5
      Top             =   120
      Width           =   2295
   End
   Begin VB.Label lblLabels 
      Caption         =   "&User Name:"
      Height          =   270
      Index           =   0
      Left            =   105
      TabIndex        =   0
      Top             =   150
      Width           =   1080
   End
   Begin VB.Label lblLabels 
      Caption         =   "&Password:"
      Height          =   270
      Index           =   1
      Left            =   105
      TabIndex        =   1
      Top             =   540
      Width           =   1080
   End
End
Attribute VB_Name = "frmAdminLogin"
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
    If confirmAdminPassword(txtPassword.Text) Then
        Me.Hide
        Unload Me
        Unload Form1
        Load frmAdminPage
        frmAdminPage.Show
    Else
        MsgBox "Invalid Password, try again!", , "Login"
        txtPassword.SetFocus
        SendKeys "{Home}+{End}"
    End If
End Sub

Private Function confirmAdminPassword(pass As String) As Boolean
    'confirmAdminPassword = True
    'Exit Function
    ' remove upper 2 lines
    confirmAdminPassword = False
    Set dbRecordSet = New Recordset
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
