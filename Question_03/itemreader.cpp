#include "itemreader.h"
#include <QTextStream>

ItemReader::ItemReader(QString fname) : inputFile(fname) { }

bool ItemReader::openForReading() {
    return inputFile.open(QIODevice::ReadOnly | QIODevice::Text);
}

Item ItemReader::readItem() {
    QStringList itemSL = QString(inputFile.readLine()).split('\t');
    return Item(itemSL[0].trimmed(), itemSL[1].trimmed(), itemSL[2].toInt(), itemSL[3].toDouble());
}

bool ItemReader::endOfFile() {
    return inputFile.atEnd();
}

ItemReader::~ItemReader() {
    inputFile.close();
}
