from setuptools import setup, find_packages, Extension
import platform
import glob

configURL = "http://www.seancrazy.net/ListGass.xml"
_myapp_version = "0.2.1.0" #major.minor.release.build
myScript = "GassApp.py"
myrevisionstring="GassApp internal rev " + _myapp_version

python_version = platform.python_version()[0:3]

# The libtorrent extension
_extra_compile_args = [
    "-Wno-missing-braces",
    "-DHAVE_INCLUDE_LIBTORRENT_ASIO____ASIO_HPP=1", 
    "-DHAVE_INCLUDE_LIBTORRENT_ASIO_SSL_STREAM_HPP=1", 
    "-DHAVE_INCLUDE_LIBTORRENT_ASIO_IP_TCP_HPP=1", 
    "-DHAVE_PTHREAD=1",
    "-DTORRENT_USE_OPENSSL=1",
    "-DHAVE_SSL=1"
]

_include_dirs = [
    './libtorrent',
    './libtorrent/include',
    './libtorrent/include/libtorrent',
    '/opt/local/include/python' + python_version,
    '/opt/local/include'
]

_library_dirs = [
    '/opt/local/lib'
]                     
   
_libraries = [
    'boost_filesystem',
    'boost_date_time',
    'boost_thread-mt',
    'boost_python',
    'z',
    'pthread',
    'ssl'
]
			
_sources = glob.glob("./libtorrent/src/*.cpp") + \
                        glob.glob("./libtorrent/src/kademlia/*.cpp") + \
                        glob.glob("./libtorrent/bindings/python/src/*.cpp")

# Remove file_win.cpp as it is only for Windows builds
for source in _sources:
    if "file_win.cpp" in source:
        _sources.remove(source)
        break

libtorrent = Extension(
    'libtorrent',
    include_dirs = _include_dirs,
    libraries = _libraries,
    extra_compile_args = _extra_compile_args,
    sources = _sources
)


setup(
    app=['GassApp.py'],
    data_files=[],
    #ext_package = "GassLib.Downloader.Bittorrent",
    #ext_modules = [libtorrent],
    options=dict(
		py2app=dict(
			argv_emulation=1,
			optimize=2,
			dist_dir='dist/GassApp_mac',
			iconfile='contrib/GassApp.ico',
			plist=dict(
				CFBundleGetInfoString='Audiohacked\'s Steam-clone Program',
				CFBundleIdentifier='net.seancrazy.GassApp',
				CFBundleVersion=_myapp_version,
			),
		)
    ),
    setup_requires=['py2app'],
)
