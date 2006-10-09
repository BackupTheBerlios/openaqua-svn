/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pc1_ADKC_Bitmap



\date     $Date: 2006/05/23 13:05:48,20 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc1_ADKC_Bitmap"

#include  <pdesign.h>
#include  <spc1_ADKC_Bitmap.hpp>


/******************************************************************************/
/**
\brief  DefineFromList

\return term - 

\param  srtptr
\param  sysvar
\param  filext
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DefineFromList"

logical pc1_ADKC_Bitmap :: DefineFromList (srt *srtptr, char *sysvar, char *filext )
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
\brief  pc1_ADKC_Bitmap


\param  obhandle
\param  accopt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc1_ADKC_Bitmap"

     pc1_ADKC_Bitmap :: pc1_ADKC_Bitmap (DBObjectHandle &obhandle, PIACC accopt )
                     : PropertyHandle (obhandle,"ADKC_Bitmap",accopt)
{



}


