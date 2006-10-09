#ifndef __CoaAction_h__
#define __CoaAction_h__


#include <QAction>
#include <CoaString>
#include <QKeySequence>


class CoaSettingsWidget;
class CoaSignal;

class QObject;

class CoaAction: public QAction
{
   Q_OBJECT

public:
   CoaAction(CoaSettingsWidget * const parent);
   CoaAction(const int Id, QObject * const parent = 0 );
   CoaAction(const int Id, const CoaString& objectName, QObject * const parent = 0 );
   CoaAction(const CoaString& Id, QObject * const parent = 0 );
   CoaAction(const CoaString& Id, const CoaString& objectName, QObject * const parent = 0 );
   virtual ~CoaAction();

   virtual bool enabledForDefaultToolbar() const;
   virtual void setEnabledForDefaultToolbar(bool enabled);

   virtual bool enabledForToolbar() const;
   virtual void setEnabledForToolbar(bool enabled);

   virtual CoaString defaultShortcut() const;
   virtual void setDefaultShortcut(const CoaString& shortcut);

   virtual void setWhatsThis ( const CoaString & what );
   virtual void makeWhatsthisHelptext();
   virtual void setShortcut ( const QKeySequence & shortcut );

   virtual void setActionBlock (const CoaString& block);
   virtual CoaString actionBlock () const;
   virtual CoaString defaultWhatsThisText() const;

   inline const int id (void) const;

   void setStringId (const CoaString& id);
   CoaString stringId (void) const;

   //!@brief Return the Action Text without the & char
   virtual CoaString pureText() const;
   virtual void removeSavedShortcut( );
   virtual void saveShortcut(const QKeySequence & shortcut );
   virtual QKeySequence loadSavedShortcut( const QKeySequence& def ) const;

   /**
   @brief compare actions on base of the action text

   This method can be used to sort CoaAction in a List like
   @code
   List<CoaAction*> list;
   list << new CoaAction("foo");
   list << new CoaAction("bar");
   list << new CoaAction("FooBar");
   qSort(list.begin(), list.end(), caseCompareActionText);
   @endcode


   */
   static  bool compareActionsOnText(CoaAction const*const a1, CoaAction const*const a2);

   void setIcon(const CoaString& iconPath);
   CoaString iconPath() const;
   void setIcon(const QIcon& icon);

public slots:
   virtual void handleSignal(CoaSignal const*const);

   virtual void handleTriggered();


signals:
   void signal(CoaSignal const*const);


private:
   CoaAction ( ); //not implemented
   CoaAction ( const QIcon & icon, const CoaString & text, QObject * parent ); //not implemented

   const int          m_actionId;
   CoaString          m_actionIdStr;
   bool               m_enabledForDefaultToolbar; //default true
   bool               m_enabledForToolbar; //default true
   QKeySequence       m_defaultShortcut;
   CoaString          m_defaultWhatsthisText;
   CoaString          m_actionBlock;
   CoaString          m_iconPath;
};


inline const int CoaAction::id (void) const
{
   return m_actionId;
}




#endif //__CoaCommand_h__
