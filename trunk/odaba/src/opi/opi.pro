TARGET = odaba_opi
CONFIG += odabalibs
include (../projects.pri)
#macx: LIBS +=  -lodaba_greta -lodaba_zlib -lodaba_sos



# Input
HEADERS += h/cApplicationTypes.h \
           h/ccctp.h \
           h/cclient.h \
           h/cctxerr.h \
           h/cDB_Event.h \
           h/chlpmac.h \
           h/coctp.h \
           h/codaba2.h \
           h/compatibility.h \
           h/copadll.h \
           h/cOperationTypes.h \
           h/cPIREPL.h \
           h/csdberr.h \
           h/csysdef.h \
           h/csysstr.h \
           h/cutihdl.h \
           h/cutimac.h \
           h/dbfdefs.h \
           h/OPIFactoryI.hpp \
           h/OPIHelper.hpp \
           h/OPII.hpp \
           h/OPIICE.hpp \
           h/pdefault.h \
           h/podaba2.h \
           h/s_if_DatabaseHandle.hpp \
           h/s_if_DBObjectHandle.hpp \
           h/s_if_DictionaryHandle.hpp \
           h/s_if_FileHandle.hpp \
           h/s_if_PropertyHandle.hpp \
           h/sCheckOptions.hpp \
           h/sCSUtilityHandle.hpp \
           h/sDatabaseHandle.hpp \
           h/sDataSourceHandle.hpp \
           h/sDBErrorHandle.hpp \
           h/sDBObjectHandle.hpp \
           h/sDictionaryHandle.hpp \
           h/sExecAlloc.hpp \
           h/sExecExchange.hpp \
           h/sExecField.hpp \
           h/sExecFieldAlloc.hpp \
           h/sExecStruct.hpp \
           h/sExtentList.hpp \
           h/sExtentListEntry.hpp \
           h/sFileHandle.hpp \
           h/sInstance.hpp \
           h/sKeyClass.hpp \
           h/sODABAClient.hpp \
           h/sODABAServer.hpp \
           h/sOperationHandle.hpp \
           h/sParmList.hpp \
           h/sPI.h \
           h/sPI.hpp \
           h/sPICache.hpp \
           h/sPIStack.hpp \
           h/sPropertyHandle.hpp \
           h/sQueryHandle.hpp \
           h/sUtilityHandle.hpp \
           h/uthglob.h \
           qlib/OPIICEHelper.hpp
SOURCES +=         qlib/CSUtilityHandle.cpp\
        qlib/CheckOptions.cpp\
        qlib/DBErrorHandle.cpp\
        qlib/DBObjectHandle.cpp\
        qlib/DataSourceHandle.cpp\
        qlib/DatabaseHandle.cpp\
        qlib/DictionaryHandle.cpp\
        qlib/ExecAlloc.cpp\
        qlib/ExecExchange.cpp\
        qlib/ExecField.cpp\
        qlib/ExecFieldAlloc.cpp\
        qlib/ExecStruct.cpp\
        qlib/ExtentListEntry.cpp\
        qlib/FileHandle.cpp\
        qlib/Instance.cpp\
        qlib/KeyClass.cpp\
        qlib/ODABAClient.cpp\
        qlib/ODABAServer.cpp\
        qlib/OperationHandle.cpp\
        qlib/PICache.cpp\
        qlib/PIStack.cpp\
        qlib/ParmList.cpp\
        qlib/PropertyHandle.cpp\
        qlib/UtilityHandle.cpp\
