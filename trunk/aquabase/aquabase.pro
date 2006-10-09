
TEMPLATE = lib
DESTDIR = lib
TARGET = odabaclient
INCLUDEPATH += inc \
               ../odaba/src/opa/h \
               ../odaba/src/sos/h \
               ../odaba/src/opi/h


LIBS *= -L../odaba/lib/
LIBS += -lodaba_sos -lodaba_opa -lodaba_opi -lodaba_greta -lodaba_oxml -lodaba_oql -lodaba_ops -lodaba_functional_model


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


HEADERS += inc/odabaclient.h
SOURCES += src/odabaclient.cpp


