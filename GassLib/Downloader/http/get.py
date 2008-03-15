from urlparse import urlparse
from urllib import urlopen
from string import split

def download(url):
	instream = urlopen(url)
	filename = split(urlparse(url)[2], '/')[-1]
	outstream = open(filename, "wb")
	outstream.write(instream.read())
	outstream.close()
	return filename


