/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    cftp

\brief    


\date     $Date: 2006/03/12 19:20:28,09 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cftp_HPP
#define   cftp_HPP

class     cftp;

class     CTX_Base;
#pragma pack(8)

class  cftp
{
protected  :         char                                        *cftpname;                                                  //
protected  :         CTX_Base                                    *cftpfnc;                                                   //
protected  :         void                                        *cftpres;                                                   //
protected  :         CTX_Base                                   **cftpret;                                                   //

public     :
                     char                                        *get_cftpname() { return(cftpname); }
                     CTX_Base                                    *get_cftpfnc() { return(cftpfnc); }
public     :         SOS7ImpExp                  CTX_Base *HighContext ( );
public     :         SOS7ImpExp                  void SetContext (CTX_Base *fncptr );
public     :         SOS7ImpExp                                          cftp (char *fnames, void *resptr, CTX_Base *highfnc=NULL, CTX_Base **fncptr_p=NULL );
};

#pragma pack()
#endif
