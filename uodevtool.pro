# -------------------------------------------------
# Project created by QtCreator 2009-11-17T21:05:54
# -------------------------------------------------
TARGET = uodevtool
TEMPLATE = app
SOURCES += main.cpp \
	MainWindow.cpp \
	ArmorCalc.cpp \
	Table.cpp \
	Row.cpp \
	Column.cpp
HEADERS += MainWindow.h \
	ArmorCalc.h \
	Table.h \
	Row.h \
	Column.h
RESOURCES += icons.qrc
win32:RC_FILE = winicon.rc
macx:ICON = icons/uodt.icns
