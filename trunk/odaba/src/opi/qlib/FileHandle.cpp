/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|08:38:31,48}|(REF)
\class    FileHandle

\brief    


\date     $Date: 2006/03/13 08:38:36,62 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "FileHandle"

#include  <pdefault.h>
#include  <sFile.hpp>
#include  <sFileHandle.hpp>


/******************************************************************************/
/**
\brief  AlignText - 


\return term - Termination code
/******************************************************************************/
/**
\brief i00


\param  string - String area
\param  size - Size
\param  indent -
\param  align_type -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AlignText"

logical FileHandle :: AlignText (char *string, uint32 size, uint16 indent, TextAlignment align_type )
{

  return ( file 
           ? file->AlignText(string,UNDEF,size,indent,align_type) 
           : YES );

}

/******************************************************************************/
/**
\brief  Close - Close File


\return term - Termination code
/******************************************************************************/
/**
\brief i00


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical FileHandle :: Close ( )
{

  if ( file )
    file->Close();
  return(NO);
}

/******************************************************************************/
/**
\brief  CurrentLine - Get current line number
        The  function  returns  the  line  number  on  which the write cursor is
        currently positioned.

\return line_cnt - line number relativly 1
/******************************************************************************/
/**
\brief i00


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CurrentLine"

int32 FileHandle :: CurrentLine ( )
{

  return ( file ? file->CurrentLine() : AUTO );

}

/******************************************************************************/
/**
\brief  FileHandle - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FileHandle"

                        FileHandle :: FileHandle ( )
                     : file(NULL)
{



}

/******************************************************************************/
/**
\brief  IsOpened - 


\return cond - Return value
/******************************************************************************/
/**
\brief i00


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsOpened"

logical FileHandle :: IsOpened ( )
{

  return ( file && file->IsOpened() ? YES : NO );

}

/******************************************************************************/
/**
\brief  LinePosition - Position the write cursor within the current line.
        The  pos is interpreted relavly 1. If  the new position is located after
        the current write cursor posion, Blanks are addedup to the new posion.

\return term - Termination code
/******************************************************************************/
/**
\brief i00


\param  pos - position relativly 1
\param  min_forward -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LinePosition"

logical FileHandle :: LinePosition (uint16 pos, int16 min_forward )
{

  return ( file ? file->LinePosition(pos) : YES );

}

/******************************************************************************/
/**
\brief  Open - Open File
        The  file is opened at  the location cpath in  the given access mode and
        as  binary file, always.. If the file is opened in write mode (PI_Write)
        existing file will be overwritten.

\return term - Termination code
/******************************************************************************/
/**
\brief i00


\param  cpath - Complete path
\param  accopt - Access option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical FileHandle :: Open (char *cpath, PIACC accopt )
{

BEGINSEQ
  if ( !file )
    if ( !(file = new File()) )                      SDBERR(95)

  if ( file->Open(cpath,accopt) )                    ERROR
RECOVER
  delete file;
  file = NULL;
ENDSEQ
  return ( file ? NO : YES );
}

/******************************************************************************/
/**
\brief  Out - 


\return term - Termination code
/******************************************************************************/
/**
\brief i00


\param  format_string -
\param  parm1 -
\param  parm2 -
\param  parm3 -
\param  parm4 -
\param  parm5 -
\param  parm6 -
\param  parm7 -
\param  parm8 -
\param  parm9 -
\param  parm10 -
\param  parm11 -
\param  parm12 -
\param  parm13 -
\param  parm14 -
\param  parm15 -
\param  parm16 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Out"

logical FileHandle :: Out (char *format_string, char *parm1, char *parm2, char *parm3, char *parm4, char *parm5, char *parm6, char *parm7, char *parm8, char *parm9, char *parm10, char *parm11, char *parm12, char *parm13, char *parm14, char *parm15, char *parm16 )
{

  return ( file ? file->Out(format_string,
                            parm1,parm2,parm3,
                            parm4,parm5,parm6,
                            parm7,parm8,parm9,
                            parm10,parm11,parm12,
                            parm13,parm14,parm15,parm16) 
                : YES );

}

/******************************************************************************/
/**
\brief  ~FileHandle - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~FileHandle"

                        FileHandle :: ~FileHandle ( )
{

  Close();
  
  delete file;
  file = NULL;

}


