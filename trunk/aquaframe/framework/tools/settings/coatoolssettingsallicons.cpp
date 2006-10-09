#include "coatoolssettingsallicons.h"
#include <CoaDebug>
#include <CoaAction>
#include <CoaWidget>
#include <CoaPushButton>

#include <QVBoxLayout>



CoaToolsSettingsAllIcons::CoaToolsSettingsAllIcons( QWidget * const parent, Qt::WFlags f)
: CoaSettingsWidget(parent, f)
, m_mainLayout(0)
{
   BEGIN;
   Q_INIT_RESOURCE(tools);
   buildGui();
   setShortName(tr("Show All"));
   setIcon(":/tools/settings/icons/showall.png");
}



CoaToolsSettingsAllIcons::~CoaToolsSettingsAllIcons()
{
   BEGIN;
}


bool CoaToolsSettingsAllIcons::applyChanges()
{
   BEGIN;
   RETURN(true);
}


void CoaToolsSettingsAllIcons::buildGui()
{
   BEGIN;

   //setup the action
   CoaAction *action = widgetAction();
   assert(action);
   action->setToolTip (tr("Show All Setting Pages"));
   action->setStatusTip(action->toolTip());
   action->setText(action->iconText());
   action->setWhatsThis(tr("If you click on this icon a ..."));

   //setup the mainView
   m_mainLayout = new QVBoxLayout(this);
   setLayout(m_mainLayout);
}


void CoaToolsSettingsAllIcons::addSettingsWidget(CoaSettingsWidget *const widget)
{
   BEGIN;
   assert(widget);
   if (widget == 0) return;

   const CoaString group = widget->groupName();

   //create a empty frame
   if (!m_widgetGroups.contains (group)){
      CoaGroupBox *frame = new CoaGroupBox(this);
      frame->setFlat(true);
      frame->setTitle(group);
      frame->setChecked(false);
      frame->setLayout(new QHBoxLayout(frame));
      m_widgetGroups[group] = frame;
      assert(m_mainLayout);
      m_mainLayout->addWidget(frame);
   }

   //add an icon to a group frame
   CoaToolButton * btn = new CoaToolButton ();
   btn->setText(widget->widgetAction()->text());
   btn->setIcon(widget->widgetAction()->icon());
   connect(btn, SIGNAL(clicked()), widget->widgetAction(), SIGNAL(triggered ()));
   makeLayoutWidgetButtons(btn);

   QObject* object = m_widgetGroups[group];
   CoaGroupBox *frame = dynamic_cast<CoaGroupBox*>(object);
   assert(frame);

   QBoxLayout *layout = dynamic_cast<QBoxLayout *>(frame->layout());
   assert(layout);
   if (layout != 0){
      QSpacerItem *s = dynamic_cast<QSpacerItem*>(layout->itemAt (layout->count()-1));
      if (s != 0) {
         layout->removeItem(s);
      }
      layout->addWidget(btn);
      layout->addStretch();
   }


}



void CoaToolsSettingsAllIcons::remSettingsWidget(CoaSettingsWidget *const widget)
{
   BEGIN;
   assert(widget);
   if (widget == 0) return;

   const CoaString group = widget->groupName();
   if (m_widgetGroups.contains (group)){

      //get the right box/layout
      CoaGroupBox *box = dynamic_cast<CoaGroupBox*>(m_widgetGroups[group]);
      if (box == 0) return;
      QBoxLayout *layout = dynamic_cast<QBoxLayout *>(box->layout());

      //iterate over the layout item and get the correct Button
      for (int i = 0; i < layout->count(); ++i){
         QLayoutItem *item = layout->itemAt(i);
         if (item == 0) {
            ERR("NULL value in Layout");
            return;
         }
         CoaPushButton *btn = dynamic_cast<CoaPushButton*>(item->widget());
         if (btn != 0){
            //if (btn->defaultAction() == widget->widgetAction()){
            //   delete btn;
            //}
         }
      }
   } else {
      WRN(QString("Group <%1> not known").arg(group));
   }
}


void CoaToolsSettingsAllIcons::makeLayoutWidgetButtons(CoaToolButton *const button)
{
   BEGIN;
   assert(button);
   if (button == 0) return;
   button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
   button->setIconSize(QSize(64,64));
   button->setMinimumSize(QSize(94, 94));
   button->setMaximumSize(button->minimumSize());
   //button->setFlat(true);
   //button->setAutoDefault(false);
   button->setBackgroundRole(QPalette::Base);
}


bool CoaToolsSettingsAllIcons::canApplyDefaults() const
{
   BEGIN;
   RETURN(false);
}

bool CoaToolsSettingsAllIcons::applyDefaults()
{
   BEGIN;
   RETURN(false);
}
