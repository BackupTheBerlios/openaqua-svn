/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ExtentCacheKey

\brief    


\date     $Date: 2006/03/13 21:33:39,09 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ExtentCacheKey_HPP
#define   ExtentCacheKey_HPP

class     ExtentCacheKey;

#include  <sDBObjectHandle.hpp>
#include  <sExtentCacheKey.hpp>
class  ExtentCacheKey
{
public     :         DBObjectHandle                               db;                                                        //
public     :         std_string                                   name;                                                      //

public     :
public     :                                                             ExtentCacheKey (DBObjectHandle &_obhandle, const std_string &rcsName );
public     :                                     logical operator== (const ExtentCacheKey &rcExtentCacheKey );
};

#endif
