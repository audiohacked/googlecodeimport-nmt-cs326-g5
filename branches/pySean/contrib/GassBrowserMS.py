import wx

if wx.Platform == '__WXMSW__':
	import wx.lib.iewin as iewin




class exHtmlPanel(wx.Panel):
	def __init__(self, parent, id, frame, url):
		wx.Panel.__init__(self,parent,-1,
			style=wx.TAB_TRAVERSAL|wx.CLIP_CHILDREN|wx.NO_FULL_REPAINT_ON_RESIZE)

		self.home = url
		self.box = wx.BoxSizer(wx.VERTICAL)
		self.ie = iewin.IEHtmlWindow(self, -1, style = wx.NO_FULL_REPAINT_ON_RESIZE)

        btnSizer = wx.BoxSizer(wx.HORIZONTAL)
		btn1 = wx.Button(self, -1, "< Back", style=wx.BU_EXACTFIT)
		self.Bind(wx.EVT_BUTTON, self.OnBackButton, btn1)
		btnSizer.Add(btn1, 0, wx.EXPAND|wx.ALL, 2)
		btn2 = wx.Button(self, -1, "^ Home", style=wx.BU_EXACTFIT)
		self.Bind(wx.EVT_BUTTON, self.OnHomeButton, btn2)
		btnSizer.Add(btn2, 0, wx.EXPAND|wx.ALL, 2)

		self.box.Add(btnSizer, 0, wx.EXPAND)
		self.box.Add(self.ie, 1, wx.EXPAND)
		self.SetSizer(self.box)
		self.SetAutoLayout(True)
		self.ie.LoadUrl(self.current)
		
	def OnHomeButton(self, event):
		self.html.LoadURL(self.home)

	def OnBackButton(self, event):
		self.html.GoBack()