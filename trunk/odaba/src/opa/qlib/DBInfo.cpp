/********************************* Class Source Code ***************************/
/**
\package  OPA
\class    DBInfo



\date     $Date: 2006/05/09 12:22:59,26 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBInfo"

#include  <popa7.h>
#include  <sACObject.hpp>
#include  <sDBHandle.hpp>
#include  <sDictionary.hpp>
#include  <sDBInfo.hpp>


/******************************************************************************/
/**
\brief  CheckLicence

\return term - Termination code

\param  dbhandle - Database handle
\param  lic_owner
\param  lic_number
\param  applname_w
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckLicence"

logical DBInfo :: CheckLicence (DBHandle *dbhandle, char *lic_owner, char *lic_number, char *applname_w )
{
  char                    lm[LICENCE_MASK_LEN];   
  uint8                   cmonth;
  uint16                  musers;
  char                    buffer[128];
  char                    applname[40];
  PropertyHandle         *pi;
  char                    string[513];
  logical                 term = NO;
BEGINSEQ
  if ( !check_count )                                ERROR
  check_count--;
  
  if ( !lic_number )
    lic_number = licence_number;
  if ( !lic_owner )
    lic_owner = owner;
  SetSysVariable("LICENCE_OWNER",gvtxbts(string,owner,48)); // nur 48 sind max. sinnvoll eingelesen
  
  gvtxstb(owner,lic_owner,sizeof(owner));
  GetLicenceMask(applname_w,lm);
  
  if ( memcmp(lm,lic_number,6)     ||
       memcmp(lm+7,lic_number+7,3) ||
       lm[11] != lic_number[11]        )          ERROR

  cmonth = (uint8)lic_number[10];     // month limit
  if ( cmonth >= '0' && cmonth <= '9' )
  {
//    if ( month_limit && cmonth-'0' != month_limit )     ERROR
    if ( (month_limit = cmonth-'0') && expiration_date.IsEmpty() )
    {
      expiration_date.SetDate();
      expiration_date += ((int16)month_limit)*31;
      month_limit = 15;
    }
  }
  if ( cmonth == 'F' )
    month_limit = 15;
  if ( month_limit != 15 )
    expiration_date = dbdt();
  
  switch ( lic_number[6] )             // max users
  {
    case '0' : musers = 0;                 break;
    case '1' : musers = 1000;              break;
    case '2' : musers = 500;               break;
    case '3' : musers = 400;               break;
    case '4' : musers = 300;               break;
    case '5' : musers = 200;               break;
    case '6' : musers = 100;               break;
    case '7' : musers = 50;                break;
    case '8' : musers = 40;                break;
    case '9' : musers = 30;                break;
    case 'A' : musers = 20;                break;
    case 'B' : musers = 10;                break;
    case 'C' : musers = 4;                 break;
    case 'D' : musers = 3;                 break;
    case 'E' : musers = 2;                 break;
    case 'F' : musers = 1;                 break;
    default  :                                       ERROR
  }
  if ( max_users && max_users != musers )            ERROR
  max_users = musers;
  
  memcpy(licence_number,lic_number,sizeof(licence_number));
  
  if ( dbhandle )
  {
    DatabaseHandle    temp_db(dbhandle);  
    PropertyHandle  db_pi(temp_db,"ODC_Database",PI_Write);  
                                                     SDBCERR
    if ( !db_pi(FIRST_INSTANCE) )                    ERROR
    pi = &db_pi;
  
    if ( applname_w )
    {
      pi = db_pi.GetPropertyHandle("applications");
      if ( !pi->Get(gvtxstb(applname,applname_w,40)) ) LEAVESEQ
    }
  
    PropertyHandle(*pi,"licence.max_users")      = (int16)max_users;
    PropertyHandle(*pi,"licence.month_limit")    = (int16)month_limit;
    PropertyHandle(*pi,"licence.time_limit")     = expiration_date;
    PropertyHandle(*pi,"licence.owner")          = gvtxbxor((char *)memcpy(buffer,owner,48),48);
    PropertyHandle(*pi,"licence.licence_number") = gvtxbxor((char *)memcpy(buffer,licence_number,12),12);

    pi->Save();
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DBInfo

-------------------------------------------------------------------------------
\brief  i0


\param  dbhandle - Database handle
\param  applname_w
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBInfo"

     DBInfo :: DBInfo (DBHandle *dbhandle, char *applname_w )
                     :   max_users(0),
  expiration_date(),
  version(0),
  sub_version(0),
  licenced(YES),
  month_limit(0),
  check_count(MAXCHECKS),
  db_number(0)
{
  Dictionary   *dictionary = dbhandle->GetDictionary();
  DBHandle     *dicthdl = (DBHandle *)dictionary;
BEGINSEQ
  memset(db_ident,0,sizeof(db_ident));
  memset(owner,' ',sizeof(owner));
  memset(licence_number,' ',sizeof(licence_number));
  *version_string = 0;

  if ( !dictionary || !dictionary->get_db_handle() || // nur internes dict.
       (ACObject *)dbhandle == (ACObject *)(DBHandle *)dictionary ) 
                                                     LEAVESEQ

  PropertyHandle  db_pi(*dictionary->GetDatabaseHandle(),"ODC_Database",PI_Read);
                                                     SDBCERR
  db_pi(FIRST_INSTANCE);
  Initialize(&db_pi,applname_w);
RECOVER
ENDSEQ
  SDBRESET
}

/******************************************************************************/
/**
\brief  i01


\param  piptr - Property handle
\param  applname_w
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBInfo"

     DBInfo :: DBInfo (PropertyHandle *piptr, char *applname_w )
                     :   max_users(0),
  expiration_date(),
  version(0),
  sub_version(0),
  licenced(YES),
  month_limit(0),
  check_count(MAXCHECKS),
  db_number(0)
{
  Initialize(piptr,applname_w);
}

/******************************************************************************/
/**
\brief  GetDBIdent

\return database_id

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBIdent"

char *DBInfo :: GetDBIdent ( )
{

  return(db_ident);

}

/******************************************************************************/
/**
\brief  GetLicenceMask

\return licence_mask

\param  applname_w
\param  licence_mask
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLicenceMask"

char *DBInfo :: GetLicenceMask (char *applname_w, char *licence_mask )
{
  static  char   static_area[LICENCE_MASK_LEN];
  char           hexnum[8];
  char           applname[40];
  char           hexmon[2];
  char           hexver[2];
  char           hexusr[2];
  char          *pos  = owner;
  int32           lnum = 1;
  int32           num  = 0;
  uint8          cmax;
  int            i;
  int            j;
  if ( !licence_mask )
    licence_mask = static_area;
    
  for ( j=0; j<3; j++ )
  {
    for ( i=0; i<16; i++, pos++ )
      num += *pos;
    lnum *=num;
    num = 0;
  }
  if ( applname_w )
  {
    pos = gvtxstb(applname,applname_w,40);
    for ( i=0, num = 0; i<40; i++, pos++ )
      num += *pos;
    lnum += num;
  }

  gvtxlth(hexnum,lnum);
  gvtxcth(hexver,(uint8)(version+sub_version*10));
  gvtxcth(hexmon,month_limit);
  
  if ( max_users == 0 )
    cmax = 0;
  if ( max_users < 5 )
    cmax = 16 - max_users;
  else if ( max_users <= 50 )
    cmax = 12 - (max_users+9)/10;
  else if ( max_users <= 500 )
    cmax = 7 - (max_users+99)/100;
  else if ( max_users <= 500 )
    cmax = 7 - (max_users+99)/100;
  else if ( max_users <= 1000 )
    cmax = 1;
  else
    cmax = 0;
  gvtxcth(hexusr,cmax);
  
  licence_mask[0]  = hexnum[0];
  licence_mask[1]  = hexnum[1];
  licence_mask[2]  = hexver[0];    // version und subversion
  licence_mask[3]  = hexver[1];    //
  licence_mask[4]  = hexnum[2];
  licence_mask[5]  = hexnum[3];
  licence_mask[6]  = hexusr[1];    // maximale zugelassene Nutzer
  licence_mask[7]  = hexnum[4];
  licence_mask[8]  = hexnum[5];
  licence_mask[9]  = hexnum[6];
  licence_mask[10] = hexmon[1];    // Zeitliche Begrenzung in Monaten 
  licence_mask[11] = hexnum[7];
  
  


  return(licence_mask);
}

/******************************************************************************/
/**
\brief  GetMaxUsers

\return max_users

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMaxUsers"

int16 DBInfo :: GetMaxUsers ( )
{

  return(licenced ? max_users : 1);

}

/******************************************************************************/
/**
\brief  GetVersionString

\return version_string

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetVersionString"

char *DBInfo :: GetVersionString ( )
{

  return(version_string);

}

/******************************************************************************/
/**
\brief  Initialize

\return term - Termination code

\param  piptr - Property handle
\param  applname_w
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical DBInfo :: Initialize (PropertyHandle *piptr, char *applname_w )
{
  char           applname[40];
  PropertyHandle       *pi;
  logical        term = NO;
BEGINSEQ
  memset(db_ident,0,sizeof(db_ident));
  memset(owner,' ',sizeof(owner));
  memset(licence_number,' ',sizeof(licence_number));
  *version_string = 0;

  if ( !piptr->Get() )                                 ERROR
  
  PropertyHandle       applications(*piptr,"applications");
  PropertyHandle       copy_pi(applications);
  
  pi = piptr;
  if ( applname_w )
  {
    gvtxstb(applname,applname_w,40);
    if ( copy_pi(applname) )
      pi = &copy_pi;
    else
      applname_w = NULL;
  }

  version         = (uint16)piptr->GetPropertyHandle("odaba2_version")->GetInt();
  sub_version     = (uint16)piptr->GetPropertyHandle("sub_version")->GetInt();

  max_users       = (uint16)pi->GetPropertyHandle("licence.max_users")->GetInt();
  month_limit     = *pi->GetString("licence.month_limit");
  expiration_date = pi->GetPropertyHandle("licence.time_limit")->GetDate();
  gvtxbxor(gvtxstb(owner,pi->GetPropertyHandle("licence.owner")->GetArea(),48),sizeof(owner));
  gvtultu(gvtxbxor((char *)memcpy(licence_number,pi->GetPropertyHandle("licence.licence_number")->GetArea(),12),sizeof(licence_number)),12);

  memcpy(db_ident,piptr->GetPropertyHandle("ident")->GetArea(),sizeof(db_ident));
  db_number   = piptr->GetPropertyHandle("ident.id")->GetInt();;

  strcat(gvtxitoa(version,version_string,10),".");
  gvtxitoa(sub_version,version_string+strlen(version_string),10);

  if ( pi->GetPropertyHandle("licence.req_licence_id")->IsTrue() )
    licenced = !CheckLicence(NULL,owner,licence_number,applname_w);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsExpired

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsExpired"

logical DBInfo :: IsExpired ( )
{
  dbdt                    curdate;
  logical                 cond = NO;
  curdate.SetDate();
  return( !expiration_date.IsEmpty() && expiration_date < curdate 
          ? YES : NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  IsLicenced

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsLicenced"

logical DBInfo :: IsLicenced ( )
{

  return(licenced);

}

/******************************************************************************/
/**
\brief  SetLicence

\return term - Termination code

\param  dbhandle - Database handle
\param  lic_owner
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLicence"

logical DBInfo :: SetLicence (DBHandle *dbhandle, char *lic_owner )
{
  PropertyHandle         *pi;
  char                   *lic_number;
  int32                    indx0 = 0;
  logical                 term = NO;
BEGINSEQ
  DatabaseHandle  temp_db(dbhandle);  
  PropertyHandle  db_pi(temp_db,"ODC_Database",PI_Read);  

  if ( !db_pi(FIRST_INSTANCE) )                      LEAVESEQ

  if ( lic_number = GetSysVariable("GENERAL") )
    if ( CheckLicence(dbhandle,lic_owner,lic_number,NULL) )
      SDBError().DisplayMessage(318,"GENERAL");

  pi = db_pi.GetPropertyHandle("applications");
  while ( pi->Get(indx0++) )
    if ( lic_number = GetSysVariable(pi->GetString("name")) )
      if ( CheckLicence(dbhandle,lic_owner,lic_number,pi->GetString("name")) )
        SDBError().DisplayMessage(318,pi->GetString("name"));

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~DBInfo - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DBInfo"

     DBInfo :: ~DBInfo ( )
{
}


