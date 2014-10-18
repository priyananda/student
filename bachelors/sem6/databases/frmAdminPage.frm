VERSION 5.00
Begin VB.Form frmAdminPage 
   Caption         =   "admin Page"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form2"
   ScaleHeight     =   11115
   ScaleWidth      =   15240
   StartUpPosition =   3  'Windows Default
   WindowState     =   2  'Maximized
   Begin VB.CommandButton btnQuery 
      Caption         =   "Query Builder "
      Height          =   495
      Left            =   7920
      TabIndex        =   5
      Top             =   5760
      Width           =   2055
   End
   Begin VB.CommandButton btnLecrep 
      Caption         =   "Lecturer Report"
      Height          =   495
      Left            =   2040
      TabIndex        =   4
      Top             =   5760
      Width           =   1815
   End
   Begin VB.CommandButton btnStudRep 
      Caption         =   "Student Report"
      Height          =   495
      Left            =   4920
      TabIndex        =   3
      Top             =   6960
      Width           =   2055
   End
   Begin VB.CommandButton btnPass 
      Caption         =   "Change Password"
      Height          =   495
      Left            =   5040
      TabIndex        =   2
      Top             =   1800
      Width           =   1815
   End
   Begin VB.CommandButton btnStatistics 
      Caption         =   "Statistics"
      Height          =   495
      Left            =   8040
      TabIndex        =   1
      Top             =   3000
      Width           =   1935
   End
   Begin VB.CommandButton btnTasks 
      Caption         =   "Administrative Tasks"
      Height          =   495
      Left            =   1680
      TabIndex        =   0
      Top             =   3120
      Width           =   2055
   End
   Begin VB.Image Image1 
      Height          =   9000
      Left            =   0
      Picture         =   "frmAdminPage.frx":0000
      Top             =   0
      Width           =   12000
   End
End
Attribute VB_Name = "frmAdminPage"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub btnLecrep_Click()
    LectReport.Show vbModal
End Sub

Private Sub btnPass_Click()
    frmChangeAdminPassword.Show vbModal
End Sub

Private Sub btnQuery_Click()
    frmQuery.Show vbModal
End Sub

Private Sub btnStatistics_Click()
    frmStats.Show vbModal
End Sub

Private Sub btnStudRep_Click()
    StudentReport.Show vbModal
End Sub

Private Sub btnTasks_Click()
    frmAdminTasks.Show vbModal, Me
End Sub
Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
    Form1.Show
End Sub



