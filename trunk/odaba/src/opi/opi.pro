

isEmpty(PATH_PREFIX) {
   message ("Configure OPI")
   PATH_PREFIX=.
   TARGET = odaba_opi
   CONFIG += odabalibs
   include (../projects.pri)
   #macx: LIBS +=  -lodaba_greta -lodaba_zlib -lodaba_sos
}

# Input
HEADERS += $$PATH_PREFIX/h/cApplicationTypes.h \
           $$PATH_PREFIX/h/ccctp.h \
           $$PATH_PREFIX/h/cclient.h \
           $$PATH_PREFIX/h/cctxerr.h \
           $$PATH_PREFIX/h/cDB_Event.h \
           $$PATH_PREFIX/h/chlpmac.h \
           $$PATH_PREFIX/h/coctp.h \
           $$PATH_PREFIX/h/codaba2.h \
           $$PATH_PREFIX/h/compatibility.h \
           $$PATH_PREFIX/h/copadll.h \
           $$PATH_PREFIX/h/cOperationTypes.h \
           $$PATH_PREFIX/h/cPIREPL.h \
           $$PATH_PREFIX/h/csdberr.h \
           $$PATH_PREFIX/h/csysdef.h \
           $$PATH_PREFIX/h/csysstr.h \
           $$PATH_PREFIX/h/cutihdl.h \
           $$PATH_PREFIX/h/cutimac.h \
           $$PATH_PREFIX/h/dbfdefs.h \
           $$PATH_PREFIX/h/OPIFactoryI.hpp \
           $$PATH_PREFIX/h/OPIHelper.hpp \
           $$PATH_PREFIX/h/OPII.hpp \
           $$PATH_PREFIX/h/OPIICE.hpp \
           $$PATH_PREFIX/h/pdefault.h \
           $$PATH_PREFIX/h/podaba2.h \
           $$PATH_PREFIX/h/s_if_DatabaseHandle.hpp \
           $$PATH_PREFIX/h/s_if_DBObjectHandle.hpp \
           $$PATH_PREFIX/h/s_if_DictionaryHandle.hpp \
           $$PATH_PREFIX/h/s_if_FileHandle.hpp \
           $$PATH_PREFIX/h/s_if_PropertyHandle.hpp \
           $$PATH_PREFIX/h/sCheckOptions.hpp \
           $$PATH_PREFIX/h/sCSUtilityHandle.hpp \
           $$PATH_PREFIX/h/sDatabaseHandle.hpp \
           $$PATH_PREFIX/h/sDataSourceHandle.hpp \
           $$PATH_PREFIX/h/sDBErrorHandle.hpp \
           $$PATH_PREFIX/h/sDBObjectHandle.hpp \
           $$PATH_PREFIX/h/sDictionaryHandle.hpp \
           $$PATH_PREFIX/h/sExecAlloc.hpp \
           $$PATH_PREFIX/h/sExecExchange.hpp \
           $$PATH_PREFIX/h/sExecField.hpp \
           $$PATH_PREFIX/h/sExecFieldAlloc.hpp \
           $$PATH_PREFIX/h/sExecStruct.hpp \
           $$PATH_PREFIX/h/sExtentList.hpp \
           $$PATH_PREFIX/h/sExtentListEntry.hpp \
           $$PATH_PREFIX/h/sFileHandle.hpp \
           $$PATH_PREFIX/h/sInstance.hpp \
           $$PATH_PREFIX/h/sKeyClass.hpp \
           $$PATH_PREFIX/h/sODABAClient.hpp \
           $$PATH_PREFIX/h/sODABAServer.hpp \
           $$PATH_PREFIX/h/sOperationHandle.hpp \
           $$PATH_PREFIX/h/sParmList.hpp \
           $$PATH_PREFIX/h/sPI.h \
           $$PATH_PREFIX/h/sPI.hpp \
           $$PATH_PREFIX/h/sPICache.hpp \
           $$PATH_PREFIX/h/sPIStack.hpp \
           $$PATH_PREFIX/h/sPropertyHandle.hpp \
           $$PATH_PREFIX/h/sQueryHandle.hpp \
           $$PATH_PREFIX/h/sUtilityHandle.hpp \
           $$PATH_PREFIX/h/uthglob.h \
           $$PATH_PREFIX/qlib/OPIICEHelper.hpp
SOURCES +=         $$PATH_PREFIX/qlib/CSUtilityHandle.cpp\
        $$PATH_PREFIX/qlib/CheckOptions.cpp\
        $$PATH_PREFIX/qlib/DBErrorHandle.cpp\
        $$PATH_PREFIX/qlib/DBObjectHandle.cpp\
        $$PATH_PREFIX/qlib/DataSourceHandle.cpp\
        $$PATH_PREFIX/qlib/DatabaseHandle.cpp\
        $$PATH_PREFIX/qlib/DictionaryHandle.cpp\
        $$PATH_PREFIX/qlib/ExecAlloc.cpp\
        $$PATH_PREFIX/qlib/ExecExchange.cpp\
        $$PATH_PREFIX/qlib/ExecField.cpp\
        $$PATH_PREFIX/qlib/ExecFieldAlloc.cpp\
        $$PATH_PREFIX/qlib/ExecStruct.cpp\
        $$PATH_PREFIX/qlib/ExtentListEntry.cpp\
        $$PATH_PREFIX/qlib/FileHandle.cpp\
        $$PATH_PREFIX/qlib/Instance.cpp\
        $$PATH_PREFIX/qlib/KeyClass.cpp\
        $$PATH_PREFIX/qlib/ODABAClient.cpp\
        $$PATH_PREFIX/qlib/ODABAServer.cpp\
        $$PATH_PREFIX/qlib/OperationHandle.cpp\
        $$PATH_PREFIX/qlib/PICache.cpp\
        $$PATH_PREFIX/qlib/PIStack.cpp\
        $$PATH_PREFIX/qlib/ParmList.cpp\
        $$PATH_PREFIX/qlib/PropertyHandle.cpp\
        $$PATH_PREFIX/qlib/UtilityHandle.cpp\

        
        