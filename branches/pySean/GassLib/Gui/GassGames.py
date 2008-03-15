import sys
import wx
import wx.lib.mixins.listctrl  as  listmix

from GassLib.Downloader import GassDownloader

import urllib
if wx.Platform == '__WXMSW__':
	import xml.etree.ElementTree as ET
elif wx.Platform == '__WXMAC__':
	import elementtree.ElementTree as ET
gamesList = {}
#---------------------------------------------------------------------------

class TestListCtrl(wx.ListCtrl, listmix.ListCtrlAutoWidthMixin):
	def __init__(self, parent, ID, pos=wx.DefaultPosition,
				 size=wx.DefaultSize, style=0):
		wx.ListCtrl.__init__(self, parent, ID, pos, size, style)
		listmix.ListCtrlAutoWidthMixin.__init__(self)

class GamesList(wx.Panel, listmix.ColumnSorterMixin):
	def __init__(self, parent, url):
		wx.Panel.__init__(self, parent, -1, style=wx.WANTS_CHARS)

		tID = wx.NewId()
		
		sizer = wx.BoxSizer(wx.VERTICAL)
		
		if wx.Platform == "__WXMAC__":
			self.OnUseNative()
			
		self.list = TestListCtrl(self, tID,
								 style=wx.LC_REPORT 
								 #| wx.BORDER_SUNKEN
								 | wx.BORDER_NONE
								 #| wx.LC_EDIT_LABELS
								 | wx.LC_SORT_ASCENDING
								 #| wx.LC_NO_HEADER
								 #| wx.LC_VRULES
								 #| wx.LC_HRULES
								 | wx.LC_SINGLE_SEL
								 )
		
		sizer.Add(self.list, 1, wx.EXPAND)

		self.PopulateList(url)

		# Now that the list exists we can init the other base class,
		# see wx/lib/mixins/listctrl.py
		#self.itemDataMap = gamesList
		#listmix.ColumnSorterMixin.__init__(self, 5)
		#self.SortListItems(0, True)

#		btnSizerTwo = wx.BoxSizer(wx.HORIZONTAL)
#		btnSizerThree = wx.BoxSizer(wx.HORIZONTAL)
#		btn11 = wx.Button(self, -1, "Add non-Gass Game...", style=wx.BU_EXACTFIT)
#		btnSizerTwo.Add(btn11, 0, wx.EXPAND|wx.ALL, 2)
#		btnSizerTwo.Add(btn12, 0, wx.EXPAND|wx.ALL, 2)
#		btn21 = wx.Button(self, -1, "News", style=wx.BU_EXACTFIT)
#		btnSizerThree.Add(btn21, 0, wx.EXPAND|wx.ALL, 2)
#		btn22 = wx.Button(self, -1, "Friends", style=wx.BU_EXACTFIT)
#		btnSizerThree.Add(btn22, 0, wx.EXPAND|wx.ALL, 2)
#		btn23 = wx.Button(self, -1, "Servers", style=wx.BU_EXACTFIT)
#		btnSizerThree.Add(btn23, 0, wx.EXPAND|wx.ALL, 2)
#		btn24 = wx.Button(self, -1, "Settings", style=wx.BU_EXACTFIT)
#		btnSizerThree.Add(btn24, 0, wx.EXPAND|wx.ALL, 2)
#		btn25 = wx.Button(self, -1, "Support", style=wx.BU_EXACTFIT)
#		btnSizerThree.Add(btn25, 0, wx.EXPAND|wx.ALL, 2)
#		sizer.Add(btnSizerTwo, 2, wx.EXPAND)
#		sizer.Add(btnSizerThree, 3, wx.EXPAND)
		
		self.SetSizer(sizer)
		self.SetAutoLayout(True)

		self.Bind(wx.EVT_LIST_ITEM_SELECTED, self.OnItemSelected, self.list)
		self.Bind(wx.EVT_LIST_ITEM_DESELECTED, self.OnItemDeselected, self.list)
		self.Bind(wx.EVT_LIST_ITEM_ACTIVATED, self.OnItemActivated, self.list)
		self.Bind(wx.EVT_LIST_DELETE_ITEM, self.OnItemDelete, self.list)
		self.Bind(wx.EVT_LIST_COL_CLICK, self.OnColClick, self.list)
		self.Bind(wx.EVT_LIST_COL_RIGHT_CLICK, self.OnColRightClick, self.list)
		self.Bind(wx.EVT_LIST_COL_BEGIN_DRAG, self.OnColBeginDrag, self.list)
		self.Bind(wx.EVT_LIST_COL_DRAGGING, self.OnColDragging, self.list)
		self.Bind(wx.EVT_LIST_COL_END_DRAG, self.OnColEndDrag, self.list)
		#self.Bind(wx.EVT_LIST_BEGIN_LABEL_EDIT, self.OnBeginEdit, self.list)

		self.list.Bind(wx.EVT_LEFT_DCLICK, self.OnDoubleClick)
		self.list.Bind(wx.EVT_RIGHT_DOWN, self.OnRightDown)

		# for wxMSW
		if wx.Platform == '__WXMSW__':
			self.list.Bind(wx.EVT_COMMAND_RIGHT_CLICK, self.OnRightClick)

		# for wxGTK
		if wx.Platform == '__WXGTK__':
			self.list.Bind(wx.EVT_RIGHT_UP, self.OnRightClick)


	def OnUseNative(self):
		wx.SystemOptions.SetOptionInt("mac.listctrl.always_use_generic", True)

	def PopulateList(self, url):
		# for normal, simple columns, you can add them like this:
		self.list.InsertColumn(0, "Games")
		self.list.InsertColumn(1, "Status")
		self.list.InsertColumn(2, "Update")
		self.list.InsertColumn(3, "Metascore")
		self.list.InsertColumn(4, "Developer")
		self.list.SetColumnWidth(0, 100)
		self.list.SetColumnWidth(1, 200)
		self.list.SetColumnWidth(2, 100)
		self.list.SetColumnWidth(3, 100)
		self.list.SetColumnWidth(4, 100)

		dataList = urllib.urlopen(url)
		gamesXml = ET.parse(dataList).getroot().find("service-media").find("games")
		domGamesPackage = gamesXml.findall("package")		

		_g2 = 0
		for nodeGamesPackage in domGamesPackage:
			packageGameName = nodeGamesPackage.get("name")
			packageGameHomepage = nodeGamesPackage.find("homepage").text
			packageGamePreview = nodeGamesPackage.find("preview-url").text
			packageGameDownload = nodeGamesPackage.find("package-url").text
			packageGameScore = nodeGamesPackage.find("score").text
			self.list.InsertStringItem(_g2, packageGameName)
			self.list.SetStringItem(_g2, 1, packageGameDownload)
			self.list.SetStringItem(_g2, 2, packageGamePreview)
			self.list.SetStringItem(_g2, 3, packageGameScore)
			self.list.SetStringItem(_g2, 4, packageGameHomepage)
			gamesList[_g2] = (packageGameName, packageGameHomepage, 
				packageGamePreview, packageGameScore, packageGameDownload)
			_g2 += 1
		dataList.close()
		# show how to select an item
		#self.list.SetItemState(1, wx.LIST_STATE_SELECTED, wx.LIST_STATE_SELECTED)

		# show how to change the colour of a couple items
		#item = self.list.GetItem(1)
		#item.SetTextColour(wx.BLUE)
		#self.list.SetItem(item)
		#item = self.list.GetItem(4)
		#item.SetTextColour(wx.RED)
		#self.list.SetItem(item)

		self.currentItem = 0


	# Used by the ColumnSorterMixin, see wx/lib/mixins/listctrl.py
	def GetListCtrl(self):
		return self.list

	# Used by the ColumnSorterMixin, see wx/lib/mixins/listctrl.py
	#def GetSortImages(self):
	#    return (self.sm_dn, self.sm_up)

	def OnRightDown(self, event):
		x = event.GetX()
		y = event.GetY()
		item, flags = self.list.HitTest((x, y))

		if item != wx.NOT_FOUND and flags & wx.LIST_HITTEST_ONITEM:
			self.list.Select(item)

		event.Skip()


	def getColumnText(self, index, col):
		item = self.list.GetItem(index, col)
		return item.GetText()


	def OnItemSelected(self, event):
		self.currentItem = event.m_itemIndex
		self.list.SetItemState(self.currentItem, wx.LIST_STATE_SELECTED, \
		   wx.LIST_STATE_SELECTED)
		event.Skip()


	def OnItemDeselected(self, evt):
		item = evt.GetItem()
		# Show how to reselect something we don't want deselected
		#if evt.m_itemIndex == 11:
		#    wx.CallAfter(self.list.SetItemState, 11, \
		#    wx.LIST_STATE_SELECTED, wx.LIST_STATE_SELECTED)


	def OnItemActivated(self, event):
		self.currentItem = event.m_itemIndex

	def OnBeginEdit(self, event):
		event.Skip()

	def OnItemDelete(self, event):
		event.Skip()
		
	def OnColClick(self, event):
		event.Skip()

	def OnColRightClick(self, event):
		item = self.list.GetColumn(event.GetColumn())

	def OnColBeginDrag(self, event):
		## Show how to not allow a column to be resized
		#if event.GetColumn() == 0:
		#    event.Veto()
		event.Skip()


	def OnColDragging(self, event):
		event.Skip()

	def OnColEndDrag(self, event):
		event.Skip()

	def OnDoubleClick(self, event):
		item = self.list.GetItem(self.currentItem, 1)
		GassDownloader.Downloader(self, item.GetText())
		event.Skip()

	def OnRightClick(self, event):
		# only do this part the first time so the events are only bound once
		if not hasattr(self, "popupID1"):
			self.popupID1 = wx.NewId()
			self.popupID2 = wx.NewId()
			self.popupID3 = wx.NewId()

			self.Bind(wx.EVT_MENU, self.RefreshList, id=self.popupID1)
			self.Bind(wx.EVT_MENU, self.GoToHomepage, id=self.popupID2)
			self.Bind(wx.EVT_MENU, self.DownloadItem, id=self.popupID3)

		# make a menu
		menu = wx.Menu()
		# add some items
		menu.Append(self.popupID1, "Refresh List")
		menu.Append(self.popupID2, "Goto Producer's Homepage")
		menu.Append(self.popupID3, "Download...")

		# Popup the menu.  If an item is selected then its handler
		# will be called before PopupMenu returns.
		self.PopupMenu(menu)
		menu.Destroy()


	def RefreshList(self, event):
		self.list.ClearAll()
		wx.CallAfter(self.PopulateList)

	def GoToHomepage(self, event):
		item = self.list.GetItem(self.currentItem, 4)
		#GassDownloader.Downloader(self, item.GetText())
		print item.GetText()

	def DownloadItem(self, event):
		item = self.list.GetItem(self.currentItem, 1)
		GassDownloader.Downloader(self, item.GetText())
		print item.m_text, item.m_itemId, \
		   self.list.GetItemData(self.currentItem)

#---------------------------------------------------------------------------
