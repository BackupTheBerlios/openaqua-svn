/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    ODC_DBLicence

\brief    License definition
          License  definitions define the conditions for  using a database or an
          application  based  on  the  database. By means of license conditions,
          the  duration of use, the number of users or a termination date can be
          defined.  License definitions  can be  provided for each customer, but
          also  as  a  general  license  (test  license).  The  general  license
          determines  the conditions, under which any user can use a database or
          applications.
          Running  the License  utility with  the proper  owner name and license
          number  activates  licenses  for  a  user. The License utility must be
          executed  once for  each dictionary,  where the license information is
          stored for further use.

\date     $Date: 2006/03/13 21:30:31,03 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODC_DBLicence_HPP
#define   ODC_DBLicence_HPP

class     ODC_DBLicence;

#pragma pack(8)

class  ODC_DBLicence
{
protected  :         logical                                      req_licence_id;                                            // License required
protected  :         uint8                                        month_limit;                                               // Time limit in month
protected  :         char                                         owner[48];                                                 // Owner name
protected  :         char                                         licence_number[12];                                        // License number
protected  :         dbdt                                         time_limit;                                                // Time limit
protected  :         uint16                                       max_users;                                                 // Maximal number of users
protected  :         char                                         reserved[12];                                              // Reserved for future
protected  :         char                                         licence_number_t[12];                                      // Transient license number field
protected  :         char                                         owner_t[48];                                               // Transient owner field

public     :
                     logical                                      get_req_licence_id() { return(req_licence_id); }
                     uint8                                        get_month_limit() { return(month_limit); }
                     char                                        *get_owner() { return(owner); }
                     char                                        *get_licence_number() { return(licence_number); }
                     dbdt                                         get_time_limit() { return(time_limit); }
                     uint16                                       get_max_users() { return(max_users); }
                     char                                        *get_reserved() { return(reserved); }
                     char                                        *get_licence_number_t() { return(licence_number_t); }
                     char                                        *get_owner_t() { return(owner_t); }
};

#pragma pack()
#endif
