/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/07|16:46:42,89}|(REF)
\class    CSInstance

\brief    


\date     $Date: 2006/04/10 21:31:21,82 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CSInstance"

#include  <popa7.h>
#include  <sCS_Handle.hpp>
#include  <sCS_Message.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBStructDef.hpp>
#include  <iNetConversion.h>
#include  <sParmList.hpp>
#include  <sSC_Property.hpp>
#include  <sStructDef.hpp>
#include  <ssmcb.hpp>
#include  <sCSInstance.hpp>


/******************************************************************************/
/**
\brief  CSInstance - 


-------------------------------------------------------------------------------
\brief  i0


\param  maxlen - Size of the output buffer
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSInstance"

                        CSInstance :: CSInstance (int32 maxlen )
                     : CSInstHeader (maxlen,CPT_void),
  datarea(NULL),
  cursize(0),
  converted(NO),
  allocated(NO)
{

  if ( size )
  {
    datarea   = malloc(size);
    allocated = YES;
  }

}

/******************************************************************************/
/**
\brief  i01


\param  datarea - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSInstance"

                        CSInstance :: CSInstance (void *datarea )
                     : CSInstHeader (),
  datarea(NULL),
  cursize(0),
  converted(NO),
  allocated(NO)
{



}

/******************************************************************************/
/**
\brief  i02


\param  rInstance - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSInstance"

                        CSInstance :: CSInstance (CSInstance &rInstance )
                     : CSInstHeader (rInstance),
  datarea(rInstance.get_datarea()),
  cursize(rInstance.get_cursize()),
  converted(rInstance.get_converted()),
  allocated(NO)
{



}

/******************************************************************************/
/**
\brief  vier


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSInstance"

                        CSInstance :: CSInstance ( )
                     : CSInstHeader (),
  datarea(NULL),
  cursize(0),
  converted(NO),
  allocated(NO)
{



}

/******************************************************************************/
/**
\brief  Fill - 


-------------------------------------------------------------------------------
\brief  i00


\param  keyhandle - 
\param  smcbptr - Pointer to general structure definition
\param  conversion - 
\param  append - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstance :: Fill (Key keyhandle, smcb *smcbptr, logical conversion, logical append )
{
  char    *area;
BEGINSEQ
  if ( !(area = Setup(CPT_key,!keyhandle ? 0 : smcbptr->GetLength(),conversion,append)) )
                                                     ERROR
  if ( keyhandle.GetData() )
  {
    if ( conversion )
      smcbptr->ConvertToNet(area,keyhandle.GetData());
    else
      memcpy(area,keyhandle.GetData(),smcbptr->GetLength());
  }
    
  converted = NO;

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i01


\param  lindx0 - 
\param  conversion - 
\param  append - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstance :: Fill (int32 lindx0, logical conversion, logical append )
{
  char    *area;
BEGINSEQ
  if ( !(area = Setup(CPT_long,sizeof(lindx0),conversion,append)) )
                                                     ERROR
  if ( conversion )
    lindx0 = htonl((u_long)lindx0);
  StoreLong(area,lindx0);

  converted = NO;

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i02


\param  sindx0 - 
\param  conversion - 
\param  append - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstance :: Fill (int16 sindx0, logical conversion, logical append )
{
  char    *area;
BEGINSEQ
  if ( !(area = Setup(CPT_short,sizeof(sindx0),conversion,append)) )
                                                     ERROR
  if ( conversion )
    sindx0 = htons((u_short)sindx0);
  StoreShort(area,sindx0);

  converted = NO;

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i03


\param  uchar_val - 
\param  conversion - 
\param  append - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstance :: Fill (uint8 uchar_val, logical conversion, logical append )
{
  char    *area;
BEGINSEQ
  if ( !(area = Setup(CPT_char,sizeof(uchar_val),conversion,append)) )
                                                     ERROR
  *area = uchar_val;

  converted = NO;

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i04


\param  ushort_val - 
\param  conversion - 
\param  append - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstance :: Fill (uint16 ushort_val, logical conversion, logical append )
{
  char    *area;
BEGINSEQ
  if ( !(area = Setup(CPT_short,sizeof(ushort_val),conversion,append)) )
                                                     ERROR
  if ( conversion )
    ushort_val = htons((u_short)ushort_val);
  StoreShort(area,ushort_val);

  converted = NO;

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i05


\param  ulong_val - 
\param  conversion - 
\param  append - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstance :: Fill (uint32 ulong_val, logical conversion, logical append )
{
  char    *area;
BEGINSEQ
  if ( !(area = Setup(CPT_long,sizeof(ulong_val),conversion,append)) )
                                                     ERROR
  if ( conversion )
    ulong_val = htonl((u_long)ulong_val);
  StoreLong(area,ulong_val);

  converted = NO;

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i06


\param  handle - 
\param  conversion - 
\param  append - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstance :: Fill (CS_Handle *handle, logical conversion, logical append )
{
  char       *area;
BEGINSEQ
  if ( !(area = Setup(CPT_handle,handle ? sizeof(CS_Handle) : 0,conversion,append)) )
                                                     ERROR
  if ( handle )
    memcpy(area,handle,sizeof(CS_Handle));
  else
    memset(area,0,sizeof(CS_Handle));
  
  converted = NO;

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i07


\param  string - 
\param  conversion - 
\param  append - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstance :: Fill (char *string, logical conversion, logical append )
{
  char       *area;
BEGINSEQ
  if ( !(area = Setup(CPT_string,string ? strlen(string)+1 : 0,conversion,append)) )
                                                     ERROR
  if ( string )
    strcpy(area,string);
  
  converted = NO;

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i08


\param  buffer - 
\param  len - 
\param  conversion - 
\param  append - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstance :: Fill (void *buffer, uint16 len, logical conversion, logical append )
{
  char       *area;
BEGINSEQ
  if ( !(area = Setup(CPT_buffer,buffer ? len : 0,conversion,append)) )
                                                     ERROR
  if ( buffer && len )
    memcpy(area,buffer,len);
    
  converted = NO;

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i09


\param  insthandle - 
\param  strdef - Structure definition
\param  instlen - 
\param  conversion - 
\param  append - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstance :: Fill (Instance insthandle, DBStructDef *strdef, int32 instlen, logical conversion, logical append )
{
  char       *area;
  logical     inst_conversion = conversion;
BEGINSEQ
  if ( !strdef || strdef->smcbityp == T_MEMO || strdef->smcbityp == T_BLOB )
    inst_conversion = NO;
  else
    instlen = strdef->GetLength();
  
  if ( !(area = Setup(CPT_instance,!insthandle ? 0 : inst_conversion ? strdef->get_net_length() : instlen,conversion,append)) )
                                                     ERROR
  if ( insthandle.GetData() )
  {
    if ( inst_conversion )
      strdef->IntToNet(area,(char *)insthandle.GetData());
    else
      memcpy(area,insthandle.GetData(),instlen);
  }
  converted = NO;

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i10


\param  timestamp1 - 
\param  conversion - 
\param  append - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstance :: Fill (dttm timestamp1, logical conversion, logical append )
{
  char       *area;
  uint32       time;
  uint32       date;
BEGINSEQ
  if ( !(area = Setup(CPT_timestamp,sizeof(dttm),conversion,append)) )
                                                     ERROR
  if ( timestamp1.GetTime().IsEmpty() )
    time = -1;
  else
    time = timestamp1.GetTime().GetLongInt();
  date = timestamp1.GetDate().GetLongInt();
  
  if (conversion)
  {
    time = (uint32)htonl(time);
    date = (uint32)htonl(date);
  }
  
  StoreLong(area,date);
  StoreLong(area+4,time);
  
  converted = NO;

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i11


\param  insthandle - 
\param  field_def - 
\param  conversion - 
\param  append - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstance :: Fill (Instance insthandle, DBFieldDef *field_def, logical conversion, logical append )
{
  char      *area;
  logical    inst_conversion = conversion;
  int32       length = 0;
BEGINSEQ
  if ( field_def->fmcbityp == T_MEMO || 
       field_def->fmcbityp == T_BLOB || 
       field_def->fmcbityp == T_STRING    )
  {
    inst_conversion = NO;
    if ( insthandle.GetData() )
    {
      length = strlen((char *)insthandle.GetData()) + 1;
      length = MIN(field_def->get_net_length(),length);
    }
  }
  else
    length = field_def->fmcbbyte;
    
  if ( !(area = Setup(CPT_instance,!insthandle ? 0 : inst_conversion ? field_def->get_net_length() : length,conversion,append)) )
                                                     ERROR
  if ( insthandle.GetData() )
  {
    if ( inst_conversion )
      field_def->IntToNet(area,(char *)insthandle.GetData());
    else
      memcpy(area,insthandle.GetData(),length);
  }
  converted = NO;

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i12


\param  parameters - 
\param  conversion - 
\param  append - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstance :: Fill (ParmList *parameters, logical conversion, logical append )
{
  char           *area;
  int             count = parameters ? parameters->GetSize() : 0;
  CS_Handle      *handles;
  PropertyHandle *prop_hdl;
  int             indx0;
BEGINSEQ
  if ( !(area = Setup(CPT_handle_list,sizeof(int32)+count*sizeof(CS_Handle),conversion,append)) )
                                                     ERROR
  if ( conversion ) 
    count = htonl((u_long)count);
  StoreLong(area,count);
  converted = NO;
  
  handles = (CS_Handle *)(((int32 *)area)+1);

  for ( indx0 = 0; indx0 < count; indx0++, handles++ )
  {
    prop_hdl = (*parameters)[indx0];
//  if ( !prop_hdl->get_connection() )               SDBERR(99)
    memcpy(handles,(CS_Handle *)prop_hdl,sizeof(CS_Handle));
  }
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i13


\param  loid
\param  conversion - 
\param  append - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstance :: Fill (int64 loid, logical conversion, logical append )
{
  char    *area;
BEGINSEQ
  if ( !(area = Setup(CPT_LOID,sizeof(loid),conversion,append)) )
                                                     ERROR
  loid = BigToPIF(loid,conversion);
  StoreBigInt(area,loid);

  converted = NO;

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  GetBuffer - Get undescribed buffer


\return buffer - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBuffer"

void *CSInstance :: GetBuffer ( )
{
  void       *buffer = NULL;
BEGINSEQ
  if ( type != CPT_buffer )                          SDBERR(508)

  if ( !cursize )                                    LEAVESEQ

  buffer = datarea;
RECOVER
  buffer = NULL;
ENDSEQ
  return(buffer);
}

/******************************************************************************/
/**
\brief  GetChar - Get single character (8 bit)


\return char_val - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetChar"

char CSInstance :: GetChar ( )
{
  char        char_val = UNDEF;
BEGINSEQ
  if ( type != CPT_char )                           SDBERR(508)

  char_val = *(char *)datarea;
RECOVER

ENDSEQ
  return(char_val);
}

/******************************************************************************/
/**
\brief  GetCurSize - Get cuttent buffer size


\return size - Field size

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurSize"

int32 CSInstance :: GetCurSize ( )
{

  return(cursize);

}

/******************************************************************************/
/**
\brief  GetData - 


\return inst_area

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetData"

void *CSInstance :: GetData ( )
{

  return ( cursize ? datarea : NULL );

}

/******************************************************************************/
/**
\brief  GetDouble - Get double value


\return dbl_value - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDouble"

double CSInstance :: GetDouble ( )
{
  double                    dbl_value;
BEGINSEQ
  if ( type != CPT_double )                           SDBERR(508)

  LoadLong(dbl_value,datarea);
RECOVER

ENDSEQ
  return(dbl_value);
}

/******************************************************************************/
/**
\brief  GetFieldInst - 


\return insthandle - 

\param  field_def - 
\param  rInstance - 
\param  conversion - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFieldInst"

Instance CSInstance :: GetFieldInst (DBFieldDef *field_def, CSInstance &rInstance, logical conversion )
{
  Instance                insthandle;
  int32                    length;
BEGINSEQ
  if ( field_def->fmcbityp == T_MEMO || 
       field_def->fmcbityp == T_BLOB || 
       field_def->fmcbityp == T_STRING    )
  {
    conversion = NO;
    length = cursize+(field_def->fmcbityp != T_BLOB);
  }
  else
    length = field_def->fmcbrlev == R_REFR 
             ? field_def->fmcbsmcb->GetLength()
             : field_def->fmcbbyte;
    
  if ( type != CPT_instance )                       SDBERR(508)

  rInstance.Resize(length);
  if ( conversion )
  {
    if ( field_def->fmcbrlev == R_REFR )
      field_def->GetDBStruct()->NetToInt((char *)rInstance.get_datarea(),(char *)datarea);
    else
      field_def->NetToInt((char *)rInstance.get_datarea(),(char *)datarea);
  }
  else
  {
    memcpy((char *)rInstance.get_datarea(),datarea,length);
    if ( length > cursize )
      *(((char *)rInstance.get_datarea())+cursize) = 0;
  }
RECOVER

ENDSEQ
  return(Instance((char *)rInstance.get_datarea()));
}

/******************************************************************************/
/**
\brief  GetHandle - Get communication handle


\return handle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHandle"

CS_Handle *CSInstance :: GetHandle ( )
{
  CS_Handle     *handle = NULL;
BEGINSEQ
  if ( type != CPT_handle )                          SDBERR(508)

  if ( !cursize )                                    LEAVESEQ
  
  handle = (CS_Handle *)datarea;
RECOVER

ENDSEQ
  return(handle);
}

/******************************************************************************/
/**
\brief  GetInstance - Get described instance


\return insthandle - 
-------------------------------------------------------------------------------
\brief  i00


\param  strdef - Structure definition
\param  rInstance - 
\param  conversion - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstance"

Instance CSInstance :: GetInstance (DBStructDef *strdef, CSInstance &rInstance, logical conversion )
{
  char              *instance = NULL;
BEGINSEQ
  if ( type != CPT_instance )                       SDBERR(508)

  if ( !cursize )                                   LEAVESEQ
  
  if ( strdef->smcbityp == T_MEMO || strdef->smcbityp == T_BLOB )
    rInstance = *this;
  else
  {
    rInstance.Resize(strdef->GetLength());
    if ( conversion )
      strdef->NetToInt((char *)rInstance.get_datarea(),(char *)datarea);
    else
      memcpy((char *)rInstance.get_datarea(),datarea,strdef->GetLength());
  }
  instance = (char *)rInstance.get_datarea();
RECOVER

ENDSEQ
  return(Instance(instance));
}

/******************************************************************************/
/**
\brief  i01


\param  strdef - Structure definition
\param  instance - Instance handle
\param  conversion - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstance"

Instance CSInstance :: GetInstance (DBStructDef *strdef, Instance instance, logical conversion )
{

BEGINSEQ
  if ( type != CPT_instance )                       SDBERR(508)

  if ( strdef->smcbityp == T_MEMO || strdef->smcbityp == T_BLOB )
  {
    memcpy(instance.GetData(),datarea,cursize);
  }
  else
  {
    if ( conversion )
      strdef->NetToInt((char *)instance.GetData(),(char *)datarea);
    else
      memcpy((char *)instance.GetData(),datarea,strdef->GetLength());
  }
RECOVER

ENDSEQ
  return(instance);
}

/******************************************************************************/
/**
\brief  i02


\param  field_def - 
\param  instance - Instance handle
\param  conversion - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstance"

Instance CSInstance :: GetInstance (DBFieldDef *field_def, Instance instance, logical conversion )
{

BEGINSEQ
  if ( type != CPT_instance )                        SDBERR(508)
  if ( !field_def )                                  SDBERR(99)

  if ( conversion )
    field_def->NetToInt((char *)instance.GetData(),(char *)datarea);
  else
    memcpy((char *)instance.GetData(),datarea,field_def->fmcbbyte);

RECOVER

ENDSEQ
  return(instance);
}

/******************************************************************************/
/**
\brief  GetKey - Provide key instance


\return keyhandle - 

\param  smcbptr - Pointer to general structure definition
\param  keyhandle - 
\param  conversion - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKey"

Key CSInstance :: GetKey (smcb *smcbptr, Key keyhandle, logical conversion )
{
  char      *instarea = NULL;
BEGINSEQ
  if ( type != CPT_key )                            SDBERR(508)

  if ( !cursize )                                    LEAVESEQ
    
  instarea = !keyhandle ? (char *)datarea : keyhandle.GetData();
  
  if ( conversion && !converted )
  {
    smcbptr->ConvertFromNet((char *)datarea,instarea);
    if ( datarea == instarea )
      converted = YES;
  }
  else if ( instarea != datarea )
    memcpy(instarea,(char *)datarea,smcbptr->GetLength());

RECOVER

ENDSEQ
  return(Key(instarea));
}

/******************************************************************************/
/**
\brief  GetLOID

\return loid

\param  conversion - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLOID"

int64 CSInstance :: GetLOID (logical conversion )
{
  int64        loid = UNDEF;
BEGINSEQ
  if ( type != CPT_LOID )                          
                                                     SDBERR(508)

  LoadBigInt(loid,datarea);
  if ( conversion && !converted )
    loid = PIFToBig(loid,YES);

RECOVER

ENDSEQ
  return(loid);
}

/******************************************************************************/
/**
\brief  GetLong - Get long integer (32 bit)


\return long_val - 

\param  conversion - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLong"

int32 CSInstance :: GetLong (logical conversion )
{
  int32        long_val = UNDEF;
BEGINSEQ
  if ( type != CPT_long )                          
                                                     SDBERR(508)

  LoadLong(long_val,datarea);
  if ( conversion && !converted )
    long_val = ntohl((u_long )long_val);

RECOVER

ENDSEQ
  return(long_val);
}

/******************************************************************************/
/**
\brief  GetParmList - Provide operation parmlist


\return parmlist - 

\param  conversion - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetParmList"

ParmList *CSInstance :: GetParmList (logical conversion )
{
  ParmList               *parmlist = NULL;
  CS_Handle              *handles;
  CS_Handle               cs_handle;
  SC_Property            *sc_prop;
  int                     indx0;
  int                     count;
BEGINSEQ
  if ( type != CPT_handle_list )                   SDBERR(508)
  
  parmlist = new ParmList(NO);

  LoadLong(count,datarea);
  if ( conversion && !converted )
    count = (int32)ntohl((u_long )count);
    
  handles = (CS_Handle *)(((int32 *)datarea)+1);

  for ( indx0 = 0;
        indx0 < count;
        indx0++, handles++          )
  {
    memcpy(&cs_handle,handles,sizeof(CS_Handle));
    if ( !(sc_prop = (SC_Property *)(cs_handle.GetServerPointer())) )
                                                     ERROR
    parmlist->AddParm(sc_prop);
  }
RECOVER
  parmlist = NULL;
ENDSEQ
  return(parmlist);
}

/******************************************************************************/
/**
\brief  GetShort - Get short integer (16 bit)


\return short_val - 16 bit integer value

\param  conversion - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetShort"

int16 CSInstance :: GetShort (logical conversion )
{
  int16       short_val = UNDEF;
BEGINSEQ
  if ( type != CPT_short )                          SDBERR(508)

  LoadShort(short_val,datarea);
  if ( conversion && !converted )
    short_val = ntohs((u_short)short_val);
RECOVER

ENDSEQ
  return(short_val);
}

/******************************************************************************/
/**
\brief  GetString - Get character string


\return string - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetString"

char *CSInstance :: GetString ( )
{
  char       *string = NULL;
BEGINSEQ
  if ( type != CPT_string )                          SDBERR(508)

  if ( !cursize )                                    LEAVESEQ
  
  string = (char *)datarea;
RECOVER

ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  GetTimestamp - Get timeatamp from buffer


\return timestamp - Date/time value

\param  conversion - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTimestamp"

dttm CSInstance :: GetTimestamp (logical conversion )
{
  dttm        timestamp;
  uint32       time;
  uint32       date;
BEGINSEQ
  if ( type != CPT_timestamp )                     SDBERR(508)

  LoadLong(date,datarea);
  LoadLong(time,datarea+4);
  
  if ( conversion && !converted )
  {
    time = (uint32)ntohl(time);
    date = (uint32)ntohl(date);
  }
  
  timestamp.SetDate(dbdt(date));
  timestamp.SetTime(dbtm(time));

RECOVER

ENDSEQ
  return(timestamp);
}

/******************************************************************************/
/**
\brief  GetUChar - Get single unsigned character (8 bit)


\return uchar_val - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetUChar"

uint8 CSInstance :: GetUChar ( )
{
  uint8       uchar_val = UNDEF;
BEGINSEQ
  if ( type != CPT_char )                           
                                                     SDBERR(508)
  uchar_val = *(uint8 *)datarea;
RECOVER

ENDSEQ
  return(uchar_val);
}

/******************************************************************************/
/**
\brief  GetULong - Get unsigned long integer (32 bit)


\return ulong_val - 

\param  conversion - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetULong"

uint32 CSInstance :: GetULong (logical conversion )
{
  uint32       ulong_val = UNDEF;
BEGINSEQ
  if ( type != CPT_long )                          SDBERR(508) 

  LoadLong(ulong_val,datarea);
  if ( conversion && !converted )
    ulong_val = ntohl((u_long )ulong_val);

RECOVER

ENDSEQ
  return(ulong_val);
}

/******************************************************************************/
/**
\brief  GetUShort - Get unsigned short integer (16 bit)


\return ushort_val - 

\param  conversion - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetUShort"

uint16 CSInstance :: GetUShort (logical conversion )
{
  uint16       ushort_val = UNDEF;
BEGINSEQ
  if ( type != CPT_short )                          SDBERR(508)

  LoadShort(ushort_val,datarea);
  if ( conversion && !converted )
    ushort_val = ntohs((u_short)ushort_val);
RECOVER

ENDSEQ
  return(ushort_val);
}

/******************************************************************************/
/**
\brief  Initialize - 



\param  inst_header - 
\param  inst_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void CSInstance :: Initialize (CSInstHeader &inst_header, char *inst_data )
{

  SetData(inst_data);

  cursize = inst_header.get_size();
  type    = inst_header.get_type();
  converted = NO;


}

/******************************************************************************/
/**
\brief  Release - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Release"

void CSInstance :: Release ( )
{

  if ( allocated )
  {
    free(datarea);
    allocated = NO;
  }
      
  datarea = NULL;
  size    = 0;
//cursize = 0;  das führt zur Katastrophe, da Länge manchmal auch nach dem Release benötigt wird


}

/******************************************************************************/
/**
\brief  Resize - 


\return datarea - 

\param  maxlen - Size of the output buffer
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Resize"

void *CSInstance :: Resize (int32 maxlen )
{

BEGINSEQ
  if ( size < maxlen )
  {
    if ( allocated && datarea )
    {
      if ( !(datarea = realloc(datarea,size=maxlen)) ) SDBERR(95)
    }
    else
    {
      datarea   = malloc(size=maxlen);
      allocated = YES;
    }
  }

RECOVER

ENDSEQ
  return(datarea);
}

/******************************************************************************/
/**
\brief  SetCurSize - 



\param  inst_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCurSize"

void CSInstance :: SetCurSize (int32 inst_len )
{

  cursize = inst_len;

}

/******************************************************************************/
/**
\brief  SetData - 



\param  inst_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetData"

void CSInstance :: SetData (char *inst_data )
{

  Release();
  datarea = inst_data;

}

/******************************************************************************/
/**
\brief  Setup - 


\return instance - Instance handle

\param  parm_type - 
\param  arealen - 
\param  conversion - 
\param  append - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

char *CSInstance :: Setup (CS_ParmTypes parm_type, int32 arealen, logical conversion, logical append )
{
  int32            newlen = arealen;
  CSInstHeader   *inst_header;
  char           *instance;
BEGINSEQ
  if ( append )
    newlen += (cursize + sizeof(CSInstHeader));
  else
    type = parm_type;
    
  if ( !(instance = (char *)Resize(newlen)) )         ERROR
  
  if ( append )
  {
    inst_header = (CSInstHeader *)(instance + cursize);
    inst_header->Initialize(parm_type,arealen);
    if ( conversion )
      inst_header->ConvertToNet(*inst_header);
    instance = (char *)(inst_header+1);
  }

  cursize = newlen;
RECOVER
  instance = NULL;
ENDSEQ
  return(instance);
}

/******************************************************************************/
/**
\brief  operator= - 


\return rInstance - 
-------------------------------------------------------------------------------
\brief  i0


\param  rInstance - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

CSInstance &CSInstance :: operator= (CSInstance &rInstance )
{

  cursize   = rInstance.get_cursize();
  type      = rInstance.get_type();
  converted = rInstance.get_converted();
  
  if ( rInstance.get_size() )
  {
    Resize(rInstance.get_cursize());
    memcpy(datarea,rInstance.get_datarea(),cursize);
    memset(((char *)datarea)+cursize,0,size-cursize);
  }
  else
  {
    Release();
    datarea = rInstance.get_datarea();
  }
  return(*this);
}

/******************************************************************************/
/**
\brief  i01


\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

CSInstance &CSInstance :: operator= (int32 lindx0 )
{

  Resize(cursize = sizeof(lindx0));
  type = CPT_long;
  memcpy(datarea,&lindx0,sizeof(lindx0));

  return(*this);
}

/******************************************************************************/
/**
\brief  i02


\param  sindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

CSInstance &CSInstance :: operator= (int16 sindx0 )
{

  Resize(cursize = sizeof(sindx0));
  type = CPT_short;
  memcpy(datarea,&sindx0,sizeof(sindx0));
  return(*this);
}

/******************************************************************************/
/**
\brief  i03


\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

CSInstance &CSInstance :: operator= (char *string )
{

  Resize(cursize = strlen(string)+1);
  type = CPT_string;
  memcpy(datarea,string,cursize);

  return(*this);
}

/******************************************************************************/
/**
\brief  i04


\param  dblval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

CSInstance &CSInstance :: operator= (double dblval )
{

  Resize(cursize = sizeof(dblval));
  type = CPT_double;
  memcpy(datarea,&dblval,sizeof(dblval));

  return(*this);
}

/******************************************************************************/
/**
\brief  i05


\param  handle_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

CSInstance &CSInstance :: operator= (CS_Handle &handle_ref )
{

  Resize(cursize = sizeof(CS_Handle));
  type = CPT_handle;
  memcpy(datarea,&handle_ref,cursize);

  return(*this);
}

/******************************************************************************/
/**
\brief  i06


\param  cs_msg - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

CSInstance &CSInstance :: operator= (CS_Message *cs_msg )
{

  Resize(cursize = cs_msg->GetLength());
  type = CPT_void;
  memcpy(datarea,(char *)cs_msg+1,cursize);

  return(*this);
}

/******************************************************************************/
/**
\brief  ~CSInstance - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CSInstance"

                        CSInstance :: ~CSInstance ( )
{

  Release();

}


