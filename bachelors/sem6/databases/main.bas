Attribute VB_Name = "Module1"
Global dbConn As Connection
Global dbCommand As Command
Global dbRecordSet As Recordset
Global studentId As String
Global lecturerId As String
Declare Function ShellExecute Lib "shell32.dll" Alias "ShellExecuteA" ( _
                            ByVal hWnd As Long, _
                            ByVal lpVerb As String, _
                            ByVal lpFile As String, _
                            ByVal lpParameters As String, _
                            ByVal lpDir As String, _
                            ByVal iCmdShow As Long _
                        ) As Long

Public Type Question
    vOption1 As String
    vOption2 As String
    vOption3 As String
    vOption4 As String
    correct As Integer
    weight As Integer
    vQuestion As String
    cSubjectId As String
End Type

Sub Main()
    
    Load frmSplash
    frmSplash.Show
    frmSplash.Refresh
    getConnection
End Sub
Public Function getConnection() As Boolean
    On Error GoTo baba
    Set dbConn = New Connection
    Set dbCommand = New Command
    Set dbRecordSet = New Recordset
    'In College , use the following line
    'dbConn.Open "Provider=MSDAORA.1;User ID=techtest;Persist Security Info=False", "techtest", "k4fecn6"
    dbConn.Open "Provider=MSDASQL.1;Persist Security Info=False;User ID=techtest;Data Source=tech", "techtest", "k4fecn6"
    getConnection = True
    Exit Function
baba:
    MsgBox "Could Not get Connection"
    MsgBox Err.Description
    End
End Function

Public Function getMaxId(TABLENAME As String, id As String) As String
    Dim dbXRecordSet As Recordset
    Set dbXRecordSet = New Recordset
    Dim ss$
    ss = "select max(" & _
        id & _
        ") as dxMid from " & _
        TABLENAME
    dbXRecordSet.Open ss$, dbConn
    dbXRecordSet.MoveFirst
    getMaxId = dbXRecordSet!dxMid
    dbXRecordSet.Close
End Function

Public Function getNewId(ByVal id As String) As String
    Dim pLen, length As Integer
    Dim sid As Variant
    pLen = 2
    length = 4
    sid = Mid(id, 3, 4)
    sid = Int(sid) + 1
    While Len(sid) < length
        sid = "0" & sid
    Wend
    sid = Mid(id, 1, 2) & sid
    getNewId = sid
End Function

Public Function checkCourse(ByVal cname As String) As Boolean
    checkCourse = False
    With dbRecordSet
        .Open "select count(*) CNT from Course where vName = '" & cname & "'", dbConn
        .MoveFirst
        Dim ss%
        ss = dbRecordSet!CNT
        If ss <> 0 Then
            checkCourse = True
        End If
        .Close
    End With
End Function

Public Function checkSubject(ByVal cname As String) As Boolean
    checkSubject = False
    With dbRecordSet
        .Open "select count(*) CNT from Subject where vName = '" & cname & "'", dbConn
        .MoveFirst
        Dim ss%
        ss = dbRecordSet!CNT
        If ss <> 0 Then
            checkSubject = True
        End If
        .Close
    End With
End Function

Public Sub insertQuestion(qs As Question)
    With dbCommand
        .CommandText = _
            "insert into Question values ('" & _
            qs.cSubjectId & _
            "','" & qs.vQuestion & _
            "','" & qs.vOption1 & _
            "','" & qs.vOption2 & _
            "','" & qs.vOption3 & _
            "','" & qs.vOption4 & _
            "','" & qs.weight & _
            "','" & qs.correct & "')"
        .ActiveConnection = dbConn
        .Execute
    End With
End Sub


