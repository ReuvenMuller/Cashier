//Implementation of the PurchaseList class
//file: purchaselist.cpp

#include "purchaselist.h"
#include "itemwriter.h"
#include <QDateTime>
#include <QString>

PurchaseList::PurchaseList(ItemList * sList)
{
    stockList = sList;
}

//adds the purchase with a barcode to the purchase list also updates stock list
void PurchaseList::addPurchase(QString bc)
{
    Item *currentItem = stockList->findItem(bc);
    if(currentItem != NULL)
    {
        currentItem->setStock((currentItem->getStock() - 1));
        append(currentItem);
    }
}

//removes the purchase with a barcode from the purchase list also updates stock list
void PurchaseList::removePurchase(QString bc)
{
    Item *currentItem = stockList->findItem(bc);
    for (int i(0);i < size();i++)
    {
        if(at(i)->getBarcode() == bc)
        {
            currentItem->setStock((currentItem->getStock()) + 1);
            removeAt(i);
        }
    }
}

//writes the purchase list to a textfile with with the current date and time as its name
void PurchaseList::toTextFile()
{
    QDateTime d;
    QString flname = d.currentDateTime().toString("MMM hh mm ss zz");
    flname.append(".text");
    ItemWriter iWriter(flname);
    for (int i(0);i < size();i++)
    {
        iWriter.writeItem(*at(i));
    }
}

PurchaseList::~PurchaseList()
{
    delete stockList;
}
