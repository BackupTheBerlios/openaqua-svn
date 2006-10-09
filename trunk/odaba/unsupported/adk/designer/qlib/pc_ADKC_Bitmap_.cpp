/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    pc_ADKC_Bitmap_



\date     $Date: 2006/03/12 19:37:36,78 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_ADKC_Bitmap_"

#include  <pdesign.h>
#include  <spc_ADKC_Bitmap_.hpp>


/******************************************************************************/
/**
\brief  DefineFromList - 


\return term -

\param  srtptr -
\param  sysvar -
\param  filext -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DefineFromList"

logical pc_ADKC_Bitmap_ :: DefineFromList (srt *srtptr, char *sysvar, char *filext )
{
  char              *name;
  char              *pkt;
  char               string[1000];
  int32              indx0 = 0;
  logical            term  = NO;
  while ( name = (char *)srtptr->srtigt(++indx0) )
  {
    if ( pkt = strchr(name,'.') )
      *pkt = 0;
    PropertyHandle  skey(strcat(strcat(strcpy(string,sysvar),"_"),name));
    if ( pkt )
      *pkt = '.';
      
    if ( !Get(skey) )
    {
      Add(skey);
      *GPH("inaktiv_bitmap.path") = strcat(strcat(strcat(strcpy(string,"%"),sysvar),"%"),name);
    }

  }

  return(term);
}

/******************************************************************************/
/**
\brief  pc_ADKC_Bitmap_ - 



\param  obhandle -
\param  accopt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ADKC_Bitmap_"

                        pc_ADKC_Bitmap_ :: pc_ADKC_Bitmap_ (DBObjectHandle &obhandle, PIACC accopt )
                     : PropertyHandle (obhandle,"ADKC_Bitmap",accopt)
{



}


