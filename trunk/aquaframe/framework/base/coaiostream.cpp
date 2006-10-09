#include "coaiostream.h"



std::ostream& operator<< (std::ostream& out, const QString& string)
{

   out << string.toUtf8().data();
   return out;
}


std::ostream& operator<< (std::ostream& out, const QModelIndex& index)
{
   if (!index.isValid()){
      out << "valid=false";
   } else {
      out << "valid=true"
          << " row=" << index.row()
          << " col="<<index.column()
          << " id=" << index.internalId ()
      ;
      if (!index.parent().isValid()){
         out << " parent=(valid=false)";
      } else {
         out << " parent=(valid=true"
             << " row="<< index.parent().row()
             << " col="<< index.parent().column()
             << " id=" << index.parent().internalId ()
             << ')';
      }
   }


   return out;
}



