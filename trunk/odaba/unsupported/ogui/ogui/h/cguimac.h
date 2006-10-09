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

#define QCOLOR2DCOLOR(d) \
  DColor((d).red(), (d).green(), (d).blue())

#define DCOLOR2QCOLOR(d) \
  QColor((d).Red(), (d).Green(), (d).Blue())

#define COLOR2DCOLOR(o) \
  DColor( (o).GetInt("ColorValue.clrred"), \
          (o).GetInt("ColorValue.clrgreen"), \
          (o).GetInt("ColorValue.clrblue") )
