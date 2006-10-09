/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    DBViewPath

\brief    


\date     $Date: 2006/08/25 15:14:11,04 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBViewPath_HPP
#define   DBViewPath_HPP

class     DBViewPath;

class     BNFData;
class     DBStructDef;
class     ODC_ViewPath;
class  DBViewPath
{
protected  :         DBStructDef                                 *struct_def;                                                // 
protected  :         char                                         name[41];                                                  // 
protected  :         char                                         struct_name[40];                                           // 
protected  :         char                                        *path;                                                      // 

public     :
                     char                                        *get_name() { return(name); }
                     char                                        *get_struct_name() { return(struct_name); }
                     char                                        *get_path() { return(path); }
public     :                                             DBViewPath (DBStructDef *strdef, PropertyHandle &ph );
public     :                                             DBViewPath (DBStructDef *strdef, BNFData *bnf_data, int32 indx0 );
public     :                                             DBViewPath (DBStructDef *strdef );
public     :                                        void Initialize (PropertyHandle &ph );
public     :                                        void Initialize (BNFData *bnf_data, int32 indx0 );
public     :                                             ~DBViewPath ( );
};

#endif
