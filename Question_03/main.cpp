/*
 * Assignment_03:   Question_01
 * Name:            Reuven Muller
 * Student number:  54790344
 * Unique code:     894050
 *
 * GUI app testing a cash register system
 *
 */

#include "dialog.h"
#include <QApplication>
#include "item.h"
#include "purchaselist.h"
#include "itemlist.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Dialog w;
    w.show();

    return a.exec();
}
