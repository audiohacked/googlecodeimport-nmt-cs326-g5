import wx, sys, os
import xml.etree.ElementTree as ET
from urllib import urlopen
from urlparse import urlparse
from string import split
from ftplib import FTP

ID_ABOUT = 101
ID_EXIT = 102

class GassXml:

	def __init__(self):
		self.locationURL = "http://www.seancrazy.net/"
		self.configFile = "ListGass.xml"

		if os.path.exists(self.configFile) == False:
			fileName = self.download(self.locationURL+self.configFile)

		self.tree = ET.parse("ListGass.xml")
		GassAppService = self.tree.getroot()

		service_info = GassAppService.find("service-info")
		service_media = GassAppService.find("service-media")

		self.app = service_info.find("app")
		self.games = service_media.find("games")
		self.media = service_media.find("media")

	def download(self, url):
		instream = urlopen(url)
		filename = split(urlparse(url)[2], '/')[-1]
		outstream = open(filename, "wb")
		outstream.write(instream.read())
		outstream.close()
		return filename
	
	def saveXml(self, fname):
		self.tree.write(fname)
		ftp = FTP("seancrazy.net", "u40385432", "deathball")
		ftp.set_pasv(True)
		print ftp.sendcmd("CWD /subdomains/sean")
		print ftp.storlines("STOR "+self.configFile, open(fname))
		ftp.close()
	
	def cleanFiles(self,fname):
		os.remove(fname)
		os.remove(self.configFile)

class UpdateAppData(wx.Panel):
	def __init__(self, parent, id, frame):
		wx.Panel.__init__(self, parent, -1)
		self.AppXml = GassXml()
		self.app_version = self.AppXml.app.find("version")
		self.app_homepage = self.AppXml.app.find("homepage")
		self.app_update_url = self.AppXml.app.find("update-url")
		self.app_net_config = self.AppXml.app.find("net-config")
		
		versionLabel = wx.StaticText(self, -1, "Latest App Version:")
		self.version = versionField = wx.TextCtrl(self, -1, 
				self.app_version.text, size=(350, -1))
		
		homepageLabel = wx.StaticText(self, -1, "Homepage-tab URL:")
		self.homepage =  homepageField = wx.TextCtrl(self, -1,
		 		self.app_homepage.text, size=(350, -1))

		updateLabel = wx.StaticText(self, -1, "Update-tab URL:")
		self.update = updateField = wx.TextCtrl(self, -1, 
				self.app_update_url.text, size=(350, -1))
		
		netconfigLabel = wx.StaticText(self, -1, "NetConfig URL:")
		self.netconfig = netconfigField = wx.TextCtrl(self, -1, 
				self.app_net_config.text, size=(350, -1))
		
		saveButton = wx.Button(self, -1, "Save App Configuration")
		self.Bind(wx.EVT_BUTTON, self.SaveValues)
		
		self.sizer = wx.FlexGridSizer(cols=3, hgap=8, vgap=8)
		self.sizer.AddMany([ 
				versionLabel, versionField, (0,0),
				homepageLabel, homepageField, (0,0),
				updateLabel, updateField, (0,0),
				netconfigLabel, netconfigField, (0,0),
				(0,0), (0,0), (0,0),
				(0,0), saveButton, (0,0),
		])
		self.border = wx.BoxSizer(wx.VERTICAL)
		self.border.Add(self.sizer, 0, wx.ALL, 20)
		self.SetSizer(self.border)
		self.SetAutoLayout(True)

	def EvtText(self, event):
		print "EvtText: %s\n" % event.GetString()
		self.PrintValues()
	
	def EvtTextEnter(self, event):
		print "EvtTextEnter\n"
		
	def SaveValues(self, event):
		self.app_version.text = self.version.GetValue()
		self.app_homepage.text = self.homepage.GetValue()
		self.app_update_url.text = self.update.GetValue()
		self.app_net_config.text = self.netconfig.GetValue()
		self.AppXml.saveXml("app_out.xml")
		self.AppXml.cleanFiles("app_out.xml")
		
class AddGame(wx.Panel):
	def __init__(self, parent, id, frame):
		wx.Panel.__init__(self, parent, -1)
		nameLabel = wx.StaticText(self, -1, "Game Name:")
		self.name = nameField = wx.TextCtrl(self, -1, 
				"", size=(350, -1))

		homepageLabel = wx.StaticText(self, -1, "Homepage URL:")
		self.homepage = homepageField = wx.TextCtrl(self, -1, 
				"http://", size=(350, -1))

		downloadLabel = wx.StaticText(self, -1, "Download URL:")
		self.download = downloadField = wx.TextCtrl(self, -1, 
				"http://", size=(350, -1))

		previewLabel = wx.StaticText(self, -1, "Preview Video URL:")
		self.preview = previewField = wx.TextCtrl(self, -1, 
				"http://", size=(350, -1))

		scoreLabel = wx.StaticText(self, -1, "Game Score:")
		self.score = scoreField = wx.TextCtrl(self, -1, 
				"00", size=(350, -1))

		buildLabel = wx.StaticText(self, -1, "Build Script URL:")
		self.build = buildField = wx.TextCtrl(self, -1, 
				"http://", size=(350, -1))

		saveButton = wx.Button(self, -1, "Save App Configuration")
		self.Bind(wx.EVT_BUTTON, self.SaveValues)
		
		self.GameSizer = wx.FlexGridSizer(cols=3, hgap=8, vgap=8)
		self.GameSizer.AddMany([ 
				nameLabel, nameField, (0,0),
				homepageLabel, homepageField, (0,0),
				downloadLabel, downloadField, (0,0),
				previewLabel, previewField, (0,0),
				scoreLabel, scoreField, (0,0),
				buildLabel, buildField, (0,0),
				(0,0), (0,0), (0,0),
				(0,0), saveButton, (0,0),
		])
		self.GameBorder = wx.BoxSizer(wx.VERTICAL)
		self.GameBorder.Add(self.GameSizer, 0, wx.ALL, 20) 
		self.SetSizer(self.GameBorder)
		self.SetAutoLayout(True)

	def SaveValues(self, event):
		GamesXml = GassXml()
		games = GamesXml.games
		package = ET.SubElement(games, "package")
		package.set("name", self.name.GetValue())
		package_homepage = ET.SubElement(package, "homepage")
		package_homepage.text = self.homepage.GetValue()
		package_url = ET.SubElement(package, "package-url")
		package_url.text = self.download.GetValue()
		preview_url = ET.SubElement(package, "preview-url")
		preview_url.text = self.preview.GetValue()
		package_score = ET.SubElement(package, "score")
		package_score.text = self.score.GetValue()
		package_build = ET.SubElement(package, "build")
		package_build.text = self.build.GetValue()
		GamesXml.saveXml("game_out.xml")
		GamesXml.cleanFiles("game_out.xml")
		
	def EvtText(self, event):
		print "EvtText: %s\n" % event.GetString()
		self.PrintValues()

	def EvtTextEnter(self, event):
		print "EvtTextEnter\n"

class AddMedia(wx.Panel):
	def __init__(self, parent, id, frame):
		wx.Panel.__init__(self, parent, -1)

		self.GameBorder = wx.BoxSizer(wx.VERTICAL)
		#self.GameBorder.Add(self.GameSizer, 0, wx.ALL, 20) 
		self.SetSizer(self.GameBorder)
		self.SetAutoLayout(True)

	def EvtText(self, event):
		print "EvtText: %s\n" % event.GetString()
		self.PrintValues()

	def EvtTextEnter(self, event):
		print "EvtTextEnter\n"

	def SaveValues(self, event):
		self.MediaXml = GassXml()
		media = self.MediaXml.media
		package = ET.SubElement(media, "package")
		package.set("name", packageMediaName)
		package_url = ET.SubElement(package, "package-url")
		package_url.text = packageMediaUrl
		package_homepage = ET.SubElement(package, "package-homepage")
		package_homepage.text = packageMediaHomepage
		package_type = ET.SubElement(package, "package-type")
		package_type.text = packageMediaType
		self.MediaXml.saveXml("media_out.xml")
		self.MediaXml.cleanFiles("media_out.xml")

class GassEditorNotebook(wx.Notebook):
	def __init__(self, parent, id):
		wx.Notebook.__init__(self, parent, id, size=(21,21))

		win = UpdateAppData(self, -1, self)
		self.AddPage(win, "Update GassApp Data")

		win = AddGame(self, -1, self)
		self.AddPage(win, "Add Game")

		#win = AddMedia(self, -1, self)
		#self.AddPage(win, "Add Media")

		#win = UpdateGame()
		#self.AddPage(win, "Update Game")

		#win = UpdateMedia()
		#self.AddPage(win, "Update Media")
		
		self.Bind(wx.EVT_NOTEBOOK_PAGE_CHANGED, self.OnPageChanged)
		self.Bind(wx.EVT_NOTEBOOK_PAGE_CHANGING, self.OnPageChanging)

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

class EditorFrame(wx.Frame):
	def __init__(self, parent, id, title):
		wx.Frame.__init__(self, parent, id, title,
				wx.DefaultPosition, wx.Size(640,480))
		self.CreateStatusBar()
		self.SetStatusText("This is the statusbar")
		
		menu = wx.Menu()
		itemAbout = menu.Append(ID_ABOUT, "&About",
				"More information about this program")
		menu.AppendSeparator()
		itemQuit = menu.Append(ID_EXIT, "E&xit", "Terminate the program")
		menuBar = wx.MenuBar()
		menuBar.Append(menu, "&File")
		self.SetMenuBar(menuBar)
		self.Bind(wx.EVT_MENU, self.OnAbout, itemAbout)
		self.Bind(wx.EVT_MENU, self.ClosingTimeJames, itemQuit)

		win = GassEditorNotebook(self, -1)
		if win:
			win.SetFocus()
			self.window = win
		#	frect = frame.GetRect()
		#else:
		#	self.Close(True)

	def OnAbout(self, event):
		dlg = wx.MessageDialog(self, "This sample progam shows off \n"+\
								"frames, menus, statusbars, and this\n"+\
								"message dialog.",
								"About Me", wx.OK | wx.ICON_INFORMATION)
		dlg.ShowModal()
		dlg.Destroy()

	def ClosingTimeJames(self, event):
		self.Close(True)

class GassXmlEditorApp(wx.App):
	def OnInit(self):
		frame = EditorFrame(None, -1, "Hello from wxPython")
		frame.Show(True)
		self.SetTopWindow(frame)
		return True
		
app = GassXmlEditorApp()
app.MainLoop()