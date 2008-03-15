import os
import xml.etree.ElementTree as ET
#=== Start Version Update Code ========
tree = ET.parse("ListGass.xml")
GassAppService = tree.getroot()
service_info = GassAppService.find("service-info")
app = service_info.find("app")
app_version = app.find("version")
app_version.text = _myapp_version
tree.write("out.xml")
os.rename("out.xml", "ListGass.xml")
#=== End Version Update Code ==========

#=== Start Add-New-Game Code ==========
"""
<package name="Test Game" gapid="1">
	<homepage>http://nmtlan/</homepage>
	<preview-url>http://nmtlan/preview</preview-url>
	<package-url>http://nmtlan/test-game-1.0.tar.bz2</package-url>
	<package-score>00</package-score>
	<package-build>http://nmtlan/test-game-1.0.build</package-build>
</package>

"""
tree = ET.parse("ListGass.xml")
GassAppService = tree.getroot()
service_media = GassAppService.find("service-media")
games = service_media.find("games")

package = ET.SubElement(games, "package")
package.set("name", packageGameName)

package_homepage = ET.SubElement(package, "homepage")
package_homepage.text = packageGameHomepage

package_url = ET.SubElement(package, "package-url")
package_url.text = packageGameDownloadUrl

preview_url = ET.SubElement(package, "preview-url")
preview_url.text = packageGamePreviewUrl

package_score = ET.SubElement(package, "score")
package_score.text = packageGameScore

package_build = ET.SubElement(package, "build")
package_build.text = packageGameBuildFile

#=== End Add-New-Game Code ============

#=== Start Add-New-Media Code ==========
tree = ET.parse("ListGass.xml")
GassAppService = tree.getroot()
service_media = GassAppService.find("service-media")
media = service_media.find("media")
package = ET.SubElement(media, "package")
package.set("name", packageMediaName)
package_url = ET.SubElement(package, "package-url")
package_url.text = packageMediaUrl
package_homepage = ET.SubElement(package, "package-homepage")
package_homepage.text = packageMediaHomepage
package_type = ET.SubElement(package, "package-type")
package_type.text = packageMediaType

#=== End Add-New-Media Code ============

#=== Start Login Box ==================
box = wx.StaticBox(self, -1, "Login:")
boxSizer = wx.StaticBoxSizer(box, wx.VERTICAL)
ul = wx.StaticText(self, -1, "Username:")
uf = wx.TextCtrl(self, -1, "input username here!", size=(125, -1))
uf.SetInsertionPoint(0)
pl = wx.StaticText(self, -1, "Password:")
pf = wx.TextCtrl(self, -1, "password", size=(125,-1), style=wx.TE_PASSWORD)
boxSizer.Add(ul, 0, wx.GROW|wx.ALL, 5)
boxSizer.Add(uf, 0, wx.GROW|wx.ALL, 5)
boxSizer.Add(pl, 0, wx.GROW|wx.ALL, 5)
boxSizer.Add(pf, 0, wx.GROW|wx.ALL, 5)
self.border.Add(boxSizer, 1, wx.GROW|wx.ALL, 5)
#=== End Login Box ====================