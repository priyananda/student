VERSION 5.00
Begin VB.Form frmEnquiry 
   BackColor       =   &H80000007&
   Caption         =   "Enquiry Page"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form2"
   ScaleHeight     =   8595
   ScaleWidth      =   11880
   StartUpPosition =   3  'Windows Default
   WindowState     =   2  'Maximized
   Begin VB.Label temp 
      BackStyle       =   0  'Transparent
      Caption         =   "__TODO__ : Put some stuff here ( Boooooring )"
      ForeColor       =   &H8000000E&
      Height          =   855
      Left            =   1560
      TabIndex        =   1
      Top             =   5280
      Width           =   5895
   End
   Begin VB.Image Image1 
      Height          =   3405
      Left            =   2040
      Picture         =   "frmEnquiry.frx":0000
      Stretch         =   -1  'True
      Top             =   960
      Width           =   4800
   End
   Begin VB.Label lblTitle 
      Alignment       =   2  'Center
      BackStyle       =   0  'Transparent
      Caption         =   "R V College Of Engineering "
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   18
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00C00000&
      Height          =   615
      Left            =   720
      TabIndex        =   0
      Top             =   120
      Width           =   6975
   End
End
Attribute VB_Name = "frmEnquiry"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
