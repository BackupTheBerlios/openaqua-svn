/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pc1_ADKC_Bitmap



\date     $Date: 2006/05/23 13:05:47,04 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc1_ADKC_Bitmap_HPP
#define   pc1_ADKC_Bitmap_HPP

class     pc1_ADKC_Bitmap;

#include  <sDBObjectHandle.hpp>
#include  <sPropertyHandle.hpp>
class  pc1_ADKC_Bitmap :public PropertyHandle
{

public     :
public     :                                        logical DefineFromList (srt *srtptr, char *sysvar, char *filext );
public     :                                             pc1_ADKC_Bitmap (DBObjectHandle &obhandle, PIACC accopt );
};

#endif
