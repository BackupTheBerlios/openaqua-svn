#ifndef __CoaSqlConnectionWidget_h__
#define __CoaSqlConnectionWidget_h__

#include <CoaTreeWidget>
#include <CoaSqlDatabase>
#include <CoaString>


class CoaSqlConnectionWidget: public CoaTreeWidget
{
    Q_OBJECT
public:
    CoaSqlConnectionWidget(QWidget *parent = 0);
    virtual ~CoaSqlConnectionWidget();

    CoaSqlDatabase currentDatabase() const;

signals:
    void tableActivated(const CoaString &table);

public slots:
    void refresh();
    void slotItemActivated(QTreeWidgetItem *item, int column);

private:
   //!returns a formated database name in form Driver:Username@Database
   CoaString qDBCaption(const QSqlDatabase &db);

   void setActive(QTreeWidgetItem *);
   CoaString m_activeDb;
};

#endif
