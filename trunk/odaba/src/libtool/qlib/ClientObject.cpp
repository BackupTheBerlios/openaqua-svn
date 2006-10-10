/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:21:31,04}|(REF)
\class    ClientObject

\brief    


\date     $Date: 2006/03/12 19:21:42,09 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ClientObject"

#include  <puti.h>
#include  <sCSUtilityHandle.hpp>
#include  <sDataSourceHandle.hpp>
#include  <sStatistic.hpp>
#include  <sClientObject.hpp>


/******************************************************************************/
/**
\brief  ClientObject - Konstruktor



\param  uti_handle -
\param  extent_name -
\param  max_objects -
\param  client_num -
\param  client_cnt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClientObject"

                        ClientObject :: ClientObject (CSUtilityHandle &uti_handle, char *extent_name, int32 max_objects, int32 client_num, int32 *client_cnt )
                     : vcls (),
  extent(),
  max_obj(max_objects),
  id(client_num),
  utility_handle(&uti_handle),
  client_count(client_cnt),
  ds_handle(NULL)

{

  if ( extent_name )
    extent = strdup(extent_name);


}

/******************************************************************************/
/**
\brief  Close


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

void ClientObject :: Close ( )
{

  if ( ds_handle )
  {
    ds_handle->Close();
    ds_handle->client.ShutDown();
    delete ds_handle;
    ds_handle = NULL;
  }


}

/******************************************************************************/
/**
\brief  Start - Start Thread


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Start"

logical ClientObject :: Start ( )
{
  int32                    lindx0 = 0;
  int32                   *loid_array;
  int32                    count;
  int32                    err_count = 0;
  Statistic               stats;
  ODABAClient             client;
  DBObjectHandle          obhandle(utility_handle->sdbures->dbhandle);
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       ERROR
  (*client_count)++;

  stats.Start();
  
  if ( !obhandle.IsServer() )  // client/server application
  {
    ds_handle = new DataSourceHandle();
    ds_handle->SetDataSource(utility_handle->sdbures);
    client.Open(NULL,"TestCS");
    if ( ds_handle->Open(client) )                   ERROR
    obhandle = ds_handle->dbhandle;
  }

  PropertyHandle  ext_ph(obhandle,extent,PI_Read);  SDBCERR
  PropertyHandle  void_ph(obhandle,"VOID",PI_Read); SDBCERR

  printf("\nThread %i started (%s)",id,extent);

  if ( (count = ext_ph.GetCount()) > 0 )
  {
    loid_array = new int32[count];
    memset(loid_array,0,count*sizeof(int32));
    
    while ( ext_ph.Get(lindx0) )
      loid_array[lindx0++] = ext_ph.GetLOID();
    
    lindx0 = 0;
    while ( lindx0 < count ) 
      if ( !void_ph.Get(loid_array[lindx0++]) )
        err_count++;
      
    delete loid_array;
  }
  stats.Stop();


  printf("\nThread %i stopped (%s) normally. Errors: %i",id,extent,err_count);
  printf("\n          total time: %s",stats.GetTotalTime());

RECOVER
  printf("\nThread %i terminated (%s) with error",id,extent);
  term = YES;
ENDSEQ
  if ( this ) 
  {  
    obhandle.Close();
    Close();
    client.ShutDown();
    (*client_count)--;
    delete this;
  }
  return(term);
}

/******************************************************************************/
/**
\brief  ~ClientObject - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ClientObject"

                        ClientObject :: ~ClientObject ( )
{

  Close();

  if ( extent )
    free(extent);
  extent = NULL;



}


