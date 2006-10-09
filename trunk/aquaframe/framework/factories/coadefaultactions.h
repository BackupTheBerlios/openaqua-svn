#ifndef __CoaDefaultActions_h__
#define __CoaDefaultActions_h__


namespace CoaDefaultActions {

   enum RANGE_BEGIN {
      coaActionRangeBegin                     = 0
   };


   enum actionApplication  {
      //actionApplicationQuit                  = 1 + coaActionRangeBegin,
      actionApplicationQuit                  = 10,
      actionApplicationSettings              = 1 + actionApplicationQuit,
      actionApplicationSetShortcuts          = 1 + actionApplicationSettings,
      actionApplicationPrintShortcuts        = 1 + actionApplicationSetShortcuts,
      actionApplicationSwitchNeutralMode     = 1 + actionApplicationPrintShortcuts,
      actionApplicationSwitchSDIMode         = 1 + actionApplicationSwitchNeutralMode,
      actionApplicationSwitchMDIMode         = 1 + actionApplicationSwitchSDIMode,
      actionApplicationAboutApplication      = 1 + actionApplicationSwitchMDIMode
   };


   enum actionEdit  {
      //actionEditSelectAll                    = 1 + actionApplicationAboutApplication,
      actionEditSelectAll                    = 20,
      actionEditCut                          = 1 + actionEditSelectAll,
      actionEditCopy                         = 1 + actionEditCut,
      actionEditPaste                        = 1 + actionEditCopy,
      actionEditUndo                         = 1 + actionEditPaste,
      actionEditRedo                         = 1 + actionEditUndo
   };



   enum actionHelp  {
      //actionHelpHandbook                     = 1 + actionEditRedo,
      actionHelpHandbook                     = 30,
      actionHelpWhatsthis                    = 1 + actionHelpHandbook,
      actionHelpTipOfTheDay                  = 1 + actionHelpWhatsthis
   };


   enum actionFile  {
      //actionFileNew                          = 1 + actionHelpTipOfTheDay,
      actionFileNew                          = 40,
      actionFileOpen                         = 1 + actionFileNew,
      actionFileClose                        = 1 + actionFileOpen,
      actionFileCloseAll                     = 1 + actionFileClose,
      actionFileSave                         = 1 + actionFileCloseAll,
      actionFileSaveAs                       = 1 + actionFileSave,
      actionFileSaveAll                      = 1 + actionFileSaveAs
   };


   enum actionDebug  {
      actionDebugSettings                   = 50,
      actionDebugOnOff                      = 51,
      actionDebugShowTimeOnOff              = 52,

      actionDebugFileDefaultsOff             = 53,
      actionDebugFileDefaultsErr             = 54,
      actionDebugFileDefaultsWrn             = 55,
      actionDebugFileDefaultsInf             = 56,
      actionDebugFileDefaultsDbg             = 57
   };


   enum actionDatabase  {
      actionDatabaseCreate                   = 60,
      actionDatabaseImportFromXml            = 61,
      actionDatabaseExportToXml              = 62,

      actionDatabaseOpenConnection           = 63,
      actionDatabaseCloseConnection          = 64,
            
      actionDatabaseGotoFirst                = 65,
      actionDatabaseGotoPrevius              = 66,
      actionDatabaseGotoNext                 = 67,
      actionDatabaseGotoLast                 = 68,
      
      actionDatabaseLookup                   = 69,
      actionDatabaseSqlBrowser               = 70,
      actionDatabaseSqlEditor                = 71
   };
   

};

#endif //__CoaDefaultActions_h__

