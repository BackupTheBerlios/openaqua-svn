#ifndef DIALOG_H
#define DIALOG_H

#include <CoaDialog>
#include "testserver.h"

class CoaLabel;
class CoaPushButton;

class Dialog : public CoaDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);

private:
    CoaLabel *statusLabel;
    CoaPushButton *quitButton;
    TestServer server;
};

#endif
