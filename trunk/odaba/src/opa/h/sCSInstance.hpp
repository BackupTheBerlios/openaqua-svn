/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/07|16:46:42,89}|(REF)
\class    CSInstance

\brief    


\date     $Date: 2006/04/10 21:29:17,84 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CSInstance_HPP
#define   CSInstance_HPP

class     CSInstance;

class     CS_Message;
class     DBFieldDef;
class     DBStructDef;
class     ParmList;
class     StructDef;
class     smcb;
#include  <cCS_ParmTypes.h>
#include  <sCSInstHeader.hpp>
#include  <sCSInstance.hpp>
#include  <sCS_Handle.hpp>
#include  <sInstance.hpp>
#include  <sdttm.hpp>
#pragma pack(1)

class  CSInstance :public CSInstHeader
{
protected  :         void                                        *datarea ATTR_ALIGN(1);                                     
protected  :         int32                                        cursize;                                                   
protected  :         logical                                      converted;                                                 
protected  :         logical                                      allocated;                                                 

public     :
                     void                                        *get_datarea() { return(datarea); }
                     int32                                        get_cursize() { return(cursize); }
                     logical                                      get_converted() { return(converted); }
                     logical                                      get_allocated() { return(allocated); }
public     :         OPAImpExp                                           CSInstance (int32 maxlen );
public     :         OPAImpExp                                           CSInstance (void *datarea );
public     :         OPAImpExp                                           CSInstance (CSInstance &rInstance );
public     :         OPAImpExp                                           CSInstance ( );
public     :         OPAImpExp                   void Fill (Key keyhandle, smcb *smcbptr, logical conversion, logical append );
public     :         OPAImpExp                   void Fill (int32 lindx0, logical conversion, logical append );
public     :         OPAImpExp                   void Fill (int16 sindx0, logical conversion, logical append );
public     :         OPAImpExp                   void Fill (uint8 uchar_val, logical conversion, logical append );
public     :         OPAImpExp                   void Fill (uint16 ushort_val, logical conversion, logical append );
public     :         OPAImpExp                   void Fill (uint32 ulong_val, logical conversion, logical append );
public     :         OPAImpExp                   void Fill (CS_Handle *handle, logical conversion, logical append );
public     :         OPAImpExp                   void Fill (char *string, logical conversion, logical append );
public     :         OPAImpExp                   void Fill (void *buffer, uint16 len, logical conversion, logical append );
public     :         OPAImpExp                   void Fill (Instance insthandle, DBStructDef *strdef, int32 instlen, logical conversion, logical append );
public     :         OPAImpExp                   void Fill (dttm timestamp1, logical conversion, logical append );
public     :         OPAImpExp                   void Fill (Instance insthandle, DBFieldDef *field_def, logical conversion, logical append );
public     :         OPAImpExp                   void Fill (ParmList *parameters, logical conversion, logical append );
public     :         OPAImpExp                   void Fill (int64 loid, logical conversion, logical append );
public     :         OPAImpExp                   void *GetBuffer ( );
public     :         OPAImpExp                   char GetChar ( );
public     :                                     int32 GetCurSize ( );
public     :                                     void *GetData ( );
public     :         OPAImpExp                   double GetDouble ( );
public     :                                     Instance GetFieldInst (DBFieldDef *field_def, CSInstance &rInstance, logical conversion );
public     :         OPAImpExp                   CS_Handle *GetHandle ( );
public     :         OPAImpExp                   Instance GetInstance (DBStructDef *strdef, CSInstance &rInstance, logical conversion );
public     :         OPAImpExp                   Instance GetInstance (DBStructDef *strdef, Instance instance, logical conversion );
public     :         OPAImpExp                   Instance GetInstance (DBFieldDef *field_def, Instance instance, logical conversion );
public     :         OPAImpExp                   Key GetKey (smcb *smcbptr, Key keyhandle, logical conversion );
public     :         OPAImpExp                   int64 GetLOID (logical conversion );
public     :         OPAImpExp                   int32 GetLong (logical conversion );
public     :                                     ParmList *GetParmList (logical conversion );
public     :         OPAImpExp                   int16 GetShort (logical conversion );
public     :         OPAImpExp                   char *GetString ( );
public     :         OPAImpExp                   dttm GetTimestamp (logical conversion );
public     :         OPAImpExp                   uint8 GetUChar ( );
public     :         OPAImpExp                   uint32 GetULong (logical conversion );
public     :         OPAImpExp                   uint16 GetUShort (logical conversion );
public     :                                     void Initialize (CSInstHeader &inst_header, char *inst_data );
public     :                                     void Release ( );
public     :                                     void *Resize (int32 maxlen );
public     :                                     void SetCurSize (int32 inst_len );
public     :                                     void SetData (char *inst_data );
public     :                                     char *Setup (CS_ParmTypes parm_type, int32 arealen, logical conversion, logical append );
public     :                                     CSInstance &operator= (CSInstance &rInstance );
public     :                                     CSInstance &operator= (int32 lindx0 );
public     :                                     CSInstance &operator= (int16 sindx0 );
public     :                                     CSInstance &operator= (char *string );
public     :                                     CSInstance &operator= (double dblval );
public     :                                     CSInstance &operator= (CS_Handle &handle_ref );
public     :                                     CSInstance &operator= (CS_Message *cs_msg );
public     :         OPAImpExp                                           ~CSInstance ( );
};

#pragma pack()
#endif
