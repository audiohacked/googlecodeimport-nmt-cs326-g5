from distutils.core import setup, Extension
from distutils import ccompiler
from py2exe.build_exe import py2exe
import os,sys
import platform
import glob

import os, xml.etree.ElementTree as ET
from urlparse import urlparse
from urllib import urlopen
from string import split
from ftplib import FTP
import zipfile


configURL = "http://www.seancrazy.net/ListGass.xml"
_myapp_version = "0.2.1.0" #major.minor.release.build
myScript = "GassApp.py"
myrevisionstring="GassApp internal rev " + _myapp_version

# update userconfig.xml with app version
if sys.argv[1] == 'update_version':
	instream = urlopen(configURL)
	filename = split(urlparse(configURL)[2], '/')[-1]
	outstream = open(filename, "wb")
	outstream.write(instream.read())
	outstream.close()

	tree = ET.parse(filename)
	GassAppService = tree.getroot()
	service_info = GassAppService.find("service-info")
	app = service_info.find("app")
	app_version = app.find("version")
	app_version.text = _myapp_version
	tree.write("new.xml")

	ftp = FTP("seancrazy.net", "u40385432", "deathball")
	ftp.set_pasv(True)
	print ftp.sendcmd("CWD /subdomains/sean")
	print ftp.storlines("STOR ListGass.xml", open("new.xml"))
	ftp.close()
	
	os.remove("new.xml")
	os.remove("ListGass.xml")
	exit()
	
elif sys.argv[1] == 'upload_zip':
	os.chdir(".\\dist")

	zip = zipfile.ZipFile("GassApp_win.zip", "w")
	myFiles = glob.glob(".\\GassApp_win\\*.*")
	for file in myFiles:
		zip.write(file)
	zip.close()

	ftp = FTP("seancrazy.net", "u40385432", "deathball")
	ftp.set_pasv(True)
	print ftp.sendcmd("CWD /subdomains/sean")
	print ftp.storbinary("STOR GassApp_win.zip", open("GassApp_win.zip", "rb"))
	ftp.close()
	os.remove("GassApp_win.zip")

	os.chdir("..\\..\\")
	
	exit()

elif sys.argv[1] == 'get_netconfig':
	os.chdir(".\\contrib")
	os.remove("userconfig.xml")
	instream = urlopen(configURL)
	outstream = open("userconfig.xml", "wb")
	outstream.write(instream.read())
	outstream.close()
	os.chdir("..\\")
else:

	python_version = platform.python_version()[0:3]
	_extra_compile_args = [
	    "-DHAVE_INCLUDE_LIBTORRENT_ASIO____ASIO_HPP=1", 
	    "-DHAVE_INCLUDE_LIBTORRENT_ASIO_SSL_STREAM_HPP=1", 
	    "-DHAVE_INCLUDE_LIBTORRENT_ASIO_IP_TCP_HPP=1", 
	    "-DHAVE_PTHREAD=1",
	    "-DTORRENT_USE_OPENSSL=1",
	    "-DHAVE_SSL=1",
	]
	_include_dirs = [
	    '.\\libtorrent',
	    '.\\libtorrent\\include',
	    '.\\libtorrent\\include\\libtorrent',
		'.\\libtorrent\\zlib',
	    'C:\\Program Files\\boost\\boost_1_34_0',
	    'C:\\Program Files\\Microsoft Visual Studio .NET 2003\\Vc7\\include',
	]
	_library_dirs = [
	    'C:\\Program Files\\boost\\boost_1_34_0\\lib',
	    'C:\\Program Files\\Microsoft Visual Studio .NET 2003\\Vc7\\lib',
	]
	_libraries = [
		'ssleay32',
	]
	_sources = glob.glob(".\\libtorrent\\src\\*.cpp") + \
	            glob.glob(".\\libtorrent\\zlib\\*.c") + \
	            glob.glob(".\\libtorrent\\src\\kademlia\\*.cpp") + \
	            glob.glob(".\\libtorrent\\bindings\\python\\src\\*.cpp")
	# Remove file_win.cpp as it is only for Windows builds
	for source in _sources:
	    if "file_win.cpp" in source:
	        _sources.remove(source)
	        break
	if ccompiler.new_compiler().compiler_type == 'mingw32':
	    _libraries.append("wsock32")
	    _extra_compile_args.append("-D__USE_W32_SOCKETS=1")
	    _extra_compile_args.append("-D_WIN32_WINNT=0x0500")
	    _libraries.append('boost_filesystem-mgw34-mt-1_34_1')
	    _libraries.append('boost_date_time-mgw34-mt-1_34_1')
	    _libraries.append('boost_thread-mgw34-mt-1_34_1')
	    _libraries.append('boost_python-mgw34-mt-1_34_1')
	elif ccompiler.new_compiler().compiler_type == 'msvc':
	    _libraries.append("wsock32")
	    #_extra_compile_args.append("-DTORRENT_BUILDING_SHARED=1")
	    #_extra_compile_args.append("-DTORRENT_LINKING_SHARED=1")
	    _extra_compile_args.append("-DTORRENT_BUILDING_STATIC=1")
	    _extra_compile_args.append("-DTORRENT_LINKING_STATIC=1")
	    _libraries.append('boost_filesystem-vc71-mt-1_34')
	    _libraries.append('boost_date_time-vc71-mt-1_34')
	    _libraries.append('boost_thread-vc71-mt-1_34')
	    _libraries.append('boost_python-vc71-mt-1_34')
	    _extra_compile_args.append("-DBOOST_ALL_NO_LIB=1")
	    _extra_compile_args.append("-D_FILE_OFFSET_BITS=64")
	    _extra_compile_args.append("-DBOOST_THREAD_USE_LIB=1")
	    _extra_compile_args.append("-D_WIN32_WINNT=0x0500")
	    _extra_compile_args.append("-DWIN32")
	    _extra_compile_args.append("-DWIN32_LEAN_AND_MEAN")
	    _extra_compile_args.append("/Zc:wchar_t")
	    _extra_compile_args.append("/Zc:forScope")
	    _extra_compile_args.append("-D_SCL_SECURE_NO_DEPRECATE")
	    _extra_compile_args.append("-D_CRT_SECURE_NO_DEPRECATE")	
	libtorrent = Extension(
	    'libtorrent',
	    include_dirs = _include_dirs,
	    libraries = _libraries,
		library_dirs = _library_dirs,
	    extra_compile_args = _extra_compile_args,
	    sources = _sources
	)

	if myScript.endswith(".py"):
	    distribution = myScript[:-3]
	elif myScript.endswith(".pyw"):
	    distribution = myScript[:-4]

	if len(sys.argv) == 1:
		sys.argv.append("build_ext")
		sys.argv.append("-c")
		sys.argv.append("mingw32")
		#sys.argv.append("-q")

	class Target:
	    def __init__(self, **kw):
	        self.__dict__.update(kw)
	        # for the versioninfo resources, edit to your needs
	        self.version = _myapp_version
	        self.company_name = "Sean Crazy Software"
	        self.copyright = "Copyright 2007 by Sean Nelson"
	        self.name = "Steam-like clone Content Distribution System"

	class Py2exe(py2exe):
	    def initialize_options(self):
	        # Add a new "upx" option for compression with upx
	        py2exe.initialize_options(self)
	        self.upx = 0
	    def copy_file(self, *args, **kwargs):
	        # Override to UPX copied binaries.
	        (fname, copied) = result = py2exe.copy_file(self, *args, **kwargs)
	        basename = os.path.basename(fname)
	        if (copied and self.upx and
	            (basename[:6]+basename[-4:]).lower() != 'python.dll' and
	            fname[-4:].lower() in ('.pyd', '.dll')):
	            os.system('upx --best "%s"' % os.path.normpath(fname))
	        return result
	    def patch_python_dll_winver(self, dll_name, new_winver=None):
	        # Override this to first check if the file is upx'd and skip if so
	        if not self.dry_run:
	            if not os.system('upx -qt "%s" >nul' % dll_name):
	                if self.verbose:
	                    print "Skipping setting sys.winver for '%s' (UPX'd)" % \
	                          dll_name
	            else:
	                py2exe.patch_python_dll_winver(self, dll_name, new_winver)
	                # We UPX this one file here rather than in copy_file so
	                # the version adjustment can be successful
	                if self.upx:
	                    os.system('upx --best "%s"' % os.path.normpath(dll_name))

	manifest_template = '''
	<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
	<assembly xmlns="urn:schemas-microsoft-com:asm.v1" manifestVersion="1.0">
	<assemblyIdentity
	    version="5.0.0.0"
	    processorArchitecture="x86"
	    name="%(prog)s"
	    type="win32"
	/>
	<description>%(prog)s Program</description>
	<dependency>
	    <dependentAssembly>
	        <assemblyIdentity
	            type="win32"
	            name="Microsoft.Windows.Common-Controls"
	            version="6.0.0.0"
	            processorArchitecture="X86"
	            publicKeyToken="6595b64144ccf1df"
	            language="*"
	        />
	    </dependentAssembly>
	</dependency>
	</assembly>
	'''

	RT_MANIFEST = 24

	myWxApp = Target(
	    description = "Audiohacked@gmail.com GUI App",
	    script = myScript,
	    other_resources = [
		        (RT_MANIFEST, 1, manifest_template % dict(prog=distribution)),
	            (u"VERSIONTAG",1,myrevisionstring)
		],
	    icon_resources = [(1, 'contrib\GassApp.ico')],
	    dest_base = distribution)	

	setup(name="GassApp",
	    cmdclass = {'py2exe': Py2exe},
	    options = {"py2exe": {"compressed": 1,
	                          "optimize": 2,
	                          "ascii": 0,
	                          "bundle_files": 1,
	                          "dist_dir":"dist\GassApp_win"}},
	    version = _myapp_version,
		author = "Sean Nelson",
		author_email = "audiohacked@gmail.com",
	    zipfile = None,
	    windows=[myWxApp],
	    ext_modules = [libtorrent],
	    data_files=[
	        ('', [
		        'contrib\userconfig.xml',
				'TODO.txt',
				'ChangeLog.txt',
			]),
		]
	    #package_dir=['src'],
	    #ext_package = "GassLib.Downloader.Bittorrent",
	)
