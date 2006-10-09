/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OScriptFile

\brief    


\date     $Date: 2006/03/12 19:20:16,85 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OScriptFile_HPP
#define   OScriptFile_HPP

class     OScriptFile;

class     BNFParser;
#include  <sBNFData.hpp>
class  OScriptFile
{
protected  :         char                                        *expression;                                                //
protected  :         BNFData                                     *bnf_data;                                                  //
protected  :         char                                        *path;                                                      //

public     :
                     BNFData                                     *get_bnf_data() { return(bnf_data); }
                     char                                        *get_path() { return(path); }
public     :                                                             OScriptFile (char *script_path, BNFParser *parser, char *symbol );
public     :                                                             ~OScriptFile ( );
};

#endif
