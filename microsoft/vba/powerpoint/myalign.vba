Private Function LogInfo(log)
    Debug.Print ("[" & Now() & "][Info ]: " & log)
End Function

Private Function LogError(log)
    Debug.Print ("[" & Now() & "][Error]: " & log)
End Function

Private Sub PrintControlInfo(ByVal ctrl As Object)
    LogInfo ("id: " & ctrl.Id & ", index: " & ctrl.Index)
    LogInfo ("caption: " & ctrl.Caption & ", left: " & ctrl.Left & ", width: " & ctrl.Width & "，top: " & ctrl.Top & "， height: " & ctrl.Height)
End Sub

Private Sub MyAlignCommandBar()
'    Dim ctrlId As Integer: ctrlId = 0
    Dim cbar As Object
    Dim newCommandBarName As String

    ' 若命令栏已创建，先删除，保证可重入
    newCommandBarName = "MyCommandBar"
    For Each cbar In CommandBars
        If cbar.Name = newCommandBarName Then
            LogInfo ("Will delete cbar: " & cbar.Name)
            cbar.Delete
        End If
    Next

    ' 新建命令栏
    Set newCommandBar = PowerPoint.Application.CommandBars.Add(Name:=newCommandBarName, Position:=msoBarFloating, Temporary:=True)
    newCommandBar.Visible = True

    Dim newCtrl As Object
    ' 新建按钮
    Set newCtrl = newCommandBar.Controls.Add(Type:=msoControlButton, Id:=1)
    With newCtrl
        .Visible = True
        .Caption = "左对齐"
        .Style = msoButtonCaption
        .OnAction = "MyAlignLeft"
'        .Left = 1592
        .Width = 4000
'        .Top = -8
        .Height = 23
    End With
    Call PrintControlInfo(newCtrl)


    ' 新建按钮
    Set newCtrl = newCommandBar.Controls.Add(Type:=msoControlButton, Id:=2)
    With newCtrl
        .Visible = True
        .Caption = "右对齐"
        .Style = msoButtonCaption
        .OnAction = "MyAlignRight"
    End With
    Call PrintControlInfo(newCtrl)

    ' 新建按钮
    Set newCtrl = newCommandBar.Controls.Add(Type:=msoControlButton)
    With newCtrl
        .Visible = True
        .Caption = "顶端对齐"
        .Style = msoButtonCaption
        .OnAction = "MyAlignTop"
    End With
    Call PrintControlInfo(newCtrl)

    ' 新建按钮
    Set newCtrl = newCommandBar.Controls.Add(Type:=msoControlButton)
    With newCtrl
        .Visible = True
        .Caption = "底端对齐"
        .Style = msoButtonCaption
        .OnAction = "MyAlignBottom"
    End With
    Call PrintControlInfo(newCtrl)

    ' 新建按钮
    Set newCtrl = newCommandBar.Controls.Add(Type:=msoControlButton)
    With newCtrl
        .Visible = True
        .Caption = "竖直居中"
        .Style = msoButtonCaption
        .OnAction = "MyAlignVertical"
    End With

    ' 新建按钮
    Set newCtrl = newCommandBar.Controls.Add(Type:=msoControlButton)
    With newCtrl
        .Visible = True
        .Caption = "水平居中"
        .Style = msoButtonCaption
        .OnAction = "MyAlignHorizon"
    End With

    ' 新建按钮
    Set newCtrl = newCommandBar.Controls.Add(Type:=msoControlButton)
    With newCtrl
        .Visible = True
        .Caption = "竖直紧挨"
        .Style = msoButtonCaption
        .OnAction = "MyAlignVerticalTouch"
    End With

    ' 新建按钮
    Set newCtrl = newCommandBar.Controls.Add(Type:=msoControlButton)
    With newCtrl
        .Visible = True
        .Caption = "水平紧挨"
        .Style = msoButtonCaption
        .OnAction = "MyAlignHorizonTouch"
    End With

    LogInfo ("ctrl count: " & newCommandBar.Controls.Count)
    LogInfo ("ctrl left: " & newCommandBar.Controls(1).Left)
    LogInfo ("ctrl left: " & newCommandBar.Controls(2).Left)
'    LogInfo ("ctrl top: " & newCommandBar.Controls(1).Top)
'    LogInfo ("ctrl top: " & newCommandBar.Controls(2).Top)
End Sub

Public Sub MyAlignLeft()
    Dim sRange As Object

    ' 未选中任何形状
    If PowerPoint.ActiveWindow.Selection.Type = ppSelectionNone Then
        LogError ("Does not select any shape")
        Exit Sub
    End If

    ' 选中形状少于2个
    Set sRange = PowerPoint.ActiveWindow.Selection.ShapeRange
    If sRange.Count < 2 Then
        LogError ("Select shape count less than 2")
        Exit Sub
    End If

    For i = 1 To sRange.Count
        LogInfo ("shape[" & i & "].left: " & sRange(i).Left)
    Next
    ' 所有形状与第一个形状左对齐: li=l1
    For i = 2 To sRange.Count
        sRange(i).Left = sRange(1).Left
    Next
End Sub

Public Sub MyAlignRight()
    Dim sRange As Object

    ' 未选中任何形状
    If PowerPoint.ActiveWindow.Selection.Type = ppSelectionNone Then
        LogError ("Does not select any shape")
        Exit Sub
    End If

    ' 选中形状少于2个
    Set sRange = PowerPoint.ActiveWindow.Selection.ShapeRange
    If sRange.Count < 2 Then
        LogError ("Select shape count less than 2")
        Exit Sub
    End If

    For i = 1 To sRange.Count
        LogInfo ("shape[" & i & "].right: " & sRange(i).Left + sRange(i).Width)
    Next
    ' 所有形状与第一个形状右对齐: li = l1 + w1 - wi
    For i = 2 To sRange.Count
        sRange(i).Left = sRange(1).Left + sRange(1).Width - sRange(i).Width
    Next
End Sub

Public Sub MyAlignTop()
    Dim sRange As Object

    ' 未选中任何形状
    If PowerPoint.ActiveWindow.Selection.Type = ppSelectionNone Then
        LogError ("Does not select any shape")
        Exit Sub
    End If

    ' 选中形状少于2个
    Set sRange = PowerPoint.ActiveWindow.Selection.ShapeRange
    If sRange.Count < 2 Then
        LogError ("Select shape count less than 2")
        Exit Sub
    End If

    For i = 1 To sRange.Count
        LogInfo ("shape[" & i & "].Top: " & sRange(i).Top)
    Next
    ' 所有形状与第一个形状顶端对齐: ti = t1
    For i = 2 To sRange.Count
        sRange(i).Top = sRange(1).Top
    Next
End Sub

Public Sub MyAlignBottom()
    Dim sRange As Object

    ' 未选中任何形状
    If PowerPoint.ActiveWindow.Selection.Type = ppSelectionNone Then
        LogError ("Does not select any shape")
        Exit Sub
    End If

    ' 选中形状少于2个
    Set sRange = PowerPoint.ActiveWindow.Selection.ShapeRange
    If sRange.Count < 2 Then
        LogError ("Select shape count less than 2")
        Exit Sub
    End If

    For i = 1 To sRange.Count
        LogInfo ("shape[" & i & "].bottom: " & sRange(i).Top + sRange(i).Height)
    Next
    ' 所有形状与第一个形状底端对齐: ti = t1 + h1 - hi
    For i = 2 To sRange.Count
        sRange(i).Top = sRange(1).Top + sRange(1).Height - sRange(i).Height
    Next
End Sub

Public Sub MyAlignVertical()
    Dim sRange As Object

    ' 未选中任何形状
    If PowerPoint.ActiveWindow.Selection.Type = ppSelectionNone Then
        LogError ("Does not select any shape")
        Exit Sub
    End If

    ' 选中形状少于2个
    Set sRange = PowerPoint.ActiveWindow.Selection.ShapeRange
    If sRange.Count < 2 Then
        LogError ("Select shape count less than 2")
        Exit Sub
    End If

    For i = 1 To sRange.Count
        LogInfo ("shape[" & i & "].vertical: " & sRange(i).Left + sRange(i).Width / 2)
    Next
    ' 所有形状与第一个形状竖直居中: li = l1 + w1 / 2 - wi / 2
    For i = 2 To sRange.Count
        sRange(i).Left = sRange(1).Left + sRange(1).Width / 2 - sRange(i).Width / 2
    Next
End Sub

Public Sub MyAlignHorizon()
    Dim sRange As Object

    ' 未选中任何形状
    If PowerPoint.ActiveWindow.Selection.Type = ppSelectionNone Then
        LogError ("Does not select any shape")
        Exit Sub
    End If

    ' 选中形状少于2个
    Set sRange = PowerPoint.ActiveWindow.Selection.ShapeRange
    If sRange.Count < 2 Then
        LogError ("Select shape count less than 2")
        Exit Sub
    End If

    For i = 1 To sRange.Count
'        LogInfo ("shape[" & i & "].horizon: " & sRange(i).Top + sRange(i).Height / 2)
    Next
    ' 所有形状与第一个形状水平居中: ti = t1 + h1 / 2 - hi / 2
    For i = 2 To sRange.Count
'        sRange(i).Top = sRange(1).Top + sRange(1).Height / 2 - sRange(i).Height / 2
    Next
End Sub

Public Sub MyAlignVerticalTouch()
    Dim sRange As Object

    ' 未选中任何形状
    If PowerPoint.ActiveWindow.Selection.Type = ppSelectionNone Then
        LogError ("Does not select any shape")
        Exit Sub
    End If

    ' 选中形状少于2个
    Set sRange = PowerPoint.ActiveWindow.Selection.ShapeRange
    If sRange.Count < 2 Then
        LogError ("Select shape count less than 2")
        Exit Sub
    End If

    For i = 1 To sRange.Count
'        LogInfo ("shape[" & i & "].Top: " & sRange(i).Top & ", bottom: " & sRange(i).Top + sRange(i).Height)
    Next
    ' 所有形状竖直紧挨: ti = t(i-1) + h(i-1)
    For i = 2 To sRange.Count
'        sRange(i).Top = sRange(i - 1).Top + sRange(i - 1).Height
    Next
End Sub

Public Sub MyAlignHorizonTouch()
    Dim sRange As Object

    ' 未选中任何形状
    If PowerPoint.ActiveWindow.Selection.Type = ppSelectionNone Then
        LogError ("Does not select any shape")
        Exit Sub
    End If

    ' 选中形状少于2个
    Set sRange = PowerPoint.ActiveWindow.Selection.ShapeRange
    If sRange.Count < 2 Then
        LogError ("Select shape count less than 2")
        Exit Sub
    End If

    For i = 1 To sRange.Count
        LogInfo ("shape[" & i & "].left: " & sRange(i).Left & ", right: " & sRange(i).Left + sRange(i).Width)
    Next
    ' 所有形状水平紧挨: li = l(i-1) + w(i-1)
    For i = 2 To sRange.Count
        sRange(i).Left = sRange(i - 1).Left + sRange(i - 1).Width
    Next
End Sub
