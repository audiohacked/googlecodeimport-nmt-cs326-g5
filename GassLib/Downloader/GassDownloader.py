import wx
from string import split
#---------------------------------------------------------------------------


class Downloader:
	def __init__(self, parent, url=None):
		fname = split(url, '/')[-1]
		if split(fname, '.')[-1] == 'torrent':
			if wx.Platform != '__WXMAC__':
				from GassLib.Downloader.GassTorrenter import TorrentDlg
				TorrentDlg(parent, url)
		else:
			from GassLib.Downloader.GassUpdater import HttpDownloadDlg
			HttpDownloadDlg(parent, url)
#---------------------------------------------------------------------------
