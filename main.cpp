#include "mainwindow.h"

#include <QApplication>
#include <iostream>

#include <qgsvectorlayer.h>
#include <qgsfeature.h>
#include <qgsgeometry.h>
#include <qgsfields.h>// Include iostream for printing
#include <qgsproject.h>
#include "SearchBoxBackend.h"

using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    objSearchBox=SearchBoxBackend();

    SearchBoxBackend  objSearchBox;
    objSearchBox.run();
//    objSearchBox=S


//    cout << "Hello World!" << endl;



////     QString path = "/path/to/cities.shp";   // keep .shp/.shx/.dbf/.prj together




//     }




    return a.exec();
}
