TEMPLATE    = lib
CONFIG     += plugin
HEADERS     = PluginStyle.h
SOURCES     = PluginStyle.cpp
TARGET      = DDPSDefault

win32 {
    debug:DESTDIR = debug/styles/
    release:DESTDIR = release/styles/
} else {
    DESTDIR = styles/
}
