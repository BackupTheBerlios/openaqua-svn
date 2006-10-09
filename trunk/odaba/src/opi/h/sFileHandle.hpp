/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|08:38:31,48}|(REF)
\class    FileHandle

\brief    


\date     $Date: 2006/03/13 08:38:33,62 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   FileHandle_HPP
#define   FileHandle_HPP

class     FileHandle;

class     File;
#include  <cPIACC.h>
#include  <cTextAlignment.h>
#pragma pack(8)

class  FileHandle
{
protected  :         File                                        *file;                                                      //

public     :
public     :         OPI7ImpExp                  logical AlignText (char *string, uint32 size, uint16 indent, TextAlignment align_type );
public     :         OPI7ImpExp                  logical Close ( );
public     :         OPI7ImpExp                  int32 CurrentLine ( );
public     :         OPI7ImpExp                                          FileHandle ( );
public     :         OPI7ImpExp                  logical IsOpened ( );
public     :         OPI7ImpExp                  logical LinePosition (uint16 pos, int16 min_forward=AUTO );
public     :         OPI7ImpExp                  logical Open (char *cpath, PIACC accopt );
public     :         OPI7ImpExp                  logical Out (char *format_string, char *parm1=NULL, char *parm2=NULL, char *parm3=NULL, char *parm4=NULL, char *parm5=NULL, char *parm6=NULL, char *parm7=NULL, char *parm8=NULL, char *parm9=NULL, char *parm10=NULL, char *parm11=NULL, char *parm12=NULL, char *parm13=NULL, char *parm14=NULL, char *parm15=NULL, char *parm16=NULL );
public     :         OPI7ImpExp                                          ~FileHandle ( );
};

#pragma pack()
#endif
