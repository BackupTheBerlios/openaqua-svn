/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/07|16:46:42,89}|(REF)
\class    EnumValue



\date     $Date: 2006/04/07 17:25:58,03 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EnumValue_HPP
#define   EnumValue_HPP

class     EnumValue;

class     PropertyHandle;
class  EnumValue
{
protected  :         int32                                        code;                                                      
protected  :         char                                         name[40];                                                  
protected  :         char                                        *basetype;                                                  
protected  :         char                                        *display_name;                                              
protected  :         char                                        *title;                                                     

public     :
                     int32                                        get_code() { return(code); }
                     char                                        *get_name() { return(name); }
                     char                                        *get_basetype() { return(basetype); }
                     char                                        *get_display_name() { return(display_name); }
                     char                                        *get_title() { return(title); }
public     :                                                             EnumValue (int32 cval, char *cstring, char *btype );
public     :                                     void Initialize (PropertyHandle *val_ph );
public     :                                     void Initialize (int32 cval, char *cstring, char *btype );
public     :                                     void ReleaseEntry ( );
};

#endif
