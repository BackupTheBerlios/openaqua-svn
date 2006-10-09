/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    SeparatorDef

\brief    Separator definition


\date     $Date: 2006/03/12 19:20:17,09 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SeparatorDef_HPP
#define   SeparatorDef_HPP

class     SeparatorDef;

class     fmcb;
class  SeparatorDef
{
public     :         fmcb                                        *stringfmcb;                                                
public     :         char                                         string_start;                                              //
public     :         char                                         string_stop;                                               //
public     :         char                                         string_repl;                                               //
public     :         char                                         field_start;                                               //
public     :         char                                         field_stop;                                                //
public     :         char                                         field_repl;                                                //
public     :         char                                         block_start;                                               //
public     :         char                                         block_stop;                                                //
public     :         char                                         block_repl;                                                //
protected  :         char                                         new_line[9];                                               
public     :         char                                         empty_str[41];                                             

public     :
public     :                                                             SeparatorDef (char *str_sep, char *field_sep, char *block_sep, char *line_sep, char *empty_string );
public     :                                                             ~SeparatorDef ( );
};

#endif
