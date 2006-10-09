#ifndef __CoaIoStream_h__
#define __CoaIoStream_h__

#include <ostream>
#include <QString>
#include <QModelIndex>


std::ostream& operator<< (std::ostream& out, const QString& string);
std::ostream& operator<< (std::ostream& out, const QModelIndex& index);


#endif //__CoaIoStream_h__
