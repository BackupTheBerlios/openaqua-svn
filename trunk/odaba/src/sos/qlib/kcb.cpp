/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    kcb

\brief    


\date     $Date: 2006/03/12 19:22:38,29 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "kcb"

#include  <pdefault.h>
#include  <csmcbmac.h>
#include  <sfmcb.hpp>
#include  <skcb.hpp>
#include  <skfcl.hpp>
#include  <ssmcb.hpp>
#include  <skcb.hpp>


/******************************************************************************/
/**
\brief  AddKey - 


\return term - Success

\param  kcbptr - Key definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddKey"

logical kcb :: AddKey (kcb *kcbptr )
{
  fmcb      *skeyfmcb;
  fmcb      *tkeyfmcb;
  short      indx = 0;
  logical    term = NO;
BEGINSEQ
  while ( skeyfmcb = kcbptr->scbsmcb->smcbfmcl->GetEntry(++indx) )
  {
    if ( !(tkeyfmcb = scbsmcb->smcbfmcl->AddFreeEntry()) )
                                                     SOSERR(95)
    *tkeyfmcb = *skeyfmcb;
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CompareInstances - 


\return cmpval - Comparision result

\param  instance1 -
\param  instance2 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CompareInstances"

int16 kcb :: CompareInstances (char *instance1, char *instance2 )
{

  return ( kcbkcp(instance1,instance2,CMP_II) );

}

/******************************************************************************/
/**
\brief  CompareKeys - 


\return cmpval - Comparision result

\param  skey1 - Key value
\param  skey2 - Key value
\param  cmptyp -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CompareKeys"

int16 kcb :: CompareKeys (char *skey1, char *skey2, char cmptyp )
{

  return(scbfcbl->kfclkcp(skey1,skey2,cmptyp ? cmptyp : CMP_KK) );


}

/******************************************************************************/
/**
\brief  CreateFieldList - 


\return term - Success

\param  count -
\param  w_expand -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateFieldList"

logical kcb :: CreateFieldList (int16 count, logical w_expand )
{
  logical   term = NO;

BEGINSEQ
  if ( !(scbsmcb->smcbfmcl = new fmcl(count,w_expand)) ) 
                                                SOSERR(95)

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  Deinitialize - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deinitialize"

void kcb :: Deinitialize ( )
{
  fmcb     *keyfmcb;
  scbfcbl->Deinitialize();
  
  delete kcbarea;
  if ( IsMemoKey() )
    if ( keyfmcb = scbsmcb->smcbfmcl->GetEntry(1) )
      delete keyfmcb->fmcbsmcb;    


}

/******************************************************************************/
/**
\brief  FromPIF - 


\return term - Success

\param  buffer -
\param  convert -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromPIF"

logical kcb :: FromPIF (char *buffer, logical convert )
{
  logical                 term = NO;
BEGINSEQ
  if ( !convert || !is_pd )                         LEAVESEQ

  scbsmcb->ConvertFromNet(buffer,buffer);
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetKey - 


\return keyptr -

\param  instance - Structured instance
\param  key_area -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKey"

char *kcb :: GetKey (char *instance, char *key_area )
{


BEGINSEQ
  if ( !this )                                       ERROR
     
  if ( !key_area )
    key_area = kcbarea;  
  scbfcbl->kfclkgt(instance,key_area);

RECOVER
  key_area = NULL;
ENDSEQ
  return(key_area);

}

/******************************************************************************/
/**
\brief  GetKeyArea - 


\return keyptr -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeyArea"

char *kcb :: GetKeyArea ( )
{

  return(kcbarea);

}

/******************************************************************************/
/**
\brief  GetKeyLength - 


\return klen -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeyLength"

int16 kcb :: GetKeyLength ( )
{

  return ( this ? (int16)scbsmcb->GetInstLength(NO) : UNDEF );


}

/******************************************************************************/
/**
\brief  GetKeyNumPtr - 


\return key_number -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeyNumPtr"

int16 *kcb :: GetKeyNumPtr ( )
{

  return(&key_num);

}

/******************************************************************************/
/**
\brief  Initialize - 


\return term - Success

\param  count -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical kcb :: Initialize (int16 count )
{
  logical                 term = NO;
BEGINSEQ
  if ( CreateFieldList(NULL,MAX(count,1)) )  SOSERR(95)
    
  if ( !memcmp(scbsmcb->smcbname,"__IDENTITY ",11) )
  {
    fmcb keyfmcb("__IDENTITY","INT",0,R_DIRECT,20,0,1,0,8,T_INT,NO,NO,NO,NO);
    scbsmcb->smcbfmcl->AddEntry(1,&keyfmcb);
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsMemoKey - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsMemoKey"

logical kcb :: IsMemoKey ( )
{

   return(NO);    // 11.5.00
                  // wird von ref:Konstruktur benutzt, um acc zu ersetzten
                  // die gerät jetzt in KOnflikt mit Copy
   return(this && scbsmcb ? scbsmcb->smcbsts.stscusr3() : NO);


}

/******************************************************************************/
/**
\brief  IsPD - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPD"

logical kcb :: IsPD ( )
{


  return(this ? is_pd : NO);
}

/******************************************************************************/
/**
\brief  SetGenField - 


\return term - Success

\param  fmcbptr - Field definition block
\param  fldoff -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGenField"

logical kcb :: SetGenField (fmcb *fmcbptr, int32 fldoff )
{
  logical   term = NO;
BEGINSEQ
  if ( kcbgfmcb )
  {  
    if ( kcbgfmcb == fmcbptr )                       LEAVESEQ
                                                     SOSERR(99)
  }
  
  kcbgfmcb = fmcbptr;
  kcbgoff  = fldoff + fmcbptr->fmcbposn;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetKey - 


\return instance - Structured instance

\param  instance - Structured instance
\param  keyptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetKey"

char *kcb :: SetKey (char *instance, char *keyptr )
{

  scbfcbl->kfclkpt(instance,keyptr);

  return(instance);
}

/******************************************************************************/
/**
\brief  SetKeyNumber - 



\param  key_number -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetKeyNumber"

void kcb :: SetKeyNumber (int16 key_number )
{

  key_num = key_number;

}

/******************************************************************************/
/**
\brief  ToPIF - 


\return term - Success

\param  buffer -
\param  convert -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToPIF"

logical kcb :: ToPIF (char *buffer, logical convert )
{
  logical                 term = NO;
BEGINSEQ
  if ( !convert || !is_pd )                         LEAVESEQ

  scbsmcb->ConvertToNet(buffer,buffer);
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  kcb - 


-------------------------------------------------------------------------------
\brief KCB_D


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "kcb"

                        kcb :: kcb ( )
                     : GSCB(kfc) (),
  kcbarea(NULL),
  kcbgfmcb(NULL),
  kcbgoff(0),
  key_num(0),
  is_pd(NO)
{



}

/******************************************************************************/
/**
\brief KCB_I


\param  keynames -
\param  smcbptr - Structure definition block
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "kcb"

                        kcb :: kcb (char *keynames, smcb *smcbptr )
                     : GSCB(kfc) (),
  kcbarea(NULL),
  kcbgfmcb(NULL),
  kcbgoff(0),
  key_num(0),
  is_pd(NO)
{

BEGINSEQ
  if ( !(scbsmcb = new smcb(keynames,0,UNDEF,UNDEF,ST_KEY,AT_NONE)) )
                                                   SOSERR(95)
  scbsmcb->defined_align = MIN(4,smcbptr->defined_align);
  
  smcbptr->AddKCB(this);

RECOVER


ENDSEQ

}

/******************************************************************************/
/**
\brief KCB_N


\param  ksmcbptr -
\param  smcbptr - Structure definition block
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "kcb"

                        kcb :: kcb (smcb *ksmcbptr, smcb *smcbptr )
                     : GSCB(kfc)(ksmcbptr),
  kcbarea(NULL),
  kcbgfmcb(NULL),
  kcbgoff(0),
  key_num(0),
  is_pd(NO)
{

BEGINSEQ
  SOSCERR
  
  scbfcbl->kfclesu(smcbptr,!memcmp(scbsmcb->smcbname,"_ic",3));

  if ( !(kcbarea = new char[(short int)ksmcbptr->GetInstLength(NO)]) )	
                                                   SOSERR(95)
  if ( scbfcbl->stscold() )
    scbsmcb->smcbsts.stssold();

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  kcbfad - 



\param  kfname -
\param  indx -
\param  ignore -
\param  descend -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "kcbfad"

void kcb :: kcbfad (char *kfname, int16 indx, logical ignore, logical descend )
{

  fmcb  *keyfmcb = scbsmcb->smcbfmcl->AddFreeEntry();
  if ( keyfmcb )
  {
    strncpy(keyfmcb->fmcbname,kfname,2*ID_SIZE-1);     // name + type
    keyfmcb->fmcbname[2*ID_SIZE-1] = 0;
    keyfmcb->fmcbic   = ignore;
    keyfmcb->fmcbdesc = descend;
  }


}

/******************************************************************************/
/**
\brief  kcbini - 


\return term - Success

\param  smcbptr - Structure definition block
\param  keyname - Key name
\param  kfname -
\param  count -
\param  allign -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "kcbini"

logical kcb :: kcbini (smcb *smcbptr, char *keyname, char *kfname, int16 count, int16 allign )
{
  smcb     *keysmcb;
  fmcb     *keyfmcb;
  char      name[ID_SIZE];
  ushort    pos  = 0;
  short     indx = 1;
  logical   memokey = NO;
  short     memolen;
  logical   term = NO;

BEGINSEQ
  if ( scbsmcb )
  {
    if ( keyname && memcmp(scbsmcb->smcbname,gvtxstb(name,keyname,ID_SIZE),ID_SIZE) )
                                                     SOSERR(33)
    keysmcb = scbsmcb;
    if ( !count && keysmcb->smcbfmcl )               LEAVESEQ
  }
  else
    if ( !(keysmcb = new smcb(keyname,0,UNDEF,UNDEF,ST_KEY,AT_NONE)) )
                                                     SOSERR(95)
  keysmcb->defined_align   = MIN(4,allign);
  keysmcb->plattform_align = MIN(4,allign);
  
  if ( count )
  {
    if ( !keysmcb->smcbfmcl )
    {
      if ( !(keysmcb->smcbfmcl = new fmcl(count,NO)) ) 
                                                     SOSERR(95)
      while ( keysmcb->smcbfmcl->AddFreeEntry() ) ;
    }  
    scbini(keysmcb,sizeof(kfc));                     SOSCERR
    
    while ( indx <= count )
    {
      keyfmcb = keysmcb->smcbfmcl->GetEntry(indx);
      if ( keyfmcb->fmcbityp == T_MEMO )
      {
        if ( count > 1 )                             SOSERR(6)
        memokey = YES;
        scbsmcb->smcbsts.stssusr3();
        memolen = keyfmcb->fmcbsize;
      }

      if ( kfname )
        memcpy(keyfmcb->fmcbname,kfname+(indx-1)*ID_SIZE,ID_SIZE);
      indx++;
    }
    if ( kcblini(smcbptr) )                          ERROR
  }
  else
  {
    scbini(keysmcb,sizeof(kfc));                    SOSCERR
    if ( scbfcbl )
    {
      scbfcbl->kfclesu(smcbptr,!memcmp(scbsmcb->smcbname,"_ic",3));
      if ( scbfcbl->stscold() )
        scbsmcb->smcbsts.stssold();
    }
  }
  if ( keysmcb->GetLength() > 0 && !(kcbarea = new char[memokey ? memolen : (int16)keysmcb->GetInstLength(NO)]) )
                                                     SOSERR(95)

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  kcblini - 


\return term - Success

\param  smcbptr - Structure definition block
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "kcblini"

logical kcb :: kcblini (smcb *smcbptr )
{
  int16     indx   = 0;
  int32     offset = 0;
  int32     pos    = 0;
  fmcb     *keyfmcb;
  fmcb     *fmcbptr;
  kfc      *kfcptr;
  char      genattr[ID_SIZE];
  logical   term   = NO;


BEGINSEQ
  while ( kfcptr = scbfcbl->GetEntry(++indx) )
  {
    keyfmcb = scbsmcb->smcbfmcl->GetEntry(indx);
    offset  = 0;
    kfcptr->set_kc_name(keyfmcb->fmcbname);
    if ( fmcbptr = smcbptr->SearchField(keyfmcb->fmcbname,&offset,this) )
    {
      if ( keyfmcb->fmcbkfil(fmcbptr,pos,scbsmcb->defined_align,scbsmcb->plattform_align) )
                                                     ERROR
      kfcptr->kfcesu(fmcbptr,offset);
      if ( fmcbptr->fmcbdim != 1 )
        scbsmcb->smcbsts.stsssav();                  // mehrdimensionaler Schlüsselbestandteil
    }
    else 
    {
      if ( !keyfmcb->fmcbvirt )
      {
        if ( memcmp(scbsmcb->smcbname,"__IDENTITY ",11) )
                                                     SOSERR(99)
        scbsmcb->smcbsts.stssnof();                    // Identity-Sortierung
      }
    }
    pos = keyfmcb->fmcbposn + keyfmcb->fmcbbyte;
    if ( !is_pd && keyfmcb->IsPD() )
      is_pd = YES;
  }
  scbsmcb->SetLength(pos);

  if ( kcbgfmcb )
  {
    scbsmcb->smcbsts.stssusr1();                    // generischer Schlüssel
    smcbptr->smcbsts.stssusr1();                    // smcb hat generische Schlüssel
  }
  
//if ( scbfcbl->GetCount() == 1 && !offset &&  // warum soll der AUITOIDENT nicht in der zweiten Struktur stehen
  if ( scbfcbl->GetCount() == 1            &&     
       !scbsmcb->smcbsts.stscnof()         &&       // not IDENTITY
       !scbsmcb->smcbsts.stsclck()         &&       // not IDENTITY
       !IsMemoKey()                        &&       
       ( !memcmp(fmcbptr->fmcbname,"#_AUTOIDENT ",12) ||
         !memcmp(fmcbptr->fmcbname,"__AUTOIDENT ",12)   ) )
    scbsmcb->smcbsts.stssold();                     // AOTOIdent-Schlüssel

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  ~kcb - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~kcb"

                        kcb :: ~kcb ( )
{

  Deinitialize();
  


}


