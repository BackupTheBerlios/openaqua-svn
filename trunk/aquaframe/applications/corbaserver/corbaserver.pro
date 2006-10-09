
######################################
# Corba parts
system( "tao_idl -Ge 1 -Wb,pre_include=ace/pre.h -Wb,post_include=ace/post.h -I/home/anbehren/ACE_wrappers/TAO -Sa -St -o .corba contact.idl ")

SOURCES +=   .corba/contactS.cpp \
             .corba/contactC.cpp
HEADERS +=   .corba/contactS.h \
             .corba/contactC.h
             
CONFIG  += taocorba


########################################
# qt partss

HEADERS +=  oasimplecorba.h \
            contact_Factory_i.h
SOURCES +=  main.cpp \
            contact_Factory_i.cpp

#            oasimplecorba.cpp  \

CONFIG  *= coaapps 

include (../../xml.pri)

