####################
#

QT              +=      xml sql network

CONFIG          +=     debug warn_on
CONFIG          +=      precompile_header




#########################################
#config coa libs
coalibs {
INCLUDEPATH     +=   ../framework/inc
INCLUDEPATH     +=   ../../framework/inc
LIBS            *=      -L../lib
TEMPLATE        =       lib
CONFIG          *=      create_prl
DESTDIR         =       ../lib
# VERSION         = 0.0.0
VERSION =
message         ("Build as Library")


#########################################
#config coa plugins
} else: coaplugins {
INCLUDEPATH     +=   ../framework/inc
INCLUDEPATH     +=   ../../framework/inc
LIBS            *= -L../../lib
TEMPLATE        =       lib
CONFIG          *=      link_prl
VERSION         = 1.0.0
CONFIG          += designer plugin
message         ("Build as Plugin")


#########################################
#config coa apps
} else: coaapps {
INCLUDEPATH     +=   ../framework/inc
INCLUDEPATH     +=   ../../framework/inc
LIBS            *= -L../../lib
TEMPLATE        =       app
CONFIG          *=      link_prl
message         ("Build as Application")


#########################################
#catch errors
} else {
        error   ("Target Type not declared")
}


CONFIG(taocorba) {
   INCLUDEPATH += .corba $$(ACE_ROOT) $$(TAO_ROOT) $$(TAO_ROOT)/orbsvcs
   LIBS += -L $$(ACE_ROOT)/lib -lTAO_PortableServer -lTAO_AnyTypeCode -lTAO -lACE -lTAO_CosNaming -lTAO_Utils -lTAO_IORTable
   DEFINES += ACE_HAS_AIO_CALLS ACE_HAS_EXCEPTIONS __ACE_INLINE__


#a better way would be...
#tao.output  = ${QMAKE_FILE_BASE}C.cpp
#tao.commands = tao_idl -o .corba ${QMAKE_FILE_NAME}
#tao.depend_command = g++ -E -M ${QMAKE_FILE_NAME} | sed "s,^.*: ,,"
#tao.input = IDL
#QMAKE_EXTRA_COMPILERS += tao

}


CONFIG(debug) {
   DEFINES         += DEBUG
   MOC_DIR         =       .moc
   UI_DIR          =       .ui
   OBJECTS_DIR     =       .obj
} else {
   DEFINES         += NDEBUG
   MOC_DIR         =       .rmoc
   UI_DIR          =       .rui
   OBJECTS_DIR     =       .robj
}



#contains(TEMPLATE,lib) {
#   CONFIG(debug, debug|release) {
#      unix:TARGET = $$member(TARGET, 0)_debug
#      else:TARGET = $$member(TARGET, 0)d
#   }
#}
