#include <cqt.h>

#define DPOINT2QPOINT(d) \
  QPoint( d.X, d.Y )

#define DRECT2QRECT(d) \
  QRect( d.Origin.X, d.Origin.Y, d.Size.Width, d.Size.Height )

#define QPOINT2DPOINT(d) \
  DPoint( d.x(), d.y() )

#define QSIZE2DSIZE(d) \
  DSize( d.width(), d.height() )

#define DSIZE2QSIZE(d) \
  QSize( d.Width, d.Height )

#define QRECT2DRECT(d) \
  DRect( d.left(), d.top(), d.width(), d.height() )

#define OPS2DPOINT(o) \
  DPoint( (o).GetInt("opsx"), (o).GetInt("opsy") ) 

#define OSZ2DSIZE(o) \
  DSize( (o).GetInt("oszwdth"), (o).GetInt("oszhgth") ) 

#define MARGIN2DMARGIN(o) \
  DMargin( (o).GetInt("left"), \
           (o).GetInt("top"), \
           (o).GetInt("right"),\
           (o).GetInt("bottom") )

#define COLOR2DCOLOR(o) \
  DColor( (o).GetInt("ColorValue.clrred"), \
          (o).GetInt("ColorValue.clrgreen"), \
          (o).GetInt("ColorValue.clrblue") )

#define OADIPROPERR( pname, pv ) \
  { OADIEV1( CC (pname), strlen( pname ? pname : "" ) ) \
  OADIEV2( CC (pv), strlen( pv ? pv : "" ) ) \
  OADIERR(100) }

#define ADKFACTORY(ph,dest) \
  ((dest*) OADKFactory::Factory()->New(ph,#dest) )

#define CACHE_READ(ph,name,dest) \
((dest*) ObjectInfo::StaticCast(TProjectManager::TPM->GetResource(ph,name),#dest))

inline PropertyHandle* PHREF( PropertyHandle* ph )
{
  return ph ? (ph->Get() ? ph : 0) : 0;
}

inline uint32 PHID( PropertyHandle* ph )
{
  return ph ? ph->GetLOID(0) : 0;
}

#define QMOUSEBUTTON2DMOUSEBUTTON(d) \
  DMouseButton( d & Qt::LeftButton, \
                d & Qt::RightButton, \
                d & Qt::MidButton, \
                d & Qt::ShiftButton, \
                d & Qt::ControlButton, \
                d & Qt::AltButton )

#define QMOUSEEVENT2AMOUSE(d,p) \
  AMouse( QMOUSEBUTTON2DMOUSEBUTTON( d->button() ), \
          QMOUSEBUTTON2DMOUSEBUTTON( d->state() ), \
          QMOUSEBUTTON2DMOUSEBUTTON( d->stateAfter() ), \
          QPOINT2DPOINT( p ), \
          QPOINT2DPOINT( d->globalPos() )