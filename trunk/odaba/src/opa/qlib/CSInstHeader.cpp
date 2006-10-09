/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    CSInstHeader

\brief    


\date     $Date: 2006/03/12 19:16:38,21 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CSInstHeader"

#include  <popa7.h>
#include  <cwinsock.h>
#include  <sCSInstance.hpp>
#include  <sInstance.hpp>
#include  <sCSInstHeader.hpp>


/******************************************************************************/
/**
\brief  CSInstHeader - 


-------------------------------------------------------------------------------
\brief i00


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSInstHeader"

                        CSInstHeader :: CSInstHeader ( )
                     : size(0),
  type(CPT_void)
{



}

/******************************************************************************/
/**
\brief i01


\param  inst_len -
\param  inst_type -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSInstHeader"

                        CSInstHeader :: CSInstHeader (int32 inst_len, CS_ParmTypes inst_type )
                     : size(inst_len),
  type(inst_type)
{



}

/******************************************************************************/
/**
\brief i02


\param  inst_header_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSInstHeader"

                        CSInstHeader :: CSInstHeader (CSInstHeader &inst_header_ref )
                     : size(inst_header_ref.get_size()),
  type(inst_header_ref.get_type())
{



}

/******************************************************************************/
/**
\brief  ConvertFromNet - Convert Heder to net


-------------------------------------------------------------------------------
\brief i0


\param  parm_type -
\param  arealen -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConvertFromNet"

void CSInstHeader :: ConvertFromNet (CS_ParmTypes parm_type, int32 arealen )
{

  size = ntohl((u_long)arealen);
  type = (CS_ParmTypes)ntohl((u_long)parm_type);

}

/******************************************************************************/
/**
\brief i01


\param  inst_header_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConvertFromNet"

void CSInstHeader :: ConvertFromNet (CSInstHeader &inst_header_ref )
{

  ConvertFromNet(inst_header_ref.type,inst_header_ref.size);

}

/******************************************************************************/
/**
\brief  ConvertToNet - 


-------------------------------------------------------------------------------
\brief i0


\param  parm_type -
\param  arealen -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConvertToNet"

void CSInstHeader :: ConvertToNet (CS_ParmTypes parm_type, int32 arealen )
{

  size = htonl((u_long)arealen);
  type = (CS_ParmTypes)htonl((u_long)parm_type);


}

/******************************************************************************/
/**
\brief i01


\param  inst_header_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConvertToNet"

void CSInstHeader :: ConvertToNet (CSInstHeader &inst_header_ref )
{

  ConvertToNet(inst_header_ref.type,inst_header_ref.size);

}

/******************************************************************************/
/**
\brief  Initialize - 


-------------------------------------------------------------------------------
\brief i0


\param  cs_inst -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void CSInstHeader :: Initialize (CSInstance *cs_inst )
{

  size = cs_inst->get_cursize();
  type = cs_inst->get_type();

}

/******************************************************************************/
/**
\brief i01


\param  parm_type -
\param  arealen -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void CSInstHeader :: Initialize (CS_ParmTypes parm_type, int32 arealen )
{

  size = arealen;
  type = parm_type;

}

/******************************************************************************/
/**
\brief  ~CSInstHeader - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CSInstHeader"

                        CSInstHeader :: ~CSInstHeader ( )
{



}


