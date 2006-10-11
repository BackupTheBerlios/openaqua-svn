#########################################
message ("Include demos.pri")


#########################################
#General Settings
#include(../odaba.pri)
DEPENDPATH *= . 
CONFIG += thread


  
#########################################
 demos {
   message ("Make a Bin")
   unix:   TEMPLATE = app
   macx:   TEMPLATE = app
   win32:   TEMPLATE = console
   
   INCLUDEPATH = .
   INCLUDEPATH *= ../../../aquabase/src
   
   LIBS *= -L../../../aquabase/lib
   LIBS *= -L../../../odaba/lib/
   LIBS += -laquabase
   LIBS += -lodaba_server  -lodaba_greta  -lodaba_sos  -lodaba_zlib
   LIBS += -ldl 
    
      
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

