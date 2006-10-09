/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    sImportProtokoll

\brief    


\date     $Date: 2006/06/29 15:00:55,09 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sImportProtokoll_HPP
#define   sImportProtokoll_HPP

class     sImportProtokoll;

#include  <sCTX_Structure.hpp>
class  sImportProtokoll :protected CTX_Structure
{

public     :
public     :                                        int32 Create (CTX_Structure **ctx_str_ptrp );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical ImportXMLActions ( );
public     :                                             sImportProtokoll ( );
public     : virtual                                     ~sImportProtokoll ( );
};

#endif
