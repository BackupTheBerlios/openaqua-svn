/********************************* Class Source Code ***************************/
/**
\package  OPA
\class    eb_SubBase



\date     $Date: 2006/05/01 17:36:52,98 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "eb_SubBase"

#include  <popa7.h>
#include  <sEBDataArea.hpp>
#include  <sEB_Header.hpp>
#include  <sEB_SBHeader.hpp>
#include  <seb_Buffer.hpp>
#include  <seb_DataArea.hpp>
#include  <seb_SubBase.hpp>


/******************************************************************************/
/**
\brief  Append

\return position64 - 

\param  instlen - 
\param  length - 
\param  danumber - Number for DataArea
\param  area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Append"

int64 eb_SubBase :: Append (int32 instlen, int32 length, uint16 danumber, void *area )
{
  logical       extlock = sb_header->stsclck();
  int64         position64;
  int16     number;
BEGINSEQ
  if ( !data_areas )                                 SDBERR(45)
    
  if ( sb_netopt && !extlock )
  {
    if ( sb_header->Lock() )                          SDBERR(6)
    if ( sb_header->Read() )                          ERROR
  }  

  number = danumber == USHORTMAX ? sb_header->get_act_da() : danumber;  
  if ( CheckDANumber(number) )                        ERROR

  if ( !(position64 = (data_areas+number)->Append(instlen,length,area)) )
  {
    if ( SDBERROR != 39 || danumber != AUTO )         ERROR

    if ( number == number_da-1 )
      if ( InitNewArea() )                            ERROR
    sb_header->NextArea();
    if ( !number )
      data_areas->SetDynamic();

    if ( !(position64 = (data_areas+number+1)->Append(instlen,length,area)) ) 
                                                      ERROR
  }
  sb_header->SetMaxEntry(length);
  
  if ( sb_netopt && !extlock )
    if ( sb_header->Write() )                        ERROR

RECOVER
  position64 = 0;
ENDSEQ
  if ( !extlock )
    sb_header->Unlock();
  return(position64);

}

/******************************************************************************/
/**
\brief  CheckDANumber

\return term - Termination code

\param  danumber - Number for DataArea
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDANumber"

logical eb_SubBase :: CheckDANumber (uint16 danumber )
{
  eb_DataArea     *oldareas  = data_areas;
  int16        oldnumber = number_da;
  logical          term = NO;
BEGINSEQ
  if ( !data_areas )                                 SDBERR(45)
  if ( danumber < number_da )                        LEAVESEQ

  sb_header->Read();
  if ( danumber >= sb_header->get_da_count() )       SDBERR(99)

  data_areas = new eb_DataArea[number_da = sb_header->get_da_count()];
  memcpy(data_areas,oldareas,oldnumber*sizeof(eb_DataArea));

  // hier müssen wir uns irgendwie den PIF-Anzeiger beschaffen, jetzt:NO
  if ( OpenDataAreas(oldnumber,NO) )                 ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Close


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

void eb_SubBase :: Close ( )
{
BEGINSEQ
  if ( !this )                                       LEAVESEQ
  if ( sb_header && sb_outopt && sb_number )
    sb_header->Write();

  if ( data_areas )
    while ( number_da-- )
      (data_areas+number_da)->Close();

  delete[] data_areas;
  data_areas = NULL;

  if ( sb_number > 0 )
    delete sb_header;
  sb_header = NULL;
ENDSEQ

}

/******************************************************************************/
/**
\brief  Create

\return position64 - 

\param  odblen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int64 eb_SubBase :: Create (int32 odblen )
{
  int64       position64;

BEGINSEQ

  if ( !(position64  = Append(0,odblen,USHORTMAX,NULL)) )    ERROR

RECOVER
  position64 = 0;
ENDSEQ
  return(position64);

}

/******************************************************************************/
/**
\brief  CreateIndexEntry

\return position64 - 

\param  length - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateIndexEntry"

int64 eb_SubBase :: CreateIndexEntry (int32 length )
{
  int64       position64;

BEGINSEQ

  if ( !(position64  = Append(0,length,0,NULL)) )  ERROR

RECOVER
  position64 = 0;
ENDSEQ
  return(position64);
}

/******************************************************************************/
/**
\brief  Flush

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Flush"

logical eb_SubBase :: Flush ( )
{
  int         danumber = number_da;
  logical     term     = NO;
  if ( data_areas )
    while ( danumber-- )
      (data_areas+danumber)->Flush();

  return(term);
}

/******************************************************************************/
/**
\brief  GetActDA

\return danumber - Number for DataArea

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetActDA"

int16 eb_SubBase :: GetActDA ( )
{
  return(sb_header ? sb_header->get_act_da() : 0);
}

/******************************************************************************/
/**
\brief  InitHeader

\return term - Termination code

\param  pheader - 
\param  filename - File name for DataArea file
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitHeader"

logical eb_SubBase :: InitHeader (EB_Header *pheader, char *filename )
{
  EBDataArea       daentry(NULL);
  EBDataArea       danew(filename);
  int64            position64;
  int16            danumber = 1;
  logical          term = NO;
BEGINSEQ
  if ( !data_areas )                                 SDBERR(45)
  if ( data_areas->Read(sb_header->get_header_length(),sizeof(EBDataArea),&daentry) )
                                                      SDBERR(30)
  position64 = sb_header->get_header_length();
  while ( daentry.get_next_da() )
  {
    position64 = daentry.get_next_da();
    danumber++;
    if ( data_areas->Read(position64,sizeof(EBDataArea),&daentry) )
                                                      SDBERR(31)
  }
  if ( !daentry.SetNext(data_areas->Append(sizeof(EBDataArea),sizeof(EBDataArea),&danew)) )
                                                      ERROR
  sb_header->Lock();
  sb_header->set_da_count(sb_header->get_da_count()+1);
  sb_header->stssmod();
  sb_header->Unlock();
  if ( data_areas->Write(position64,sizeof(EBDataArea),&daentry) )
                                                      ERROR
  if ( eb_DataArea::InitFile(pheader,&danew,sizeof(EBDataArea)) )  
                                                      ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitNewArea

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitNewArea"

logical eb_SubBase :: InitNewArea ( )
{
  logical     term = NO;
  term = YES;

// mehr passiert hier noch nicht
  return(term);
}

/******************************************************************************/
/**
\brief  Locate

\return area

\param  danumber - Number for DataArea
\param  position64 - 
\param  length - 
\param  area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

void *eb_SubBase :: Locate (uint16 danumber, uint64 position64, int32 length, void *area )
{
BEGINSEQ
  if ( !data_areas )                                 SDBERR(45)
  if ( danumber >= number_da )                       SDBERR(99)

  if ( (data_areas+danumber)->Read(position64,length,area) )
                                                     ERROR

RECOVER
  area = NULL;
ENDSEQ
  return(area);
}

/******************************************************************************/
/**
\brief  Lock

\return term - Termination code

\param  danumber - Number for DataArea
\param  position64 - 
\param  length - 
\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical eb_SubBase :: Lock (uint16 danumber, uint64 position64, int32 length, logical wait )
{
  logical       term = NO;
BEGINSEQ
  if ( CheckDANumber(danumber) )                     ERROR
 
  if ( (data_areas+danumber)->Lock(position64,length,wait) )
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Open

\return term - Termination code

\param  psbheader - 
\param  path - 
\param  outopt - 
\param  netopt - Multi-user access
\param  pif_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical eb_SubBase :: Open (EB_SBHeader *psbheader, char *path, logical outopt, logical netopt, logical pif_opt )
{
  eb_DataArea     dataarea;
  EBDataArea     daentry(NULL);
  int32        len;
  logical         term = NO;

BEGINSEQ
  sb_outopt = outopt;
  sb_netopt = netopt;

  if ( psbheader )
    sb_header = psbheader;
  else
    sb_header = new EB_SBHeader(sizeof(EB_extSBHeader),netopt);

  if ( dataarea.Open(sb_header,path,outopt,netopt) )  ERROR
  number_da    = sb_header->get_da_count();
  sb_number    = sb_header->get_sb_number();

  data_areas = new eb_DataArea[number_da];
  *data_areas = dataarea;

  if ( number_da > 1 )
    if ( OpenDataAreas(1,pif_opt) )                   ERROR

  if ( sb_number )
    if ( sb_header->Write() )                         ERROR

RECOVER
  int16 errsav = SDBERROR;
  Close();
  term = YES;
  SDBISET(errsav);
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OpenDataAreas

\return term - Termination code

\param  startDA - 
\param  pif
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenDataAreas"

logical eb_SubBase :: OpenDataAreas (int16 startDA, logical pif )
{
  EBDataArea     daentry(NULL);
  int64          position64;
  int16          danumber = 0;
  logical        term = NO;

BEGINSEQ
  if ( data_areas->Read(sb_header->get_header_length(),sizeof(EBDataArea),&daentry) )
                                                      SDBERR(33)
  daentry.FromPIF(pif);

  while ( danumber < number_da && (position64 = daentry.get_next_da()) )
  {
    if ( data_areas->Read(position64,sizeof(EBDataArea),&daentry) )
                                                      SDBERR(33)
    daentry.FromPIF(pif);
    if ( ++danumber >= startDA )
      (data_areas+danumber)->Open(NULL,daentry.get_file_name(),sb_outopt,sb_netopt);
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ResetSize

\return term - Termination code

\param  danumber - Number for DataArea
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetSize"

logical eb_SubBase :: ResetSize (uint16 danumber )
{
  int16     number;
  logical       term = NO;
BEGINSEQ
  if ( !data_areas )                                 SDBERR(45)
    
  number = danumber == USHORTMAX ? sb_header->get_act_da() : danumber;  
  if ( CheckDANumber(number) )                       ERROR

  if ( (data_areas+number)->ResetSize() )            ERROR

RECOVER

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  SetNetOpt

\return term - Termination code

\param  netopt - Multi-user access
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetNetOpt"

logical eb_SubBase :: SetNetOpt (logical netopt )
{
  int32                    dan  = number_da;
  logical                 term = NO;
  sb_netopt = netopt;

  if ( data_areas && dan > 0 )
    while ( dan-- )
      (data_areas+dan)->SetNetOpt(netopt);

  return(term);
}

/******************************************************************************/
/**
\brief  Unlock

\return term - Termination code

\param  danumber - Number for DataArea
\param  position64 - 
\param  length - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical eb_SubBase :: Unlock (uint16 danumber, uint64 position64, int32 length )
{
  logical       term = NO;
BEGINSEQ
  if ( CheckDANumber(danumber) )                      ERROR

  if ( (data_areas+danumber)->Unlock(position64,length) ) ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Update

\return term - Termination code

\param  danumber - Number for DataArea
\param  position64 - 
\param  length - 
\param  area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Update"

logical eb_SubBase :: Update (uint16 danumber, uint64 position64, int32 length, void *area )
{
  void       *datatmp;
  logical     term    = NO;

BEGINSEQ
  if ( CheckDANumber(danumber) )                      ERROR
  if ( (data_areas+danumber)->Check(position64,length) ) ERROR

  if ( (data_areas+danumber)->Write(position64,length,area) )
                                                      ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  eb_SubBase


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "eb_SubBase"

     eb_SubBase :: eb_SubBase ( )
                     :   sb_header(NULL), 
  sb_number(0), 
  data_areas(NULL), number_da(0),   sb_outopt(NO),
  sb_netopt(NO)
{
}

/******************************************************************************/
/**
\brief  ~eb_SubBase


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~eb_SubBase"

     eb_SubBase :: ~eb_SubBase ( )
{
}


