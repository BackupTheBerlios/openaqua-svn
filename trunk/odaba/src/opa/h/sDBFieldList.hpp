/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    DBFieldList

\brief    


\date     $Date: 2006/06/04 13:12:20,48 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBFieldList_HPP
#define   DBFieldList_HPP

class     DBFieldList;

class     DBFieldDef;
class     DBFieldList;
class     DBStructDef;
class     Dictionary;
#include  <sFieldList.hpp>
#pragma pack(8)

class  DBFieldList :public FieldList
{

public     :
public     : static                                 DBFieldList *__cdecl Create (Dictionary *dictptr, DBStructDef *strdef_ptr, char *pathes );
public     : static                                 DBFieldList *__cdecl Create (Dictionary *dictptr, DBFieldDef *field_def );
public     :                  OPAImpExp             DBFieldDef *CreateField ( );
public     :                  OPAImpExp             DBFieldDef *CreateField (int32 lindx );
public     :                  OPAImpExp                  DBFieldList (int16 memcnt );
public     :                  OPAImpExp                  DBFieldList ( );
public     :                  OPAImpExp             DBFieldDef *GetEntry (int16 indx );
public     :                  OPAImpExp                  ~DBFieldList ( );
};

#pragma pack()
#endif
