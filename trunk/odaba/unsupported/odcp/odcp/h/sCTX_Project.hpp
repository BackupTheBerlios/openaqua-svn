/********************************* Class Declaration ***************************/
/**
\package  ODCP - 
\class    CTX_Project

\brief    


\date     $Date: 2006/08/28 08:00:40,31 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CTX_Project_HPP
#define   CTX_Project_HPP

class     CTX_Project;

#include  <cCTX_Types.h>
#include  <sCTX_Application.hpp>
#include  <sInputArea.hpp>
#include  <sOutputArea.hpp>
class  CTX_Project :public CTX_Application,
public OutputArea,
public InputArea
{

public     :
public     :                  ODCPImpExp                 CTX_Project ( );
public     : virtual          ODCPImpExp            CTX_Types GetContextType ( );
public     :                  ODCPImpExp            char *Input (char *string );
public     :                  ODCPImpExp            logical Output (char *string, logical clear_opt=YES, logical flush_opt=YES );
public     : virtual          ODCPImpExp                 ~CTX_Project ( );
};

#endif
