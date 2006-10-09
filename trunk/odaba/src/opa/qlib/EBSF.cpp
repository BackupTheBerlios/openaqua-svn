/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EBSF

\brief    


\date     $Date: 2006/03/12 19:17:26,53 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EBSF"

#include  <popa7.h>
#include  <seb_SubBase.hpp>
#include  <sEBSF.hpp>


/******************************************************************************/
/**
\brief  ebsfadd - 


\return term - Termination code

\param  odbptr -
\param  ebsfpos -
\param  odblen -
\param  odbpos -
\param  real -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ebsfadd"

logical __cdecl EBSF :: ebsfadd (eb_SubBase *odbptr, int32 ebsfpos, int32 odblen, uint64 odbpos, logical real )
{
  ebsf             *ebsfptr;
  int32          ebsfdbp;
  logical           term = NO;
BEGINSEQ
  if ( !*ebsfpos && !(*ebsfpos = odbptr->Create(sizeof(EBSF))) )
                                                           ERROR

  for( ebsfdbp = *ebsfpos;
       (ebsfptr = (ebsf *)odbptr->odbget(ebsfdbp,EBSF,real)) &&
       ebsfptr->ebsfcnt == EBSF_MAX;
       ebsfdbp = ebsfptr->ebsfnxt                      )
    if ( !ebsfptr->ebsfnxt )
    {
      if ( !(ebsfptr->ebsfnxt = odbptr->odbcrt(EBSF)) )    ERROR
      if ( odbptr->odbupd(ebsfptr,ebsfdbp,EBSF) )          ERROR
    }  
    
  if ( !ebsfptr )                                          ERROR

  ebsfptr->ebsfofe[ebsfptr->ebsfcnt].ofepos = odbpos;
  ebsfptr->ebsfofe[ebsfptr->ebsfcnt++].ofelen = odblen;
  if ( odbptr->odbupd(ebsfptr,ebsfdbp,EBSF) )              ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ebsfchk - 


\return term - Termination code

\param  odbptr -
\param  ebsfpos -
\param  odbpos -
\param  odblen -
\param  real -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ebsfchk"

logical __cdecl EBSF :: ebsfchk (eb_SubBase *odbptr, int32 ebsfpos, uint64 odbpos, int32 odblen, logical real )
{

  ebsf             *ebsfptr;
  register int      i = -1;
  logical           term = NO;

  while ( ebsfpos )              
  {
    if ( !(ebsfptr = (ebsf *)odbptr->odbget(ebsfpos,EBSF,real)) )
							   SOSPERR

    while ( !term && ++i < ebsfptr->ebsfcnt ) 
      if ( odbpos == ebsfptr->ebsfofe[i].ofepos )
        term = YES;
      
    if ( term )
    { 
      if ( odblen != ebsfptr->ebsfofe[i].ofelen )
        return(NO);
      
      memcpy(&ebsfptr->ebsfofe[i],&ebsfptr->ebsfofe[i+1],OFE*(--ebsfptr->ebsfcnt-i) );

      if ( odbptr->odbupd(ebsfptr,ebsfpos,EBSF) )          ERROR
      return(YES);
    }
    
    ebsfpos = ebsfptr->ebsfnxt;
  }
     
on_error:
          return(NO);


}

/******************************************************************************/
/**
\brief  ebsfget - 


\return odbpos -

\param  odbptr -
\param  ebsfpos -
\param  odblen -
\param  stype -
\param  real -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ebsfget"

int32 __cdecl EBSF :: ebsfget (eb_SubBase *odbptr, int32 ebsfpos, int32 odblen, char stype, logical real )
{

  ebsf             *ebsfptr;
  register int      i = -1;
  int32          odbpos;
  logical           term = NO;

  while ( ebsfpos )              
  {
    if ( !(ebsfptr = (ebsf *)odbptr->odbget(ebsfpos,EBSF,real)) )
							   SOSPERR

    while ( !term && ++i < ebsfptr->ebsfcnt ) 
      switch ( stype )
      {
        case 'e' :
        case 'E' : term = ( odblen == ebsfptr->ebsfofe[i].ofelen ? YES : NO);
                   break;
        case 'l' :
        case 'L' :           
        default  : term = ( odblen <= ebsfptr->ebsfofe[i].ofelen ? YES : NO);
                   break;
      }
    
      if ( term )
      { 
        odbpos = ebsfptr->ebsfofe[i].ofepos;
        ebsfptr->ebsfofe[i].ofepos += odblen;
      
        if ( (ebsfptr->ebsfofe[i].ofelen -= odblen) == 0 )
          memcpy(&ebsfptr->ebsfofe[i],&ebsfptr->ebsfofe[i+1],OFE*(--ebsfptr->ebsfcnt-i) );

        if ( odbptr->odbupd(ebsfptr,ebsfpos,EBSF) )          ERROR
        return(odbpos);
      }
      ebsfpos = ebsfptr->ebsfnxt;
    }  

on_error:
          return(0);


}


