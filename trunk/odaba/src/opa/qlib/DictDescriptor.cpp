/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DictDescriptor

\brief    


\date     $Date: 2006/03/12 19:17:17,82 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DictDescriptor"

#include  <popa7.h>
#include  <sDictDescriptor.hpp>


/******************************************************************************/
/**
\brief  DictDescriptor - 


-------------------------------------------------------------------------------
\brief i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DictDescriptor"

                        DictDescriptor :: DictDescriptor ( )
                     :   dicthdl(),
  dict_clients()
{

  memset(path,0,sizeof(path));

}

/******************************************************************************/
/**
\brief i01


\param  cpath - Complete path
\param  accopt - Access mode
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DictDescriptor"

                        DictDescriptor :: DictDescriptor (char *cpath, PIACC accopt, uint16 version_nr )
                     : path(),
  dicthdl(),
  dict_clients(),
  version(version_nr),
  access_mode(accopt)
{

  memset(path,0,sizeof(path));
  strncpy(path,cpath,sizeof(path)-1);

}

/******************************************************************************/
/**
\brief  ~DictDescriptor - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DictDescriptor"

                        DictDescriptor :: ~DictDescriptor ( )
{



}


