
TARGET = odaba_prce
CONFIG += odabalibs
include (../../projects.pri)

QMAKE_CXXFLAGS += -xc



# Input
HEADERS += h/config.h \
           h/pcre.h \
           h/pcre_internal.h \
           h/pcre_scanner.h \
           h/pcrecpp.h \
           h/pcreposix.h \
           h/ucp.h \
           h/ucpinternal.h 
           
           
SOURCES += h/ucptable.c \
           qlib/pcre_chartables.cpp \
           qlib/pcre_compile.cpp \
           qlib/pcre_config.cpp \
           qlib/pcre_dfa_exec.cpp \
           qlib/pcre_exec.cpp \
           qlib/pcre_fullinfo.cpp \
           qlib/pcre_get.cpp \
           qlib/pcre_globals.cpp \
           qlib/pcre_info.cpp \
           qlib/pcre_maketables.cpp \
           qlib/pcre_ord2utf8.cpp \
           qlib/pcre_refcount.cpp \
           qlib/pcre_study.cpp \
           qlib/pcre_tables.cpp \
           qlib/pcre_try_flipped.cpp \
           qlib/pcre_ucp_searchfuncs.cpp \
           qlib/pcre_valid_utf8.cpp \
           qlib/pcre_version.cpp \
           qlib/pcre_xclass.cpp
