/******************************** Enumeration Declaration *****************************************************/
/**
\class ImportStatus

\brief 

\date $Date: 2006/07/05 14:11:33,50 $
\dbsource q:\transparent\transparent.dev - ODABA Version 9.0

 */
/*************************************************************************************/
#ifndef   ImportStatus_HPP
#define   ImportStatus_HPP

enum ImportStatus
{
  IMPORT_angelegt                 = 0,
  IMPORT_erfolgreich_beendet      = 3,
  IMPORT_fehlerhaft_beendet       = 4,
  IMPORT_gestartet                = 2,
  IMPORT_initialisiert            = 1,
  IMPORT_nein                     = -1,
};

#endif
