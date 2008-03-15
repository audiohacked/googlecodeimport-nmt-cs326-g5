import wx

if wx.Platform == '__WXMSW__':
	import wx.lib.iewin as iewin



class exHtmlPanel(wx.Panel):
	def __init__(self, parent, id, frame, url, communityTab=None):
		wx.Panel.__init__(self,parent,-1)

		self.current = url
		self.home = url
		self.community = "http://infohost.nmt.edu/~nmtlan/forum"

		self.ie = iewin.IEHtmlWindow(self, -1, style = wx.NO_FULL_REPAINT_ON_RESIZE)
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

		if communityTab != None:
			self.AddrBar = wx.TextCtrl(self, -1, value=self.home, size=wx.Size(400), style=wx.TE_PROCESS_ENTER)
			self.Bind(wx.EVT_TEXT_ENTER, self.OnGoButton, self.AddrBar)
			btnSizer.Add(self.AddrBar, 0, wx.EXPAND|wx.ALL, 2)
			
			#btn6 = wx.Button(self, -1, "Go", style=wx.BU_EXACTFIT)
			#self.Bind(wx.EVT_BUTTON, self.OnGoButton, btn6)
			#btnSizer.Add(btn6, 0, wx.EXPAND|wx.ALL, 2)
			
			#spacer
			
			#btn7 = wx.Button(self, -1, "Community", style=wx.BU_EXACTFIT)
			#self.Bind(wx.EVT_BUTTON, self.OnCommunityButton, btn7)
			#btnSizer.Add(btn7, 0, wx.EXPAND|wx.ALL, 2)
		self.box.Add(btnSizer, 0, wx.EXPAND)
		self.box.Add(self.ie, 1, wx.EXPAND)

#		btnSizerTwo = wx.BoxSizer(wx.HORIZONTAL)

#		btn21 = wx.Button(self, -1, "News", style=wx.BU_EXACTFIT)
#		self.Bind(wx.EVT_BUTTON, self.OnCommunityButton, btn21)
#		btnSizerTwo.Add(btn21, 0, wx.EXPAND|wx.ALL, 2)

#		btn22 = wx.Button(self, -1, "Friends", style=wx.BU_EXACTFIT)
#		self.Bind(wx.EVT_BUTTON, self.OnCommunityButton, btn22)
#		btnSizerThree.Add(btn22, 0, wx.EXPAND|wx.ALL, 2)

#		btn23 = wx.Button(self, -1, "Servers", style=wx.BU_EXACTFIT)
#		self.Bind(wx.EVT_BUTTON, self.OnCommunityButton, btn23)
#		btnSizerThree.Add(btn23, 0, wx.EXPAND|wx.ALL, 2)

#		btn24 = wx.Button(self, -1, "Settings", style=wx.BU_EXACTFIT)
#		self.Bind(wx.EVT_BUTTON, self.OnCommunityButton, btn24)
#		btnSizerThree.Add(btn24, 0, wx.EXPAND|wx.ALL, 2)

#		btn25 = wx.Button(self, -1, "Support", style=wx.BU_EXACTFIT)
#		self.Bind(wx.EVT_BUTTON, self.OnCommunityButton, btn25)
#		btnSizerThree.Add(btn25, 0, wx.EXPAND|wx.ALL, 2)

#		self.box.Add(btnSizerTwo, 2, wx.EXPAND)
		
		self.SetSizer(self.box)
		self.SetAutoLayout(True)
		
		if communityTab != None:
			self.ie.LoadUrl(self.community)
		else:
			self.ie.LoadUrl(self.current)
		
	def OnHomeButton(self, event):
		if communityTab != None:
			self.ie.LoadUrl(self.community)
		else:
			self.ie.LoadUrl(self.current)

	def OnCommunityButton(self, event):
		self.ie.LoadUrl(self.community)

	def OnNextButton(self, event):
		self.ie.GoForward()

	def OnRefreshButton(self, event):
		self.ie.RefreshPage()

	def OnStopButton(self, event):
		self.ie.Stop()

	def OnGoButton(self, event):
		self.ie.LoadUrl(self.AddrBar.GetValue())

	def OnBackButton(self, event):
		self.ie.GoBack()