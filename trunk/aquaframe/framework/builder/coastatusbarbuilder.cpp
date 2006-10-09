#include "coastatusbarbuilder.h"
#include <cassert>
#include <CoaDebug>
#include <CoaMainWindow>
#include <CoaStatusBar>


CoaStatusBarBuilder::CoaStatusBarBuilder()
{
   BEGIN;
}



CoaStatusBar* CoaStatusBarBuilder::load(CoaFile* file, CoaMainWindow *parent)
{
   BEGIN;
   Q_UNUSED(file);
   CoaStatusBar *bar = new CoaStatusBar(parent);
   assert(bar);
   return bar;
}
