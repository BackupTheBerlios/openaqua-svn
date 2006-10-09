//#include <cstdlib>

#include <CoaMessageBox>
#include <CoaHBoxLayout>
#include <CoaVBoxLayout>
#include <CoaLabel>

#include "dialog.h"
#include "testserver.h"

Dialog::Dialog(QWidget *parent)
    : CoaDialog("Dialog", parent)
{
   BEGIN;
    statusLabel = new CoaLabel;
    quitButton = new CoaPushButton(tr("Quit"));
    quitButton->setAutoDefault(false);

    if (!server.listen(QHostAddress::Any, 32000)) {
        CoaMessageBox::critical(this, tr("Threaded Fortune Server"),
                              tr("Unable to start the server: %1.")
                              .arg(server.errorString()));
        close();
        return;
    }

    statusLabel->setText(tr("The server is running on port %1.\n"
                            "Run the Fortune Client example now.")
                         .arg(server.serverPort()));

    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    CoaHBoxLayout *buttonLayout = new CoaHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitButton);

    CoaVBoxLayout *mainLayout = new CoaVBoxLayout;
    mainLayout->addWidget(statusLabel);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Threaded Fortune Server"));
}
