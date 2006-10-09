/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    XMLValue

\brief    XML element
          An  XML element describes  the attribute area,  the type and the value
          for  an XML element.  Strings are referenced  in the original text and
          should not me replaced.

\date     $Date: 2006/03/12 19:20:24,26 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   XMLValue_HPP
#define   XMLValue_HPP

class     XMLValue;

#include  <sNString.hpp>
#include  <sXMLValue.hpp>
#pragma pack(8)

class  XMLValue
{
protected  :         char                                        *name;                                                      
protected  :         int32                                        name_len;                                                  
protected  :         char                                        *value;                                                     
protected  :         int32                                        value_len;                                                 
protected  :         logical                                      owner;                                                     
protected  :         NString                                     *ovalue;                                                    
protected  :         NString                                      work_area;                                                 

public     :
                     char                                        *get_name() { return(name); }
                     int32                                        get_name_len() { return(name_len); }
                     char                                        *get_value() { return(value); }
                     int32                                        get_value_len() { return(value_len); }
                     logical                                      get_owner() { return(owner); }
                     NString                                     *get_ovalue() { return(ovalue); }
                     NString                                     &get_work_area() { return(work_area); }
public     :         SOS7ImpExp                  char *GetName ( );
public     :         SOS7ImpExp                  char *GetValue ( );
public     :         SOS7ImpExp                  void Reset ( );
public     :                                     void SetName (char *string, int32 slen );
public     :                                     logical SetValue (char *string, int32 slen );
public     :         SOS7ImpExp                                          XMLValue ( );
public     :         SOS7ImpExp                                          XMLValue (char *names );
public     :         SOS7ImpExp                                          XMLValue (char *string, int32 slen );
public     :         SOS7ImpExp                  XMLValue &operator= (char *string );
public     :         SOS7ImpExp                  XMLValue &operator= (int32 int_val );
public     :         SOS7ImpExp                                          ~XMLValue ( );
};

#pragma pack()
#endif
