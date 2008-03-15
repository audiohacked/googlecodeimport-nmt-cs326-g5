RD /S /Q dist
RD /S /Q build\bdist.win32
RD /S /Q build\lib.win32-2.5

python setup.py update_version
python setup.py get_netconfig

python setup.py py2exe

CD dist\GassApp_win

7z.exe -aoa x library.zip -olibrary\
del library.zip
cd library\

upx --best pywintypes25.dll
upx --best *.pyd
cd GassLib\Downloader\Bittorrent
upx --best libtorrent.pyd
cd ..\..\..

7z.exe a -tzip -mx9 ..\library.zip -r
cd ..
RD /s /q library

upx --best *.dll
upx --best *.exe
CD ..\..\

python setup.py make_zip
REM python setup.py upload_zip

PAUSE