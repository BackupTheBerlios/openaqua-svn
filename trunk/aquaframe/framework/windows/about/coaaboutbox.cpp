#include "coaaboutbox.h"

#include <CoaDebug>
#include <cassert>
#include <CoaFormFactory>
#include <CoaAction>
#include <CoaApplication>
#include <CoaSingletonWatch>
#include <CoaTextBrowser>
#include <CoaLabel>
#include <CoaFile>




COAMAKRO_DEFINE_SINGLETONMETHODS(CoaAboutBox);

CoaAboutBox::CoaAboutBox()
: CoaToolWindow("CoaAboutBox", 0)
{
   BEGIN;

   //Create the central form
   Q_INIT_RESOURCE(about);
   CoaFormFactory factory(this);
   factory.formBuild(":/about/coaaboutbox.ui");

   setWindowTitle(QString(tr("About: %1")).arg("Applicationname"));

   CoaLabel *labelIcon  = qFindChild<CoaLabel*>(this, "labelIcon");
   labelIcon->setPixmap(QPixmap(":/about/about_coa.png"));

   initLicencePage();
   initApplicationPage();

   readSettings();
}




CoaAboutBox::~CoaAboutBox()
{
   BEGIN;
   writeSettings();
}


void CoaAboutBox::initLicencePage()
{
   BEGIN;
   CoaTextBrowser *text  = qFindChild<CoaTextBrowser*>(this, "browserLicence");
   if (text == 0) {
      ERR("Cannot find Widget \"browserLicence\"");
      return;
   }

   CoaFile file(":/about/licence.html");
   if (file.open(QIODevice::ReadOnly)) {
      INF(QString("Build Licence text from file <%1>").arg(file.fileName()))
      QString html(file.readAll());
      text->setHtml(html);
      file.close();
   } else {
      WRN(QString("Cannot find licence text file <%1>").arg(file.fileName()))
      text->setHtml("<h3>Licence not found</h3>");
   }

   text = 0;
}



void CoaAboutBox::initApplicationPage()
{
   BEGIN;
   CoaLabel *labelApplication  = qFindChild<CoaLabel*>(this, "labelApplication");
   CoaLabel *labelVersion  = qFindChild<CoaLabel*>(this, "labelVersion");

   labelApplication->setTextFormat(Qt::RichText);
   labelApplication->setWordWrap(true);
   labelApplication->setText(QString("<H3>%1</H3").arg(COAAPP->applicationName()));
   labelApplication = 0;

   labelVersion->setTextFormat(Qt::RichText);
   labelVersion->setWordWrap(true);
   labelVersion->setText(QString("<H3>Version: %1</H3").arg("0.0.1"));
   labelVersion = 0;

}
