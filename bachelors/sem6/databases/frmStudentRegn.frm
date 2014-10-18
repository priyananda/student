VERSION 5.00
Begin VB.Form frmStudentRegn 
   BorderStyle     =   0  'None
   Caption         =   "Student Registration"
   ClientHeight    =   3195
   ClientLeft      =   240
   ClientTop       =   1380
   ClientWidth     =   4680
   FillStyle       =   0  'Solid
   LinkTopic       =   "Form2"
   Picture         =   "frmStudentRegn.frx":0000
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   WindowState     =   2  'Maximized
   Begin VB.TextBox txtOtherSkill 
      Appearance      =   0  'Flat
      Height          =   375
      Left            =   3000
      TabIndex        =   19
      Tag             =   "Other Skills"
      Top             =   6960
      Width           =   2535
   End
   Begin VB.TextBox txtCreditCardNo 
      Appearance      =   0  'Flat
      Height          =   375
      Left            =   3000
      TabIndex        =   18
      Tag             =   "Your credit card number"
      Top             =   6120
      Width           =   2535
   End
   Begin VB.CommandButton btnCourseAbout 
      Appearance      =   0  'Flat
      Caption         =   "About The Courses ..."
      Height          =   375
      Left            =   5040
      TabIndex        =   16
      Top             =   3720
      Width           =   1935
   End
   Begin VB.TextBox txtAge 
      Appearance      =   0  'Flat
      Height          =   375
      Left            =   3000
      TabIndex        =   15
      Tag             =   "Age"
      Top             =   4320
      Width           =   1455
   End
   Begin VB.TextBox txtPassword 
      Appearance      =   0  'Flat
      Height          =   375
      IMEMode         =   3  'DISABLE
      Left            =   3000
      PasswordChar    =   "*"
      TabIndex        =   14
      Tag             =   "Password"
      Top             =   4920
      Width           =   2535
   End
   Begin VB.TextBox txtVPass 
      Appearance      =   0  'Flat
      Height          =   375
      IMEMode         =   3  'DISABLE
      Left            =   3000
      PasswordChar    =   "*"
      TabIndex        =   13
      Tag             =   "Confirmation Password"
      Top             =   5520
      Width           =   2535
   End
   Begin VB.ComboBox cmbCourse 
      Appearance      =   0  'Flat
      BackColor       =   &H00FFFF80&
      Height          =   315
      ItemData        =   "frmStudentRegn.frx":1059D
      Left            =   3000
      List            =   "frmStudentRegn.frx":1059F
      Style           =   2  'Dropdown List
      TabIndex        =   10
      Tag             =   "Course"
      Top             =   3720
      Width           =   1575
   End
   Begin VB.TextBox txtEmail 
      Appearance      =   0  'Flat
      Height          =   375
      Left            =   3000
      TabIndex        =   9
      Tag             =   "Email Address"
      Top             =   3120
      Width           =   2895
   End
   Begin VB.TextBox txtAddress 
      Appearance      =   0  'Flat
      Height          =   1095
      Left            =   3000
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   8
      Tag             =   "Address"
      Top             =   1800
      Width           =   2895
   End
   Begin VB.TextBox txtname 
      Appearance      =   0  'Flat
      Height          =   375
      Left            =   3000
      TabIndex        =   7
      Tag             =   "Name"
      Top             =   1080
      Width           =   2895
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
      TabIndex        =   22
      Top             =   4440
      Width           =   5415
   End
   Begin VB.Label btnCancel 
      BackStyle       =   0  'Transparent
      Height          =   855
      Left            =   9960
      TabIndex        =   21
      Top             =   7680
      Width           =   1335
   End
   Begin VB.Label btnSubmit 
      BackStyle       =   0  'Transparent
      Height          =   735
      Left            =   8400
      TabIndex        =   20
      Top             =   7680
      Width           =   1335
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Credit Card Number"
      Height          =   375
      Left            =   720
      TabIndex        =   17
      Top             =   6240
      Width           =   1455
   End
   Begin VB.Label Label21 
      BackStyle       =   0  'Transparent
      Caption         =   "Reenter Password"
      Height          =   375
      Left            =   720
      TabIndex        =   12
      Top             =   5640
      Width           =   1455
   End
   Begin VB.Label Label20 
      BackStyle       =   0  'Transparent
      Caption         =   "Password"
      Height          =   375
      Left            =   720
      TabIndex        =   11
      Top             =   5040
      Width           =   1695
   End
   Begin VB.Label Label9 
      BackStyle       =   0  'Transparent
      Caption         =   "Other Skills ( if Any )"
      Height          =   375
      Left            =   720
      TabIndex        =   6
      Top             =   7080
      Width           =   2175
   End
   Begin VB.Label Label6 
      BackStyle       =   0  'Transparent
      Caption         =   "Date Of Birth"
      Height          =   375
      Left            =   720
      TabIndex        =   5
      Top             =   4320
      Width           =   1815
   End
   Begin VB.Label Label5 
      BackStyle       =   0  'Transparent
      Caption         =   "Course Enrolled"
      Height          =   375
      Left            =   720
      TabIndex        =   4
      Top             =   3720
      Width           =   1935
   End
   Begin VB.Label Label4 
      BackStyle       =   0  'Transparent
      Caption         =   "E-Mail Address"
      Height          =   375
      Left            =   720
      TabIndex        =   3
      Top             =   3120
      Width           =   1575
   End
   Begin VB.Label lblAddress 
      BackStyle       =   0  'Transparent
      Caption         =   "Permanant Address"
      Height          =   375
      Left            =   720
      TabIndex        =   2
      Top             =   1800
      Width           =   2175
   End
   Begin VB.Label lblName 
      BackStyle       =   0  'Transparent
      Caption         =   "Name"
      Height          =   255
      Left            =   720
      TabIndex        =   1
      Top             =   1200
      Width           =   2175
   End
   Begin VB.Label lblTitle 
      Alignment       =   2  'Center
      BackStyle       =   0  'Transparent
      Caption         =   "Please Enter the following details"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   11.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000000&
      Height          =   495
      Left            =   1800
      TabIndex        =   0
      Top             =   360
      Width           =   6015
   End
End
Attribute VB_Name = "frmStudentRegn"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim clnCourse As Collection
Private Sub btnCourseAbout_Click()
    frmAboutCourses.Show (vbModal)
End Sub

Private Sub btnSubmit_Click()
    Validate
End Sub

Private Sub btnCancel_Click()
    Me.Hide
    Unload Me
    Load Form1
    Form1.Show
    Form1.Refresh
End Sub

Private Sub Validate()
    Dim correct As Boolean
    correct = True
    For Each cntl In Me.Controls
        If TypeOf cntl Is TextBox Then
            If cntl.Text = "" And Trim(cntl.Tag) <> "Other Skills" Then
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
    If Trim(txtOtherSkill.Text) = "" Then txtOtherSkill.Text = "   "
    If correct Then
        insertStudent
    End If
End Sub

Private Sub insertStudent()
    On Error GoTo tfu
    sname = txtName.Text
    Addr = txtAddress.Text
    Email = txtEmail.Text
    dob = txtAge
    pass = txtPassword.Text
    ccno = txtCreditCardNo.Text
    oth = txtOtherSkill.Text
    ss = getMaxId("Student", "cStudentId")
    cid = clnCourse.Item(cmbCourse.ListIndex + 1)
    If Trim(ss) = "" Then
        id = "st0001"
    Else
        id = getNewId(ByVal ss)
    End If
    Set dbCommand = New Command
    dbCommand.CommandText = "insert into Student values('" & _
        id & "','" & _
        sname & "','" & _
        dob & "','" & _
        cid & "','" & _
        Addr & "','" & _
        Email & "',0,'" & _
        pass & "','" & _
        oth & "','" & _
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
    dbRecordSet.Open "select cCourseId , vName from Course where bUsed = 1", dbConn
    Set clnCourse = New Collection
    dbRecordSet.MoveFirst
    While Not dbRecordSet.BOF And Not dbRecordSet.EOF
        Dim nm$, id$
        nm = dbRecordSet!vName
        id = dbRecordSet!cCourseId
        cmbCourse.AddItem (nm)
        clnCourse.Add id
        dbRecordSet.MoveNext
    Wend
    dbRecordSet.Close
    cmbCourse.ListIndex = 0
End Sub
