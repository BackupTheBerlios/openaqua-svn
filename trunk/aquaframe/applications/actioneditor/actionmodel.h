#ifndef __ActionModel_h__
#define __ActionModel_h__

#include <CoaXmlItemModel>


class ActionModel: public CoaXmlItemModel{
Q_OBJECT

public:

   //Constructors
   explicit ActionModel (QObject *const parent = 0 );
   virtual ~ActionModel ();
   virtual bool saveChanges();
   virtual int columnCount ( const QModelIndex & parent ) const;

   bool loadXmlData (CoaIODevice * const device);
   bool loadXmlData (const CoaDomDocument& doc, const bool deepCopy = false);

   //Editing
   virtual bool setData ( const QModelIndex & index, const QVariant & value, int role );
   virtual Qt::ItemFlags flags ( const QModelIndex & index ) const;

   //Reading
   virtual QVariant data ( const QModelIndex & index, int role ) const;


public slots:


private:
   //no default constructors
   ActionModel(const ActionModel&);
   ActionModel();



};

#endif //__ActionModel_h__

