/********************************* Class Declaration ***************************/
/**
\package  VGKbase - 
\class    pc_Notiz

\brief    


\date     $Date: 2006/07/17 18:28:00,48 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_Notiz_HPP
#define   pc_Notiz_HPP

class     pc_Notiz;

#include  <sPropertyHandle.hpp>
#include  <spcBase.hpp>
class  pc_Notiz :public pcBase
{

public     :
public     :                                        logical CreateDeckungsnote (char *betreff_text, char *mail_text, char *von_an );
public     :                                        logical CreateEmailEingangNotiz (char *betreff_text, char *sender_email, char *mail_text, logical offen );
public     :                                        logical CreateNotiz (char *typ_string, char *betreff_text, char *mail_text, char *von_an );
public     :                                        logical CreateOffeneNotiz (char *typ_string, char *betreff_text, char *von_an );
public     :                                        logical CreatePolice (char *betreff_text, char *anhang );
public     :                                        logical CreateWiedervorlageNotiz (char *typ_string, char *betreff_text, char *von_an );
public     :                                        logical CreateWiedervorlageNotiz (char *betreff_text, char *von_an );
public     :                                        logical IsWiedervorlageExtent ( );
public     :                                        int32 LocateDeckungsnote ( );
public     :                                        logical ResetWV ( );
public     :                                        logical SetMailSend ( );
public     :                                        logical SetWV (int32 days );
public     :                                             pc_Notiz (PropertyHandle *prophdl );
};

#endif
