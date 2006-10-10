#########################################
message ("Include projects.pri")


#########################################
#General Settings
include(../odaba.pri)
#DEPENDPATH *= . h qlib
CONFIG += thread warn_off


#########################################
#config libs
odabalibs {
   message ("Make a Odaba Lib")
   TEMPLATE = lib
   DESTDIR = ../../lib/
   QT -= gui core
   INCLUDEPATH *= .
   INCLUDEPATH *=  h   
   INCLUDEPATH *= ../sos/h/
   INCLUDEPATH *= ../greta/h/
   INCLUDEPATH *= ../opi/h/
   INCLUDEPATH *= ../opa/h
   INCLUDEPATH *= ../oxml/h
   INCLUDEPATH *= ../ops/h/
   INCLUDEPATH *= ../functionalmodel/h/
   INCLUDEPATH *= ../oql/h/

   macx:LIBS *= -L../../lib/
   macx:LIBS +=  -undefined  define_a_way
   
#########################################
} else:   collectlibs {
   message ("Make a Collect Lib")
   TEMPLATE = lib
   DESTDIR = ../../lib/
   QT -= gui core
   QMAKE_CXXFLAGS *= -fpermissive

   INCLUDEPATH *= ../sos/h/
   INCLUDEPATH *= ../greta/h/
   INCLUDEPATH *= ../opi/h/
   INCLUDEPATH *= ../opa/h
   INCLUDEPATH *= ../oxml/h
   INCLUDEPATH *= ../ops/h/
   INCLUDEPATH *= ../functionalmodel/h/
   INCLUDEPATH *= ../oql/h/
   INCLUDEPATH *= ..
   

   
#########################################
} else: odababins {
   message ("Make a Odaba Bin")
   CONFIG += console
   mac:CONFIG     -= app_bundle incremental
   TEMPLATE = app
   win32:   TEMPLATE = console
   DESTDIR = ../../../bin/
   QT -= gui core

   INCLUDEPATH = .
   INCLUDEPATH *= .
   INCLUDEPATH *=  h   
   INCLUDEPATH *= ../../sos/h/
   INCLUDEPATH *= ../../greta/h/
   INCLUDEPATH *= ../../opi/h/
   INCLUDEPATH *= ..
   INCLUDEPATH *= ../../opa/h
   INCLUDEPATH *= ../../oxml/h
   INCLUDEPATH *= ../../ops/h/
   INCLUDEPATH *= ../../functionalmodel/h/
   INCLUDEPATH *= ../../oql/h/
   INCLUDEPATH *= ../../toollib/h/
   
   LIBS *= -L../../../lib/
   
   LIBS +=  -lodaba_greta \
                -lodaba_zlib \
                -lodaba_sos \
                -lodaba_server \
                -ldl
    
      
#########################################
} else {
   warning("project file wrong configured not supported")
}



#########################################
#a macro to store temp files in hidden directories
CONFIG(debug) {
   DEFINES         +=       DEBUG
   MOC_DIR         =       .moc
   UI_DIR          =       .ui
   OBJECTS_DIR     =       .obj
} else {
   DEFINES         +=       NDEBUG
   MOC_DIR         =       .rmoc
   UI_DIR          =       .rui
   OBJECTS_DIR     =       .robj
}

macx: DEFINES += __unix__ __UNIX__
