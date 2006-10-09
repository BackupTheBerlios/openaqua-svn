/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    CTX_DataBase

\brief    Database Context
          The  database context  allows defining  functionality that is executed
          when  opening  or  closing  a  database. The database context does not
          have a parent context.
          The  default  database  context  can  be  overloaded  by a application
          specific database context class.

\date     $Date: 2006/08/27 20:31:11,68 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CTX_DataBase"

#include  <popa7.h>
#include  <coctp.h>
#include  <streams.h>
#include  <sACObject.hpp>
#include  <sCTX_Base.hpp>
#include  <sDBErrorHandle.hpp>
#include  <sDBHandle.hpp>
#include  <sPropertyHandle.hpp>
#include  <sCTX_DataBase.hpp>


/******************************************************************************/
/**
\brief  CTX_DataBase - Konstructor




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CTX_DataBase"

     CTX_DataBase :: CTX_DataBase ( )
                     : CTX_DBBase (),
  object_handle(NULL)
{



}

/******************************************************************************/
/**
\brief  ExecLogin - 



\return term - Termination code

\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecLogin"

logical CTX_DataBase :: ExecLogin (PropertyHandle *prophdl )
{
  char            string[101];
  logical         term = AUTO;  // sollte int8 executed sein
BEGINSEQ
  if ( SystemServices()->GetErrorHandle()->GUIMessagesActivated() )
                                                     ERROR
// das sollte anders zu ermitteln sein  
  if ( !TestSysVariable("CONSOLE","YES") )           LEAVESEQ
    
  std::cout << "user name: ";
  std::cout.flush();
    
  *string = 0;
  while ( !*string )
    std::cin.getline(string,sizeof(string));
  *prophdl->GPH("name") = string;
  
  std::cout << "password: ";
  std::cout.flush();
    
  *string = 0;
  while ( !*string )
    std::cin.getline(string,sizeof(string));
  *prophdl->GPH("password") = string;
  
  term = NO;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetConnectionClient - 



\return client - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetConnectionClient"

ODABAClient &CTX_DataBase :: GetConnectionClient ( )
{

  return (   this && object_handle 
           ? object_handle->GetConnectionClient()
           : GetMainClient() );

}

/******************************************************************************/
/**
\brief  GetContextType - Get context type

        The function returns the specific context type as CTX_Database.

\return ctxtype - Context type

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetContextType"

CTX_Types CTX_DataBase :: GetContextType ( )
{


  return(CTXT_Database);
}

/******************************************************************************/
/**
\brief  GetDBHandle - Det database handle

        The function returns a database handle for the database.

\return dbhdl - Database handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBHandle"

DatabaseHandle &CTX_DataBase :: GetDBHandle ( )
{


  return(*(DatabaseHandle *)&object_handle);
}

/******************************************************************************/
/**
\brief  Initialize - 




\param  dbhandle - Database handle
\param  highctx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void CTX_DataBase :: Initialize (DBHandle *dbhandle, CTX_Base *highctx )
{

  CTX_DBBase::Initialize(NULL,highctx);
  object_handle = dbhandle;

}

/******************************************************************************/
/**
\brief  Login - 



\return executed - 

\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Login"

int8 CTX_DataBase :: Login (PropertyHandle *prophdl )
{
  CTX_Base       *login_context;

  if ( !(login_context = GetApplicationContext()) )
    login_context = this;

  return ( login_context->ExecLogin(prophdl) );

}

/******************************************************************************/
/**
\brief  ~CTX_DataBase - Destructor

        The  function  destroys  the  database  context.  The  function  must be
        overloaded  in  an  application  specific implementation of the database
        context.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CTX_DataBase"

     CTX_DataBase :: ~CTX_DataBase ( )
{



}


