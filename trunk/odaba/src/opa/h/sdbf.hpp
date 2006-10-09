/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    dbf

\brief    


\date     $Date: 2006/06/25 17:19:06,42 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   dbf_HPP
#define   dbf_HPP

class     dbf;

#include  <sDLL.h>
class     Operation;
class     ACObject;
class     DBFieldDef;
class     DBHandle;
class     DBStructDef;
class     Dictionary;
class     Operation;
class     ParmList;
class     fmcb;
class     node;
class     smcb;
#include  <cFunctionTypes.h>
#include  <cPIACC.h>
#include  <cSDB_RLEV.h>
#include  <sObjectReference.hpp>
#include  <sPropertyHandle.hpp>
#include  <sdbf.hpp>
#include  <sdttm.hpp>
#include  <sfld.hpp>
#pragma pack(8)

class  dbf :public fld,
public ObjectReference
{
protected  :         node                                        *highnod;                                                   // 
protected  :         int32                                        nodecur;                                                   // 
protected  :         DLL(Operation)                              *operations;                                                // 

public     :
                     node                                        *get_highnod() { return(highnod); }
                     int32                                        get_nodecur() { return(nodecur); }
                     DLL(Operation)                              *get_operations() { return(operations); }
public     :                  OPAImpExp             logical AllocDescription ( );
public     :                                        logical AllocateArea ( );
public     :                  OPAImpExp             logical Cancel ( );
public     :                  OPAImpExp             logical CompareType (dbf *dbfptr, logical convert );
public     :                  OPAImpExp             void Connect (node *nodptr );
public     : static           OPAImpExp             logical __cdecl ConversionError (fld &fldenty, char *targtype );
public     :                  OPAImpExp             logical Copy (const dbf *dbfenty_c );
public     :                                        void CopyDBF (dbf &dbfref );
public     :                                        logical CopyDescription (fmcb *fmcbptr );
public     :                                        logical CopyInstanceArea (dbf *dbfptr );
public     :                                        void DelDescription ( );
public     :                                        logical Dereference (dbf *dbfptr );
public     :                  OPAImpExp             void Disconnect ( );
public     :                  OPAImpExp             char *Get (int32 lindx0 );
public     :                  OPAImpExp             dbdt GetDate ( );
public     :                  OPAImpExp             dttm GetDateTime ( );
public     :                  OPAImpExp             fmcb *GetDescription ( );
public     :                  OPAImpExp             double GetDouble ( );
public     :                  OPAImpExp             dbf GetField (char *fldnames );
public     :                  OPAImpExp             PropertyHandle *GetHighPropertyHandle ( );
public     :                  OPAImpExp             int32 GetInt ( );
public     :                                        Operation **GetOperationPtr (char *expression );
public     :                  OPAImpExp             char *GetString (char *string, int32 lsize );
public     :                  OPAImpExp             dbtm GetTime ( );
public     :                  OPAImpExp             logical InitResult (dbf *operand1, dbf *operand2 );
public     :                  OPAImpExp             logical InitResult (Dictionary *dictptr, char *scoped_name, uint32 fldsize, uint16 fldprec );
public     :                                        logical Initialize (PropertyHandle &pi_handle, char *fldnames, int32 offset );
public     :                                        logical IsReference ( );
public     :                                        logical IsUnused ( );
public     :                  OPAImpExp             void Modify ( );
public     :                  OPAImpExp             logical OwnsData ( );
public     :                  OPAImpExp             logical RemoveOperation (Operation *op );
public     :                  OPAImpExp             void RemoveOperations ( );
public     :                  OPAImpExp             void RemoveOperations (PropertyHandle *pibptr );
public     :                  OPAImpExp             logical Reset ( );
public     :                  OPAImpExp             int32 Search (char *string, int32 curpos=0, logical case_opt=YES );
public     :                                        void *SetArea (void *datarea );
public     :                                        void SetDescription (fmcb *fmcbptr );
public     :                                        logical SetInitValue (char *init_value );
public     :                  OPAImpExp             char *SetInstance (void *instptr );
public     :                  OPAImpExp             void SetTemp ( );
public     :                                        logical SetupDescription ( );
public     :                  OPAImpExp                  dbf (int64 int64_val );
public     :                  OPAImpExp                  dbf (logical logval );
public     :                  OPAImpExp                  dbf (const dbf &dbfenty_refc );
public     :                  OPAImpExp                  dbf (fmcb *fmcbptr, void *datarea );
public     :                  OPAImpExp                  dbf (dbdt date_val );
public     :                  OPAImpExp                  dbf ( );
public     :                  OPAImpExp                  dbf (DBFieldDef *dbfield_ptr );
public     :                  OPAImpExp                  dbf (Dictionary *dictptr, fmcb *fmcbptr, char *init_string, logical init_opt, logical const_opt );
public     :                  OPAImpExp                  dbf (Dictionary *dictptr, char *scoped_name );
public     :                  OPAImpExp                  dbf (double dbl_value );
public     :                  OPAImpExp                  dbf (Dictionary *dictptr, char *fldnames, char *fldtypes, int32 fldnsid, SDB_RLEV fldreflev, uint32 fldsize, uint16 fldprec, uint32 flddim, char *init_value );
public     :                  OPAImpExp                  dbf (char *fldnames, char *fldtypes, int32 fldnsid, SDB_RLEV fldreflev, uint32 fldsize, uint16 fldprec, uint32 flddim, char *init_value );
public     :                  OPAImpExp                  dbf (fmcb *fmcbptr, char *init_value );
public     :                  OPAImpExp                  dbf (int32 int_val );
public     :                  OPAImpExp                  dbf (node *nodptr, char *fldnames, logical term_dbf );
public     :                  OPAImpExp                  dbf (PropertyHandle &pi_handle );
public     :                  OPAImpExp                  dbf (char *string, uint16 len );
public     :                  OPAImpExp                  dbf (char *string );
public     :                  OPAImpExp                  dbf (smcb *smcbptr, char *fldnames, void *instptr );
public     :                  OPAImpExp                  dbf (dbtm time_val );
public     :                  OPAImpExp                  dbf (smcb *smcbptr, void *instptr );
public     :                  OPAImpExp             logical dbffmcbc (DBHandle *dbhandle, char *fldnames, char *fldtypes, int32 fldnsid, int16 fldrlev, uint32 fldsize, uint16 fldprec, uint32 flddim );
public     :                  OPAImpExp             dbf &operator() (void *instptr );
public     :                  OPAImpExp             dbf &operator= (fld &fldenty );
public     :                  OPAImpExp             dbf &operator= (const dbf &dbfenty_refc );
public     :                  OPAImpExp                  ~dbf ( );
};

#pragma pack()
#endif
