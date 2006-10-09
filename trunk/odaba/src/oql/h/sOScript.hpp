/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/10|23:48:19,31}|(REF)
\class    OScript

\brief    


\date     $Date: 2006/04/12 11:37:28,54 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OScript_HPP
#define   OScript_HPP

class     OScript;

class     BNFData;
class     ParmList;
#include  <sOPDecl.hpp>
#include  <sOSchema.hpp>
class  OScript :public OSchema,
public OPDecl
{
protected  :         OperationHandle                              main_function;                                             // 
public     :         OperationHandle            &get_main_function() { return(main_function); }
public     :         OQLImpExp                   logical Execute (char *entry_point, ParmList *parmlist );
public     :                                     logical LoadDebugInfo (BNFData *bdata );
public     :                                     logical LoadDefinition (BNFData *bdata );
public     :                                     logical LoadFile (BNFData *bdata );
public     :                                     logical LoadScript (BNFData *bdata );
public     :         OQLImpExp                                           OScript (char *script_path, char *ini_file, char *dict_path );
public     :         OQLImpExp                                           ~OScript ( );
};

#endif
