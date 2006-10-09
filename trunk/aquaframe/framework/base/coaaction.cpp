#include "coaaction.h"
#include <CoaDebug>
#include <CoaSignals>
#include <CoaSettings>
#include <CoaSettingsWidget>

#include <QObject>
#include <QKeySequence>


const CoaString SETTING_SHORTCUT="CoaActionShortCuts";


CoaAction::CoaAction(CoaSettingsWidget * const parent)
:QAction(parent)
,m_actionId(0)
,m_enabledForDefaultToolbar(true)
,m_enabledForToolbar(true)
,m_defaultShortcut("")
,m_iconPath("")
{
   BEGIN;
}




CoaAction::CoaAction(const int Id, QObject * const parent)
:QAction(parent)
,m_actionId(Id)
,m_enabledForDefaultToolbar(true)
,m_enabledForToolbar(true)
,m_defaultShortcut("")
,m_iconPath("")
{
   BEGIN;
   setObjectName("CoaAction");
}




CoaAction::CoaAction(const int Id, const CoaString& objectName, QObject * parent)
:QAction(parent)
,m_actionId(Id)
,m_enabledForDefaultToolbar(true)
,m_enabledForToolbar(true)
,m_defaultShortcut("")
{
   BEGIN;
   setObjectName(objectName);
}

CoaAction::CoaAction(const CoaString& Id, QObject * const parent)
: QAction(parent)
, m_actionId(0)
, m_actionIdStr(Id)
, m_enabledForDefaultToolbar(true)
, m_enabledForToolbar(true)
, m_defaultShortcut("")
{
   BEGIN;
   setObjectName("CoaAction");
}


CoaAction::CoaAction(const CoaString& Id, const CoaString& objectName, QObject * const parent)
:QAction(parent)
, m_actionId(0)
, m_actionIdStr(Id)
, m_enabledForDefaultToolbar(true)
, m_enabledForToolbar(true)
, m_defaultShortcut("")
{
   BEGIN;
   setObjectName(objectName);
}




CoaAction::~CoaAction()
{
   BEGIN;
}


bool CoaAction::enabledForDefaultToolbar() const
{
   BEGIN;
   RETURN(m_enabledForDefaultToolbar);
   //return m_enabledForDefaultToolbar;
}



void CoaAction::setEnabledForDefaultToolbar(bool enabled)
{
   BEGIN;
   m_enabledForDefaultToolbar = enabled;
}



bool CoaAction::enabledForToolbar() const
{
   BEGIN;
   RETURN(m_enabledForToolbar);
   //return m_enabledForToolbar;
}

void CoaAction::handleSignal(CoaSignal const*const)
{
   BEGIN;
}



void CoaAction::setEnabledForToolbar(bool enabled)
{
   //BEGIN;
   m_enabledForToolbar = enabled;
}


CoaString CoaAction::defaultShortcut() const
{
   return m_defaultShortcut;
}

void CoaAction::setDefaultShortcut(const CoaString& shortcut)
{
   m_defaultShortcut = shortcut;
}


void CoaAction::handleTriggered()
{
   BEGIN;
   INF(CoaString("Action %1: handleTriggered()").arg(objectName()));
}

void  CoaAction::makeWhatsthisHelptext()
{
   BEGIN;

   CoaString what="";

   //Add the Name
   CoaString name = text();
   name.remove(QChar('&'));
   what = what +  "<H3>";

   what = what +  name;
   if (!m_iconPath.isEmpty()) {
      what = what +  "<IMG SRC=\"" + m_iconPath +"\" ALIGN=LEFT>";
   }
   what = what +  "</H3>";
   what = what +  "<TABLE BORDER=0 CELLPADDING=5 CELLSPACING=5>\n";


   //Description
   what = what + "<TR VALIGN=TOP>\n";
   what = what + "<TD><b>"+ tr("Description")      +"</b></TD>\n";
   what = what + "<TD>  " + m_defaultWhatsthisText  +    "</TD>\n";
   what = what + "</TR>\n";


   //Second Line (Shortcut)
   QKeySequence sequence = shortcut();
   CoaString scut = sequence;


   if (!scut.isEmpty()) {
      what = what + "<TR VALIGN=TOP>\n";
      what = what + "<TD><b>" + tr("Shortcut") + "</b></TD>\n";
      what = what + "<TD>"     + scut          +     "</TD>\n";
      what = what + "</TR>\n";
   } else {
   }


   what = what + "</TABLE>\n";
   QAction::setWhatsThis(what);
}


void CoaAction::setWhatsThis ( const CoaString & what )
{
   BEGIN;
   m_defaultWhatsthisText = what;
   makeWhatsthisHelptext();
}


void CoaAction::setShortcut ( const QKeySequence & shortcut )
{
   BEGIN;
   if (shortcut == m_defaultShortcut){
      removeSavedShortcut();
   } else {
      saveShortcut(shortcut);
   }

   QAction::setShortcut(shortcut);
   makeWhatsthisHelptext();
}


void CoaAction::setActionBlock (const CoaString& block)
{
   BEGIN;
   m_actionBlock = block;
}


CoaString CoaAction::actionBlock () const
{
   BEGIN;
   RETURN(m_actionBlock);
}



//!@brief Return the Action Text without the & char
CoaString CoaAction::pureText() const
{
   BEGIN;
   CoaString t = text();
   t.remove(QChar('&'));
   return t;
}


void CoaAction::removeSavedShortcut()
{
   BEGIN;
   if (text().isEmpty()) return;
   CoaSettings settings;
   settings.beginGroup(SETTING_SHORTCUT);
   settings.remove(text());
   settings.endGroup();
}


void CoaAction::saveShortcut(const QKeySequence & shortcut )
{
   BEGIN;
   if (text().isEmpty()) return;
   CoaSettings settings;
   settings.beginGroup(SETTING_SHORTCUT);
   const CoaString key(shortcut);
   settings.setValue(text(), key);
   settings.endGroup();

}

QKeySequence CoaAction::loadSavedShortcut( const QKeySequence& def ) const
{
   BEGIN;
   if (text().isEmpty()) return QKeySequence();
   CoaSettings settings;
   settings.beginGroup(SETTING_SHORTCUT);
   const CoaString key(def);
   QKeySequence seq(settings.value( text(), def).toString());
   settings.endGroup();
   return seq;
}

bool CoaAction::compareActionsOnText(CoaAction const*const a1, CoaAction const*const a2)
{
   BEGIN;
   return a1->pureText() < a2->pureText();
}


CoaString CoaAction::defaultWhatsThisText() const
{
   BEGIN;
   RETURN(m_defaultWhatsthisText);
}

void CoaAction::setIcon(const QIcon& icon)
{
   BEGIN;
   QAction::setIcon(icon);
}


void CoaAction::setIcon(const CoaString& iconPath)
{
   BEGIN;
   m_iconPath = iconPath;
   setIcon(QIcon(m_iconPath));
}


CoaString CoaAction::iconPath() const
{
   BEGIN;
   return m_iconPath;
}

void CoaAction::setStringId (const CoaString& id)
{
   BEGIN;
   m_actionIdStr = id;
}


CoaString CoaAction::stringId (void) const
{
   BEGIN;
   RETURN(m_actionIdStr);
}


