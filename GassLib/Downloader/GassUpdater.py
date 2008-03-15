import wx
from GassLib.Downloader.http import get
from GassLib.Downloader.urlgrabber.grabber import URLGrabber
from GassLib.Downloader.urlgrabber.progress import BaseMeter
from string import split
import sys, time, math
#---------------------------------------------------------------------------

class GassHttpMeter(BaseMeter):
	def __init__(self, fo=sys.stderr, dialog=None):
		BaseMeter.__init__(self)
		self.fo = fo
		self.dialogBox = dialog
		self.keepGoing = True
		
	def _do_update(self, amount_read, now=None):
		fread = format_number(amount_read)
		frac = self.re.fraction_read()
		percentComplete = frac*100
		print fread, frac, percentComplete
		(self.keepGoing, self.skip) = self.dialogBox.Update(percentComplete, fread)
		if self.keepGoing == False:
			self._do_end(amount_read, now)
	
	def _do_end(self, amount_read, now=None):
		self.dialogBox.Destroy()

class HttpDownloadDlg:
	def __init__(self, parent, url=None):
		fname = split(url, '/')[-1]

		max = 100.00
		dlg = wx.ProgressDialog(fname,
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
		)

		g = URLGrabber(reget='check_timestamp', progress_obj=GassHttpMeter(dialog=dlg))
		local_filename = g.urlgrab(url)#, filename=fname)
		
		#keepGoing = True

		#while (keepGoing == True):
		#	(keepGoing, skip) = dlg.Update(
		#		local_filename.fraction_read(),
		#		local_filename.average_rate()
		#	)
		#	wx.Sleep(1)

		#if keepGoing == False:
		#	dlg.Destroy()

#---------------------------------------------------------------------------
def format_number(number, SI=0, space=' '):
	"""Turn numbers into human-readable metric-like numbers"""
	symbols = ['',  # (none)
			   'k', # kilo
			   'M', # mega
			   'G', # giga
			   'T', # tera
			   'P', # peta
			   'E', # exa
			   'Z', # zetta
			   'Y'] # yotta
	
	if SI: step = 1000.0
	else: step = 1024.0

	thresh = 999
	depth = 0
	max_depth = len(symbols) - 1
	
	# we want numbers between 0 and thresh, but don't exceed the length
	# of our list.  In that event, the formatting will be screwed up,
	# but it'll still show the right number.
	while number > thresh and depth < max_depth:
		depth  = depth + 1
		number = number / step

	if type(number) == type(1) or type(number) == type(1L):
		# it's an int or a long, which means it didn't get divided,
		# which means it's already short enough
		format = '%i%s%s'
	elif number < 9.95:
		# must use 9.95 for proper sizing.  For example, 9.99 will be
		# rounded to 10.0 with the .1f format string (which is too long)
		format = '%.1f%s%s'
	else:
		format = '%.0f%s%s'
		
	return(format % (float(number or 0), space, symbols[depth]))

