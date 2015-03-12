# Modifications #

OK, this page is to discuss additions/changes to primarily Section 5 of the Design Spec.

Will add significantly in a few hours to this page -> by tonight, we can delegate redesign of class diagrams for the resubmission tomorrow evening.

# UI System #
Currently, the UI system breakdown consists only of the GUI class:

http://nmt-cs326-g5.googlecode.com/files/class_gui_v2.JPG

The GUI class will encompass objects like the main GUI, preference dialogues, and the web browser.
This GUI class will have generic methods like invoke() and destroy().

The GUI class (after reviewing the code) will subclass the wxFrame class.
We can expand the GUI class by adding wxWidget objects as attributes:
  * Menus (class which subclasses wxMenu)
  * Panel (class which subclasses wxPanel)
  * Dialogs (general interface which subclasses wxWindow)
  * Notebook (class which subclasses wxNotebook)
  * WebBrowser (another in-house class which implements the web browser)

The GUI class will retain most of its existing methods.

The Menu, Panel, Dialog, WebBrowser and Notebook classes are interface wrapper classes which inherit from their corresponding wxWidget classes (we should make a textual note of some of the methods they will inherit from these relationships so Dr. Shin can see that all the GUI functionality is there) and have whatever attributes they need as well as at least two methods, invoke() and destroy().


---


Version 1 of the GUI Class Diagram: Gimme some feedback!

![http://nmt-cs326-g5.googlecode.com/files/GUIClassDiagramV1.jpg](http://nmt-cs326-g5.googlecode.com/files/GUIClassDiagramV1.jpg)

Alternate Version:

![http://nmt-cs326-g5.googlecode.com/files/Class%20Diagram%20-%20UI%20v4.jpeg](http://nmt-cs326-g5.googlecode.com/files/Class%20Diagram%20-%20UI%20v4.jpeg)

Transfer Manager:

![http://nmt-cs326-g5.googlecode.com/files/Class%20Diagram%20-%20Transfer%20Manager.jpeg](http://nmt-cs326-g5.googlecode.com/files/Class%20Diagram%20-%20Transfer%20Manager.jpeg)

Pictures:

GUI additions:

http://nmt-cs326-g5.googlecode.com/files/DSC00780.JPG

TM additions:

http://nmt-cs326-g5.googlecode.com/files/DSC00781.JPG