Private Sub LogInfo(log)
    Debug.Print ("[" & Now() & "][Info]: " & log)
End Sub

Private Sub LogError(log)
    Debug.Print ("[" & Now() & "][Error]: " & log)
End Sub

Private Sub Helloworld()
    Dim mBar As Object
    Set mBar = PowerPoint.Application.CommandBars.ActiveMenuBar

    Debug.Print ("----------------------------------------------------------")
    Debug.Print ("time: " & Now())
'    Debug.Print ("name: " & PowerPoint.Application.Name)
    Debug.Print ("active menu bar name: " & PowerPoint.Application.CommandBars.ActiveMenuBar.Name)
    Debug.Print ("type: " & PowerPoint.Application.CommandBars.ActiveMenuBar.Type)
    Debug.Print ("controls count: " & PowerPoint.Application.CommandBars.ActiveMenuBar.Controls.Count)
'    Debug.Print ("context: " & PowerPoint.Application.CommandBars.ActiveMenuBar.Context)
'    Debug.Print ("index: " & PowerPoint.Application.CommandBars.ActiveMenuBar.Index)
'    Debug.Print ("left: " & PowerPoint.Application.CommandBars.ActiveMenuBar.Left)
'    Debug.Print ("top: " & PowerPoint.Application.CommandBars.ActiveMenuBar.Top)
'    Debug.Print ("width: " & PowerPoint.Application.CommandBars.ActiveMenuBar.Width)
'    Debug.Print ("height: " & mBar.Height)
'    Debug.Print ("position: " & mBar.Position)
'    Debug.Print ("parent: " & mBar.Parent.Name)
'    Debug.Print ("name: " & PowerPoint.Application.CommandBars("Reviewing").Name)
'    Debug.Print ("name: " & PowerPoint.Application.CommandBars("我的").Name)
'    PowerPoint.Application.CommandBars.Add(Name:="My command bar")
'    Debug.Print ("count: " & PowerPoint.Application.CommandBars.ActiveMenuBar.Controls.Count)

    Dim cbar As Object
    For Each cbar In CommandBars
        Debug.Print ("cbar name: " & cbar.Name)
        If cbar.Name = "huangxing" Then
            Debug.Print ("Will delete cbar: " & cbar.Name)
            cbar.Delete
        End If

'        Debug.Print ("msoBarMenu = " & msoBarMenu)
'        If cbar.Type = msoBarMenu Then
'            Debug.Print ("cbar name: [" & cbar.Type & "]" & cbar.Name)
'        End If
    Next

'    Set newItem = CommandBars("My command bar").Controls.Add(Type:=msoControlButton)
'    With newItem
'        .BeginGroup = True
'        .Caption = "Make Report"
'        .FaceId = 0
'        .OnAction = "qtrReport"
'    End With

'    Debug.Print ("count: " & PowerPoint.Application.CommandBars.ActionControl.)

    Set newBar = PowerPoint.Application.CommandBars.Add(Name:="huangxing", Position:=msoBarFloating, Temporary:=True)
    newBar.Visible = True
    ' 控件类型：msoControlButton、msoControlEdit、msoControlDropdown、msoControlComboBox、msoControlPopup
    Set newCtrl = newBar.Controls.Add(Type:=msoControlButton)
'    Set newctrl = newBar.Controls.Add(Type:=msoControlButton, Id:=1)
    With newCtrl
        .Visible = True
'        .BeginGroup = True
'        .DescriptionText = "test cbar"
        .Caption = "左对齐"
'        .Tag = "xxx"
'        .FaceId = 10
'        .OnAction = "xxx"
'        .BackColor = &H8000000F
'        .TooltipText = "test cbar"
'        .Top = -2
'        .Width = 50
        .Style = msoButtonCaption
'        .Click = GlobalEvents.TestCmdBarClick
        .OnAction = "MyAlignLeft"
    End With


'    Debug.Print ("cbar name: " & PowerPoint.ActiveWindow.View.Slide.Shapes)
'    Debug.Print ("sel count: " & PowerPoint.ActiveWindow.Selection.ShapeRange.Count) '当前选中的图形数量
'    Debug.Print ("left: " & PowerPoint.ActiveWindow.Selection.ShapeRange(1).Left)
'    Debug.Print ("top: " & PowerPoint.ActiveWindow.Selection.ShapeRange(1).Top)
'    Debug.Print ("width: " & PowerPoint.ActiveWindow.Selection.ShapeRange(1).Width)
'    Debug.Print ("height: " & PowerPoint.ActiveWindow.Selection.ShapeRange(1).Height)
'
'    Debug.Print ("left: " & PowerPoint.ActiveWindow.Selection.ShapeRange(2).Left)
'    Debug.Print ("top: " & PowerPoint.ActiveWindow.Selection.ShapeRange(2).Top)
'    Debug.Print ("width: " & PowerPoint.ActiveWindow.Selection.ShapeRange(2).Width)
'    Debug.Print ("height: " & PowerPoint.ActiveWindow.Selection.ShapeRange(2).Height)

    PowerPoint.ActiveWindow.Selection.ShapeRange(2).Left = 570

End Sub

Public Sub MyAlignLeft()
    Dim sRange As Object

    ' 未选中任何形状
    If PowerPoint.ActiveWindow.Selection.Type = ppSelectionNone Then
        LogError ("Error: Does not select any shape")
        Exit Sub
    End If

    ' 选中形状少于2个
    Set sRange = PowerPoint.ActiveWindow.Selection.ShapeRange
    If sRange.Count < 2 Then
        Debug.Print ("Error: Select shape count less than 2")
        Exit Sub
    End If

    For i = 1 To sRange.Count
        Debug.Print ("[" & Now() & "][Info ]: shape[" & i & "].left: " & sRange(i).Left)
    Next
    ' 所有形状与第一个形状左对齐
    For i = 2 To sRange.Count
        sRange(i).Left = sRange(1).Left
    Next
End Sub
