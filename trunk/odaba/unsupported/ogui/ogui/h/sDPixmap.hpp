/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    DPixmap

\brief    


\date     $Date: 2006/03/13 21:33:37,78 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DPixmap_HPP
#define   DPixmap_HPP

class     DPixmap;

class  DPixmap
{
public     :         char                                        *path;                                                      //

public     :
public     :         OGUI7ImpExp                                         DPixmap ( );
public     :         OGUI7ImpExp                                         DPixmap (char *cpath );
public     :         OGUI7ImpExp                 char *GetPath ( );
public     :                                     char *GetUsedPath ( );
public     :         OGUI7ImpExp                 void ReleasePath ( );
public     :         OGUI7ImpExp                 void SetPath (char *cpath );
public     :         OGUI7ImpExp                                         ~DPixmap ( );
};

#endif
