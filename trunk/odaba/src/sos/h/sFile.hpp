/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    File

\brief    


\date     $Date: 2006/03/12 19:20:00,06 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   File_HPP
#define   File_HPP

class     File;

#include  <cPIACC.h>
#include  <cTextAlignment.h>
#include  <sNString.hpp>
#include  <ssts.hpp>
class  File :public sts
{
protected  :         char                                        *filpath ATTR_ALIGN(1);                                     //
protected  :         FILE                                        *filhandle;                                                 //
protected  :         PIACC                                        accmode;                                                   //
protected  :         logical                                      net_opt;                                                   //
protected  :         int32                                        file_len;                                                  //
protected  :         int32                                        linecount;                                                 //
protected  :         NString                                      curline;                                                   //
protected  :         NString                                      formatline;                                                //

public     :
                     char                                        *get_filpath() { return(filpath); }
                     FILE                                        *get_filhandle() { return(filhandle); }
                     PIACC                                        get_accmode() { return(accmode); }
                     logical                                      get_net_opt() { return(net_opt); }
                     int32                                        get_file_len() { return(file_len); }
                     int32                                        get_linecount() { return(linecount); }
                     NString                                     &get_curline() { return(curline); }
public     :         SOS7ImpExp                  logical AlignText (char *string, int32 maxlen, uint16 size, uint16 indent=0, TextAlignment align_type=TA_undefined );
public     :         SOS7ImpExp                  logical Close ( );
public     :         SOS7ImpExp                  int32 CurrentLine ( );
public     :         SOS7ImpExp                                          File ( );
public     :                                     logical FormatParm (char *parm_string, uint16 &index_ref );
public     :         SOS7ImpExp                  logical IsOpened ( );
public     :         SOS7ImpExp                  logical LinePosition (uint16 pos, int16 min_forward=AUTO );
public     :         SOS7ImpExp                  logical Open ( );
public     :         SOS7ImpExp                  logical Open (char *cpath, PIACC acc_opt );
public     :         SOS7ImpExp                  logical Out (char *format_string, char *parm1=NULL, char *parm2=NULL, char *parm3=NULL, char *parm4=NULL, char *parm5=NULL, char *parm6=NULL, char *parm7=NULL, char *parm8=NULL, char *parm9=NULL, char *parm10=NULL, char *parm11=NULL, char *parm12=NULL, char *parm13=NULL, char *parm14=NULL, char *parm15=NULL, char *parm16=NULL );
public     :         SOS7ImpExp                                          ~File ( );
};

#endif
