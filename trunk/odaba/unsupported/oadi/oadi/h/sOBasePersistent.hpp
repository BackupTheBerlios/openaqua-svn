/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OBasePersistent



\date     $Date: 2006/04/30 14:49:52,54 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OBasePersistent_HPP
#define   OBasePersistent_HPP

class     OBasePersistent;

class     PropertyHandle;
#pragma pack(4)

class  OBasePersistent
{
protected  :         DBObjectHandle                               resDB;                                                     
protected  :         int                                          resID;                                                     

public     :
                     DBObjectHandle                              &get_resDB() { return(resDB); }
                     int                                         &get_resID() { return(resID); }
public     : virtual                                int GetID ( );
public     :                                        DBObjectHandle GetPersistentDBHandle ( );
public     :                                             OBasePersistent ( );
public     :                                             OBasePersistent (int resID );
public     : virtual                                logical Read (PropertyHandle *ph );
public     :                                        void SetID (int32 res_id );
public     :                                        logical SetProperties ( );
public     :                                        logical Setup ( );
public     : virtual                                     ~OBasePersistent ( );
};

#pragma pack()
#endif
