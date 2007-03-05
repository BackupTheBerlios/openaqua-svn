QT              +=		xml sql network
CONFIG          +=		debug warn_on
CONFIG          +=		precompile_header




#########################################
ormapping_libs {
#INCLUDEPATH     +=   ../framework/inc
#INCLUDEPATH     +=   ../../framework/inc
LIBS            *=      -L../lib
TEMPLATE        =       lib
CONFIG          *=      create_prl
DESTDIR         =       ../lib
VERSION         = 1.0.0
message         ("Build Library")

#########################################
} else: ormapping_test {
#INCLUDEPATH     +=   ../framework/inc
#INCLUDEPATH     +=   ../../framework/inc
LIBS            *= -L../../lib
TEMPLATE        =       app
CONFIG          *=      link_prl
message         ("Build Application")


#########################################
#catch errors
} else {
      error   ("Target Type not declared")
}


##########################################
# General Config
CONFIG(debug) {
	DEFINES			+=		DEBUG
	MOC_DIR			=		.moc
	UI_DIR			=		.ui
	OBJECTS_DIR		=		.obj
}	else {
	DEFINES			+=		NDEBUG
	MOC_DIR			=		.rmoc
	UI_DIR			=		.rui
	OBJECTS_DIR		=		.robj
}

