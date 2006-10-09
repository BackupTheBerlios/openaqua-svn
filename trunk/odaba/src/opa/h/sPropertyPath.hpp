/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    PropertyPath

\brief    


\date     $Date: 2006/03/12 19:13:46,59 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   PropertyPath_HPP
#define   PropertyPath_HPP

class     PropertyPath;

class     DBStructDef;
#pragma pack(8)

class  PropertyPath
{
protected  :         DBStructDef                                 *struct_ref;                                                //
protected  :         char                                         name[82];                                                  //
protected  :         int32                                        index;                                                     //
protected  :         char                                         attr_type[33];                                             //
protected  :         int32                                        reserve;                                                   //

public     :
                     DBStructDef                                 *get_struct_ref() { return(struct_ref); }
                     char                                        *get_name() { return(name); }
                     int32                                        get_index() { return(index); }
                     char                                        *get_attr_type() { return(attr_type); }
                     int32                                        get_reserve() { return(reserve); }
};

#pragma pack()
#endif
