import urllib, os, wx.lib.dialogs, sys, wx, wx.lib.popupctl
if wx.Platform == '__WXMSW__':
	import xml.etree.ElementTree as ET
elif wx.Platform == '__WXMAC__':
	import elementtree.ElementTree as ET

from urlparse import urljoin

if wx.Platform == '__WXMSW__':
	from GassLib.Browser import GassBrowserMS as WwwBrowser
elif wx.Platform == '__WXMAC__':
	from GassLib.Browser import GassBrowserSafari as WwwBrowser
elif wx.Platform == '__WXGTK__':
	from GassLib.Browser import GassBrowserMoz as WwwBrowser

from GassLib.Gui import GassGames, GassMedia, GassTools
from GassLib.Downloader import GassDownloader
from GassLib.Downloader.http import get

#----------------------------------------------------------------------------

def isonline(reliableserver='http://www.google.com'):
	"""Returns True if we appear to have an internet connecton or False.
		It defaults to using google as a test server, but you can supply an alt if you want."""
	try:
		urllib.urlopen(reliableserver)
		return True
	except IOError:
		return False

class ColoredPanel(wx.Window):
    def __init__(self, parent, color):
        wx.Window.__init__(self, parent, -1, style = wx.SIMPLE_BORDER)
        self.SetBackgroundColour(color)
        if wx.Platform == '__WXGTK__':
            self.SetBackgroundStyle(wx.BG_STYLE_CUSTOM)

class MainWin(wx.Notebook):
	def __init__(self, parent, id):
		wx.Notebook.__init__(self, parent, id, size=(21,21))
		
		if isonline() == False:
			message = "It Appears that you are not connected to the Internet. Please connect now and Press OK"
			offlineDialog = wx.MessageDialog(self, message)
			responseOffline = offlineDialog.ShowModal()
			if responseOffline == wx.ID_OK:
				offlineDialog.Destroy()
			else:
				offlineDialog.Destroy()
				parent.Destroy()
		
		if isonline():
			from GassLib.GassCheckVersion import CheckForUpdate
			check = CheckForUpdate(self)
			
			win = self.makeHomepage(check.netAppHomepage)
			self.AddPage(win, "Home")

			win = self.makeHomepage(check.netAppHomepage, communityTab=True)
			self.AddPage(win, "Community")
			
			win = GassGames.GamesList(self, check.appNetConfig)
			self.AddPage(win, "My Games")

			win = GassMedia.MediaList(self, check.appNetConfig)
			self.AddPage(win, "My Media")

			#win = self.makeColorPanel()
			win = GassTools.ToolsList(self, check.appNetConfig)
			self.AddPage(win, "Tools")
			#st = wx.StaticText(win.win, -1, "ToolsTest;"+\
			#	" AppVersion: "+check.winAppVer, (10, 10))

			self.Bind(wx.EVT_NOTEBOOK_PAGE_CHANGED, self.OnPageChanged)
			self.Bind(wx.EVT_NOTEBOOK_PAGE_CHANGING, self.OnPageChanging)
		else:
			parent.Destroy()


	def makeColorPanel(self, color=wx.WHITE):
		p = wx.Panel(self, -1)
		win = ColoredPanel(p, color)
		p.win = win
		def OnCPSize(evt, win=win):
			win.SetPosition((0,0))
			win.SetSize(evt.GetSize())
		p.Bind(wx.EVT_SIZE, OnCPSize)
		return p

	def makeHomepage(self, url, communityTab=None):
		p = WwwBrowser.exHtmlPanel(self, -1, self, url, communityTab)
		return p

	def OnPageChanged(self, event):
		old = event.GetOldSelection()
		new = event.GetSelection()
		sel = self.GetSelection()
		event.Skip()

	def OnPageChanging(self, event):
		old = event.GetOldSelection()
		new = event.GetSelection()
		sel = self.GetSelection()
		event.Skip()


