/********************************* Class Declaration ***************************/
/**
\package  OPA
\class    eb_SubBase



\date     $Date: 2006/05/01 17:36:30,51 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   eb_SubBase_HPP
#define   eb_SubBase_HPP

class     eb_SubBase;

class     EB_Header;
#include  <sEB_SBHeader.hpp>
#include  <seb_Buffer.hpp>
#include  <seb_DataArea.hpp>
#pragma pack(8)

class  eb_SubBase
{
protected  :         EB_SBHeader                                 *sb_header;                                                 
protected  :         int16                                        sb_number;                                                 
protected  :         eb_DataArea                                 *data_areas;                                                
protected  :         int16                                        number_da;                                                 
protected  :         logical                                      sb_outopt;                                                 
protected  :         logical                                      sb_netopt;                                                 

public     :
                     EB_SBHeader                                 *get_sb_header() { return(sb_header); }
                     int16                                        get_sb_number() { return(sb_number); }
                     eb_DataArea                                 *get_data_areas() { return(data_areas); }
                     int16                                        get_number_da() { return(number_da); }
                     logical                                      get_sb_outopt() { return(sb_outopt); }
                     logical                                      get_sb_netopt() { return(sb_netopt); }
public     :                                        int64 Append (int32 instlen, int32 length, uint16 danumber, void *area );
public     :                                        logical CheckDANumber (uint16 danumber );
public     :                                        void Close ( );
public     :                                        int64 Create (int32 odblen );
public     :                                        int64 CreateIndexEntry (int32 length );
public     :                                        logical Flush ( );
public     :                                        int16 GetActDA ( );
public     :                                        logical InitHeader (EB_Header *pheader, char *filename );
public     :                                        logical InitNewArea ( );
public     :                                        void *Locate (uint16 danumber, uint64 position64, int32 length, void *area );
public     :                                        logical Lock (uint16 danumber, uint64 position64, int32 length, logical wait );
public     :                                        logical Open (EB_SBHeader *psbheader, char *path, logical outopt, logical netopt, logical pif_opt=NO );
public     :                                        logical OpenDataAreas (int16 startDA, logical pif );
public     :                                        logical ResetSize (uint16 danumber );
public     :                                        logical SetNetOpt (logical netopt );
public     :                                        logical Unlock (uint16 danumber, uint64 position64, int32 length );
public     :                                        logical Update (uint16 danumber, uint64 position64, int32 length, void *area );
public     :                                             eb_SubBase ( );
public     :                                             ~eb_SubBase ( );
public     :                                        logical Delete (uint16 danumber, uint64 position64 ){
//  if ( ebshnrl(ebsodb,entnr) )                       RROR
  // retcodes: AUTO - kein löschen ausgeführt
  //           NO   - Löschen erfolgreich
  //           YES  - Löschen fehlgeschlagen
  return ( AUTO );

}

public     :                                        char *Initialize (int32 odblen, uint16 danumber, uint64 position64 ){
  return ( NULL );

}

};

#pragma pack()
#endif
