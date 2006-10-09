#include "actionmodel.h"
#include <CoaDebug>
#include <CoaXmlItemModelReference>
#include <QRegExp>
#include <CoaXmlItemModel>




const CoaString DOCDESCRIPTION="CoaActionSetDescription";
const CoaString DOCVERSION    ="1.0";



   //Constructors
ActionModel::ActionModel (QObject *const parent)
: CoaXmlItemModel(parent)
{
   BEGIN;
   setDocumentType(DOCDESCRIPTION);
   setDocumentVersion(DOCVERSION);

   //Mapping attribute name 2 id and opposit

   //for actions
   setAttributeAndId("action", "name"      ,0 );
   setAttributeAndId("action", "icon"      ,1 );
   setAttributeAndId("action", "text"      ,2 );
   setAttributeAndId("action", "tooltip"   ,3 );
   setAttributeAndId("action", "shortcut"  ,4 );
   setAttributeAndId("action", "whatsthis" ,5 );

   //for folders
   setAttributeAndId("folder", "name"      ,0 );
   setAttributeAndId("folder", "folded"    ,1 );

}





ActionModel::~ActionModel ()
{
   BEGIN;
}





bool ActionModel::saveChanges()
{
   BEGIN;
   RETURN(false);
}




int ActionModel::columnCount ( const QModelIndex & parent ) const
{
   CoaString tagName = index2TagName (parent);
   if (tagName == "action") return 6 + 1; //1 for the element itselfActionDocument
   if (tagName == "folder") return 1 + 1; //1 for the element itselfActionDocument
   if (tagName.isEmpty()) return 0;
   return 1; //default
}







/**
@todo Test auf ungueltige Werte, etwa Umlaute
*/
bool ActionModel::setData ( const QModelIndex & index, const QVariant & value, int role )
{
   BEGIN;

   RETURN(false);
   CoaString s = value.toString();

   //Some checks
   if (role != Qt::EditRole)            RETURN(false);
   if (!index.isValid())                RETURN(false);
   if (s.isEmpty())                     RETURN(false);
   if (s.indexOf(QRegExp("\\s")) != -1) RETURN(false);

   //store the changes
   QDomElement e = index2DomElement(index);
   e.setTagName(s);

   //test it
   if (e.tagName() != s)              RETURN(false);
   RETURN(true);
}




Qt::ItemFlags ActionModel::flags ( const QModelIndex & index ) const
{
   if (!index.isValid())
      return Qt::ItemIsEnabled| Qt::ItemIsSelectable;

   if (index.column() == 0) {
      return CoaAbstractItemModel::flags(index) | Qt::ItemIsEditable| Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
   } else {
      return Qt::ItemIsEnabled | Qt::ItemIsSelectable;;
   }
}


QVariant ActionModel::data ( const QModelIndex & index, int role ) const
{
   switch( role )
   {
   case Qt::DisplayRole:
   case Qt::EditRole:
   {
      //get the reference
      CoaXmlItemModelReference * const ref = index2reference(index);

      //check the reference
      if (ref == 0)        return QVariant();
      if (!ref->isValid()) return QVariant();

      if (index.column()> 0) INF(QString("columnd: %1").arg(index.column()));

       //react on tagName
      QDomElement e = ref->toElement();
      if (e.isNull()) return QVariant();
      return e.attribute(mapIndex2AttributeName(index, ""));
    }
   }

   return(QVariant());

}


