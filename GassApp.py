import zlib
import sys, wx, wx.lib.dialogs
from GassLib.Gui import GassGui
#----------------------------------------------------------------------------

class GassTaskBarIcon(wx.TaskBarIcon):
	TBMENU_RESTORE = wx.NewId()
	TBMENU_CLOSE = wx.NewId()
	TBMENU_HIDE = wx.NewId()

	def __init__(self, frame):
		wx.TaskBarIcon.__init__(self)
		self.frame = frame

		self.SetIcon(frame._icon)

		self.Bind(wx.EVT_TASKBAR_LEFT_DCLICK, self.OnTaskBarActivate)
		self.Bind(wx.EVT_MENU, self.OnTaskBarActivate, id=self.TBMENU_RESTORE)
		self.Bind(wx.EVT_MENU, self.OnHide, id=self.TBMENU_HIDE)
		self.Bind(wx.EVT_MENU, self.OnTaskBarClose, id=self.TBMENU_CLOSE)

	def CreatePopupMenu(self):
		menu = wx.Menu()
		menu.Append(self.TBMENU_RESTORE, "Show GassApp")
		menu.Append(self.TBMENU_HIDE, "Hide GassApp")
		menu.Append(self.TBMENU_CLOSE,   "Exit GassApp")
		return menu

	def OnHide(self, evt):
		if not self.frame.IsIconized():
			self.frame.Iconize(True)
		if self.frame.IsShown():
			self.frame.Show(False)
		
	def OnTaskBarActivate(self, evt):
		if self.frame.IsIconized():
			self.frame.Iconize(False)
		if not self.frame.IsShown():
			self.frame.Show(True)
		self.frame.Raise()
		self.frame.Raise()

	def OnTaskBarClose(self, evt):
		self.frame.Destroy()
		self.Destroy()

class GassMenu:
	def __init__(self, parent):
		self.parent = parent
	
	def mainMenu(self):
		menuBar = wx.MenuBar()
		fileMenu = wx.Menu()
		item01 = fileMenu.Append(-1, "Logout...", "Logout/Login or Change user..")
		item02 = fileMenu.Append(-1, "Check for GassApp updates", "Check online for latest version of GassApp")
		self.parent.Bind(wx.EVT_MENU, self.parent.OnUpdateCheck, item02)
		fileMenu.AppendSeparator()
		item03 = fileMenu.Append(-1, "Settings", "Configure GassApp Settings")
		fileMenu.AppendSeparator()
		item04 = fileMenu.Append(-1, "E&xit\tCtrl-Q", "Exit demo")
		self.parent.Bind(wx.EVT_MENU, self.parent.OnExitApp, item04)
		menuBar.Append(fileMenu, "&File")
		viewMenu = wx.Menu()
		item21 = viewMenu.Append(-1, "Switch to mini mode", "Switch to mini App Mode")
		viewMenu.AppendSeparator()
		item22 = viewMenu.Append(-1, "Messenger", "Open Chat Messenger")
		self.parent.Bind(wx.EVT_MENU, self.parent.OnOpenChat, item22)
		viewMenu.AppendSeparator()
		item23 = viewMenu.Append(-1, "Bandwidth monitor", "View Bandwidth Usage/Speed")
		viewMenu.AppendSeparator()
		item24 = viewMenu.Append(-1, "Home", "Go to Homepage")
		item25 = viewMenu.Append(-1, "My Games", "View Games")
		item26 = viewMenu.Append(-1, "My Media", "View Media")
		item27 = viewMenu.Append(-1, "Tools", "View Tools")
		menuBar.Append(viewMenu, "&View")
		gamesMenu = wx.Menu()
		item41 = gamesMenu.Append(-1, "Activate a product...")
		item42 = gamesMenu.Append(-1, "Invite a Guest...")
		item43 = gamesMenu.Append(-1, "Add a non-Gass game to My Games list...")
		menuBar.Append(gamesMenu, "&Games")
		helpMenu = wx.Menu()
		item61 = helpMenu.Append(-1, "Support", "Technical support")
		item62 = helpMenu.Append(-1, "System information")
		helpMenu.AppendSeparator()
		item63 = helpMenu.Append(-1, "Privacy policy")
		item64 = helpMenu.Append(-1, "Legal information")
		helpMenu.AppendSeparator()
		item66 = helpMenu.Append(-1, "&About", "About GassApp")
		self.parent.Bind(wx.EVT_MENU, self.parent.OnAboutBox, item66)
		menuBar.Append(helpMenu, "&Help")
		return menuBar

class GassMainFrame(wx.Frame):
	def __init__(self, parent, id, title):
		wx.Frame.__init__(self, parent, id, title,
				wx.DefaultPosition, wx.Size(640,480))
				
		_iconize_on_close = (wx.Platform == '__WXMSW__')
				
		self.CreateStatusBar()
		self.SetStatusText("This is the statusbar")
		self.parent = parent
		self.frame = self

		if wx.Platform == '__WXMSW__':
			#exeName = win32api.GetModuleFileName(win32api.GetModuleHandle(None))
			self._icon = wx.Icon(sys.executable + ";0", wx.BITMAP_TYPE_ICO)
		elif (wx.Platform == '__WXMAC__') and hasattr(sys, "frozen"):
			self._icon = wx.Icon("../Resources/GassApp.ico", wx.BITMAP_TYPE_ICO)
		else:
			self._icon = wx.Icon("contrib/GassApp.ico", wx.BITMAP_TYPE_ICO)

		self.tbicon = GassTaskBarIcon(self)
		self.SetIcon(self._icon)		

		menuBar = GassMenu(self).mainMenu()
		self.SetMenuBar(menuBar)

		self.Show(True)
		
		
		if not _iconize_on_close:
			self.Bind(wx.EVT_CLOSE, self.OnCloseFrame)
		else:
			self.Bind(wx.EVT_CLOSE, self.OnHide)

		self.Bind(wx.EVT_ICONIZE, self.OnHide)
		
		win = GassGui.MainWin(self, -1)
		if win:
			self.SetSize((1000, 650))
			win.SetFocus()
			self.window = win
			frect = self.GetRect()
		else:
			self.Destroy()

		#self.box = wx.BoxSizer(wx.VERTICAL)
		#btnSizer = wx.BoxSizer(wx.HORIZONTAL)
		#btn1 = wx.Button(self, -1, "News", style=wx.BU_EXACTFIT)
		#self.Bind(wx.EVT_BUTTON, self.OnHomeButton, btn1)
		#btnSizer.Add(btn1, 0, wx.EXPAND|wx.ALL, 2)
		#btn2 = wx.Button(self, -1, "Messenger", style=wx.BU_EXACTFIT)
		#self.Bind(wx.EVT_BUTTON, self.OnHomeButton, btn1)
		#btnSizer.Add(btn2, 0, wx.EXPAND|wx.ALL, 2)
		#btn3 = wx.Button(self, -1, "Update", style=wx.BU_EXACTFIT)
		#self.Bind(wx.EVT_BUTTON, self.OnUpdateCheck, btn3)
		#btnSizer.Add(btn3, 0, wx.EXPAND|wx.ALL, 2)
		#btn4 = wx.Button(self, -1, "Settings", style=wx.BU_EXACTFIT)
		#self.Bind(wx.EVT_BUTTON, self.OnHomeButton, btn1)
		#btnSizer.Add(btn4, 0, wx.EXPAND|wx.ALL, 2)
		#self.box.Add(self.window, 0, wx.EXPAND)
		#self.box.Add(btnSizer, 1, wx.EXPAND)
		#self.SetSizer(self.box)
		#self.SetAutoLayout(True)

		#parent.SetTopWindow(self)

	def OnUpdateCheck(self, event):
		from GassLib.GassCheckVersion import CheckForUpdate
		manualCheck = CheckForUpdate(self)
		#if not manualCheck.new_version():
		dlgNew = wx.MessageDialog(self, "The Circle is Now Complete!",
			"Manual Check for Update", wx.OK|wx.ICON_INFORMATION)
		dlgNew.ShowModal()
		dlgNew.Destroy()
		
	def OnAboutBox(self, event):
		#print "AboutBox: remixing the boring!"
		dlgAbout = wx.lib.dialogs.ScrolledMessageDialog(self,
			"GassApp is a Content Distribution System"+\
			" and Social System. "+\
			"GassApp has integrated Browser, Jabber-based Instant"+\
			" Messenger, and Game Downloader/Installer",
			"About GassApp")
		dlgAbout.ShowModal()
		dlgAbout.Destroy()

	def OnHide(self, evt):
		if not self.frame.IsIconized():
			self.frame.Iconize(True)
		if self.frame.IsShown():
			self.frame.Show(False)

	def OnExitApp(self, evt):
		if self.tbicon is not None:
			self.tbicon.Destroy()
		self.frame.Close(True)
		self.Destroy()

	def OnOpenChat(self, evt):
		print "Broken!"

	def OnCloseFrame(self, evt):
		if self.tbicon is not None:
			self.tbicon.Destroy()
		self.window.Destroy()
		self.Destroy()
		evt.Skip()

#----------------------------------------------------------------------------

class GassApp(wx.App):
	def OnInit(self):
		frame = GassMainFrame(None, -1, "Games And Media Service")
		frame.Show(True)
		self.SetTopWindow(frame)
		return True


#sys.stdout = open("GassApp_out.log", "w")
#sys.stderr = open("GassApp_error.log", "w")
app = GassApp()
app.MainLoop()

