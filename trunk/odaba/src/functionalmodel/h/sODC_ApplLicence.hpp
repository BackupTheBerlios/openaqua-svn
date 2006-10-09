/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    ODC_ApplLicence

\brief    Application license
          ODABA  supports  a  simple  way  of licensing applications. Beside the
          database,  you  may  license  single  applications for specific users,
          which  are  registered  in  the  repository.  When  an  application is
          registered  and  marked  as  'license  required',  users  must  have a
          license  for  running  the  application.  This  requires,  that  the 
          application  checks  the  license  using  the  database CheckLicence()
          function.

\date     $Date: 2006/03/13 21:30:30,90 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODC_ApplLicence_HPP
#define   ODC_ApplLicence_HPP

class     ODC_ApplLicence;

#include  <sODC_DBLicence.hpp>
#pragma pack(8)

class  ODC_ApplLicence
{
protected  :         char                                         name[40];                                                  // Application name
protected  :         ODC_DBLicence                                licence;                                                   // License definition

public     :
                     char                                        *get_name() { return(name); }
                     ODC_DBLicence                               &get_licence() { return(licence); }
};

#pragma pack()
#endif
