#ifndef ITEMWRITER_H
#define ITEMWRITER_H

#include "item.h"
#include <QString>
#include <QFile>

class ItemWriter
{
private:
    QFile outputFile;
public:
    ItemWriter(QString fname);
    void writeItem(const Item & i);
    ~ItemWriter();
};

#endif // ITEMWRITER_H
