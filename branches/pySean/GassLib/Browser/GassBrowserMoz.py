import wx
import wx.mozilla

class exHtmlWindow(wx.mozilla.MozillaBrowser):
	def __init__(self, parent, id, frame):
		wx.mozilla.MozillaBrowser.__init__(self, parent, id)

class exHtmlPanel(wx.Panel):
	def __init__(self, parent, id, frame, url):
		wx.Panel.__init__(self,parent,-1)

		self.home = url
		self.html = exHtmlWindow(self, -1, frame)
		self.box = wx.BoxSizer(wx.VERTICAL)

		btnSizer = wx.BoxSizer(wx.HORIZONTAL)
		btn1 = wx.Button(self, -1, "Back", style=wx.BU_EXACTFIT)
		self.Bind(wx.EVT_BUTTON, self.OnBackButton, btn1)
		btnSizer.Add(btn1, 0, wx.EXPAND|wx.ALL, 2)

		btn2 = wx.Button(self, -1, "Next", style=wx.BU_EXACTFIT)
		self.Bind(wx.EVT_BUTTON, self.OnNextButton, btn2)
		btnSizer.Add(btn2, 0, wx.EXPAND|wx.ALL, 2)

		btn3 = wx.Button(self, -1, "Refresh", style=wx.BU_EXACTFIT)
		self.Bind(wx.EVT_BUTTON, self.OnRefreshButton, btn3)
		btnSizer.Add(btn3, 0, wx.EXPAND|wx.ALL, 2)

		btn4 = wx.Button(self, -1, "Stop", style=wx.BU_EXACTFIT)
		self.Bind(wx.EVT_BUTTON, self.OnStopButton, btn4)
		btnSizer.Add(btn4, 0, wx.EXPAND|wx.ALL, 2)

		btn5 = wx.Button(self, -1, "Home", style=wx.BU_EXACTFIT)
		self.Bind(wx.EVT_BUTTON, self.OnHomeButton, btn5)
		btnSizer.Add(btn5, 0, wx.EXPAND|wx.ALL, 2)

		self.box.Add(btnSizer, 0, wx.EXPAND)
		self.box.Add(self.html, 1, wx.EXPAND)
		self.SetSizer(self.box)
		self.SetAutoLayout(True)
		self.html.LoadURL(self.home)

	def OnHomeButton(self, event):
		self.html.LoadURL(self.home)

	def OnBackButton(self, event):
		self.html.GoBack()