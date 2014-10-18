VERSION 5.00
Object = "{0ECD9B60-23AA-11D0-B351-00A0C9055D8E}#6.0#0"; "MSHFLXGD.OCX"
Begin VB.Form frmSched 
   Caption         =   "See the Schedule of lectures"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form2"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   WindowState     =   2  'Maximized
   Begin MSHierarchicalFlexGridLib.MSHFlexGrid gridSched 
      Height          =   3015
      Left            =   3720
      TabIndex        =   0
      Top             =   2760
      Width           =   7335
      _ExtentX        =   12938
      _ExtentY        =   5318
      _Version        =   393216
      Rows            =   20
      Cols            =   6
      SelectionMode   =   1
      AllowUserResizing=   1
      Appearance      =   0
      FormatString    =   "SI|<Lecturer Name  |<Topic ( Subject ) |<Place |< Date |<    Time"
      _NumberOfBands  =   1
      _Band(0).Cols   =   6
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      Caption         =   "Theese are the Lectures Scheduled over the next few weeks"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   11.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2880
      TabIndex        =   1
      Top             =   960
      Width           =   9495
   End
End
Attribute VB_Name = "frmSched"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()
    gridSched.ColWidth(1) = 3000
    gridSched.ColWidth(2) = 1000
    gridSched.ColWidth(3) = 1000
    gridSched.ColWidth(4) = 1000
    gridSched.ColWidth(5) = 1000
    getSched
End Sub
Public Sub getSched()
    Dim nm$, subj$, eml$, var%
    var = 1
    gridSched.Clear
    Set clnSched = New Collection
    gridSched.TextMatrix(0, 0) = "SI"
    gridSched.TextMatrix(0, 1) = "Lecturer Name"
    gridSched.TextMatrix(0, 2) = "Topic Name"
    gridSched.TextMatrix(0, 3) = "Place"
    gridSched.TextMatrix(0, 4) = "Date"
    gridSched.TextMatrix(0, 5) = "Time"
    With dbRecordSet
        .Open "Select cSLectureId IDD , vName LNAME, vDescription DESR , vPlace PL , dDate DT , tTime TT from ScheduledLecture sl , Lecturer l where sl.cLecturerId = l.cLecturerId", dbConn
        If .BOF Or .EOF Then
            .Close
            Exit Sub
        End If
        .MoveFirst
        While Not .BOF And Not .EOF
            id = dbRecordSet!idd
            nm = dbRecordSet!lname
            subj = dbRecordSet!desr
            eml = dbRecordSet!pl
            dtl = dbRecordSet!dt
            ttl = dbRecordSet!tt
            gridSched.TextMatrix(var, 0) = var
            gridSched.TextMatrix(var, 1) = nm
            gridSched.TextMatrix(var, 2) = subj
            gridSched.TextMatrix(var, 3) = eml
            gridSched.TextMatrix(var, 4) = dtl
            gridSched.TextMatrix(var, 5) = ttl
            clnSched.Add id
            .MoveNext
            var = var + 1
        Wend
        .Close
    End With
End Sub

