import wx, wx.aui
class ChatFrame(wx.App):
	def __init__(self):
		wx.App.__init__(self, redirect=False)
		
	def OnInit(self):
		frame = wx.Frame(None, -1, "GAMS Messenger", pos=(50,50), 
				size=(640, 480), style=wx.DEFAULT_FRAME_STYLE, name="Chat")
		frame.CreateStatusBar()
		
		menuBar = wx.MenuBar()
		menu = wx.Menu()
		item1 = menu.Append(-1, "New Chat &Tab\tCtrl-T", "Open New Tab")
		item2 = menu.Append(-1, "&Close Win\tCtrl-W", "Close Chat Window")
		self.Bind(wx.EVT_MENU, self.OnCloseWin, item2)
		self.Bind(wx.EVT_MENU, self.OnNewTab, item1)
		menuBar.Append(menu, "&File")
		
		frame.SetMenubar(menuBar)
		frame.Show(True)
		frame.Bind(wx.EVT_CLOSE, self.OnCloseWin)
		win = ChatWin(frame, -1)
		if win:
			frame.SetSize((640, 480))
			win.SetFocus()
			self.window = win
			frect = frame.GetRect()
		else:
			frame.Destroy()
			return True
		self.SetTopWindow(frame)
		self.frame = frame
		return True
	def OnCloseWin(self, evt):
		self.window.Close(True)
		
	def OnNewTab(self, evt):

class ChatWin(wx.Panel):
	def __init__(self, parent):
		wx.Panel.__init__(self, parent, -1)
		splitter = ChatSplitter(self, -1)
		#p1 = BuddyListBox(splitter)
		p1 = wx.Window(splitter)
		#p2 = TabWindow(splitter)
		p2 = wx.Window(splitter)
		splitter.SetMinimumPaneSize(20)
		splitter.SplitVertically(p1, p2, -100)
		
class ChatSplitter(wx.SplitterWindow):
	def __init__(self, parent, id):
		wx.SplitterWindow.__init__(self, parent, id, style=wx.SP_LIVE_UPDATE)
		self.Bind(wx.EVT_SPLITTER_SASH_POS_CHANGED, self.OnSashChanged)
		self.Bind(wx.EVT_SPLITTER_SASH_POS_CHANGING, self.OnSashChanging)
	def OnSashChanged(self, evt):
		evt.Skip()
	def OnSashChanging(self, evt):
		evt.SetSashPosition(-1)
		
class TabWindow(wx.aui.AuiMDIParentFrame):
	def __init__(self, parent):
		wx.aui.AuiMDIParentFrame.__init__(self, parent, -1, 
				title="ChatWindows", size=(480,320),
				style=wx.DEFAULT_FRAME_STYLE)
		self.count = 0
		child = ChildFrame(self, self.count)
		child.Show()
	def MakeMenuBar(self):
		mb = wx.MenuBar()
		menu = wx.Menu()
		item = menu.Append(-1, "New child window\tCtrl-N")
		self.Bind(wx.EVT_MENU, self.OnNewChild, item)
		item = menu.Append(-1, "Close parent")
		self.Bind(wx.EVT_MENU, self.OnDoClose, item)
		mb.Append(menu, "&File")
		return mb
	def OnNewChild(self, evt):
		self.count += 1
		child = ChildFrame(self, self.count)
		child.Show()
	def OnDoClose(self, evt):
		self.Close()
		
		
class ChildFrame(wx.aui.AuiMDIChildFrame):
	def __init__(self, parent, count):
		wx.aui.AuiMDIChildFrame.__init__(self, parent, -1, 
				title="Child: %d" % count)
		mb = parent.MakeMenuBar()
		menu = wx.Menu()
		item = menu.Append(-1, "This is child %d's menu" % count)
		mb.Append(menu, "&Child")
		self.SetMenuBar(mb)
		p = wx.Panel(self)
		wx.StaticText(p, -1, "This is child %d" % count, (10,10))
		p.SetBackgroundColour('light blue')
		sizer = wx.BoxSizer()
		sizer.Add(p, 1, wx.EXPAND)
		self.SetSizer(sizer)
		wx.CallAfter(self.Layout)
		
class BuddyListBox(wx.Panel):
	def __init__(self, parent):
		wx.Panel.__init__(self, parent, -1)
		sampleList = ['BuddyOne', 'BuddyTwo', 'BuddyThree']
		self.buddyList = wx.ListBox(self, 60, (100,50), (90,120), sampleList, 
				wx.LB_SINGLE)
		self.Bind(wx.EVT_LISTBOX, 
				self.EvtListBox, self.buddyList)
		self.Bind(wx.EVT_LISTBOX_DCLICK, 
				self.EvtListBoxDClick, self.buddyList)
		self.buddyList.Bind(wx.EVT_RIGHT_UP, self.EvtRightButton)
		self.buddyList.SetSelection(2)
		self.buddyList.Append("with data", "This one has data")
		self.buddyList.SetClientData(2, "This one has data")
	def EvtListBox(self, event):
		lb = event.GetEventObject()
		data = lb.GetClientData(lb.GetSelection())
	def EvtListBoxDClick(self, event):
		self.lb1.Delete(self.lb1.GetSelection())
	def EvtMultiListBox(self, event):
		event.Skip()
	def EvtRightButton(self, event):
		if event.GetEventObject().GetId() == 70:
			selections = list(self.lb2.GetSelections())
			selections.reverse()
			for index in selections:
				self.lb2.Delete(index)