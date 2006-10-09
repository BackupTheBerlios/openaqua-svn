/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/06|19:43:10,20}|(REF)
\class    sLanguageDependend

\brief    


\date     $Date: 2006/04/13 13:49:38,82 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sLanguageDependend_HPP
#define   sLanguageDependend_HPP

class     sLanguageDependend;

class     PropertyHandle;
#include  <sCTX_Structure.hpp>
#pragma pack(8)

class  sLanguageDependend :public CTX_Structure
{
protected  :         PropertyHandle                              *languages ATTR_ALIGN(4);                                   
protected  :         int32                                        language;                                                  
protected  :         int32                                        old_language;                                              

public     :
                     int32                                        get_language() { return(language); }
                     int32                                        get_old_language() { return(old_language); }
public     :                                     int32 Create (CTX_Structure **strctx_ptrp );
public     : virtual OPSImpExp                   logical DBCreated ( );
public     : virtual OPSImpExp                   logical DBOpened ( );
public     : virtual OPSImpExp                   logical DBRead ( );
public     : virtual OPSImpExp                   logical SetLanguage ( );
public     :         OPSImpExp                                           sLanguageDependend ( );
public     : virtual OPSImpExp                                           ~sLanguageDependend ( );
};

#pragma pack()
#endif
