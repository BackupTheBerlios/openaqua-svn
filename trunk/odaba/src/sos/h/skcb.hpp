/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    kcb

\brief    


\date     $Date: 2006/03/12 19:20:50,40 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   kcb_HPP
#define   kcb_HPP

class     kcb;

#define  CMP_II                                    3
#define  CMP_KI                                    2
#define  CMP_KK                                    1
#define  MAX_KEYLEN                                512
#define  kcbagt                                    GetKeyArea
#define  kcbkcp                                    CompareKeys
#define  kcbkgt                                    GetKey
#define  kcbklng                                   GetKeyLength
#define  kcbkpt                                    SetKey
#ifndef   GSCB_kfc_HPP
#define   GSCB_kfc_HPP
#include  <skfc.hpp>
#include  <sGSCB.h>
#endif
class     fmcb;
class     kcb;
class     kfcl;
class     smcb;
#pragma pack(8)

class  kcb :public GSCB(kfc)
{
protected  :         char                                        *kcbarea ATTR_ALIGN(4);                                     //
protected  :         fmcb                                        *kcbgfmcb;                                                  //
protected  :         int32                                        kcbgoff;                                                   //
protected  :         int16                                        key_num;                                                   //
protected  :         logical                                      is_pd;                                                     //

public     :
                     char                                        *get_kcbarea() { return(kcbarea); }
                     fmcb                                        *get_kcbgfmcb() { return(kcbgfmcb); }
                     int32                                        get_kcbgoff() { return(kcbgoff); }
                     int16                                        get_key_num() { return(key_num); }
public     :         SOS7ImpExp                  logical AddKey (kcb *kcbptr );
public     :         SOS7ImpExp                  int16 CompareInstances (char *instance1, char *instance2 );
public     :         SOS7ImpExp                  int16 CompareKeys (char *skey1, char *skey2, char cmptyp=UNDEF );
public     :         SOS7ImpExp                  logical CreateFieldList (int16 count, logical w_expand=NO );
public     :         SOS7ImpExp                  void Deinitialize ( );
public     :         SOS7ImpExp                  logical FromPIF (char *buffer, logical convert );
public     :         SOS7ImpExp                  char *GetKey (char *instance, char *key_area );
public     :         SOS7ImpExp                  char *GetKeyArea ( );
public     :         SOS7ImpExp                  int16 GetKeyLength ( );
public     :         SOS7ImpExp                  int16 *GetKeyNumPtr ( );
public     :         SOS7ImpExp                  logical Initialize (int16 count );
public     :         SOS7ImpExp                  logical IsMemoKey ( );
public     :         SOS7ImpExp                  logical IsPD ( );
public     :         SOS7ImpExp                  logical SetGenField (fmcb *fmcbptr, int32 fldoff );
public     :         SOS7ImpExp                  char *SetKey (char *instance, char *keyptr );
public     :         SOS7ImpExp                  void SetKeyNumber (int16 key_number );
public     :         SOS7ImpExp                  logical ToPIF (char *buffer, logical convert );
public     :         SOS7ImpExp                                          kcb ( );
public     :         SOS7ImpExp                                          kcb (char *keynames, smcb *smcbptr );
public     :         SOS7ImpExp                                          kcb (smcb *ksmcbptr, smcb *smcbptr );
public     :         SOS7ImpExp                  void kcbfad (char *kfname, int16 indx, logical ignore=NO, logical descend=NO );
public     :         SOS7ImpExp                  logical kcbini (smcb *smcbptr, char *keyname, char *kfname, int16 count, int16 allign );
public     :                                     logical kcblini (smcb *smcbptr );
public     :         SOS7ImpExp                                          ~kcb ( );
};

#pragma pack()
#endif
