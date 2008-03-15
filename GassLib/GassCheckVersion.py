import wx, sys, os, urllib
from urlparse import urljoin
from GassLib.Downloader.http import get

if wx.Platform == '__WXMSW__':
	import xml.etree.ElementTree as ET
elif wx.Platform == '__WXMAC__':
	import elementtree.ElementTree as ET

class CheckForUpdate:
	def __init__(self, parent):
		
		_appBaseName = "GassApp"

		if wx.Platform == '__WXMSW__':
			_appPlatform = "win"
			_appBuildExt = ".exe"
		elif wx.Platform == '__WXMAC__':
			_appPlatform = "mac"
			_appBuildExt = ".app"
		elif wx.Platform == '__WXGTK__':
			_appPlatform = "linux"
			_appBuildExt = ""

		_appBuildArchive = _appBaseName+"_"+_appPlatform+".zip"
		_appBuildExec = _appBaseName+_appBuildExt

		self.winAppVer = ""
		if wx.Platform == '__WXMSW__' and hasattr(sys, "frozen"):
			import win32api
			fname = win32api.GetModuleFileName(win32api.GetModuleHandle(None))
			self.winAppVer += win32api.GetFileVersionInfo(fname, u'\\StringFileInfo\\040904B0\\FileVersion')
		elif wx.Platform == '__WXMAC__' and hasattr(sys, "frozen"):
			from GassLib import PListReader, XMLFilter
			reader = PListReader.PListReader()
			XMLFilter.parseFilePath("../Info.plist", reader,
				features = reader.getRecommendedFeatures())
			result = reader.getResult()

			self.winAppVer = result[r'CFBundleVersion']
		else:
			self.winAppVer = "0.2.7.1"
		
		if os.path.exists("userconfig.xml") == False:
			fileName = get.download("http://www.seancrazy.net/ListGass.xml")
			os.rename(fileName, "userconfig.xml")
			
		appXML = ET.parse("userconfig.xml")
		appData = appXML.getroot().find("service-info").find("app")
		appUpdateUrl = appData.find("update-url").text
		self.appNetConfig = appNetConfig = appData.find("net-config").text

		netXML = ET.parse(urllib.urlopen(appNetConfig))
		netData = netXML.getroot().find("service-info").find("app")
		self.netAppVersion = netAppVersion = netData.find("version").text
		self.netAppHomepage = netData.find("homepage").text
		
		appUpdateUrl = urljoin(appUpdateUrl, _appBuildArchive)
		
		if self.winAppVer < netAppVersion:
			updateText = "I'm sorry you are running an Old version of GassApp. " + \
				"Please Update your version to the latest at:\n\t" + \
				appUpdateUrl + \
				"\n You have version: " + self.winAppVer + \
				"\n The Latest version is: " + netAppVersion + "\n\n" + \
				"The Latest Version  will now Download and This Window"+\
				" will Close If you click OK!\n\n"

			dialog = wx.lib.dialogs.ScrolledMessageDialog(parent, updateText, "Updater")
			updateResponse = dialog.ShowModal()

			if updateResponse == wx.ID_OK:
				dialog.Destroy()
				GassDownloader.Downloader(parent, appUpdateUrl)

				from GassLib.GassUnzipper import GassUnzip
				un = GassUnzip()
				un.extract(_appBuildArchive, _appBuildExec,
				 	_appBaseName+"_new"+_appBuildExt)

				appXML.close()
				os.remove("userconfig.xml")
				fileName = get.download("http://www.seancrazy.net/ListGass.xml")
				os.rename(fileName, "userconfig.xml")

				parent.Destroy()

		def get_homepage(self):
			return self.netAppHomepage

		def get_config(self):
			return self.appNetConfig

		def new_version(self):
			return self.winAppVer < self.netAppVersion
