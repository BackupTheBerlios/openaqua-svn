/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|16:34:35,87}|(REF)
\class    OIconSet

\brief    


\date     $Date: 2006/03/29 15:22:30,96 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OIconSet"

#include  <pogui7.h>
#include  <sDPixmap.hpp>
#include  <sOPixmap.hpp>
#include  <sOIconSet.hpp>


/******************************************************************************/
/**
\brief  OIconSet - 


-------------------------------------------------------------------------------
\brief  i0


\param  pDPixmap_normal - 
\param  pDPixmap_active - 
\param  pDPixmap_disabled - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OIconSet"

                        OIconSet :: OIconSet (DPixmap *pDPixmap_normal, DPixmap *pDPixmap_active, DPixmap *pDPixmap_disabled )
                     : QIcon ()
{
  QSize            size;
  if ( pDPixmap_normal )
    addFile(pDPixmap_normal->GetUsedPath(),size,QIcon::Normal);
  
  if ( pDPixmap_active )
    addFile(pDPixmap_active->GetUsedPath(),size,QIcon::Active);
  
  if ( pDPixmap_disabled )
    addFile(pDPixmap_disabled->GetUsedPath(),size,QIcon::Disabled);


}

/******************************************************************************/
/**
\brief  i01


\param  pQPixmap_normal - 
\param  pQPixmap_active - 
\param  pQPixmap_disabled - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OIconSet"

                        OIconSet :: OIconSet (QPixmap *pQPixmap_normal, QPixmap *pQPixmap_active, QPixmap *pQPixmap_disabled )
                     : QIcon ()
{

  if ( pQPixmap_normal )
    addPixmap(*pQPixmap_normal,
              QIcon::Normal, QIcon::On);
  
  if ( pQPixmap_active )
    addPixmap(*pQPixmap_active,
              QIcon::Active, QIcon::On);
  
  if ( pQPixmap_disabled )
    addPixmap(*pQPixmap_disabled,
              QIcon::Disabled, QIcon::On);

}

/******************************************************************************/
/**
\brief  i02


\param  szName - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OIconSet"

                        OIconSet :: OIconSet (std_string szName )
                     : QIcon()
{

 // create a iconset from a filepattern
 // appdir/icons/qstext_[normal|active|diabled].png
 // l:\ode8t
 std_string snormal   = "res/icons/" + szName + "_normal.png";
 std_string sdisabled = "res/icons/" + szName + "_disabled.png";
 std_string sactive   = "res/icons/" + szName + "_active.png";
 addFile(QString::fromStdString(snormal),QSize(),QIcon::Normal);
 addFile(QString::fromStdString(sdisabled),QSize(),QIcon::Disabled);
 addFile(QString::fromStdString(sactive),QSize(),QIcon::Active);

}


