/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/10|23:48:19,31}|(REF)
\class    ExtentList



\date     $Date: 2006/04/15 18:15:50,57 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   _OqlExtentList_HPP
#define   _OqlExtentList_HPP

class     OqlExtentList;

#ifndef   DLL_PropertyHandle_HPP
#define   DLL_PropertyHandle_HPP
#include  <sPropertyHandle.hpp>
#include  <sDLL.h>
#endif
class  OqlExtentList :public DLL(PropertyHandle)
{

public     :
public     :                                     void Add (PropertyHandle &ph );
public     :                                                             OqlExtentList ( );
public     :                                     void Remove (PropertyHandle &ph );
public     :                                     void Reset ( );
public     :                                                             ~OqlExtentList ( );
};

#endif //_OqlExtentList_HPP
