//Header file of the class PurchaseList.h
//file: purchaselist.h


#ifndef PURCHASELIST_H
#define PURCHASELIST_H

#include "item.h"
#include "itemlist.h"

#include <QString>


class PurchaseList: public QList<Item*>
{
public:
    PurchaseList(ItemList *sList);
    ~PurchaseList();
    //adds the purchase with a barcode to the purchase list also updates stock list
    void addPurchase(QString bc);
    //removes the purchase with a barcode from the purchase list also updates stock list
    void removePurchase(QString bc);
    //writes the purchase list to a textfile with with the current date and time as its name
    void toTextFile();

private:
    ItemList *stockList;
};

#endif // PURCHASELIST_H
