//Implementation of the Dialog class
//file: dialog.cpp

#include "dialog.h"
#include <QVBoxLayout>
#include <QMenu>
#include <QPixmap>
#include <QMessageBox>
#include <QInputDialog>
#include <QString>
#include <QLineEdit>
#include "item.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setFixedWidth(width()*0.8);

    //When the program starts the items stored in the STOCK textfile are loaded into the stock list
    a1StockList = new ItemList();
    a1StockList->readList(":/Question_03/STOCK.text");
    saleFinalised = true;

    //png pics from myresources.qrc
    QPixmap iconA = QPixmap(":/Question_03/a.png");
    QPixmap iconC = QPixmap(":/Question_03/c.png");
    QPixmap iconF = QPixmap(":/Question_03/f.png");
    QPixmap iconN = QPixmap(":/Question_03/n.png");
    QPixmap iconR = QPixmap(":/Question_03/r.png");
    QPixmap iconX = QPixmap(":/Question_03/x.png");

    saleMenu = new QMenu();
    itemMenu = new QMenu();

    //multiple signals connected to the same slots for toolbar and menu bar
    itemMenu->setTitle("Item");
    itemMenu->addAction(iconA,"Add",this, SLOT(addItemToSale()));
    itemMenu->addAction(iconR,"Remove",this, SLOT(removeItemFromSale()));

    saleMenu->setTitle("Sale");
    saleMenu->addAction(iconN,"New",this, SLOT(newSale()));
    saleMenu->addAction(iconC,"Cancel",this, SLOT(cancelSale()));
    saleMenu->addAction(iconF,"Finalise",this, SLOT(finaliseSale()));
    saleMenu->addAction(iconX,"Exit",this, SLOT(exitCashRegister()));

    a1Meubar = new QMenuBar(0);
    a1Meubar->addMenu(saleMenu);
    a1Meubar->addMenu(itemMenu);

    a1Display = new QTextEdit();
    a1Display->setReadOnly(true);

    a1ToolBar = new QToolBar();
    a1ToolBar->addAction(iconN,"",this, SLOT(newSale()));
    a1ToolBar->addAction(iconC,"",this,SLOT(cancelSale()));
    a1ToolBar->addAction(iconF,"",this, SLOT(finaliseSale()));
    a1ToolBar->addAction(iconX,"",this, SLOT(exitCashRegister()));
    a1ToolBar->addSeparator();
    a1ToolBar->addAction(iconA,"",this, SLOT(addItemToSale()));
    a1ToolBar->addAction(iconR,"",this, SLOT(removeItemFromSale()));

    //enabling and disabling menu and toolbar buttons
    saleMenu->actions().at(0)->setEnabled(true);
    saleMenu->actions().at(1)->setEnabled(false);
    saleMenu->actions().at(2)->setEnabled(false);
    saleMenu->actions().at(3)->setEnabled(true);
    itemMenu->actions().at(0)->setEnabled(false);
    itemMenu->actions().at(1)->setEnabled(false);

    a1ToolBar->actions().at(0)->setEnabled(true);
    a1ToolBar->actions().at(1)->setEnabled(false);
    a1ToolBar->actions().at(2)->setEnabled(false);
    a1ToolBar->actions().at(3)->setEnabled(true);
    a1ToolBar->actions().at(5)->setEnabled(false);
    a1ToolBar->actions().at(6)->setEnabled(false);


    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(a1Meubar,0,0);
    layout->addWidget(a1Display,0,0);
    layout->addWidget(a1ToolBar,0,0);
    setLayout(layout);
    setWindowTitle("Cash Register");

}

Dialog::~Dialog()
{

}

//Slot: intialises a new sale and disables some options
void Dialog::newSale()
{
    a1PurchaseList = new PurchaseList(a1StockList);
    saleFinalised = false;

    saleMenu->actions().at(0)->setEnabled(false);
    saleMenu->actions().at(1)->setEnabled(true);
    saleMenu->actions().at(2)->setEnabled(true);
    saleMenu->actions().at(3)->setEnabled(true);
    itemMenu->actions().at(0)->setEnabled(true);
    itemMenu->actions().at(1)->setEnabled(true);

    a1ToolBar->actions().at(0)->setEnabled(false);
    a1ToolBar->actions().at(1)->setEnabled(true);
    a1ToolBar->actions().at(2)->setEnabled(true);
    a1ToolBar->actions().at(3)->setEnabled(true);
    a1ToolBar->actions().at(5)->setEnabled(true);
    a1ToolBar->actions().at(6)->setEnabled(true);

}

//Slot: removes current sale and disables some options
void Dialog::cancelSale()
{

    int confirm(0);
    confirm = QMessageBox::question(0,"Cancel Sale", "Are you sure you want to cancel",QMessageBox::Yes | QMessageBox::No);
    if (confirm == QMessageBox::Yes)
    {
        a1Display->clear();
        for (int i(0);i < a1PurchaseList->size();i++)
        {
            a1PurchaseList->removePurchase(a1PurchaseList->at(i)->getBarcode());
        }

        saleMenu->actions().at(0)->setEnabled(true);
        saleMenu->actions().at(1)->setEnabled(false);
        saleMenu->actions().at(2)->setEnabled(false);
        saleMenu->actions().at(3)->setEnabled(true);
        itemMenu->actions().at(0)->setEnabled(false);
        itemMenu->actions().at(1)->setEnabled(false);

        a1ToolBar->actions().at(0)->setEnabled(true);
        a1ToolBar->actions().at(1)->setEnabled(false);
        a1ToolBar->actions().at(2)->setEnabled(false);
        a1ToolBar->actions().at(3)->setEnabled(true);
        a1ToolBar->actions().at(5)->setEnabled(false);
        a1ToolBar->actions().at(6)->setEnabled(false);

        saleFinalised = true;

    }
    else
    {
        //Nothing
    }

}

//Slot: Adjusts stock list textfile and purchase list textfile created disables some options
void Dialog::finaliseSale()
{
    int paid(0);
    paid = QMessageBox::question(0,"Payment","Has payment been received?",QMessageBox::Yes | QMessageBox::No);
    if (paid == QMessageBox::Yes)
    {
        a1Display->clear();
        a1PurchaseList->toTextFile();
        a1StockList->writeList("STOCK.text");
        saleFinalised = true;

        saleMenu->actions().at(0)->setEnabled(true);
        saleMenu->actions().at(1)->setEnabled(false);
        saleMenu->actions().at(2)->setEnabled(false);
        saleMenu->actions().at(3)->setEnabled(true);
        itemMenu->actions().at(0)->setEnabled(false);
        itemMenu->actions().at(1)->setEnabled(false);

        a1ToolBar->actions().at(0)->setEnabled(true);
        a1ToolBar->actions().at(1)->setEnabled(false);
        a1ToolBar->actions().at(2)->setEnabled(false);
        a1ToolBar->actions().at(3)->setEnabled(true);
        a1ToolBar->actions().at(5)->setEnabled(false);
        a1ToolBar->actions().at(6)->setEnabled(false);
    }
    else
    {
        //Nothing
    }

}

//Slot: closes program only if sale has been canceled or finalised also writes stock list to textfile
void Dialog::exitCashRegister()
{

    if (saleFinalised == true)
    {
        a1StockList->writeList("STOCK.text");
        close();
    }
    else
    {
        QMessageBox::information(0,"Sale in progress","Please first finalise or cancel sale",QMessageBox::Ok);
    }
}

//Slot: Adds new item to purchase list according to the barcode also displays it on the text display
void Dialog::addItemToSale()
{
    QString top = "         Barcode\t\tItem\tStock\tPrice\n=======================================================\n";
    QString bottom = "=======================================================\n";
    QString All;
    QString barcodeFromUser;
    bool costTotal(0.0);
    bool ok;

    barcodeFromUser = QInputDialog::getText(0,"Barcode Scanner","Please Enter Barcode",QLineEdit::Normal,0, &ok);

    if (ok)
    {
        if (a1StockList->findItem(barcodeFromUser) != NULL)
        {
            a1PurchaseList->addPurchase(barcodeFromUser);
            All.append(top);
            for (int i(0); i < a1PurchaseList->size(); i++)
            {
                All.append(a1PurchaseList->at(i)->toString());
                All.append('\n');
                costTotal = costTotal + a1PurchaseList->at(i)->getPrice();
            }
            QString stringTotal = QString("Total\t\t%1").arg(costTotal);
            bottom.append(stringTotal);
            All.append(bottom);
            a1Display->setText(All);
        }
        else
        {
            QMessageBox::information(0,"Product Info","Product code does not exist",QMessageBox::Ok);
        }

    }

}

//Slot: removes item from purchase list according to the barcode also displays it on the text display
void Dialog::removeItemFromSale()
{
    QString top = "         Barcode\t\tItem\tStock\tPrice\n=======================================================\n";
    QString bottom = "=======================================================\n";
    QString All;
    QString barcodeFromUser;
    bool costTotal(0.0);
    bool ok;

    barcodeFromUser = QInputDialog::getText(0,"Barcode Scanner","Please Enter Barcode",QLineEdit::Normal,0, &ok);

    if (ok)
    {
        if (a1StockList->findItem(barcodeFromUser) != NULL)
        {
            a1PurchaseList->removePurchase(barcodeFromUser);
            All.append(top);
            for (int i(0); i < a1PurchaseList->size(); i++)
            {
                All.append(a1PurchaseList->at(i)->toString());
                All.append('\n');
                costTotal = costTotal + a1PurchaseList->at(i)->getPrice();
            }
            QString stringTotal = QString("Total\t\t%1").arg(costTotal);
            bottom.append(stringTotal);
            All.append(bottom);
            a1Display->setText(All);
        }
        else
        {
            QMessageBox::information(0,"Product Info","Product code does not exist",QMessageBox::Ok);
        }

    }

}
