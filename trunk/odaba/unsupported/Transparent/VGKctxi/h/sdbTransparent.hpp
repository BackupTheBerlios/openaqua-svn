/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    dbTransparent

\brief    


\date     $Date: 2006/07/21 14:19:49,73 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   dbTransparent_HPP
#define   dbTransparent_HPP

class     dbTransparent;

class  dbTransparent :public CTX_DataBase
{

public     :
public     :                                        int32 Create (CTX_DataBase **ctx_db_ptrp );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical ImportImportProtokoll ( );
public     :                                        logical ImportOpenXMLActions ( );
public     :                                        logical ImportStammdaten ( );
public     :                                        logical ImportXMLActions ( );
public     :                                        logical InitializeImportXMLActions ( );
public     :                                             dbTransparent ( );
public     : virtual                                     ~dbTransparent ( );
};

#endif
