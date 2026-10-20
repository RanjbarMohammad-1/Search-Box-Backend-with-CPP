#include "SearchBoxBackend.h"
#include "QDebug"


SearchBoxBackend::SearchBoxBackend()
{
}

void SearchBoxBackend::run()
{

    readShapeFile();
}

void SearchBoxBackend::readShapeFile(){
    qDebug() << "we are here";
}
