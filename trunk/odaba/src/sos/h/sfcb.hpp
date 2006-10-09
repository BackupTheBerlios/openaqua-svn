/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    fcb

\brief    


\date     $Date: 2006/03/12 19:20:36,84 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   fcb_HPP
#define   fcb_HPP

class     fcb;

class     fmcb;
#pragma pack(8)

class  fcb
{
public     :         fmcb                                        *fcbfmcb;                                                   //

public     :
public     :                                     char *GetName ( );
public     :                                                             fcb ( );
public     :                                                             fcb (fmcb *fmcbptr );
public     :                                     void fcbfmcbs (fmcb *fmcbptr );
};

#pragma pack()
#endif
