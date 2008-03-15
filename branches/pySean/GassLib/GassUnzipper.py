import sys
import zipfile
import os
import os.path
import getopt
from string import split

class GassUnzip:
	def __init__(self, verbose = False, percent = 10):
		self.verbose = verbose
		self.percent = percent
		
	def extract(self, zip, fname, outname):
		zf = zipfile.ZipFile(zip)
		num_files = len(zf.namelist())
		percent = self.percent
		divisions = 100 / percent
		perc = int(num_files / divisions)
		for i, name in enumerate(zf.namelist()):
			if self.verbose == True:
				print "Extracting %s" % name
			elif perc>0 and (i%perc)==0 and i>0:
				complete = int(i/perc) * percent
				print "%s%% complete" % complete
				
			if not name.endswith('/') and (split(name, '/')[-1] == fname):
				outfile = open(outname, 'wb')
				outfile.write(zf.read(name))
				outfile.flush()
				outfile.close()
			