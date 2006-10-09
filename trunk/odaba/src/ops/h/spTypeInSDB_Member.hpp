/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    pTypeInSDB_Member

\brief    


\date     $Date: 2006/03/13 21:30:14,71 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pTypeInSDB_Member_HPP
#define   pTypeInSDB_Member_HPP

class     pTypeInSDB_Member;

#include  <sCTX_Property.hpp>
class  pTypeInSDB_Member :public CTX_Property
{

public     :
public     :                                     int32 Create (CTX_Property **propctx_ptrp );
public     :                                     logical DBOpened ( );
public     :                                                             pTypeInSDB_Member ( );
public     :                                                             ~pTypeInSDB_Member ( );
};

#endif
