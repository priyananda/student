VERSION 5.00
Begin VB.Form frmRecRegn 
   BorderStyle     =   0  'None
   Caption         =   "Lecturer registration"
   ClientHeight    =   3195
   ClientLeft      =   180
   ClientTop       =   1035
   ClientWidth     =   4680
   LinkTopic       =   "Form2"
   Picture         =   "frmRecRegn.frx":0000
   ScaleHeight     =   8595
   ScaleWidth      =   11880
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   WindowState     =   2  'Maximized
   Begin VB.TextBox txtCreditCardNo 
      Appearance      =   0  'Flat
      Height          =   375
      Left            =   3000
      TabIndex        =   18
      Tag             =   "Credit Card Number"
      Top             =   6360
      Width           =   3255
   End
   Begin VB.ComboBox cmbSubject 
      Appearance      =   0  'Flat
      Height          =   315
      Left            =   3000
      Style           =   2  'Dropdown List
      TabIndex        =   14
      Top             =   5640
      Width           =   2055
   End
   Begin VB.TextBox txtPassword 
      Appearance      =   0  'Flat
      Height          =   375
      IMEMode         =   3  'DISABLE
      Left            =   3000
      PasswordChar    =   "*"
      TabIndex        =   13
      Tag             =   "Password "
      Top             =   4440
      Width           =   1935
   End
   Begin VB.TextBox txtVPass 
      Appearance      =   0  'Flat
      Height          =   375
      IMEMode         =   3  'DISABLE
      Left            =   3000
      PasswordChar    =   "`"
      TabIndex        =   10
      Tag             =   "Confirmation Password"
      Top             =   5040
      Width           =   1935
   End
   Begin VB.TextBox txtEmail 
      Appearance      =   0  'Flat
      Height          =   375
      Left            =   3000
      TabIndex        =   9
      Tag             =   "Email ID "
      Top             =   3840
      Width           =   3135
   End
   Begin VB.TextBox txtAge 
      Appearance      =   0  'Flat
      Height          =   405
      Left            =   3000
      MultiLine       =   -1  'True
      TabIndex        =   8
      Tag             =   "DOB"
      Top             =   3240
      Width           =   1335
   End
   Begin VB.TextBox txtAddress 
      Appearance      =   0  'Flat
      Height          =   1215
      Left            =   3000
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   7
      Tag             =   "Address"
      Top             =   1800
      Width           =   3135
   End
   Begin VB.TextBox txtName 
      Appearance      =   0  'Flat
      Height          =   375
      Left            =   3000
      TabIndex        =   6
      Tag             =   "Name"
      Top             =   1320
      Width           =   3135
   End
   Begin VB.Label Label2 
      BackStyle       =   0  'Transparent
      Caption         =   "Date Format is DD-MON-YYYY Eg : 12-APR-2003"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   4560
      TabIndex        =   19
      Top             =   3360
      Width           =   5415
   End
   Begin VB.Label lblAbused 
      BackStyle       =   0  'Transparent
      Caption         =   "Credit Card Number"
      Height          =   375
      Index           =   7
      Left            =   720
      TabIndex        =   17
      Top             =   6480
      Width           =   1455
   End
   Begin VB.Label btnCancel 
      BackStyle       =   0  'Transparent
      Height          =   855
      Left            =   9960
      TabIndex        =   16
      Top             =   7680
      Width           =   1335
   End
   Begin VB.Label btnSubmit 
      BackStyle       =   0  'Transparent
      Height          =   855
      Left            =   8400
      TabIndex        =   15
      Top             =   7680
      Width           =   1335
   End
   Begin VB.Label lblAbused 
      BackStyle       =   0  'Transparent
      Caption         =   "Reenter Password"
      Height          =   375
      Index           =   6
      Left            =   720
      TabIndex        =   12
      Top             =   5160
      Width           =   1935
   End
   Begin VB.Label lblAbused 
      BackStyle       =   0  'Transparent
      Caption         =   "Password"
      Height          =   375
      Index           =   5
      Left            =   720
      TabIndex        =   11
      Top             =   4560
      Width           =   1455
   End
   Begin VB.Label lblAbused 
      BackStyle       =   0  'Transparent
      Caption         =   "Email Address"
      Height          =   375
      Index           =   4
      Left            =   720
      TabIndex        =   5
      Top             =   3960
      Width           =   1935
   End
   Begin VB.Label lblAbused 
      BackStyle       =   0  'Transparent
      Caption         =   "Subject"
      Height          =   255
      Index           =   3
      Left            =   720
      TabIndex        =   4
      Top             =   5760
      Width           =   1455
   End
   Begin VB.Label lblAbused 
      BackStyle       =   0  'Transparent
      Caption         =   "Date Of Birth"
      Height          =   255
      Index           =   2
      Left            =   720
      TabIndex        =   3
      Top             =   3360
      Width           =   1935
   End
   Begin VB.Label lblAbused 
      BackStyle       =   0  'Transparent
      Caption         =   "Permanent Address"
      Height          =   495
      Index           =   1
      Left            =   720
      TabIndex        =   2
      Top             =   1800
      Width           =   1815
   End
   Begin VB.Label lblAbused 
      BackStyle       =   0  'Transparent
      Caption         =   "Lecturer Name"
      Height          =   375
      Index           =   0
      Left            =   720
      TabIndex        =   1
      Top             =   1320
      Width           =   1455
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      BackStyle       =   0  'Transparent
      Caption         =   "Please Enter Following Data :"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2880
      TabIndex        =   0
      Top             =   480
      Width           =   5415
   End
End
Attribute VB_Name = "frmRecRegn"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim clnSub As Collection
Private Sub btnCancel_Click()
    Unload Me
    Load Form1
    Form1.Show
End Sub

Private Sub btnSubmit_Click()
    Validate
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Load Form1
    Form1.Show
End Sub
Private Sub Validate()
   Dim correct As Boolean
   correct = True
   For Each cntl In Me.Controls
        If TypeOf cntl Is TextBox Then
            If Trim(cntl.Text) = "" Then
                MsgBox "You left " & _
                        cntl.Tag & _
                        " Empty "
                correct = False
                Exit For
            End If
        End If
    Next cntl
    If Trim(txtPassword.Text) <> Trim(txtVPass.Text) Then
        correct = False
        MsgBox "Passwords Dont Match"
        txtPassword.Text = ""
        txtVPass.Text = ""
    End If
    Dim xp As RegExp
    Set xp = New RegExp
    xp.Pattern = "^\w*@\w*\.\w*$"
    xp.IgnoreCase = False
    If Trim(txtEmail.Text) <> "" And Not xp.Test(txtEmail.Text) Then
        MsgBox "What kind of Email Id is that ?"
        correct = False
    End If
    If correct Then
        insertLecturer
    End If
End Sub

Private Sub insertLecturer()
'    On Error GoTo tfu
    sname = txtName.Text
    Addr = txtAddress.Text
    Email = txtEmail.Text
    dob = txtAge
    pass = txtPassword.Text
    ccno = txtCreditCardNo.Text
    sid = clnSub.Item(cmbSubject.ListIndex + 1)
    ss = getMaxId("Lecturer", "cLecturerId")
    If Trim(ss) = "" Then
        id = "lc0001"
    Else
        id = getNewId(ByVal ss)
    End If
    Set dbCommand = New Command
    dbCommand.CommandText = "insert into Lecturer values('" & _
        id & "','" & _
        sname & "','" & _
        dob & "','" & _
        sid & "','" & _
        Addr & "','" & _
        Email & "','" & _
        pass & "','" & _
        ccno & "')"
    dbCommand.ActiveConnection = dbConn
    dbCommand.Execute
    MsgBox "Your Login Id is : " & id, vbInformation, "TTPro"
    For Each cntl In Me.Controls
        If TypeOf cntl Is TextBox Then
            cntl.Text = ""
        End If
    Next cntl
    btnCancel_Click
    Exit Sub
tfu:
    MsgBox Err.Description
End Sub

Private Sub Form_Load()
    Set dbRecordSet = New Recordset
    dbRecordSet.Open "select cSubjectId , vName from Subject", dbConn
    Set clnSub = New Collection
    dbRecordSet.MoveFirst
    While Not dbRecordSet.BOF And Not dbRecordSet.EOF
        Dim nm$, id$
        nm = dbRecordSet!vName
        id = dbRecordSet!cSubjectId
        cmbSubject.AddItem (nm)
        clnSub.Add id
        dbRecordSet.MoveNext
    Wend
    dbRecordSet.Close
    cmbSubject.ListIndex = 0
End Sub
