/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:09:46,17}|(REF)
\class    Instance

\brief    Instance Handle
          Instance  handles  are  used  to  pass  and return structured database
          instances.  Instead  of  an  instance  handle  a  (void *) area can be
          passed,  that is automatically converted  into an instance handle. The
          instance area is allocated and freed by the application.

\date     $Date: 2006/03/12 19:10:00,45 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   Instance_HPP
#define   Instance_HPP

class     Instance;

#include  <sInstance.hpp>
#pragma pack(8)

class  Instance
{
protected  :         void                                        *datarea;                                                   

public     :
                     void                                        *get_datarea() { return(datarea); }
public     :         OPI7ImpExp                  char *GetArea ( ) const;
public     :         OPI7ImpExp                  void *GetData ( ) const;
public     :         OPI7ImpExp                                          Instance ( );
public     :         OPI7ImpExp                                          Instance (void *inst_area );
public     :         OPI7ImpExp                                          Instance (const Instance &cinst_ref );
public     :         OPI7ImpExp                  void *SetData (void *inst_area );
public     :         OPI7ImpExp                  NOTYPE operator logical ( );
public     :         OPI7ImpExp                  void *operator& ( );
public     :         OPI7ImpExp                  Instance operator= (const Instance &cinst_ref );
public     :         OPI7ImpExp                  Instance operator= (void *datarea );
public     :         OPI7ImpExp                                          ~Instance ( );
};

#pragma pack()
#endif
