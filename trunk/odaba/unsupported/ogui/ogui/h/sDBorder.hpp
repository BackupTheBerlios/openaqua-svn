/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    DBorder

\brief    


\date     $Date: 2006/03/13 21:33:35,53 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBorder_HPP
#define   DBorder_HPP

class     DBorder;

class     OBorder;
#include  <cADK_BorderStyles.h>
#include  <cADK_ShadowStyles.h>
class  DBorder
{
protected  :         ADK_BorderStyles                             type;                                                      //
protected  :         ADK_ShadowStyles                             shadow_type;                                               //
protected  :         int                                          line_with;                                                 //
protected  :         int                                          mid_line_with;                                             //

public     :
                     ADK_BorderStyles                             get_type() { return(type); }
                     ADK_ShadowStyles                             get_shadow_type() { return(shadow_type); }
                     int                                         &get_line_with() { return(line_with); }
                     int                                         &get_mid_line_with() { return(mid_line_with); }
public     :         OGUI7ImpExp                                         DBorder ( );
public     :         OGUI7ImpExp                                         DBorder (ADK_BorderStyles bstyle, ADK_ShadowStyles sstyle, int lwith=1, int mlwith=1 );
public     :         OGUI7ImpExp                 void FromOBorder (OBorder *pOBorder );
public     :         OGUI7ImpExp                 void Reset ( );
public     :         OGUI7ImpExp                 void Set (ADK_BorderStyles bstyle, ADK_ShadowStyles sstyle, int lwith=1, int mlwith=1 );
};

#endif
