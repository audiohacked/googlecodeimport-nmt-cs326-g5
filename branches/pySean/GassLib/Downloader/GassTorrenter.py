import wx
from GassLib.Downloader.http import get
from GassLib.Downloader.Bittorrent import libtorrent
from string import split
#---------------------------------------------------------------------------


class TorrentDlg:
	def __init__(self, parent, url=None):
		torrentFile = get.download(url)
		max = 100.00
		dlg = wx.ProgressDialog(torrentFile,
							   url,
							   maximum = max,
							   parent=parent,
							   style = 
								wx.PD_CAN_ABORT
								#| wx.PD_CAN_SKIP
								| wx.PD_APP_MODAL
								| wx.PD_ELAPSED_TIME
								| wx.PD_ESTIMATED_TIME
								| wx.PD_REMAINING_TIME
								#| wx.PD_SMOOTH
							   )

		keepGoing = True
		count = 0
		isTorrent = True;
		ses = libtorrent.session()
		ses.listen_on(6881, 6891)

		e = libtorrent.bdecode(open(torrentFile, 'rb').read())

		h = ses.add_torrent(libtorrent.torrent_info(e), 
						"./", compact_mode = True)

		while (keepGoing == True) and (not h.is_seed()):
			s = h.status()
			state_str = ['queued', 'checking', 'connection', \
					'downloading metadata', 'downloading', \
					'finished', 'seeding', 'allocating']
			(keepGoing, skip) = dlg.Update(s.progress * 100, state_str[s.state])
			wx.MilliSleep(250)
 
		if keepGoing == False:
			ses.remove_torrent(h)
			dlg.Destroy()

#---------------------------------------------------------------------------
