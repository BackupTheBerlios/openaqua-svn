PRECOMPILED_HEADER	=		all_headers.h
CONFIG					*=		ormapping_libs
QT							+=		sql
DESTDIR					=		../lib
TARGET					=		ormapping



#################################################
# public Headers
HEADERS		+=	ormsession.h \
					ormtransaction.h \



SOURCES		+=	ormsession.cpp \
					ormtransaction.cpp \




include (../settings.pri)
