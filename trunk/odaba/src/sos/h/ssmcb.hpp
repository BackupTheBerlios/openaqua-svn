/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    smcb

\brief    Structure control block
          A  structure  control  block  describes  a  complex  data  type  or an
          enumeration.  Fields  of  a  complex  data type are defined as list of
          field  control  blocks  (fmcb).  Enumerators for an enumeration can be
          accessed by the access object (smcbacc).
          The following status information are set in smcbsts:
          stserr   - stucture definition is not correct
          stsold    - old structure version (mainly for database structures in a
          dictionary) or
          __AUTOIDENT-index (for key-SMCB)
          stsnof   - identity key (for key SMCB, only)
          - otherwise: structure definition is a DBStructDef 
          stsmod - (old: key value has changed (key SMCB, only))
          stssav   - key contains multi-dimensional component (key SMCB, only)
          (old: key value has been checked for updates (key SMCB, only))
          stswpt   - key value cannot be updated (key SMCB, only)
          stslck     -  key  contains  IDENTITY  as component of a VIEW_KEY (key
          SMCB, only)
          stsusr1  - smcb has generic key component
          stsusr2  - generic keys need not to be maintained
          stsdel    - Structure inherits directly from __OBJECT
          he  application depends on the error handler installed (ErroerHandle).
          Usually  errors  are  written  to  the  console  output  for  console 
          applications and shown in a message box for windows applications.

\date     $Date: 2006/03/12 19:20:53,79 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   smcb_HPP
#define   smcb_HPP

class     smcb;

#define  DEFAULT_ALLIGNMENT                        8
#define  DEFAULT_PACK                              4
#include  <sDLL.h>
class     kcb;
class     DBStructDef;
class     acc;
class     fmcb;
class     kcb;
class     smcb;
#include  <sfld.hpp>
#include  <sfmcl.hpp>
#include  <ssts.hpp>
#pragma pack(8)

class  smcb
{
public     :         char                                         smcbname[40];                                              // Data type name
public     :         int32                                        smcbnsid;                                                  
public     :         int16                                        smcbityp;                                                  // Internal type number
public     :         int16                                        smcbstyp;                                                  // Data type type
public     :         int16                                        smcbatyp;                                                  // Preferred access type
public     :         int16                                        smcberr;                                                   // Error indicator
public     :         sts                                          smcbsts;                                                   // Status fields
protected  :         int8                                         is_pd;                                                     // Is platform dependent
public     :         int8                                         defined_align;                                             // Defined structure alignment
public     :         int8                                         plattform_align;                                           // Platform depending alignment
protected  :         int32                                        smcbtlen;                                                  // Error indicator
public     :         fmcl                                        *smcbfmcl;                                                  // Status fields
public     :         kcb                                         *smcbidky;                                                  // Identifying key
public     :         DLL(kcb)                                    *smcbskey;                                                  // Key definitions
public     :         acc                                         *smcbacc;                                                   // Instance access

public     :
public     :         SOS7ImpExp                  void AddKCB (kcb *kcbptr );
public     :         SOS7ImpExp                  logical CheckPD ( );
public     :         SOS7ImpExp                  int8 CompareIdentKey (char *skey1, char *skey2 );
public     :         SOS7ImpExp                  int8 CompareSortKey (char *skey1, char *skey2, char *keyname );
public     :         SOS7ImpExp                  void ConvertFromNet (char *netinst, char *intinst );
public     :         SOS7ImpExp                  void ConvertToNet (char *netinst, char *intinst );
public     :         SOS7ImpExp                  char *ConvertToString (char *instptr, char *string, char *str_sep, char *field_sep, char *block_sep, char *empty_str, int32 srlen=UNDF, logical skip_trans=NO );
public     :         SOS7ImpExp                  char *ConvertToString (char *instptr, char *string, int32 srlen=UNDF, logical skip_trans=NO );
public     :         SOS7ImpExp                  char *ConvertToString (SeparatorDef &sep_def, char *instptr, char *string, int32 srlen=UNDF, logical skip_trans=NO );
public     :         SOS7ImpExp                  char *ConvertToStruct (char *string, char *instptr, char *str_sep, char *field_sep, char *block_sep, char *empty_str, int32 srlen=UNDF );
public     :         SOS7ImpExp                  char *ConvertToStruct (char *string, char *instptr, int32 srlen=UNDF );
public     :         SOS7ImpExp                  logical CopyInstance (char *targinst, smcb *srcesmcb, char *srceinst, int16 replace=UNDEF, int16 copy_type=UNDEF );
public     :         SOS7ImpExp                  fld *CreateField (char *fldnames, char *w_instptr=NULL );
public     :         SOS7ImpExp                  char *ExtractIdentKey (char *idkey_w, char *instance );
public     :         SOS7ImpExp                  char *ExtractSortKey (char *skey_w, char *instance, char *keyname );
public     :         SOS7ImpExp                  int32 GetCharLength ( );
public     :         SOS7ImpExp                  fmcb *GetEntry (int16 indx );
public     :         SOS7ImpExp                  fmcb *GetEntry (char *fldnames );
public     :         SOS7ImpExp                  int32 GetEntryCount ( );
public     :         SOS7ImpExp                  fld GetField (char *fldnames, char *w_instptr=NULL );
public     :         SOS7ImpExp                  smcb *GetIdentKeySMCB ( );
public     :         SOS7ImpExp                  int32 GetInstLength (logical as_base );
public     :         SOS7ImpExp                  kcb *GetKCB (char *keynames );
public     :         SOS7ImpExp                  kcb *GetKCB (int16 keynum );
public     :         SOS7ImpExp                  smcb *GetKeySMCB (char *keynames );
public     :         SOS7ImpExp                  fmcb *GetLastEntry ( );
public     :         SOS7ImpExp                  int32 GetLength ( );
public     :         SOS7ImpExp                  smcb *GetLocalSortKey (char *fldnames );
public     :         SOS7ImpExp                  int16 GetMax ( );
public     :         SOS7ImpExp                  int32 GetRecursiveFieldCount ( );
public     :         SOS7ImpExp                  int32 GetStringLength ( );
public     :         SOS7ImpExp                  logical Initialize (char *instptr );
public     :         SOS7ImpExp                  logical IsEmpty (char *instptr );
public     :         SOS7ImpExp                  logical IsOdabaDescription ( );
public     :         SOS7ImpExp                  logical IsPD ( );
public     :         SOS7ImpExp                  fmcb *SearchField (char *fldpath, int32 *offset, kcb *w_kcbptr=NULL );
public     :         SOS7ImpExp                  fmcb *SearchPathField (char *fldpath, logical refr_opt, int32 *offset, kcb *w_kcbptr=NULL, smcb **w_typsmcb=NULL );
public     :                                     void SetAllignment ( );
public     :         SOS7ImpExp                  void SetLength (int32 lastpos=AUTO );
public     :         SOS7ImpExp                                          smcb ( );
public     :         SOS7ImpExp                                          smcb (smcb *smcbptr, char *w_strnames=NULL );
public     :         SOS7ImpExp                                          smcb (char *strnames, int32 nsid, int16 w_styp=UNDEF, int16 w_atyp=UNDEF, fmcl *w_fmclptr=NULL, int16 w_allign=UNDEF );
public     :         SOS7ImpExp                                          smcb (char *strnames, int32 nsid, int16 strid, int32 intlen, int16 styp, int16 w_atyp=UNDEF, int16 w_allign=UNDEF );
public     :                                     logical smcbkchk ( );
public     :                                     logical smcbmult ( );
public     :         SOS7ImpExp                                          ~smcb ( );
};

#pragma pack()
#endif
