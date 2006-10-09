/********************************* Class Source Code ***************************/
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

\date     $Date: 2006/03/13 21:30:38,93 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODC_ApplLicence"

#include  <pfmodel.h>
#include  <sODC_ApplLicence.hpp>



