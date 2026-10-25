#ifndef SEARCHBOXBACKEND_H
#define SEARCHBOXBACKEND_H

#include <QString>
#include <qgsvectorlayer.h>

class SearchBoxBackend
{
private:
    void readShapeFile();
    bool readShapeFile1();
    bool findSearchText(const QString &searchText);

    QgsVectorLayer *m_layer = nullptr;

public:
    SearchBoxBackend();
    void run();
};

#endif // SEARCHBOXBACKEND_H