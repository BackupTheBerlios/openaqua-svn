/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    cvb

\brief    


\date     $Date: 2006/07/28 11:36:18,56 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cvb"

#include  <pdefault.h>
#include  <ccvbf.h>
#include  <csmcbdef.h>
#include  <csmcbmac.h>
#include  <gcvb.h>
#include  <guidstr.h>
#include  <cDataFormSpec.h>
#include  <sdttm.hpp>
#include  <sfmcb.hpp>
#include  <sguid.hpp>
#include  <scvb.hpp>


/******************************************************************************/
/**
\brief  cvb - 




\param  srcefmcb - 
\param  targfmcb - 
\param  srcearea - 
\param  targarea - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvb"

     cvb :: cvb (fmcb *srcefmcb, fmcb *targfmcb, char *srcearea, char *targarea )
                     :  cvbsfmcb(srcefmcb), cvbtfmcb(targfmcb), 
 cvbsdata(srcearea), cvbtdata(targarea)

{



}

/******************************************************************************/
/**
\brief  cvbblbl - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbblbl"

logical cvb :: cvbblbl ( )
{

  memset(cvbtdata,0,cvbtfmcb->fmcbsize);
  memcpy(cvbtdata,cvbsdata,MIN(cvbsfmcb->fmcbsize,cvbtfmcb->fmcbsize));
  return(NO);


}

/******************************************************************************/
/**
\brief  cvbcccc - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbcccc"

logical cvb :: cvbcccc ( )
{

  gvtxctc(cvbtdata,cvbtfmcb->fmcbsize,cvbsdata,cvbsfmcb->fmcbsize);

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbccch - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbccch"

logical cvb :: cvbccch ( )
{

  gvtxctb(cvbtdata,cvbtfmcb->fmcbsize,cvbsdata,cvbsfmcb->fmcbsize);

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbccsr - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbccsr"

logical cvb :: cvbccsr ( )
{

  gvtxctb(cvbtdata,cvbtfmcb->fmcbsize,cvbsdata,cvbsfmcb->fmcbsize);
  gvtxbts(cvbtdata,cvbtdata,cvbtfmcb->fmcbsize);

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbcdcd - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbcdcd"

logical cvb :: cvbcdcd ( )
{

  *(int *)cvbtdata = *(int *)cvbsdata;
  return(NO);


}

/******************************************************************************/
/**
\brief  cvbcdch - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbcdch"

logical cvb :: cvbcdch ( )
{
  int32     indx0 = (int32)(*(int *)cvbsdata);
  char      cstr[257];
  logical   term = NO;

BEGINSEQ
  memset(cvbtdata,' ',cvbtfmcb->fmcbsize);

  if ( !cvbsfmcb->fmcbsmcb->smcbacc || 
       !cvbsfmcb->fmcbsmcb->smcbacc->Access(indx0,cstr,sizeof(cstr)) )
                                                           ERROR
  gvtxstb(cvbtdata,cstr,MIN(cvbtfmcb->fmcbsize,sizeof(cstr)));

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  cvbcdfl - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbcdfl"

logical cvb :: cvbcdfl ( )
{
  int32                    value;

  memcpy(&value,cvbsdata,4);

  if ( cvbtfmcb->fmcbdim )
  {
    if ( cvbtfmcb->fmcbbyte/cvbtfmcb->fmcbdim < 8 )
      *(float *)cvbtdata  = (float)value;
    else
      *(double *)cvbtdata = (double)value;
  }
  return(NO);
}

/******************************************************************************/
/**
\brief  cvbcdin - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbcdin"

logical cvb :: cvbcdin ( )
{


  cvbtfmcb->fmcblist(cvbtdata,*(int *)cvbsdata);


  return(NO);
}

/******************************************************************************/
/**
\brief  cvbcdlo - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbcdlo"

logical cvb :: cvbcdlo ( )
{
  char      cstr[257];

  *cvbtdata =   (*(int *)cvbsdata && 
                 cvbsfmcb->fmcbsmcb->smcbacc && 
                 cvbsfmcb->fmcbsmcb->smcbacc->Access(*(int *)cvbsdata,cstr,sizeof(cstr))) 
               ? YES : NO;
  return(NO);


}

/******************************************************************************/
/**
\brief  cvbcdsr - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbcdsr"

logical cvb :: cvbcdsr ( )
{
  int32     indx0 = (int32)(*(int *)cvbsdata);
  char      cstr[257];
  logical   term = NO;

BEGINSEQ
  *cvbtdata = 0;

  if ( !cvbsfmcb->fmcbsmcb->smcbacc || 
       !cvbsfmcb->fmcbsmcb->smcbacc->Access(indx0,cstr,sizeof(cstr)) )
                                                           ERROR
  gvtxbts(cvbtdata,cstr,MIN(cvbtfmcb->fmcbsize,sizeof(cstr)));

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  cvbchcc - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbchcc"

logical cvb :: cvbchcc ( )
{

  gvtxbtc(cvbtdata,cvbtfmcb->fmcbsize,cvbsdata,cvbsfmcb->fmcbsize);

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbchcd - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbchcd"

logical cvb :: cvbchcd ( )
{
  int	    len = MIN(cvbsfmcb->fmcbsize,cvbtfmcb->fmcbsmcb->GetLastEntry()->fmcbsize);
  logical   term = NO;
  int32     cval;

BEGINSEQ
  cvbtfmcb->fmcbsmcb->smcbacc->Access(cvbsdata,cval);
  if ( cval == CS_U )                                ERROR
       
  *(int *)cvbtdata = cval;                                                           

RECOVER
  *(int *)cvbtdata = UNDEF;
  term             = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  cvbchch - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbchch"

logical cvb :: cvbchch ( )
{

  memset(cvbtdata,' ',cvbtfmcb->fmcbsize);
  memcpy(cvbtdata,cvbsdata,MIN(cvbsfmcb->fmcbsize,cvbtfmcb->fmcbsize));
  return(NO);


}

/******************************************************************************/
/**
\brief  cvbchdm - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbchdm"

logical cvb :: cvbchdm ( )
{

  return ( cvbchst() );

}

/******************************************************************************/
/**
\brief  cvbchdt - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbchdt"

logical cvb :: cvbchdt ( )
{
  char          dstring[17];
  int           size = MIN(cvbsfmcb->fmcbsize,sizeof(dstring)-1);

  gvtxbts(dstring,cvbsdata,size);
  ((dbdt *)cvbtdata)->FromString(cvbsdata,size,
                                 dfs::GetDateFormat(dstring));


  return(NO);

}

/******************************************************************************/
/**
\brief  cvbchfl - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbchfl"

logical cvb :: cvbchfl ( )
{
  char        string[128];
  double      value;
  gvtxbts(string,cvbsdata,MIN(sizeof(string)-1,cvbsfmcb->fmcbsize));
  gvtsexc(string,",",".",sizeof(string)-1);
  
  value = strtod(string,NULL);

  if ( cvbtfmcb->fmcbbyte == 4 )
    *(float *)cvbtdata  = (float)value;
  else
    *(double *)cvbtdata = value;


  return(NO);

}

/******************************************************************************/
/**
\brief  cvbchin - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbchin"

logical cvb :: cvbchin ( )
{
  int64        ltemp; 
  int64        dctemp;
  char         string[25];
  char        *decstr;
  logical      neg = NO;
  short        i;
  gvtxbts((char *)memset(string,0,sizeof(string)),cvbsdata,MIN(sizeof(string)-1,cvbsfmcb->fmcbsize));
#ifndef __unix__
  ltemp = _atoi64(string);
#else
  ltemp = atol(string);  // was gibts unter unix??
#endif
  if ( string[strlen(string)-1] == '-' )
    ltemp = -ltemp;

  if ( cvbtfmcb->fmcbprec )
  {
    ltemp *= expval[cvbtfmcb->fmcbprec];
    neg    = strchr(string,'-') ? YES : NO;

    if ( (decstr = strchr(string,dfs::GetDecimal())) )
    {
      (++decstr)[cvbtfmcb->fmcbprec] = 0;
      for ( i=0; i < cvbtfmcb->fmcbprec && decstr[i] >= '0' && decstr[i] <= '9'; i++ ) ;
      for (    ; i < cvbtfmcb->fmcbprec && (decstr[i] = '0');                    i++ ) ;
#ifndef __unix__
      dctemp = _atoi64(decstr);
#else
      dctemp = atol(decstr);  // was gibts unter unix??
#endif
      if ( neg )
        ltemp -= dctemp;   
      else  
        ltemp += dctemp;   
    }
  }

  cvbtfmcb->fmcblist(cvbtdata,ltemp);


  return(NO);

}

/******************************************************************************/
/**
\brief  cvbchlo - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbchlo"

logical cvb :: cvbchlo ( )
{
  int32     curlen = gvtutle0(cvbsdata,cvbsfmcb->fmcbsize);

  *cvbtdata = !curlen || 
              *cvbsdata  == 'N' || *cvbsdata == 'n'   ||
              *cvbsdata  == 'F' || *cvbsdata == 'f'   ||
              (*cvbsdata == '0' && curlen == 1)
              ? NO : YES;

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbchmm - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbchmm"

logical cvb :: cvbchmm ( )
{

  memcpy(cvbtdata,cvbsdata,MIN(cvbsfmcb->fmcbsize,cvbtfmcb->fmcbsize));

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbchsc - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbchsc"

logical cvb :: cvbchsc ( )
{

  gvtxbtc(cvbtdata,cvbtfmcb->fmcbsize,cvbsdata,cvbsfmcb->fmcbsize);

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbchsr - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbchsr"

logical cvb :: cvbchsr ( )
{

  gvtxbts(cvbtdata,cvbsdata,MIN(cvbsfmcb->fmcbsize,cvbtfmcb->fmcbsize));

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbchst - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbchst"

logical cvb :: cvbchst ( )
{
  smcb     *smcbptr  = cvbtfmcb->fmcbsmcb;
  cvb       convcvb(cvbsfmcb,cvbtfmcb,cvbsdata,cvbtdata);
  char     *buffer   = cvbsdata;
  char     *end;
  ushort    len      = cvbsfmcb->fmcbsize;
  ushort    olen     = len;
  ushort    tlen;
  short int indx     = 0;
  logical   term     = NO;
BEGINSEQ
  cvbtfmcb->fmcbiini(cvbtdata);

  while ( len && (convcvb.cvbtfmcb = smcbptr->GetEntry(++indx)) )
  {
    end = NULL;
    if ( *buffer == '{' )
    {
      if ( end = gvtsfbp(buffer++,len--) )
        tlen = end - buffer - 1;
    }
    else
      if ( smcbptr->smcbfmcl->GetCount() > 1 )
        if ( end = (char *)memchr(buffer,'|',len) )
          tlen = end - buffer;

    if ( !end )
    {
      end = buffer+len;
      tlen = len;
    }
    else
      if ( *end == '|' )
        end++;

    convcvb.cvbsdata = buffer;
    cvbsfmcb->fmcbbyte = (cvbsfmcb->fmcbsize = tlen)*cvbsfmcb->fmcbdim;
    convcvb.cvbtdata = cvbtdata + convcvb.cvbtfmcb->fmcbposn;
    if ( convcvb.cvbconv() )                               ERROR

    len -= end - buffer;
    buffer = end;
  }
RECOVER
  term = YES;

ENDSEQ
  cvbsfmcb->fmcbbyte = (cvbsfmcb->fmcbsize = olen)*cvbsfmcb->fmcbdim;
  return(term);
}

/******************************************************************************/
/**
\brief  cvbchtm - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbchtm"

logical cvb :: cvbchtm ( )
{
  char          string[12];
  register int  size    = MIN(11,cvbsfmcb->fmcbsize);
  gvtxbts(string,cvbsdata,size);
  ((dbtm *)cvbtdata)->FromString(cvbsdata,size,
                                 dfs::GetTimeFormat(string));


  return(NO);

}

/******************************************************************************/
/**
\brief  cvbchui - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbchui"

logical cvb :: cvbchui ( )
{

  return ( cvbchin() );


}

/******************************************************************************/
/**
\brief  cvbconv - 



\return term - Success

\param  replace - Replace option
\param  chkonly - 
\param  copy_type - Copy type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbconv"

logical cvb :: cvbconv (int16 replace, logical chkonly, int16 copy_type )
{
  logical term = NO;
  int     stype = cvbsfmcb->fmcbityp;
  int     ttype = cvbtfmcb->fmcbityp;

BEGINSEQ
  static    CVBFP  fctvect[T_MAX+2][T_MAX+2] = {                                                                                                                                                                                                               
//               STR            CHAR           GUID           INT            UINT           MEMO           VOID           DATE           TIME           LO             STRING         BIT            REAL           DATETIME       CCHAR          BLOB           CODED         
/* STR    */     &cvb::cvbxxyy, &cvb::cvbstch, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbstsr, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbstdm, &cvb::cvbstch, &cvb::cvbxxyy, &cvb::cvbxxyy, 
/* CHAR   */     &cvb::cvbchst, &cvb::cvbchch, &cvb::cvbsrgu, &cvb::cvbchin, &cvb::cvbchui, &cvb::cvbchmm, &cvb::cvbxxyy, &cvb::cvbchdt, &cvb::cvbchtm, &cvb::cvbchlo, &cvb::cvbchsr, &cvb::cvbxxyy, &cvb::cvbchfl, &cvb::cvbchdm, &cvb::cvbchcc, &cvb::cvbxxyy, &cvb::cvbchcd, 
/* GUID   */     &cvb::cvbxxyy, &cvb::cvbgusr, &cvb::cvbgugu, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbgusr, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, 
/* INT    */     &cvb::cvbxxyy, &cvb::cvbinch, &cvb::cvbxxyy, &cvb::cvbinin, &cvb::cvbinui, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbindt, &cvb::cvbintm, &cvb::cvbinlo, &cvb::cvbinsr, &cvb::cvbxxyy, &cvb::cvbinfl, &cvb::cvbxxyy, &cvb::cvbinch, &cvb::cvbxxyy, &cvb::cvbincd, 
/* UNIT   */     &cvb::cvbxxyy, &cvb::cvbuich, &cvb::cvbxxyy, &cvb::cvbuiin, &cvb::cvbuiui, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbindt, &cvb::cvbintm, &cvb::cvbinlo, &cvb::cvbuisr, &cvb::cvbxxyy, &cvb::cvbinfl, &cvb::cvbxxyy, &cvb::cvbuich, &cvb::cvbxxyy, &cvb::cvbincd, 
/* MEMO   */     &cvb::cvbxxyy, &cvb::cvbmmch, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbmmmm, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbmmlo, &cvb::cvbmmsr, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbmmch, &cvb::cvbxxyy, &cvb::cvbxxyy, 
/* VOID   */     &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbvivi, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, 
/* DATE   */     &cvb::cvbxxyy, &cvb::cvbdtch, &cvb::cvbxxyy, &cvb::cvbdtin, &cvb::cvbdtin, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbdtdt, &cvb::cvbxxyy, &cvb::cvbdtlo, &cvb::cvbdtsr, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbdtdm, &cvb::cvbdtch, &cvb::cvbxxyy, &cvb::cvbxxyy, 
/* TIME   */     &cvb::cvbxxyy, &cvb::cvbtmch, &cvb::cvbxxyy, &cvb::cvbtmin, &cvb::cvbtmin, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbtmtm, &cvb::cvbtmlo, &cvb::cvbtmsr, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbtmdm, &cvb::cvbtmch, &cvb::cvbxxyy, &cvb::cvbxxyy, 
/* LO     */     &cvb::cvbxxyy, &cvb::cvbloch, &cvb::cvbxxyy, &cvb::cvbloin, &cvb::cvbloin, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvblolo, &cvb::cvblosr, &cvb::cvbxxyy, &cvb::cvblofl, &cvb::cvbxxyy, &cvb::cvbloch, &cvb::cvbxxyy, &cvb::cvblocd, 
/* STRING */     &cvb::cvbsrst, &cvb::cvbsrch, &cvb::cvbsrgu, &cvb::cvbsrin, &cvb::cvbsrui, &cvb::cvbsrmm, &cvb::cvbxxyy, &cvb::cvbsrdt, &cvb::cvbsrtm, &cvb::cvbsrlo, &cvb::cvbsrsr, &cvb::cvbxxyy, &cvb::cvbchfl, &cvb::cvbsrdm, &cvb::cvbsrcc, &cvb::cvbxxyy, &cvb::cvbsrcd, 
/* BIT    */     &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, 
/* REAL   */     &cvb::cvbxxyy, &cvb::cvbflch, &cvb::cvbxxyy, &cvb::cvbflin, &cvb::cvbflin, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbfllo, &cvb::cvbflch, &cvb::cvbxxyy, &cvb::cvbflfl, &cvb::cvbxxyy, &cvb::cvbflch, &cvb::cvbxxyy, &cvb::cvbflcd, 
/* DATETIME*/    &cvb::cvbdmst, &cvb::cvbdmch, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbdmdt, &cvb::cvbdmtm, &cvb::cvbdmlo, &cvb::cvbdmsr, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbdmdm, &cvb::cvbdmch, &cvb::cvbxxyy, &cvb::cvbxxyy, 
/* CCHAR  */     &cvb::cvbxxyy, &cvb::cvbccch, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbchlo, &cvb::cvbccsr, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbcccc, &cvb::cvbxxyy, &cvb::cvbxxyy, 
/* BLOB   */     &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbblbl, &cvb::cvbxxyy, 
/* CODED  */     &cvb::cvbxxyy, &cvb::cvbcdch, &cvb::cvbxxyy, &cvb::cvbcdin, &cvb::cvbcdin, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbxxyy, &cvb::cvbcdlo, &cvb::cvbcdsr, &cvb::cvbxxyy, &cvb::cvbcdfl, &cvb::cvbxxyy, &cvb::cvbcdch, &cvb::cvbxxyy, &cvb::cvbcdcd, 
                                               };

  if ( cvbsfmcb->fmcbsmcb && cvbsfmcb->fmcbityp != T_DATETIME && 
       cvbsfmcb->fmcbityp != T_MEMO  && cvbsfmcb->fmcbityp != T_BLOB )
    stype = cvbsfmcb->fmcbsmcb->smcbstyp == ST_CODE ? -(T_MAX+1) : 0;

  if ( cvbtfmcb->fmcbsmcb && cvbtfmcb->fmcbityp != T_DATETIME && 
       cvbtfmcb->fmcbityp != T_MEMO  && cvbtfmcb->fmcbityp != T_BLOB )
    ttype = cvbtfmcb->fmcbsmcb->smcbstyp == ST_CODE ? -(T_MAX+1) : 0;

  if ( chkonly )
  {
    if ( fctvect[-stype][-ttype] == &cvb::cvbxxyy || (!stype && !ttype) )
                                                     ERROR
                                                     LEAVESEQ
  }

  if ( cvbsdata == cvbtdata )
  {
    if ( cvbsfmcb->fmcbityp != cvbtfmcb->fmcbityp )  SOSERR(52)
                                                     LEAVESEQ
  }

  if ( cvbsfmcb->fmcbrlev >= 1 || cvbtfmcb->fmcbrlev >= 1 ) 
  {
    if ( cvbsfmcb->fmcbrlev != cvbtfmcb->fmcbrlev )  SOSERR(53)
    memcpy(cvbtdata,cvbsdata,4);
    LEAVESEQ
  }

  if ( (!stype && ttype == -7) || ((!ttype && stype == -7)) )
  {
    if ( cvbtfmcb->DTConversion(cvbsfmcb,cvbsdata,cvbtdata) )
                                                     SOSERR(51)
    LEAVESEQ
  }
  
  if ( stype || ttype )
  {
    if ( (this->*fctvect[-stype][-ttype])() )        SOSERR(51)
  }
  else
  {
    if ( cvbsfmcb->fmcbityp == cvbtfmcb->fmcbityp && cvbtfmcb->fmcbrlev == R_INTERN )  
      memcpy(cvbtdata,cvbsdata,cvbtfmcb->fmcbdim > 0 ? cvbtfmcb->fmcbbyte/cvbtfmcb->fmcbdim : cvbtfmcb->fmcbbyte);
    else
      if ( cvbstst(replace,copy_type) )              ERROR
  }
RECOVER
  if ( SOSERROR )
  {
    SOSError().SetErrorVariable(1,cvbsfmcb->fmcbname,ID_SIZE);
    SOSError().SetErrorVariable(2,cvbsfmcb->fmcbtype,ID_SIZE);
    SOSError().SetErrorVariable(3,cvbtfmcb->fmcbname,ID_SIZE);
    SOSError().SetErrorVariable(4,cvbtfmcb->fmcbtype,ID_SIZE);
  }
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  cvbdmch - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbdmch"

logical cvb :: cvbdmch ( )
{

  return ( cvbstch() );

}

/******************************************************************************/
/**
\brief  cvbdmdm - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbdmdm"

logical cvb :: cvbdmdm ( )
{

  return ( cvbstst() );

}

/******************************************************************************/
/**
\brief  cvbdmdt - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbdmdt"

logical cvb :: cvbdmdt ( )
{
  fmcb     *sfmcb = cvbsfmcb->fmcbsmcb->GetEntry("date");
  logical   term  = NO;

BEGINSEQ
  if ( !sfmcb )
    *((dbdt *)cvbtdata) = (int32)0;
  else
  {
    cvb  convcvb(sfmcb,cvbtfmcb,cvbsdata+sfmcb->fmcbposn,cvbtdata);
    if ( convcvb.cvbconv() )                               ERROR
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  cvbdmlo - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbdmlo"

logical cvb :: cvbdmlo ( )
{

  *cvbtdata = !((dttm *)cvbsdata)->IsEmpty(); 

  return(NO);
}

/******************************************************************************/
/**
\brief  cvbdmsr - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbdmsr"

logical cvb :: cvbdmsr ( )
{

  return ( cvbstsr() );

}

/******************************************************************************/
/**
\brief  cvbdmst - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbdmst"

logical cvb :: cvbdmst ( )
{

  return ( cvbstst() );

}

/******************************************************************************/
/**
\brief  cvbdmtm - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbdmtm"

logical cvb :: cvbdmtm ( )
{
  fmcb     *sfmcb = cvbsfmcb->fmcbsmcb->GetEntry("time");
  logical   term  = NO;

BEGINSEQ
  if ( !sfmcb )
    ((dbtm *)cvbtdata)->Clear();
  else
  {
    cvb  convcvb(sfmcb,cvbtfmcb,cvbsdata+sfmcb->fmcbposn,cvbtdata);
    if ( convcvb.cvbconv() )                               ERROR
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  cvbdtch - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbdtch"

logical cvb :: cvbdtch ( )
{
  char       *data = cvbtdata;
  char        string[11];
  cvbtdata = string;
  cvbdtsr();
  cvbtdata = data;
  gvtxstb(cvbtdata,string,MIN(cvbtfmcb->fmcbsize,10));

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbdtdm - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbdtdm"

logical cvb :: cvbdtdm ( )
{
  fmcb     *tfmcb = cvbtfmcb->fmcbsmcb ? cvbtfmcb->fmcbsmcb->GetEntry("date") : NULL;
  logical   term  = NO;
BEGINSEQ
  if ( !tfmcb )                                      ERROR
    
  cvb  convcvb(cvbsfmcb,tfmcb,cvbsdata,cvbtdata+tfmcb->fmcbposn);
  if ( convcvb.cvbconv() )                           ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  cvbdtdt - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbdtdt"

logical cvb :: cvbdtdt ( )
{

  *(int32 *)cvbtdata = *(int32 *)cvbsdata;

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbdtin - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbdtin"

logical cvb :: cvbdtin ( )
{

  cvbtfmcb->fmcblist(cvbtdata,*(int32 *)cvbsdata);  

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbdtlo - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbdtlo"

logical cvb :: cvbdtlo ( )
{

  *cvbtdata = !((dbdt *)cvbsdata)->IsEmpty(); 

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbdtsr - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbdtsr"

logical cvb :: cvbdtsr ( )
{

  ((dbdt *)cvbsdata)->ToString(cvbtdata,MIN(10,cvbtfmcb->fmcbsize),
                               dfs::GetDateFormat());

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbflcd - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbflcd"

logical cvb :: cvbflcd ( )
{

  double    value = cvbsfmcb->fmcbbyte < 8 ? *(float *)cvbsdata : 
                                             *(double *)cvbsdata;
  if ( cvbtfmcb->fmcbdim )
    cvbtfmcb->fmcblist(cvbtdata,cvbftoi(value));
  

  return(NO);
}

/******************************************************************************/
/**
\brief  cvbflch - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbflch"

logical cvb :: cvbflch ( )
{
  double    value = cvbsfmcb->fmcbbyte == 4 ? *(float *)cvbsdata : 
                                              *(double *)cvbsdata;
  ushort    targlen = cvbtfmcb->fmcbsize;
  char      string[256];
  logical   str     = memcmp(cvbtfmcb->fmcbtype,"CHAR ",5) ? YES : NO;
  logical   term    = NO;

BEGINSEQ
  memset(cvbtdata,str ? 0 : ' ',cvbtfmcb->fmcbbyte);

  if ( targlen < 8 )                                       ERROR

  gcvt(value,MIN(targlen-2,sizeof(string)-10),string);
  if ( strlen(string) > targlen )
    gcvt(value,MIN(targlen-7,sizeof(string)-10),string);

  if ( string[strlen(string)-1] == '.' )
    string[strlen(string)-1] = 0;
    
  if ( str )
    strncpy(cvbtdata,string,cvbtfmcb->fmcbsize);
  else
    gvtxstb(cvbtdata,string,cvbtfmcb->fmcbsize);

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  cvbflfl - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbflfl"

logical cvb :: cvbflfl ( )
{

  switch ( (cvbsfmcb->fmcbbyte == 4)*2 + (cvbtfmcb->fmcbbyte == 4) )
  {
    case 0 : *(double *)cvbtdata = *(double *)cvbsdata;         break;
    case 1 : *(float  *)cvbtdata = (float)*(double *)cvbsdata;  break;
    case 2 : *(double *)cvbtdata = *(float  *)cvbsdata;         break;
    case 3 : *(float  *)cvbtdata = *(float  *)cvbsdata;         break;
    default:;
  }

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbflin - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbflin"

logical cvb :: cvbflin ( )
{

  double    value = cvbsfmcb->fmcbbyte < 8 ? *(float *)cvbsdata : 
                                             *(double *)cvbsdata;
  if ( cvbtfmcb->fmcbdim )
    cvbtfmcb->fmcblist(cvbtdata,cvbftoi(value));
  

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbfllo - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbfllo"

logical cvb :: cvbfllo ( )
{

  double value = cvbsfmcb->fmcbbyte == 4 ? *(float *)cvbsdata : 
                                           *(double *)cvbsdata;
  *cvbtdata = value != 0;

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbftoi - 



\return intval - 

\param  dblval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbftoi"

int64 cvb :: cvbftoi (double dblval )
{

  if ( cvbtfmcb->fmcbprec > 0 )
    dblval *= flval[cvbtfmcb->fmcbprec];
  if ( cvbtfmcb->fmcbprec < 0 )
    dblval /= flval[-cvbtfmcb->fmcbprec];
    
//  if ( realval > chkval[cvbtfmcb->fmcbsize-abs(cvbtfmcb->fmcbprec)] )
  if ( cvbtfmcb->fmcbsize <= 10 && dblval > chkval[cvbtfmcb->fmcbsize] )
    return(INL_UNDEF);

//  if ( realval < -chkval[cvbtfmcb->fmcbsize-abs(cvbtfmcb->fmcbprec)] )
  if ( cvbtfmcb->fmcbsize <= 10 && dblval < -chkval[cvbtfmcb->fmcbsize] )
    return(-INL_UNDEF);

  if ( dblval > 0 )
    dblval += 0.5;
  else 
    dblval -= 0.5;    

  return((int64)dblval);
}

/******************************************************************************/
/**
\brief  cvbgugu - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbgugu"

logical cvb :: cvbgugu ( )
{

  memset(cvbtdata,0,cvbtfmcb->fmcbsize);
  memcpy(cvbtdata,cvbsdata,MIN(cvbsfmcb->fmcbsize,cvbtfmcb->fmcbsize));
  return(NO);


}

/******************************************************************************/
/**
\brief  cvbgusr - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbgusr"

logical cvb :: cvbgusr ( )
{
  guid       *data = (guid *)cvbsdata;
  char        string[sizeof(__guid_string)];
  data->GetString(string);
  strncpy(cvbtdata,string,MIN(cvbtfmcb->fmcbsize,sizeof(string)));
  
  if ( cvbtfmcb->fmcbityp == T_CHAR ) 
    gvtxstb(cvbtdata,cvbtdata,MIN(cvbtfmcb->fmcbsize,sizeof(string)));

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbincd - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbincd"

logical cvb :: cvbincd ( )
{


  cvbtfmcb->fmcblist(cvbtdata,cvbsfmcb->fmcbligt(cvbsdata));

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbinch - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbinch"

logical cvb :: cvbinch ( )
{
  char      string[33];
  int64     value = cvbsfmcb->fmcbligt(cvbsdata);
  ushort    len   = cvbsfmcb->fmcbsize - cvbsfmcb->fmcbprec;
  ushort    len1;
  char     *curpos  = string;
  memset(string,'9',sizeof(string));
  memset(curpos,'Z',len - 1);
  curpos += len;

  if ( cvbsfmcb->fmcbprec )
  {
    *curpos = dfs::GetDecimal();
    curpos += cvbsfmcb->fmcbprec+1;
  }  

  if ( value < 0 )
  {
    *curpos = '-';
    curpos++;
  }

  len1   = curpos-string;
  len    = MIN(len1,cvbtfmcb->fmcbsize);
  curpos = string + MAX(0,len1-len);
  gvtxbtp(curpos,value,len);

  memset(cvbtdata,' ',cvbtfmcb->fmcbsize);
  memcpy(cvbtdata+cvbtfmcb->fmcbsize-len,curpos,len);
  return(NO);

}

/******************************************************************************/
/**
\brief  cvbindt - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbindt"

logical cvb :: cvbindt ( )
{


  *(int32 *)cvbtdata = (int32)cvbsfmcb->fmcbligt(cvbsdata);


  return(NO);

}

/******************************************************************************/
/**
\brief  cvbinfl - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbinfl"

logical cvb :: cvbinfl ( )
{
  double    value;
  if ( cvbsfmcb->fmcbityp == T_INT )
    switch ( cvbsfmcb->fmcbbyte )
    {
      case 1 : value = *cvbsdata;                    break;
      case 2 : value = *(int16 *)cvbsdata;           break;
      case 4 : value = *(int32 *)cvbsdata;           break;
      case 8 : value = *(int64 *)cvbsdata;           break;
      default: value = 0;
    }
  else
    switch ( cvbsfmcb->fmcbbyte )
    {
      case 1 : value = *(uint8 *)cvbsdata;           break;
      case 2 : value = *(uint16 *)cvbsdata;          break;
      case 4 : value = *(uint32 *)cvbsdata;          break;
      case 8 : value = *(int64 *)cvbsdata;           break;
      default: value = 0;
    }

  if ( cvbsfmcb->fmcbprec > 0 )
    value = value / flval[cvbsfmcb->fmcbprec];
  if ( cvbsfmcb->fmcbprec < 0 )
    value = value * flval[-cvbsfmcb->fmcbprec];

  if ( cvbtfmcb->fmcbdim )
  {
    if ( cvbtfmcb->fmcbbyte/cvbtfmcb->fmcbdim < 8 )
      *(float *)cvbtdata  = (float)value;
    else
      *(double *)cvbtdata = value;
  }
  return(NO);

}

/******************************************************************************/
/**
\brief  cvbinin - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbinin"

logical cvb :: cvbinin ( )
{

  return(cvbuiui());


}

/******************************************************************************/
/**
\brief  cvbinlo - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbinlo"

logical cvb :: cvbinlo ( )
{

  *cvbtdata = (cvbsfmcb->fmcbligt(cvbsdata) != 0);

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbinsr - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbinsr"

logical cvb :: cvbinsr ( )
{
  char     *curpos = cvbtdata;
  logical   sign;
  if ( cvbinch() )
    return(YES);

  sign = ( *(cvbtdata+cvbtfmcb->fmcbsize-1) == '-' ) ? YES : NO;
  *(cvbtdata+cvbtfmcb->fmcbsize-sign) = 0;

  while ( *curpos == ' ' )
    curpos++;

  gvtssdl(cvbtdata,curpos-cvbtdata);
  if ( sign )
    gvtssin(cvbtdata,"-",cvbtfmcb->fmcbsize);


  return(NO);

}

/******************************************************************************/
/**
\brief  cvbintm - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbintm"

logical cvb :: cvbintm ( )
{

  *(int32 *)cvbtdata = (int32)cvbsfmcb->fmcbligt(cvbsdata);
  return(NO);

}

/******************************************************************************/
/**
\brief  cvbinui - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbinui"

logical cvb :: cvbinui ( )
{

  return(cvbuiui());


}

/******************************************************************************/
/**
\brief  cvblocd - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvblocd"

logical cvb :: cvblocd ( )
{


  cvbtfmcb->fmcblist(cvbtdata,cvbsfmcb->fmcbligt(cvbsdata));

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbloch - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbloch"

logical cvb :: cvbloch ( )
{

  memset(cvbtdata,' ',cvbtfmcb->fmcbsize);     // 21.6.99
  
  switch ( dfs::GetLanguage() )
  {
    case DFS_Deutsch : *cvbtdata = *cvbsdata ? 'J' : 'N';
                       break;
    default          : *cvbtdata = *cvbsdata ? 'Y' : 'N';
  }

  return(NO);

}

/******************************************************************************/
/**
\brief  cvblofl - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvblofl"

logical cvb :: cvblofl ( )
{

  if ( cvbtfmcb->fmcbbyte == 4 )
    *(float *)cvbtdata = *cvbsdata ? 1 : 0;
  else
    *(double *)cvbtdata = *cvbsdata ? 1 : 0;


  return(NO);

}

/******************************************************************************/
/**
\brief  cvbloin - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbloin"

logical cvb :: cvbloin ( )
{
  logical   term = NO;
BEGINSEQ
  switch ( cvbtfmcb->fmcbbyte )
  {
    case 1  : *cvbtdata = *cvbsdata ? 1 : 0;               break;
    case 2  : *(int16 *)cvbtdata = *cvbsdata ? 1 : 0;      break;
    case 4  : *(int32 *)cvbtdata = *cvbsdata ? 1 : 0;      break;
    case 8  : *(int64 *)cvbtdata = *cvbsdata ? 1 : 0;      break;
    default : ERROR
  }


RECOVER
  term = YES;
ENDSEQ
  return(NO);

}

/******************************************************************************/
/**
\brief  cvblolo - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvblolo"

logical cvb :: cvblolo ( )
{

  *cvbtdata = *cvbsdata;

  return(NO);

}

/******************************************************************************/
/**
\brief  cvblosr - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvblosr"

logical cvb :: cvblosr ( )
{

  memset(cvbtdata,0,cvbtfmcb->fmcbbyte);

  return(cvbloch());

}

/******************************************************************************/
/**
\brief  cvbmmch - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbmmch"

logical cvb :: cvbmmch ( )
{

  memset(cvbtdata,' ',cvbtfmcb->fmcbsize);

  if ( cvbsdata )
    gvtxstb(cvbtdata,cvbsdata,MIN(cvbsfmcb->fmcbsize,cvbtfmcb->fmcbsize));


  return(NO);

}

/******************************************************************************/
/**
\brief  cvbmmlo - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbmmlo"

logical cvb :: cvbmmlo ( )
{

  *cvbtdata = (gvtutle0(cvbsdata,cvbsfmcb->fmcbsize) != 0);

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbmmmm - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbmmmm"

logical cvb :: cvbmmmm ( )
{

  memset(cvbtdata,0,cvbtfmcb->fmcbsize);  
  memcpy(cvbtdata,cvbsdata,MIN(cvbsfmcb->fmcbsize,cvbtfmcb->fmcbsize));

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbmmsr - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbmmsr"

logical cvb :: cvbmmsr ( )
{

  ushort len = gvtutle0(cvbsdata,cvbsfmcb->fmcbsize);
  gvtxbts(cvbtdata,cvbsdata,MIN(len,cvbtfmcb->fmcbsize));

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbscch - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbscch"

logical cvb :: cvbscch ( )
{

  gvtxctb(cvbtdata,cvbtfmcb->fmcbsize,cvbsdata,cvbsfmcb->fmcbsize);

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbscsr - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbscsr"

logical cvb :: cvbscsr ( )
{

  gvtxctb(cvbtdata,cvbtfmcb->fmcbsize,cvbsdata,cvbsfmcb->fmcbsize);

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbsrcc - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbsrcc"

logical cvb :: cvbsrcc ( )
{

  gvtxbtc(cvbtdata,cvbtfmcb->fmcbsize,cvbsdata,cvbsfmcb->fmcbsize);

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbsrcd - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbsrcd"

logical cvb :: cvbsrcd ( )
{

  return ( cvbchcd() );


}

/******************************************************************************/
/**
\brief  cvbsrch - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbsrch"

logical cvb :: cvbsrch ( )
{

  memset(cvbtdata,' ',cvbtfmcb->fmcbsize);
  gvtxstb(cvbtdata,cvbsdata,MIN(cvbsfmcb->fmcbsize,cvbtfmcb->fmcbsize));

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbsrdm - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbsrdm"

logical cvb :: cvbsrdm ( )
{

  return ( cvbsrst() );

}

/******************************************************************************/
/**
\brief  cvbsrdt - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbsrdt"

logical cvb :: cvbsrdt ( )
{
  ushort    len = cvbsfmcb->fmcbsize;
  logical   term;
  cvbsfmcb->fmcbsize = MIN(len,strlen(cvbsdata));
  term = cvbchdt();
  cvbsfmcb->fmcbsize = len;


  return (term);

}

/******************************************************************************/
/**
\brief  cvbsrgu - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbsrgu"

logical cvb :: cvbsrgu ( )
{
  guid        data;
  char        string[sizeof(__guid_string)];
  memset(string,0,sizeof(string));
  strncpy(string,cvbsdata,MIN(cvbsfmcb->fmcbsize,sizeof(string)));
  data.Initialize(string);
  
  memcpy(cvbtdata,&data,MIN(cvbtfmcb->fmcbsize,sizeof(data)));

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbsrin - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbsrin"

logical cvb :: cvbsrin ( )
{

  return ( cvbchin() );


}

/******************************************************************************/
/**
\brief  cvbsrlo - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbsrlo"

logical cvb :: cvbsrlo ( )
{

//  *cvbtdata = *cvbsdata ? YES : NO;
  return(cvbchlo());


}

/******************************************************************************/
/**
\brief  cvbsrmm - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbsrmm"

logical cvb :: cvbsrmm ( )
{
  ulong   len = strlen(cvbsdata);

  if ( len > cvbsfmcb->fmcbsize )
    len = cvbsfmcb->fmcbsize;
    
  memcpy(cvbtdata,cvbsdata,MIN(len,cvbtfmcb->fmcbsize));

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbsrsc - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbsrsc"

logical cvb :: cvbsrsc ( )
{

  gvtxbtc(cvbtdata,cvbtfmcb->fmcbsize,cvbsdata,cvbsfmcb->fmcbsize);

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbsrsr - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbsrsr"

logical cvb :: cvbsrsr ( )
{
  int    len = MIN(cvbsfmcb->fmcbsize,cvbtfmcb->fmcbsize);
//  gvtxbts(cvbtdata,cvbsdata,MIN(cvbsfmcb->fmcbsize,cvbtfmcb->fmcbsize));
  strncpy(cvbtdata,cvbsdata,len);
  cvbtdata[len] = 0;
  return(NO);

}

/******************************************************************************/
/**
\brief  cvbsrst - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbsrst"

logical cvb :: cvbsrst ( )
{
  ushort    size = cvbsfmcb->fmcbsize; 
  logical   term;

  cvbsfmcb->fmcbityp = T_CHAR;
  cvbsfmcb->fmcbsize = MIN(strlen(cvbsdata),cvbsfmcb->fmcbsize);
  cvbsfmcb->fmcbbyte = cvbsfmcb->fmcbsize;

  term = cvbchst();

  cvbsfmcb->fmcbsize = size;
  cvbsfmcb->fmcbbyte = (size+1)*cvbsfmcb->fmcbdim;
  cvbsfmcb->fmcbityp = T_STRING;


  return(term);

}

/******************************************************************************/
/**
\brief  cvbsrtm - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbsrtm"

logical cvb :: cvbsrtm ( )
{
  ushort    len = cvbsfmcb->fmcbsize;
  logical   term;
  cvbsfmcb->fmcbsize = MIN(len,strlen(cvbsdata));
  term = cvbchtm();
  cvbsfmcb->fmcbsize = len;


  return (term);

}

/******************************************************************************/
/**
\brief  cvbsrui - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbsrui"

logical cvb :: cvbsrui ( )
{

  return ( cvbchin() );


}

/******************************************************************************/
/**
\brief  cvbstch - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbstch"

logical cvb :: cvbstch ( )
{
  smcb     *smcbptr  = cvbsfmcb->fmcbsmcb;
  cvb       convcvb(cvbsfmcb,cvbtfmcb,cvbsdata,cvbtdata);
  char     *buffer   = cvbtdata;
  uint16    targolen = cvbtfmcb->fmcbsize;
  uint16    targobyt = cvbtfmcb->fmcbbyte;
  int16     len      = cvbtfmcb->fmcbsize;
  int16     tlen;
  int16     indx     = 0;
  logical   term     = NO;

BEGINSEQ
  memset(buffer,' ',len);
  
  while ( len > 0 && (convcvb.cvbsfmcb = smcbptr->GetEntry(++indx)) )
  {
    convcvb.cvbsdata = cvbsdata + convcvb.cvbsfmcb->fmcbposn;
    convcvb.cvbtdata = buffer;
    tlen = MIN(len,convcvb.cvbsfmcb->GetCharLength());
    convcvb.cvbtfmcb->fmcbsize = convcvb.cvbtfmcb->fmcbbyte = tlen;

    if ( convcvb.cvbconv() )                               ERROR
    buffer += tlen;
    len    -= tlen;
  }

RECOVER
  term = YES;
ENDSEQ
  cvbtfmcb->fmcbsize = targolen;
  cvbtfmcb->fmcbbyte = targobyt;
  return(term);

}

/******************************************************************************/
/**
\brief  cvbstdm - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbstdm"

logical cvb :: cvbstdm ( )
{

  return ( cvbstst() );

}

/******************************************************************************/
/**
\brief  cvbstsr - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbstsr"

logical cvb :: cvbstsr ( )
{
  smcb     *smcbptr  = cvbsfmcb->fmcbsmcb;
  cvb       convcvb(cvbsfmcb,cvbtfmcb,cvbsdata,cvbtdata);
  char     *buffer   = cvbtdata;
  ushort    targolen = cvbtfmcb->fmcbsize;
  ushort    targobyt = cvbtfmcb->fmcbbyte;
  short int len      = cvbtfmcb->fmcbsize;
  short int tlen;
  short int indx     = 0;
  logical   braces;    
  logical   term     = NO;

BEGINSEQ
  memset(buffer,' ',len);
  
  while ( len > 0 && (convcvb.cvbsfmcb = smcbptr->GetEntry(++indx)) )
  {
    if ( convcvb.cvbsfmcb->fmcbrlev > 0 || convcvb.cvbsfmcb->fmcbrlev == R_REFR )
    {
      if ( indx > 1 )
      {
        *buffer = '|';
        buffer++;
        len--;
      }
      memcpy(buffer,convcvb.cvbsfmcb->fmcbrlev == R_REFR ? "(REF)" : "(PTR)",MIN(len,5));
      buffer += MIN(len,5);
      len -= MIN(len,5);
    }
    else
    {
      braces = ( convcvb.cvbsfmcb->fmcbstpg() == ST_USER || 
                 convcvb.cvbsfmcb->fmcbstpg() == ST_KEY  || 
                 convcvb.cvbsfmcb->fmcbstpg() == ST_SYS     ) &&
               convcvb.cvbsfmcb->fmcbsmcb->smcbfmcl->GetCount() > 1;
             
      if ( indx > 1 )
      {
        *buffer = '|';
        buffer++;
        len--;
      }

      if ( len > 0 && braces )
      {
        *buffer = '{';
        buffer++;
        len--;
      }
    
      convcvb.cvbsdata = cvbsdata + convcvb.cvbsfmcb->fmcbposn;
      convcvb.cvbtdata = buffer;
      convcvb.cvbtfmcb->fmcbsize = len;
      convcvb.cvbtfmcb->fmcbbyte = len+1;

      if ( convcvb.cvbconv() )                               ERROR
      tlen = MIN(len,strlen(buffer));
      buffer += tlen;
      len    -= tlen;

      if ( braces && len > 0 )
      { 
        *buffer = '}';
        buffer++;
        *buffer = 0;
        len--;
      }
    }
  }

RECOVER
  term = YES;
ENDSEQ
  cvbtfmcb->fmcbsize = targolen;
  cvbtfmcb->fmcbbyte = targobyt;
  return(term);

}

/******************************************************************************/
/**
\brief  cvbstst - 



\return term - Success

\param  replace - Replace option
\param  copy_type - Copy type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbstst"

logical cvb :: cvbstst (int16 replace, int16 copy_type )
{

  return(cvbtfmcb->fmcbsmcb->CopyInstance(cvbtdata,cvbsfmcb->fmcbsmcb,cvbsdata,
                                          replace,copy_type));


}

/******************************************************************************/
/**
\brief  cvbtmch - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbtmch"

logical cvb :: cvbtmch ( )
{
  char       *data = cvbtdata;
  char        string[12];
  cvbtdata = string;
  cvbtmsr();
  cvbtdata = data;
  gvtxbts(cvbtdata,string,MIN(cvbtfmcb->fmcbsize,11));

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbtmdm - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbtmdm"

logical cvb :: cvbtmdm ( )
{
  fmcb     *tfmcb = cvbtfmcb->fmcbsmcb ? cvbtfmcb->fmcbsmcb->GetEntry("time") : NULL;
  logical   term  = NO;
BEGINSEQ
  if ( !tfmcb )                                      ERROR
    
  cvb  convcvb(cvbsfmcb,tfmcb,cvbsdata,cvbtdata+tfmcb->fmcbposn);
  if ( convcvb.cvbconv() )                           ERROR


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  cvbtmin - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbtmin"

logical cvb :: cvbtmin ( )
{

  cvbtfmcb->fmcblist(cvbtdata,*(int32 *)cvbsdata);

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbtmlo - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbtmlo"

logical cvb :: cvbtmlo ( )
{

  *cvbtdata = !((dbtm *)cvbsdata)->IsEmpty(); 

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbtmsr - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbtmsr"

logical cvb :: cvbtmsr ( )
{

  ((dbtm *)cvbsdata)->ToString(cvbtdata,MIN(12,cvbtfmcb->fmcbsize),
                               dfs::GetTimeFormat());
  

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbtmtm - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbtmtm"

logical cvb :: cvbtmtm ( )
{

  *(int32 *)cvbtdata = *(int32 *)cvbsdata;

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbuich - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbuich"

logical cvb :: cvbuich ( )
{

  return( cvbinch() );


}

/******************************************************************************/
/**
\brief  cvbuiin - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbuiin"

logical cvb :: cvbuiin ( )
{

  return(cvbuiui());


}

/******************************************************************************/
/**
\brief  cvbuisr - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbuisr"

logical cvb :: cvbuisr ( )
{

  return ( cvbinsr() );


}

/******************************************************************************/
/**
\brief  cvbuiui - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbuiui"

logical cvb :: cvbuiui ( )
{

  cvbtfmcb->fmcblist(cvbtdata,cvbxpru(cvbsfmcb->fmcbligt(cvbsdata)));



  return(NO);

}

/******************************************************************************/
/**
\brief  cvbvivi - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbvivi"

logical cvb :: cvbvivi ( )
{

  *(void **)cvbtdata = *(void **)cvbsdata;

  return(NO);

}

/******************************************************************************/
/**
\brief  cvbxpru - 



\return lival - 

\param  val64 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbxpru"

int64 cvb :: cvbxpru (int64 val64 )
{
  int       prec  = cvbtfmcb->fmcbprec - cvbsfmcb->fmcbprec;

  if ( prec > 0 )
    val64 = val64 * expval[prec];
  if ( prec < 0 )
    val64 = val64 / expval[-prec];

  return(val64);

}

/******************************************************************************/
/**
\brief  cvbxxyy - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cvbxxyy"

logical cvb :: cvbxxyy ( )
{

  SOSSET(50)
  return(YES);


}


