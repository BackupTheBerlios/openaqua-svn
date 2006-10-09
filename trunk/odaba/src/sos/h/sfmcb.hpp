/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    fmcb

\brief    Field definition block


\date     $Date: 2006/06/13 22:21:06,20 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   fmcb_HPP
#define   fmcb_HPP

class     fmcb;

#include "csosdll.h"
#define  DEF_BUFLEN                                256
#define  FMCB_KLN                                  32
#define  FMCB_KPS                                  1
#define  FMCB_KTP                                  'C'
#define  S_GUID                                    sizeof(guid)
class     DBFieldDef;
class     smcb;
#include  <sSeparatorDef.hpp>
#include  <sfmcb.hpp>
#pragma pack(8)

class  fmcb
{
public     :         char                                         fmcbname[40];                                              // Field name
public     :         char                                         fmcbtype[40];                                              // Type name
public     :         int32                                        fmcbnsid;                                                  // 
public     :         uint32                                       fmcbsize;                                                  // 
public     :         int32                                        fmcbdim;                                                   // 
public     :         int16                                        fmcbprec;                                                  // 
public     :         int16                                        fmcbrlev;                                                  // 
public     :         int32                                        fmcbposn;                                                  // 
public     :         uint32                                       fmcbbyte;                                                  // 
public     :         int16                                        fmcbityp;                                                  // 
protected  :         bit                                          fmcbgentype: 1;                                            // Field has generic type
public     :         smcb                                        *fmcbsmcb;                                                  // Synonyms
public     :         DLL(char)                                   *fmcbsyns;                                                  // 
public     :         int8                                         fmcberr;                                                   // Field defines a base structure
public     :         bit                                          fmcbbstr: 1;                                               // Unicode option
public     :         bit                                          fmcbunicode: 1;                                            // Field may change its length
public     :         bit                                          fmcbvar: 1;                                                // Transient field
public     :         bit                                          fmcbtrans: 1;                                              // Field description is a database field
public     :         bit                                          fmcbopt: 1;                                                // Empty values allowed
public     :         bit                                          fmcbempty: 1;                                              // Indicates a field definition as under processing
public     :         bit                                          fmcbinwk: 1;                                               // Indicates an 'old' base structure instance
public     :         bit                                          fmcbold: 1;                                                // Ignore case
public     :         bit                                          fmcbic: 1;                                                 // Descending order
public     :         bit                                          fmcbdesc: 1;                                               // Constant value
public     :         bit                                          fmcbcnst: 1;                                               // Static field
public     :         bit                                          fmcbstat: 1;                                               // Virtual field
public     :         bit                                          fmcbvirt: 1;                                               // 
public     :         bit                                          fmcbinit: 1;                                               // 
public     :         bit                                          fmcballoc_opt: 1;                                          // 
public     :         bit                                          fmcbsensi: 1;                                              // 

public     :
public     :                  SOSImpExp             logical AddSynonym (char *names );
public     :                  SOSImpExp             void *AllocateArea ( );
public     :                  SOSImpExp             void CalculateLength ( );
public     :                  SOSImpExp             logical CompareConst (char *instptr, char charval );
public     :                  SOSImpExp             logical ConvertDimFromNet (char *netfld, char *intfld, int32 netlen );
public     :                  SOSImpExp             logical ConvertDimToNet (char *netfld, char *intfld, int32 netlen );
public     :                  SOSImpExp             void ConvertFromNet (char *netfld, char *intfld );
public     :                  SOSImpExp             void ConvertIFromNet (char *netfld, char *intfld );
public     :                  SOSImpExp             void ConvertIToNet (char *netfld, char *intfld );
public     :                  SOSImpExp             void ConvertToNet (char *netfld, char *intfld );
public     :                  SOSImpExp             char *ConvertToString (char *instptr, char *string, char *str_sep, char *field_sep, char *block_sep, char *empty_str, int32 srlen=UNDF, logical skip_trans=NO );
public     :                  SOSImpExp             char *ConvertToString (char *instptr, char *string, int32 srlen=UNDF, logical skip_trans=NO );
public     :                  SOSImpExp             char *ConvertToString (SeparatorDef &sep_def, char *instptr, char *string, int32 srlen=UNDF, logical skip_trans=NO );
public     :                  SOSImpExp             char *ConvertToStruct (char *instptr, char *string, int32 srlen=UNDF, logical skip_trans=NO );
public     :                  SOSImpExp             void CopySynonyms (DLL(char) *synonyms );
public     :                  SOSImpExp             logical DTConversion (fmcb *srcefmcb, char *srceinst, char *targinst );
public     : static           SOSImpExp             void __cdecl FreeArea (char **areapptr );
public     :                  SOSImpExp             int32 GetAllignedPosition (int32 fldposn, int16 allign, int8 &max_aligned );
public     :                  SOSImpExp             int32 GetCharLength ( );
public     :                  SOSImpExp             DBFieldDef *GetDescription ( );
public     : static           SOSImpExp             int16 __cdecl GetInternalType (char *typenames );
public     :                  SOSImpExp             int8 GetPlattformAlign ( );
public     :                  SOSImpExp             uint16 GetPosition (int32 setindx=UNDF );
public     : static           SOSImpExp             fmcb *__cdecl GetStaticFMCB (int16 ityp );
public     : static           SOSImpExp             fmcb *__cdecl GetStaticFMCB2 (int16 ityp, uint16 size );
public     :                  SOSImpExp             int32 GetStringLength ( );
public     :                  SOSImpExp             logical Initialize (char *intfld );
public     :                  SOSImpExp             logical IsEmpty (char *instptr );
public     :                  SOSImpExp             logical IsEnumerator ( );
public     :                  SOSImpExp             logical IsGenericType ( );
public     :                  SOSImpExp             logical IsInteger ( );
public     :                  SOSImpExp             logical IsNoField ( );
public     :                  SOSImpExp             logical IsPD ( );
public     :                                        logical IsSynonym (char *names );
public     :                  SOSImpExp             logical IsText ( );
public     :                  SOSImpExp             void RemoveSynonyms ( );
public     :                  SOSImpExp             int16 SetInternalType ( );
public     :                  SOSImpExp             logical SetNoField ( );
public     :                  SOSImpExp                  fmcb ( );
public     :                  SOSImpExp                  fmcb (char *fldnames, char *fldtypes, int32 nsid, int16 rlev, uint32 fsize, int16 prec, uint32 dim );
public     :                  SOSImpExp                  fmcb (char *fldnames, char *fldtypes, int32 nsid, int16 rlev, uint32 fsize, int16 prec, uint32 dim, int32 posn, uint32 byte, int16 ityp, logical unicode, logical var, char trans, logical opt );
public     :                  SOSImpExp                  fmcb (smcb *smcbptr );
public     :                  SOSImpExp                  fmcb (fmcb &fmcbref );
public     :                  SOSImpExp             logical fmcbbase ( );
public     :                  SOSImpExp             void fmcbbytc ( );
public     :                  SOSImpExp             logical fmcbchk ( );
public     :                  SOSImpExp             logical fmcbcmp (fmcb *fmcbptr );
public     :                  SOSImpExp             logical fmcbesu (smcb *typsmcb, int32 fldposn, int16 allign, int8 &max_aligned );
public     :                  SOSImpExp             int fmcbicmp (fmcb *srcefmcb, char *fldtarg, char *fldsrce );
public     :                  SOSImpExp             logical fmcbicpy (fmcb *srcefmcb, char *targfld, char *srcefld );
public     :                  SOSImpExp             logical fmcbicvt (fmcb *srcefmcb, char *targfld, char *srcefld, int16 replace=UNDEF, int16 copy_type=UNDEF );
public     :                  SOSImpExp             logical fmcbidtd (fmcb *srcefmcb, char *targfld, char *srcefld, int16 replace=UNDEF, int16 copy_type=UNDEF );
public     :                  SOSImpExp             logical fmcbidtr (fmcb *srcefmcb, char *targfld, char *srcefld, int16 replace=UNDEF, int16 copy_type=UNDEF );
public     :                  SOSImpExp             logical fmcbiini (char *intfld );
public     :                  SOSImpExp             void fmcbini ( );
public     :                  SOSImpExp             logical fmcbirtd (fmcb *srcefmcb, char *targfld, char *srcefld, int16 replace=UNDEF, int16 copy_type=UNDEF );
public     :                  SOSImpExp             logical fmcbirtr (fmcb *srcefmcb, char *targfld, char *srcefld, int16 replace=UNDEF, int16 copy_type=UNDEF );
public     :                                        logical fmcbkfil (fmcb *fmcbptr, int32 fldposn, int16 allign, int8 &max_aligned );
public     :                  SOSImpExp             logical fmcbkgt (char *fldsrce, char *fldkey );
public     :                  SOSImpExp             logical fmcbkpt (char *fldsrce, char *fldkey );
public     :                  SOSImpExp             int64 fmcbligt (char *fldsrce );
public     :                                        void fmcblist (char *fldtarg, int64 val64 );
public     :                  SOSImpExp             uint16 fmcblnu (fmcb *srcefmcb, void *w_entry_area=NULL );
public     :                                        uint32 fmcblugt (char *fldsrce );
public     :                                        double fmcbrgt (char *fldsrce );
public     :                  SOSImpExp             int16 fmcbstpg ( );
public     :                  SOSImpExp             fmcb &operator= (fmcb &fmcbref );
public     :                  SOSImpExp             void set_fmcbgentype (logical generic_opt );
public     :                  SOSImpExp                  ~fmcb ( );
};

#pragma pack()
#endif
