//Header file of the class Dialog.h
//file: dialog.h

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMenuBar>
#include <QTextEdit>
#include <QToolBar>
#include "purchaselist.h"
#include "itemlist.h"

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    bool saleFinalised;
    QMenuBar* a1Meubar;
    QTextEdit* a1Display;
    QToolBar* a1ToolBar;
    QMenu* saleMenu;
    QMenu* itemMenu;

    PurchaseList* a1PurchaseList;
    ItemList* a1StockList;

private slots:
    void newSale();
    void cancelSale();
    void finaliseSale();
    void exitCashRegister();
    void addItemToSale();
    void removeItemFromSale();
};

#endif // DIALOG_H
