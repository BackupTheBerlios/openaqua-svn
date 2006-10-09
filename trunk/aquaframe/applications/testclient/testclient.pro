PRECOMPILED_HEADER = allcoaheaders.h
LIBS += -lopenaquaframework


######################################
# Corba parts
system( "tao_idl -Ge 1 -Wb,pre_include=ace/pre.h -Wb,post_include=ace/post.h -I/home/anbehren/ACE_wrappers/TAO -Sa -St -o .corba contact.idl ")

SOURCES +=   .corba/contactC.cpp
HEADERS +=   .corba/contactC.h
CONFIG  += taocorba


########################################
# qt partss
HEADERS +=   workbench.h \
            mainwindow.h \
            corbaclient.h \
            coacorbaorb.h
            
            
SOURCES +=   main.cpp \   
            workbench.cpp \
            mainwindow.cpp \
            corbaclient.cpp \
            coacorbaorb.cpp


CONFIG  *= coaapps designer
RESOURCES += actioneditor.qrc

include (../../xml.pri)

