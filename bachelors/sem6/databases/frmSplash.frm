VERSION 5.00
Begin VB.Form frmSplash 
   BorderStyle     =   3  'Fixed Dialog
   ClientHeight    =   6945
   ClientLeft      =   255
   ClientTop       =   1410
   ClientWidth     =   8955
   ClipControls    =   0   'False
   ControlBox      =   0   'False
   Icon            =   "frmSplash.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   Picture         =   "frmSplash.frx":000C
   ScaleHeight     =   6945
   ScaleWidth      =   8955
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   700
      Left            =   6960
      Top             =   3960
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "1.23"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   11.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0000FFFF&
      Height          =   255
      Left            =   1200
      TabIndex        =   0
      Top             =   6480
      Width           =   495
   End
End
Attribute VB_Name = "frmSplash"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_KeyPress(KeyAscii As Integer)
    Unload Me
    Load Form1
    Form1.Show
    Timer1.Enabled = False
End Sub

Private Sub Form_Load()
    Timer1.Enabled = True
End Sub

Private Sub Frame1_Click()
    Unload Me
    Load Form1
    Form1.Show
    Timer1.Enabled = False
End Sub

Private Sub Timer1_Timer()
    Unload Me
    Load Form1
    Form1.Show
    Timer1.Enabled = False
End Sub
