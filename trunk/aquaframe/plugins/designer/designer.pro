#
#
#

warning (Still need a test to check the existens of environment variable QT4)


PRECOMPILED_HEADER      =       CoaAllHeaders

CONFIG                  *=      coaplugins 
INCLUDEPATH             *=      . 
TARGET                  =       openaquadesignerplugins
DESTDIR                 =       ../lib
PROJECTNAME             =       OpenAqua Designer Plugins
LIBS                   +=       -lopenaquaframework
DESTDIR                 =       $(QT4)/plugins/designer

include (../../xml.pri)

###################################################################




###################################################################
# Register and offer Plugins:
HEADERS +=     coasupportwidgets.h
SOURCES +=     coasupportwidgets.cpp


###################################################################
# The Plugins itself
HEADERS +=     coamainwindow_container.h \
               coamainwindow_plugin.h \
               coabaseplugin.h \
               coatexteditplugin.h \
               coalineeditplugin.h \
               coalabelplugin.h \
               coalabelplugin_extrainfo.h \
               coaprogressbarplugin.h \
               coalcdnumberplugin.h \
               coatextbrowserplugin.h \
               coadockwidgetplugin.h \
               coaframeplugin.h \
               coagroupboxplugin.h \
               coastackedwidgetplugin.h \
               coatabwidgetplugin.h \
               coasqlconnectionwidgetplugin.h \
               coatoolbuttonplugin.h \
               coapushbuttonplugin.h \
               coaradiobuttonplugin.h \
               coatoolboxplugin.h \
               coacheckboxplugin.h \
               coatableviewplugin.h \
               
               
SOURCES +=     coamainwindow_container.cpp \
               coamainwindow_plugin.cpp \
               coabaseplugin.cpp \
               coatexteditplugin.cpp \
               coalineeditplugin.cpp \
               coalabelplugin.cpp \
               coalabelplugin_extrainfo.cpp \
               coaprogressbarplugin.cpp \
               coalcdnumberplugin.cpp \
               coatextbrowserplugin.cpp \
               coadockwidgetplugin.cpp \
               coaframeplugin.cpp \
               coagroupboxplugin.cpp \
               coastackedwidgetplugin.cpp \
               coatabwidgetplugin.cpp \
               coatoolbuttonplugin.cpp \
               coapushbuttonplugin.cpp \
               coaradiobuttonplugin.cpp \
               coasqlconnectionwidgetplugin.cpp \
               coatoolboxplugin.cpp \
               coacheckboxplugin.cpp \
               coatableviewplugin.cpp \


RESOURCES +=   images/images.qrc

