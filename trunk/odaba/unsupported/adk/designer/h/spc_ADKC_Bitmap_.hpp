/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    pc_ADKC_Bitmap_



\date     $Date: 2006/03/12 19:36:42,59 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ADKC_Bitmap__HPP
#define   pc_ADKC_Bitmap__HPP

class     pc_ADKC_Bitmap_;

#include  <cPIACC.h>
#include  <sDBObjectHandle.hpp>
#include  <sPropertyHandle.hpp>
class  pc_ADKC_Bitmap_ :public PropertyHandle
{

public     :
public     :                                     logical DefineFromList (srt *srtptr, char *sysvar, char *filext );
public     :                                                             pc_ADKC_Bitmap_ (DBObjectHandle &obhandle, PIACC accopt );
};

#endif
