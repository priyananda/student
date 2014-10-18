VERSION 5.00
Object = "{0ECD9B60-23AA-11D0-B351-00A0C9055D8E}#6.0#0"; "MSHFLXGD.OCX"
Begin VB.Form frmQuery 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Query Builder"
   ClientHeight    =   7455
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   10365
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   7455
   ScaleWidth      =   10365
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton Command1 
      Caption         =   "Execute"
      Height          =   375
      Left            =   7800
      TabIndex        =   20
      Top             =   3600
      Width           =   1215
   End
   Begin VB.TextBox Text6 
      Height          =   3015
      Left            =   6600
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   19
      Top             =   480
      Width           =   3375
   End
   Begin MSHierarchicalFlexGridLib.MSHFlexGrid gridOut 
      Height          =   2655
      Left            =   1320
      TabIndex        =   18
      Top             =   4560
      Width           =   8055
      _ExtentX        =   14208
      _ExtentY        =   4683
      _Version        =   393216
      Rows            =   50
      Cols            =   20
      SelectionMode   =   1
      AllowUserResizing=   3
      _NumberOfBands  =   1
      _Band(0).Cols   =   20
   End
   Begin VB.TextBox Text5 
      Enabled         =   0   'False
      Height          =   375
      Left            =   4680
      TabIndex        =   16
      Top             =   2880
      Width           =   1575
   End
   Begin VB.ComboBox Combo2 
      Enabled         =   0   'False
      Height          =   315
      ItemData        =   "frmQuery.frx":0000
      Left            =   3360
      List            =   "frmQuery.frx":0016
      Style           =   2  'Dropdown List
      TabIndex        =   15
      Top             =   2880
      Width           =   1215
   End
   Begin VB.TextBox Text4 
      Enabled         =   0   'False
      Height          =   375
      Left            =   1680
      TabIndex        =   14
      Top             =   2880
      Width           =   1575
   End
   Begin VB.TextBox Text3 
      Height          =   375
      Left            =   4680
      TabIndex        =   13
      Top             =   1680
      Width           =   1455
   End
   Begin VB.ComboBox Combo4 
      Enabled         =   0   'False
      Height          =   315
      ItemData        =   "frmQuery.frx":0031
      Left            =   2040
      List            =   "frmQuery.frx":003B
      Style           =   2  'Dropdown List
      TabIndex        =   12
      Top             =   2400
      Width           =   1335
   End
   Begin VB.CheckBox Check1 
      Caption         =   "Check1"
      Height          =   255
      Left            =   1680
      TabIndex        =   11
      Top             =   2400
      Width           =   255
   End
   Begin VB.TextBox Text2 
      Height          =   375
      Left            =   1680
      TabIndex        =   10
      Top             =   1680
      Width           =   1575
   End
   Begin VB.ComboBox Combo3 
      Height          =   315
      ItemData        =   "frmQuery.frx":0048
      Left            =   3360
      List            =   "frmQuery.frx":005E
      Style           =   2  'Dropdown List
      TabIndex        =   9
      Top             =   1680
      Width           =   1215
   End
   Begin VB.ComboBox Combo1 
      Height          =   315
      Left            =   1680
      Style           =   2  'Dropdown List
      TabIndex        =   7
      Top             =   1200
      Width           =   2535
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   1680
      TabIndex        =   5
      Top             =   720
      Width           =   3735
   End
   Begin VB.OptionButton Option1 
      Height          =   255
      Index           =   1
      Left            =   1320
      TabIndex        =   3
      Top             =   720
      Width           =   255
   End
   Begin VB.OptionButton Option1 
      Height          =   255
      Index           =   0
      Left            =   1320
      TabIndex        =   2
      Top             =   480
      Value           =   -1  'True
      Width           =   255
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "Build"
      Height          =   375
      Left            =   2760
      TabIndex        =   0
      Top             =   3600
      Width           =   1215
   End
   Begin VB.Frame Frame1 
      Caption         =   "Frame1"
      Height          =   1335
      Left            =   1560
      TabIndex        =   17
      Top             =   2160
      Width           =   4815
   End
   Begin VB.Label Label2 
      Alignment       =   2  'Center
      BackStyle       =   0  'Transparent
      Caption         =   "Write the Entire Query"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FF0000&
      Height          =   375
      Index           =   1
      Left            =   5640
      TabIndex        =   22
      Top             =   0
      Width           =   4575
   End
   Begin VB.Label Label2 
      Alignment       =   2  'Center
      BackStyle       =   0  'Transparent
      Caption         =   "Build the Query"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FF0000&
      Height          =   375
      Index           =   0
      Left            =   120
      TabIndex        =   21
      Top             =   0
      Width           =   4575
   End
   Begin VB.Line Line1 
      BorderWidth     =   3
      Index           =   1
      X1              =   120
      X2              =   10200
      Y1              =   4200
      Y2              =   4200
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "WHERE "
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Index           =   3
      Left            =   240
      TabIndex        =   8
      Top             =   1680
      Width           =   975
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "FROM"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Index           =   2
      Left            =   240
      TabIndex        =   6
      Top             =   1200
      Width           =   975
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      BackStyle       =   0  'Transparent
      Caption         =   "*"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Index           =   1
      Left            =   1560
      TabIndex        =   4
      Top             =   480
      Width           =   375
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "SELECT"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Index           =   0
      Left            =   240
      TabIndex        =   1
      Top             =   480
      Width           =   975
   End
End
Attribute VB_Name = "frmQuery"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub executeQuery(ByVal query As String)
On Error GoTo errh
    gridOut.Clear
    gridOut.TextMatrix(0, 0) = "SI"
    With dbRecordSet
        .Open query, dbConn
        colCount = 0
        For Each x In .Fields
            colCount = colCount + 1
        Next x
        If .BOF Or .EOF Then
            MsgBox "No Rows seleted"
            .Close
            Exit Sub
        End If
        '.MoveFirst
        Row = 1
        Dim ss$
        While Not .EOF And Not .BOF
            For Col = 1 To colCount
                ss = dbRecordSet(Col - 1)
                gridOut.TextMatrix(Row, Col) = ss
            Next Col
            Row = Row + 1
            .MoveNext
        Wend
        .Close
    End With
    Exit Sub
errh:
    MsgBox Err.Description
End Sub

Private Sub Check1_Click()
    If Check1.Value = 0 Then
        Text4.Enabled = False
        Text5.Enabled = False
        Combo2.Enabled = False
        Combo4.Enabled = False
    Else
        Text4.Enabled = True
        Text5.Enabled = True
        Combo2.Enabled = True
        Combo4.Enabled = True
    End If
End Sub



Private Sub Command1_Click()
    ss = Trim(Text6.Text)
    If ss = "" Then
        MsgBox "Please Enter a Query"
        Exit Sub
    End If
    executeQuery ByVal ss
End Sub

Private Sub Form_Load()
    Combo2.ListIndex = 1
    Combo3.ListIndex = 1
    Combo4.ListIndex = 1
    fillTables
    Combo1.ListIndex = 1
End Sub

Private Sub OKButton_Click()
    buildQuery
    'executeQuery ss
End Sub


Private Sub buildQuery()
    Dim COLNAMES, TABLENAME, WHERECLAUSE
    If Option1(0).Value = True Then
        COLNAMES = "*"
    Else
        If Not checkFull(Text1) Then Exit Sub
        COLNAMES = Text1.Text
    End If
    TABLENAME = Combo1.List(Combo1.ListIndex)
    If Trim(Text2.Text) = "" Then GoTo noWhere
    If Not checkFull(Text3) Then Exit Sub
    WHERECLAUSE = Trim(Text2) & "  " & Combo3.List(Combo3.ListIndex) & "  '" & Trim(Text3) & "' "
    If Check1.Value = 1 Then
        If Not checkFull(Text4) Then Exit Sub
        If Not checkFull(Text5) Then Exit Sub
        WHERECLAUSE = WHERECLAUSE & " " & Combo4.List(Combo4.ListIndex) & " "
        WHERECLAUSE = WHERECLAUSE & "  " & Text4.Text & "  " & Combo2.List(Combo2.ListIndex) & "  '" & Text5.Text & "' "
    End If
noWhere:
    query = "select " & COLNAMES & " from " & TABLENAME
    If (Not WHERECLAUSE = "") Then
        query = query & " where " & WHERECLAUSE
    End If
    Text6 = query
End Sub
Private Function checkFull(tx As TextBox) As Boolean
    checkFull = True
    If Trim(tx.Text) = "" Then
        MsgBox "Please Fill up the Feilds"
        checkFull = False
    End If
End Function
Private Sub fillTables()
    With dbRecordSet
        .Open "select * from tab"
        .MoveFirst
        While Not .BOF And Not .EOF
            ss = dbRecordSet!TNAME
            Combo1.AddItem ss
            .MoveNext
        Wend
        .Close
    End With
End Sub
