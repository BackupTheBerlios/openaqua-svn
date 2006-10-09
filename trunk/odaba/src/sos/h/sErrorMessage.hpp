/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/05|16:41:32,95}|(REF)
\class    ErrorMessage

\brief    


\date     $Date: 2006/04/05 21:30:06,46 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ErrorMessage_HPP
#define   ErrorMessage_HPP

class     ErrorMessage;

#include "csosdll.h"
class     Error;
#pragma pack(8)

class  ErrorMessage
{
protected  :         char                                         sep00;                                                     
protected  :         char                                         year[4];                                                   
protected  :         char                                         sep01;                                                     
protected  :         char                                         month[2];                                                  
protected  :         char                                         sep02;                                                     
protected  :         char                                         day[2];                                                    
protected  :         char                                         sep1;                                                      
protected  :         char                                         hour[2];                                                   
protected  :         char                                         sep11;                                                     
protected  :         char                                         minute[2];                                                 
protected  :         char                                         sep12;                                                     
protected  :         char                                         second[2];                                                 
protected  :         char                                         sep13;                                                     
protected  :         char                                         sep2;                                                      
public     :         char                                         component[5];                                              
protected  :         char                                         sep3;                                                      
public     :         char                                         error_type[12];                                            
public     :         char                                         sep4;                                                      
public     :         char                                         error_code[4];                                             
protected  :         char                                         sep5;                                                      
public     :         char                                         object_class[40];                                          
protected  :         char                                         sep6[3];                                                   
public     :         char                                         function[40];                                              
protected  :         char                                         sep7;                                                      
public     :         char                                         text[200];                                                 
protected  :         char                                         sep8;                                                      
protected  :         char                                         new_line[2];                                               

public     :
public     :         SOSImpExp                                           ErrorMessage ( );
public     :         SOSImpExp                   void SetData (char *display_name, char *message_type, char *string );
public     :         SOSImpExp                   void SetData (Error *error_obj );
public     :         SOSImpExp                   void SetDateTime ( );
public     :         SOSImpExp                   void SetError (Error *error_obj, char *type=NULL );
};

#pragma pack()
#endif
