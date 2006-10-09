/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    ODC_Database

\brief    


\date     $Date: 2006/03/13 21:30:31,09 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODC_Database_HPP
#define   ODC_Database_HPP

class     ODC_Database;

#ifndef   P_ODC_ApplLicence_HPP
#define   P_ODC_ApplLicence_HPP
#include  <sPI.hpp>
class       ODC_ApplLicence;
PI_dcl     (ODC_ApplLicence)
#endif
#include  <sODC_DBIdent.hpp>
#include  <sODC_DBLicence.hpp>
#include  <sODC_Module.hpp>
#pragma pack(8)

class  ODC_Database :public ODC_Module
{
protected  :         char                                         reserved[30] ATTR_ALIGN(4);                                // Reserved for future
protected  :         ODC_DBIdent                                  ident;                                                     // Database identification
protected  :         int16                                        sub_version;                                               // Database sub version
protected  :         ODC_DBLicence                                licence;                                                   // Database license conditions
protected  :         PI(ODC_ApplLicence)                          applications;                                              //

public     :
                     char                                        *get_reserved() { return(reserved); }
                     ODC_DBIdent                                 &get_ident() { return(ident); }
                     int16                                        get_sub_version() { return(sub_version); }
                     ODC_DBLicence                               &get_licence() { return(licence); }
                     PI(ODC_ApplLicence)                         &get_applications() { return(applications); }
public     :                                                             ODC_Database ( );
};

#pragma pack()
#endif
