/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OEHShortcut

\brief    


\date     $Date: 2006/03/13 21:34:15,73 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OEHShortcut_HPP
#define   OEHShortcut_HPP

class     OEHShortcut;

#include  <cOEH_Frame.h>
#include  <sOEHShortcut.hpp>
class  OEHShortcut
{
protected  :         char                                        *key_sequence;                                              //
protected  :         OEH_Frame                                    frame;                                                     //

public     :
                     char                                        *get_key_sequence() { return(key_sequence); }
                     OEH_Frame                                    get_frame() { return(frame); }
public     :         OGUI7ImpExp                                         OEHShortcut (char *string, OEH_Frame oeh_frame );
public     :         OGUI7ImpExp                                         OEHShortcut (char *string );
public     :         OGUI7ImpExp                                         OEHShortcut ( );
public     :                                     QKeySequence Shortcut ( );
public     :                                     Qt::ShortcutContext ShortcutContext ( );
public     :         OGUI7ImpExp                 logical operator== (OEHShortcut &rOEHShortcut );
};

#endif
