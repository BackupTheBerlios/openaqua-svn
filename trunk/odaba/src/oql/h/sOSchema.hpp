/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OSchema

\brief    


\date     $Date: 2006/03/12 19:20:15,96 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSchema_HPP
#define   OSchema_HPP

class     OSchema;

#ifndef   DLL_OScriptFile_HPP
#define   DLL_OScriptFile_HPP
#include  <sOScriptFile.hpp>
#include  <sDLL.h>
#endif
class     BNFData;
class     BNFParser;
class     OScriptFile;
class     SchemaResources;
class  OSchema
{
protected  :         SchemaResources                             *resources;                                                 //
protected  :         BNFParser                                   *parser;                                                    //
protected  :         DLL(OScriptFile)                             file_list;                                                 //
protected  :         DictionaryHandle                             dictionary;                                                //
protected  :         DatabaseHandle                               resdb;                                                     //
protected  :         DatabaseHandle                               database;                                                  

public     :
                     SchemaResources                             *get_resources() { return(resources); }
                     BNFParser                                   *get_parser() { return(parser); }
                     DictionaryHandle                            &get_dictionary() { return(dictionary); }
                     DatabaseHandle                              &get_resdb() { return(resdb); }
                     DatabaseHandle                              &get_database() { return(database); }
public     :         OQL7ImpExp                  logical LoadSchema ( );
public     :                                     OScriptFile *LocateFile (char *script_path );
public     :         OQL7ImpExp                                          OSchema (char *script_path, char *ini_file, char *dict_path, char *applname="ODL" );
public     :                                     logical Open (char *dict_path );
public     :                                     OScriptFile *ParseFile (char *script_path, char *symbol );
public     :         OQL7ImpExp                                          ~OSchema ( );
};

#endif
