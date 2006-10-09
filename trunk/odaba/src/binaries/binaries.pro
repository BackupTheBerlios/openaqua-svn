TEMPLATE=subdirs
SUBDIRS +=  BackupDB  \
            CheckDB \
            CopyDB \
            CopyResDB \
            DBDictStatistics \
            GenCTXInterface \
            Licence \
            ODL \
            OSI \
            OShell \
            PackDB \
            RBOpen \
            ResetSchemaVersion \
            ResetSysVersion \
            RestoreDB \
            Server \
            ServerD \
            SetSysVersion \
            SetupDB \
            SystemVersion \
            TestAlignment \
            TestCS \
            TestVarious \
            DBError \
            DBSystemInfo \
            DBPerformance \
            DBStatistics

            
win32:         SUBDIRS +=   ODABAServer
