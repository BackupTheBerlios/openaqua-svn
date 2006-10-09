/********************************* Class Declaration ***************************/
/**
\package  OQL - 
\class    CLICollection

\brief    


\date     $Date: 2006/08/28 14:27:20,37 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CLICollection_HPP
#define   CLICollection_HPP

class     CLICollection;

#ifndef   DPA_char_HPP
#define   DPA_char_HPP
#include  <sDPA.h>
#endif
class     CLIDataSource;
#include  <sCLICollection.hpp>
#include  <sPropertyHandle.hpp>
#pragma pack(8)

class  CLICollection :public PropertyHandle
{
protected  :         char                                        *name;                                                      // 
protected  :         char                                        *selection;                                                 // 
protected  :         DPA(char)                                    attr_list;                                                 // 
protected  :         int32                                        attr_count;                                                // 
protected  :         CLIDataSource                               *data_source;                                               // 

public     :
                     char                                        *get_selection() { return(selection); }
                     DPA(char)                                    get_attr_list() { return(attr_list); }
                     int32                                        get_attr_count() { return(attr_count); }
                     CLIDataSource                               *get_data_source() { return(data_source); }
public     :                                             CLICollection (CLIDataSource *dsource, DBObjectHandle ds_handle, char *prop_path, PIACC accmode=PI_undefined );
public     :                                             CLICollection (CLIDataSource *dsource, PropertyHandle &prophdl, char *prop_path );
public     :                                             CLICollection (CLIDataSource *dsource, CLICollection &coll_ref );
public     :                                             CLICollection (CLIDataSource *dsource, char *names, PropertyHandle &prophdl );
public     :                                             CLICollection (CLIDataSource *dsource, PropertyHandle *ph_ptr );
public     :                                        logical Copy (CLICollection *source_coll, char *mask, char *key_value );
public     :                                        logical Create (char *key_value );
public     :                                        logical Delete (char *mask, logical err_del );
public     :                                        char *GetName ( );
public     :                                        logical List ( );
public     :                                        logical ListAttributes (char *mask );
public     :                                        logical ListCollections (char *mask );
public     :                                        logical ListKeys ( );
public     :                                        logical ListOrder ( );
public     :                                        logical Locate (char *key_value );
public     :                                        logical Move (CLICollection *source_coll, char *mask, char *key_value );
public     :                                        logical Output (char *fstring, char *parm1=NULL, char *parm2=NULL, char *parm3=NULL, char *parm4=NULL, char *parm5=NULL );
public     :                                        logical Output (char *fstring, int32 intval, char *parm1=NULL, char *parm2=NULL, char *parm3=NULL );
public     :                                        logical Output (char *fstring, char *parm0, int32 intval, char *parm2=NULL, char *parm3=NULL );
public     :                                        logical ResetAttributes ( );
public     :                                        logical ResetSelection ( );
public     :                                        logical SetAttributes (char **attribute_list, logical append );
public     :                                        void SetName (char *string );
public     :                                        logical SetPropertyHandle (PropertyHandle &prophdl );
public     :                                        logical SetSelection (char *expression );
public     :                                        logical SetValue (char *assignment );
public     :                                             ~CLICollection ( );
};

#pragma pack()
#endif
