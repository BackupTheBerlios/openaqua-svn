/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    FieldList

\brief    


\date     $Date: 2006/03/12 19:17:34,76 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "FieldList"

#include  <popa7.h>
#include  <sACObject.hpp>
#include  <sDBHandle.hpp>
#include  <sDictionary.hpp>
#include  <sFieldList.hpp>
#include  <sFieldList.hpp>


/******************************************************************************/
/**
\brief  FieldList - 


-------------------------------------------------------------------------------
\brief i0


\param  memcnt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FieldList"

                        FieldList :: FieldList (int16 memcnt )
                     : fmcl(memcnt,!memcnt)

{



}

/******************************************************************************/
/**
\brief i1


\param  table -
\param  tesize -
\param  memcnt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FieldList"

                        FieldList :: FieldList (void *table, int16 tesize, int16 memcnt )
                     : fmcl ((fmcb *)table,tesize,memcnt)
{



}

/******************************************************************************/
/**
\brief  fmcdicpy - 


\return term - Termination code

\param  srceflist -
\param  targinst -
\param  srceinst -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcdicpy"

logical FieldList :: fmcdicpy (FieldList *srceflist, void *targinst, void *srceinst )
{
  fmcb          *srcefmcb;
  fmcb          *targfmcb;
  register int   indx = 0;
  logical        term = NO;

BEGINSEQ
  if ( !this || !srceflist )                          ERROR

  while ( targfmcb = GetEntry(++indx) )
    if ( targfmcb->fmcbrlev == R_DIRECT  &&
         (srcefmcb = srceflist->GetFMCB(targfmcb->fmcbname)) )
    {
      fld targfld(targfmcb,targinst);
      fld srcefld(srcefmcb,srceinst);
      targfld = srcefld;
    }

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  ~FieldList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~FieldList"

                        FieldList :: ~FieldList ( )
{



}


