/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    NParm

\brief    Parm list
          This  string buffer supports parm lists. Parmlists are ofton passed as
          a  single string and  have to be  splitted into single parameters. The
          NParm-object  supports different types of Parameter lists according to
          type and separator:
          - position parameters
          - keyword parameters 
          Position  parameters  might  be  separated  by different separators as
          ';', ',' or spaces. Keyword parameters are supported in three ways:
          	ab keyword(value)
          	ab keyword=value;
          	ab keyword:value
          Within  one parm list different keyword types  can be used at the same
          time. Only the value is returned when requesting parameters. 

          all  functions  that  may  signal  an  error.  Otherwise  the  calling
          function  may not be  able to determine  whether the error signaled is
          an  old error or  has just been  signaled in the called function. This
          strategy  requires, on the other hand, that signaled errors have to be
          saved  when  other  functions  are  called  in the error handling thet
          might  generate  errors  again,  since  those functions will reset the
          error. You can use the Copy() function to save the error. 
          The  way errors are presented in  the application depends on the error
          handler  installed (ErroerHandle).  Usually errors  are written to the
          console  output for  console applications  and shown  in a message box
          for windows applications.

\date     $Date: 2006/03/12 19:20:05,21 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   NParm_HPP
#define   NParm_HPP

class     NParm;

#include  <sNBuffer.hpp>
#pragma pack(8)

class  NParm :public NBuffer
{
protected  :         int32                                        count ATTR_ALIGN(4);                                       
protected  :         char                                        *parm_value;                                                
protected  :         char                                         separator;                                                 
protected  :         logical                                      keyword_opt;                                               

public     :
                     int32                                        get_count() { return(count); }
                     char                                        *get_parm_value() { return(parm_value); }
                     char                                         get_separator() { return(separator); }
                     logical                                      get_keyword_opt() { return(keyword_opt); }
public     :         SOS7ImpExp                  int32 GetPos (char *parm_string );
public     :         SOS7ImpExp                                          NParm (char *parm_string, char separator=',', logical key_parms=NO );
public     :         SOS7ImpExp                                          NParm (char separator=',', logical key_parms=NO );
public     :         SOS7ImpExp                  char *operator() (int32 parm_no );
public     :         SOS7ImpExp                  char *operator() (char *parm_key );
public     :         SOS7ImpExp                  logical operator= (char *parm_string );
public     :         SOS7ImpExp                                          ~NParm ( );
};

#pragma pack()
#endif
