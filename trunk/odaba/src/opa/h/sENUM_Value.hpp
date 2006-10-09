/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/06|19:43:10,20}|(REF)
\class    ENUM_Value



\date     $Date: 2006/04/13 15:07:41,28 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ENUM_Value_HPP
#define   ENUM_Value_HPP

class     ENUM_Value;

#include  <sPropertyHandle.hpp>
#pragma pack(8)

class  ENUM_Value
{
public     :         int64                                        id;                                                        
public     :         int32                                        code;                                                      
public     :         char                                         name[40];                                                  
public     :         char                                        *type;                                                      
public     :         char                                        *display_name;                                              
public     :         char                                        *title;                                                     
public     :         char                                        *description;                                               
public     :         PropertyHandle                               values;                                                    

public     :
public     :                                     void Clear ( );
public     :                                     logical CreateSubList (PropertyHandle *parent_ph );
public     :                                                             ENUM_Value (int32 cval, char *cname, char *btype, char *clabel, char *ctitle, char *cdescr );
public     :                                                             ENUM_Value (PropertyHandle *val_ph );
public     :                                                             ENUM_Value ( );
public     :                                     logical Initialize (PropertyHandle *val_ph );
public     :                                     logical Initialize (int32 cval, char *cname, char *btype, char *clabel, char *ctitle, char *cdescr );
public     :                                     logical ReleaseEntry ( );
public     :                                                             ~ENUM_Value ( );
};

#pragma pack()
#endif
