/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    InitArea

\brief    


\date     $Date: 2006/03/12 19:13:24,64 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   InitArea_HPP
#define   InitArea_HPP

class     InitArea;

#pragma pack(8)

class  InitArea
{
protected  :         uint32                                       size;                                                      
protected  :         void                                        *area;                                                      

public     :
public     :                                                             InitArea (int32 w_size=AUTO );
public     :                                                             ~InitArea ( );
public     :                                     void *GetArea ( ){


  return(area);
}

public     :                                     uint32 GetSize ( ){


  return(size);
}

};

#pragma pack()
#endif
