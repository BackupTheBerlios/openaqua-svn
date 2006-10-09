/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/06|19:43:10,20}|(REF)
\class    sDSC_Concept

\brief    


\date     $Date: 2006/04/13 13:53:06,81 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sDSC_Concept_HPP
#define   sDSC_Concept_HPP

class     sDSC_Concept;

class     CTX_Structure;
#include  <ssLanguageDependend.hpp>
#pragma pack(8)

class  sDSC_Concept :public sLanguageDependend
{
protected  :         int32                                        old_order ATTR_ALIGN(4);                                   

public     :
public     :                                     int32 Create (CTX_Structure **strctx_ptrp );
public     : virtual                             logical SetLanguage ( );
public     :                                                             sDSC_Concept ( );
public     :                                                             ~sDSC_Concept ( );
};

#pragma pack()
#endif
