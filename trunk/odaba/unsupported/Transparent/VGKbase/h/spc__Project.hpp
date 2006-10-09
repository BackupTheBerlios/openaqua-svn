/********************************* Class Declaration ***************************/
/**
\package  VGKbase - 
\class    pc__Project

\brief    


\date     $Date: 2006/07/05 15:31:58,43 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc__Project_HPP
#define   pc__Project_HPP

class     pc__Project;

#include  <sDatabaseHandle.hpp>
#include  <sPropertyHandle.hpp>
class  pc__Project :public PropertyHandle
{

public     :
public     :                                        NString GetDocumentFolder (char *sub_folder );
public     :                                        char *GetImportFolder (NString &nstring, char *sub_folder );
public     :                                        NString GetPOP3 (char *attribute_name, char *ini_name );
public     :                                        NString GetPOP3Address ( );
public     :                                        NString GetPOP3Password ( );
public     :                                        int16 GetPOP3Port ( );
public     :                                        NString GetPOP3Server ( );
public     :                                        NString GetPOP3User ( );
public     :                                        NString GetSMTP (char *attribute_name, char *ini_name );
public     :                                        NString GetSMTPAddress ( );
public     :                                        int32 GetSMTPInfo (NString &server_string, NString &address_string, int16 &port_ref );
public     :                                        NString GetSMTPPassword ( );
public     :                                        int16 GetSMTPPort ( );
public     :                                        NString GetSMTPServer ( );
public     :                                        NString GetSMTPUser ( );
public     :                                             pc__Project (PropertyHandle *prophdl );
public     :                                             pc__Project (DatabaseHandle &dbhandle, PIACC accopt );
};

#endif
