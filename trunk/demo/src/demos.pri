#########################################
message ("Include demos.pri")


#########################################
#General Settings
#include(../odaba.pri)
DEPENDPATH *= . 
CONFIG += thread


#########################################
#config libs
odabalibs {
   message ("Make a Odaba Lib")
   TEMPLATE = lib
   DESTDIR = ../../lib/
   INCLUDEPATH *= .
   INCLUDEPATH *=  h   
   INCLUDEPATH *= ../sos/h/
   INCLUDEPATH *= ../greta/h/
   INCLUDEPATH *= ../opi/h/
   INCLUDEPATH *= ..
   INCLUDEPATH *= ../opa/h
   INCLUDEPATH *= ../oxml/h
   INCLUDEPATH *= ../ops/h/
   INCLUDEPATH *= ../functionalmodel/h/
   INCLUDEPATH *= ../oql/h/

   
   

   
#########################################
} else: demos {
   message ("Make a Bin")
   unix:   TEMPLATE = app
   macx:   TEMPLATE = app
   win32:   TEMPLATE = console
   
   INCLUDEPATH = .
   INCLUDEPATH *= ../../../odabaclient/inc
   
   LIBS *= -L../../../odabaclient/lib
   LIBS *= -L../../../odaba/lib/
   LIBS += -lodabaclient
   LIBS += -lodaba_sos -lodaba_opa -lodaba_opi -lodaba_greta -lodaba_oxml -lodaba_oql -lodaba_ops -lodaba_functional_model
   LIBS += -ldl -lrt
    
      
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

