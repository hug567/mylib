Private Function LogInfo(log)
    Debug.Print ("[" & Now() & "][Info ]: " & log)
End Function

Private Function LogError(log)
    Debug.Print ("[" & Now() & "][Error]: " & log)
End Function

Private Sub PrintControlInfo(ByVal ctrl As Object)
    LogInfo ("id: " & ctrl.Id & ", index: " & ctrl.Index)
    LogInfo ("caption: " & ctrl.Caption & ", left: " & ctrl.Left & ", width: " _
                    & ctrl.Width & "，top: " & ctrl.Top & "， height: " & ctrl.Height)
End Sub

' 打开当前代码文件后，先运行一次此函数，将在菜单栏添加自定义命令
Private Sub MyAlignCommandBarInit()
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
    Set newCommandBar = CommandBars.Add(Name:=newCommandBarName, Position:=msoBarFloating)
    With newCommandBar
        .Visible = True
        .Protection = msoBarNoChangeDock
    End With

    LogInfo ("newCommandBar Position: " & newCommandBar.Position)
    LogInfo ("newCommandBar Left: " & newCommandBar.Left)
    LogInfo ("newCommandBar Top: " & newCommandBar.Top)
    LogInfo ("newCommandBar Width: " & newCommandBar.Width)
    LogInfo ("newCommandBar Height: " & newCommandBar.Height)

    Dim newCtrl As Object
    ' 新建按钮：左对齐
    Set newCtrl = newCommandBar.Controls.Add(Type:=msoControlButton)
    With newCtrl
        .Caption = "左对齐"
        .Style = msoButtonCaption
        .OnAction = "MyAlignLeft"
        .Visible = True
    End With
    'Call PrintControlInfo(newCtrl)

    ' 新建按钮：右对齐
    Set newCtrl = newCommandBar.Controls.Add(Type:=msoControlButton)
    With newCtrl
        .Visible = True
        .Caption = "右对齐"
        .Style = msoButtonCaption
        .OnAction = "MyAlignRight"
    End With

    ' 新建按钮
    Set newCtrl = newCommandBar.Controls.Add(Type:=msoControlButton)
    With newCtrl
        .Visible = True
        .Caption = "顶端对齐"
        .Style = msoButtonCaption
        .OnAction = "MyAlignTop"
    End With

    ' 新建按钮
    Set newCtrl = newCommandBar.Controls.Add(Type:=msoControlButton)
    With newCtrl
        .Visible = True
        .Caption = "底端对齐"
        .Style = msoButtonCaption
        .OnAction = "MyAlignBottom"
    End With

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

    ' 新建按钮：同宽
    Set newCtrl = newCommandBar.Controls.Add(Type:=msoControlButton)
    With newCtrl
        .Visible = True
        .Caption = "同宽"
        .Style = msoButtonCaption
        .OnAction = "MySameWidth"
    End With

    ' 新建按钮：同高
    Set newCtrl = newCommandBar.Controls.Add(Type:=msoControlButton)
    With newCtrl
        .Visible = True
        .Caption = "同高"
        .Style = msoButtonCaption
        .OnAction = "MySameHeight"
    End With

    ' 新建按钮：同宽高
    Set newCtrl = newCommandBar.Controls.Add(Type:=msoControlButton)
    With newCtrl
        .Visible = True
        .Caption = "同宽高"
        .Style = msoButtonCaption
        .OnAction = "MySameWidthHeight"
    End With

    ' 新建按钮：与页面左对齐
    Set newCtrl = newCommandBar.Controls.Add(Type:=msoControlButton)
    With newCtrl
        .Visible = True
        .Caption = "与页面左对齐"
        .Style = msoButtonCaption
        .OnAction = "MyAlignLeftWithPage"
    End With

    ' 新建按钮：与页面右对齐
    Set newCtrl = newCommandBar.Controls.Add(Type:=msoControlButton)
    With newCtrl
        .Visible = True
        .Caption = "与页面右对齐"
        .Style = msoButtonCaption
        .OnAction = "MyAlignRightWithPage"
    End With

    ' 新建按钮：与页面顶端对齐
    Set newCtrl = newCommandBar.Controls.Add(Type:=msoControlButton)
    With newCtrl
        .Visible = True
        .Caption = "与页面顶端对齐"
        .Style = msoButtonCaption
        .OnAction = "MyAlignTopWithPage"
    End With

    ' 新建按钮：与页面底端对齐
    Set newCtrl = newCommandBar.Controls.Add(Type:=msoControlButton)
    With newCtrl
        .Visible = True
        .Caption = "与页面底端对齐"
        .Style = msoButtonCaption
        .OnAction = "MyAlignBottomWithPage"
    End With

    ' 新建按钮：与页面水平居中
    Set newCtrl = newCommandBar.Controls.Add(Type:=msoControlButton)
    With newCtrl
        .Visible = True
        .Caption = "与页面水平居中"
        .Style = msoButtonCaption
        .OnAction = "MyAlignHorizonCenterWithPage"
    End With

    ' 新建按钮：与页面垂直居中
    Set newCtrl = newCommandBar.Controls.Add(Type:=msoControlButton)
    With newCtrl
        .Visible = True
        .Caption = "与页面垂直居中"
        .Style = msoButtonCaption
        .OnAction = "MyAlignVerticalCenterWithPage"
    End With

    ' 新建按钮：与页面同宽
    Set newCtrl = newCommandBar.Controls.Add(Type:=msoControlButton)
    With newCtrl
        .Visible = True
        .Caption = "与页面同宽"
        .Style = msoButtonCaption
        .OnAction = "MySameWidthWithPage"
    End With

    ' 新建按钮：与页面同高
    Set newCtrl = newCommandBar.Controls.Add(Type:=msoControlButton)
    With newCtrl
        .Visible = True
        .Caption = "与页面同高"
        .Style = msoButtonCaption
        .OnAction = "MySameHeightWithPage"
    End With

    ' 新建按钮：与页面同宽高
    Set newCtrl = newCommandBar.Controls.Add(Type:=msoControlButton)
    With newCtrl
        .Visible = True
        .Caption = "与页面同宽高"
        .Style = msoButtonCaption
        .OnAction = "MySameWidthHeightWithPage"
    End With

    LogInfo ("ctrl count: " & newCommandBar.Controls.Count)
    LogInfo ("Finish MyAlignCommandBarInit ......")
End Sub

Public Sub MyAlignLeft()
    Dim sRange As Object

    LogInfo ("Run MyAlignLeft")
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
    LogInfo ("Select shape count: " & sRange.Count)

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

    LogInfo ("Run MyAlignRight")
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
    LogInfo ("Select shape count: " & sRange.Count)

    For i = 1 To sRange.Count
        LogInfo ("shape[" & i & "].right: " & sRange(i).Left + sRange(i).Width)
    Next
    ' 所有形状与第一个形状右对齐: li = l1 + w1 - wi
    For i = 2 To sRange.Count
        sRange(i).Left = sRange(1).Left + sRange(1).Width - sRange(i).Width
    Next
End Sub
' 顶端对齐
Public Sub MyAlignTop()
    Dim sRange As Object

    LogInfo ("Run MyAlignTop")
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
    LogInfo ("Select shape count: " & sRange.Count)

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

    LogInfo ("Run MyAlignBottom")
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
    LogInfo ("Select shape count: " & sRange.Count)

    LogInfo ("shape[1].bottom: " & sRange(1).Top + sRange(1).Height)
    ' 所有形状与第一个形状底端对齐: t(i) = t(1) + h(1) - h(i)
    For i = 2 To sRange.Count
        sRange(i).Top = sRange(1).Top + sRange(1).Height - sRange(i).Height
        LogInfo ("shape[" & i & "].bottom: " & sRange(i).Top + sRange(i).Height)
    Next
End Sub

Public Sub MyAlignVertical()
    Dim sRange As Object

    LogInfo ("Run MyAlignVertical")
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
    LogInfo ("Select shape count: " & sRange.Count)

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

    LogInfo ("Run MyAlignHorizon")
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
    LogInfo ("Select shape count: " & sRange.Count)

    For i = 1 To sRange.Count
'        LogInfo ("shape[" & i & "].horizon: " & sRange(i).Top + sRange(i).Height / 2)
    Next
    ' 所有形状与第一个形状水平居中: ti = t1 + h1 / 2 - hi / 2
    For i = 2 To sRange.Count
        sRange(i).Top = sRange(1).Top + sRange(1).Height / 2 - sRange(i).Height / 2
    Next
End Sub

' 竖直紧挨
Public Sub MyAlignVerticalTouch()
    Dim sRange As Object

    LogInfo ("Run MyAlignVerticalTouch")
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
    LogInfo ("Select shape count: " & sRange.Count)

    For i = 1 To sRange.Count
        LogInfo ("shape[" & i & "].Top: " & sRange(i).Top & ", bottom: " & sRange(i).Top + sRange(i).Height)
    Next
    ' 所有形状竖直紧挨: t(i) = t(i-1) + h(i-1)
    For i = 2 To sRange.Count
        sRange(i).Top = sRange(i - 1).Top + sRange(i - 1).Height
    Next
End Sub

' 水平紧挨
Public Sub MyAlignHorizonTouch()
    Dim sRange As Object

    LogInfo ("Run MyAlignHorizonTouch")
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
    LogInfo ("Select shape count: " & sRange.Count)

    For i = 1 To sRange.Count
        LogInfo ("shape[" & i & "].left: " & sRange(i).Left & ", right: " & sRange(i).Left + sRange(i).Width)
    Next
    ' 所有形状水平紧挨: l(i) = l(i-1) + w(i-1)
    For i = 2 To sRange.Count
        sRange(i).Left = sRange(i - 1).Left + sRange(i - 1).Width
    Next
End Sub

' 同宽
Public Sub MySameWidth()
    Dim sRange As Object

    LogInfo ("Run MySameWidth")
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
    LogInfo ("Select shape count: " & sRange.Count)

    For i = 1 To sRange.Count
        LogInfo ("shape[" & i & "].left: " & sRange(i).Left & ", right: " & sRange(i).Left + sRange(i).Width)
    Next
    ' 与第一个形状同宽：shape(i).width = shape(1).width
    For i = 2 To sRange.Count
        sRange(i).Width = sRange(1).Width
    Next
End Sub

' 同高
Public Sub MySameHeight()
    Dim sRange As Object

    LogInfo ("Run MySameHeight")
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
    LogInfo ("Select shape count: " & sRange.Count)

    For i = 1 To sRange.Count
        LogInfo ("shape[" & i & "].left: " & sRange(i).Left & ", right: " & sRange(i).Left + sRange(i).Width)
    Next
    ' 与第一个形状同高：shape(i).height = shape(1).height
    For i = 2 To sRange.Count
        sRange(i).Height = sRange(1).Height
    Next
End Sub

' 同宽高
Public Sub MySameWidthHeight()
    Dim sRange As Object

    LogInfo ("Run MySameWidthHeight")
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
    LogInfo ("Select shape count: " & sRange.Count)

    For i = 1 To sRange.Count
        LogInfo ("shape[" & i & "].left: " & sRange(i).Left & ", right: " & sRange(i).Left + sRange(i).Width)
    Next
    ' 与第一个形状同高：shape(i).width = shape(1).width, shape(i).height = shape(1).height
    For i = 2 To sRange.Count
        sRange(i).Width = sRange(1).Width
        sRange(i).Height = sRange(1).Height
    Next
End Sub

' 与页面左对齐
Public Sub MyAlignLeftWithPage()
    Dim sRange As Object

    LogInfo ("Run MyAlignHorizonCenterWithPage")
    ' 未选中任何形状
    If PowerPoint.ActiveWindow.Selection.Type = ppSelectionNone Then
        LogError ("Does not select any shape")
        Exit Sub
    End If
    
    Set sRange = PowerPoint.ActiveWindow.Selection.ShapeRange
    LogInfo ("Select shape count: " & sRange.Count)

    For i = 1 To sRange.Count
        LogInfo ("shape[" & i & "].left: " & sRange(i).Left & ", right: " & sRange(i).Left + sRange(i).Width)
    Next

    pageWidth = ActivePresentation.PageSetup.SlideWidth
    pageHeight = ActivePresentation.PageSetup.SlideHeight
    LogInfo ("page width: " & pageWidth & ", page height: " & pageHeight)
    
    ' 所有形状与页面左对齐：shape.left = 0
    For i = 1 To sRange.Count
        sRange(i).Left = 0
    Next
End Sub

' 与页面右对齐
Public Sub MyAlignRightWithPage()
    Dim sRange As Object

    LogInfo ("Run MyAlignHorizonCenterWithPage")
    ' 未选中任何形状
    If PowerPoint.ActiveWindow.Selection.Type = ppSelectionNone Then
        LogError ("Does not select any shape")
        Exit Sub
    End If
    
    Set sRange = PowerPoint.ActiveWindow.Selection.ShapeRange
    LogInfo ("Select shape count: " & sRange.Count)

    For i = 1 To sRange.Count
        LogInfo ("shape[" & i & "].left: " & sRange(i).Left & ", right: " & sRange(i).Left + sRange(i).Width)
    Next

    pageWidth = ActivePresentation.PageSetup.SlideWidth
    pageHeight = ActivePresentation.PageSetup.SlideHeight
    LogInfo ("page width: " & pageWidth & ", page height: " & pageHeight)
    
    ' 所有形状与页面左对齐：shape.left = page.width - shape.width
    For i = 1 To sRange.Count
        sRange(i).Left = pageWidth - sRange(i).Width
    Next
End Sub

' 与页面顶端对齐
Public Sub MyAlignTopWithPage()
    Dim sRange As Object

    LogInfo ("Run MyAlignHorizonCenterWithPage")
    ' 未选中任何形状
    If PowerPoint.ActiveWindow.Selection.Type = ppSelectionNone Then
        LogError ("Does not select any shape")
        Exit Sub
    End If
    
    Set sRange = PowerPoint.ActiveWindow.Selection.ShapeRange
    LogInfo ("Select shape count: " & sRange.Count)

    For i = 1 To sRange.Count
        LogInfo ("shape[" & i & "].left: " & sRange(i).Left & ", right: " & sRange(i).Left + sRange(i).Width)
    Next

    pageWidth = ActivePresentation.PageSetup.SlideWidth
    pageHeight = ActivePresentation.PageSetup.SlideHeight
    LogInfo ("page width: " & pageWidth & ", page height: " & pageHeight)
    
    ' 所有形状与页面左对齐：shape.Top = 0
    For i = 1 To sRange.Count
        sRange(i).Top = 0
    Next
End Sub

' 与页面底端对齐
Public Sub MyAlignBottomWithPage()
    Dim sRange As Object

    LogInfo ("Run MyAlignHorizonCenterWithPage")
    ' 未选中任何形状
    If PowerPoint.ActiveWindow.Selection.Type = ppSelectionNone Then
        LogError ("Does not select any shape")
        Exit Sub
    End If
    
    Set sRange = PowerPoint.ActiveWindow.Selection.ShapeRange
    LogInfo ("Select shape count: " & sRange.Count)

    For i = 1 To sRange.Count
        LogInfo ("shape[" & i & "].left: " & sRange(i).Left & ", right: " & sRange(i).Left + sRange(i).Width)
    Next

    pageWidth = ActivePresentation.PageSetup.SlideWidth
    pageHeight = ActivePresentation.PageSetup.SlideHeight
    LogInfo ("page width: " & pageWidth & ", page height: " & pageHeight)
    
    ' 所有形状与页面左对齐：shape.Top = page.height - shape.height
    For i = 1 To sRange.Count
        sRange(i).Top = pageHeight - sRange(i).Height
    Next
End Sub

' 与页面水平居中
Public Sub MyAlignHorizonCenterWithPage()
    Dim sRange As Object

    LogInfo ("Run MyAlignHorizonCenterWithPage")
    ' 未选中任何形状
    If PowerPoint.ActiveWindow.Selection.Type = ppSelectionNone Then
        LogError ("Does not select any shape")
        Exit Sub
    End If
    
    Set sRange = PowerPoint.ActiveWindow.Selection.ShapeRange
    LogInfo ("Select shape count: " & sRange.Count)

    For i = 1 To sRange.Count
        LogInfo ("shape[" & i & "].left: " & sRange(i).Left & ", right: " & sRange(i).Left + sRange(i).Width)
    Next

    pageWidth = ActivePresentation.PageSetup.SlideWidth
    pageHeight = ActivePresentation.PageSetup.SlideHeight
    LogInfo ("page width: " & pageWidth & ", page height: " & pageHeight)
    
    ' 所有形状与页面水平居中对齐：shape.top = (page.height - shape.height) / 2
    For i = 1 To sRange.Count
        sRange(i).Top = (pageHeight - sRange(i).Height) / 2
    Next
End Sub

' 与页面垂直居中
Public Sub MyAlignVerticalCenterWithPage()
    Dim sRange As Object

    LogInfo ("Run MyAlignVerticalCenterWithPage")
    ' 未选中任何形状
    If PowerPoint.ActiveWindow.Selection.Type = ppSelectionNone Then
        LogError ("Does not select any shape")
        Exit Sub
    End If
    
    Set sRange = PowerPoint.ActiveWindow.Selection.ShapeRange
    LogInfo ("Select shape count: " & sRange.Count)

    For i = 1 To sRange.Count
        LogInfo ("shape[" & i & "].left: " & sRange(i).Left & ", right: " & sRange(i).Left + sRange(i).Width)
    Next

    pageWidth = ActivePresentation.PageSetup.SlideWidth
    pageHeight = ActivePresentation.PageSetup.SlideHeight
    LogInfo ("page width: " & pageWidth & ", page height: " & pageHeight)

    ' 所有形状与页面水平垂直对齐：shape.left = (page.width - shape.width) / 2
    For i = 1 To sRange.Count
        sRange(i).Left = (pageWidth - sRange(i).Width) / 2
    Next
End Sub

' 与页面同宽
Public Sub MySameWidthWithPage()
    Dim sRange As Object

    LogInfo ("Run MyAlignVerticalCenterWithPage")
    ' 未选中任何形状
    If PowerPoint.ActiveWindow.Selection.Type = ppSelectionNone Then
        LogError ("Does not select any shape")
        Exit Sub
    End If
    
    Set sRange = PowerPoint.ActiveWindow.Selection.ShapeRange
    LogInfo ("Select shape count: " & sRange.Count)

    For i = 1 To sRange.Count
        LogInfo ("shape[" & i & "].left: " & sRange(i).Left & ", right: " & sRange(i).Left + sRange(i).Width)
    Next

    pageWidth = ActivePresentation.PageSetup.SlideWidth
    pageHeight = ActivePresentation.PageSetup.SlideHeight
    LogInfo ("page width: " & pageWidth & ", page height: " & pageHeight)

    ' 所有形状与页面同宽：shape.width = page.width
    For i = 1 To sRange.Count
        sRange(i).Width = pageWidth
    Next
End Sub

' 与页面同高
Public Sub MySameHeightWithPage()
    Dim sRange As Object

    LogInfo ("Run MyAlignVerticalCenterWithPage")
    ' 未选中任何形状
    If PowerPoint.ActiveWindow.Selection.Type = ppSelectionNone Then
        LogError ("Does not select any shape")
        Exit Sub
    End If
    
    Set sRange = PowerPoint.ActiveWindow.Selection.ShapeRange
    LogInfo ("Select shape count: " & sRange.Count)

    For i = 1 To sRange.Count
        LogInfo ("shape[" & i & "].left: " & sRange(i).Left & ", right: " & sRange(i).Left + sRange(i).Width)
    Next

    pageWidth = ActivePresentation.PageSetup.SlideWidth
    pageHeight = ActivePresentation.PageSetup.SlideHeight
    LogInfo ("page width: " & pageWidth & ", page height: " & pageHeight)

    ' 所有形状与页面同宽：shape.height = page.height
    For i = 1 To sRange.Count
        sRange(i).Height = pageHeight
    Next
End Sub

' 与页面同宽高
Public Sub MySameWidthHeightWithPage()
    Dim sRange As Object

    LogInfo ("Run MyAlignVerticalCenterWithPage")
    ' 未选中任何形状
    If PowerPoint.ActiveWindow.Selection.Type = ppSelectionNone Then
        LogError ("Does not select any shape")
        Exit Sub
    End If
    
    Set sRange = PowerPoint.ActiveWindow.Selection.ShapeRange
    LogInfo ("Select shape count: " & sRange.Count)

    For i = 1 To sRange.Count
        LogInfo ("shape[" & i & "].left: " & sRange(i).Left & ", right: " & sRange(i).Left + sRange(i).Width)
    Next

    pageWidth = ActivePresentation.PageSetup.SlideWidth
    pageHeight = ActivePresentation.PageSetup.SlideHeight
    LogInfo ("page width: " & pageWidth & ", page height: " & pageHeight)

    ' 所有形状与页面同宽：shape.width = page.width, shape.height = page.height
    For i = 1 To sRange.Count
        sRange(i).Width = pageWidth
        sRange(i).Height = pageHeight
    Next
End Sub
