/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/06|19:43:10,20}|(REF)
\class    sDSC_Topic

\brief    


\date     $Date: 2006/04/13 13:52:26,09 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sDSC_Topic_HPP
#define   sDSC_Topic_HPP

class     sDSC_Topic;

class     CTX_Structure;
#include  <ssLanguageDependend.hpp>
#pragma pack(8)

class  sDSC_Topic :public sLanguageDependend
{
protected  :         int32                                        old_order ATTR_ALIGN(4);                                   

public     :
public     :                                     int32 Create (CTX_Structure **strctx_ptrp );
public     : virtual                             logical SetLanguage ( );
public     :                                                             sDSC_Topic ( );
public     : virtual                                                     ~sDSC_Topic ( );
};

#pragma pack()
#endif
