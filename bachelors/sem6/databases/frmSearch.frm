VERSION 5.00
Object = "{0ECD9B60-23AA-11D0-B351-00A0C9055D8E}#6.0#0"; "MSHFLXGD.OCX"
Begin VB.Form frmSearch 
   Caption         =   "Search For Lectures"
   ClientHeight    =   6765
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6900
   LinkTopic       =   "Form2"
   ScaleHeight     =   6765
   ScaleWidth      =   6900
   StartUpPosition =   3  'Windows Default
   Begin MSHierarchicalFlexGridLib.MSHFlexGrid gridOutput 
      Height          =   3255
      Left            =   360
      TabIndex        =   7
      Top             =   3360
      Visible         =   0   'False
      Width           =   5895
      _ExtentX        =   10398
      _ExtentY        =   5741
      _Version        =   393216
      _NumberOfBands  =   1
      _Band(0).Cols   =   2
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   480
      TabIndex        =   6
      Top             =   2280
      Width           =   5175
   End
   Begin VB.CommandButton btnGo 
      Caption         =   "Go !!"
      Height          =   375
      Left            =   5880
      TabIndex        =   5
      Top             =   2280
      Width           =   975
   End
   Begin VB.OptionButton radSearchBy 
      Caption         =   "Date"
      Height          =   255
      Index           =   3
      Left            =   1920
      TabIndex        =   4
      Top             =   1800
      Width           =   2055
   End
   Begin VB.OptionButton radSearchBy 
      Caption         =   "Keyword"
      Height          =   255
      Index           =   2
      Left            =   1920
      TabIndex        =   3
      Top             =   1320
      Width           =   2055
   End
   Begin VB.OptionButton radSearchBy 
      Caption         =   "Subject"
      Height          =   255
      Index           =   1
      Left            =   1920
      TabIndex        =   2
      Top             =   840
      Width           =   2055
   End
   Begin VB.OptionButton radSearchBy 
      Caption         =   "Author"
      Height          =   255
      Index           =   0
      Left            =   1920
      TabIndex        =   1
      Top             =   360
      Width           =   2055
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Search On : "
      Height          =   375
      Left            =   360
      TabIndex        =   0
      Top             =   360
      Width           =   1335
   End
End
Attribute VB_Name = "frmSearch"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
