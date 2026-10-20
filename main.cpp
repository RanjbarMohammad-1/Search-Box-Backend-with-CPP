#include "mainwindow.h"

#include <QApplication>
#include <iostream>

#include <qgsvectorlayer.h>
#include <qgsfeature.h>
#include <qgsgeometry.h>
#include <qgsfields.h>// Include iostream for printing
#include <qgsproject.h>

using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    cout << "Hello World!" << endl;



//     QString path = "/path/to/cities.shp";   // keep .shp/.shx/.dbf/.prj together


     QString path = "/home/northfinder/NorthFinder/Code/MapSource/iran-latest-free.shp/gis_osm_places_free_1.shp";

     QgsVectorLayer *layer = new QgsVectorLayer(path, "cities", "ogr");

     if (!layer->isValid()) {
         qDebug() << "Failed to load shapefile:" << path;
         delete layer;
         return 1;
     }

     // Add to project so it shows up in the map canvas / layer tree
     QgsProject::instance()->addMapLayer(layer);

     // Reproject to WGS84 if needed (so x=lon, y=lat)
     if (layer->crs() != QgsCoordinateReferenceSystem("EPSG:4326")) {
         // For display you can just rely on the project CRS;
         // for true lat/lon values, transform each geometry (see below).
     }

     const QgsFields fields = layer->fields();
     qDebug() << "Fields:" << fields.names();

     QgsFeature f;
     QgsFeatureIterator it = layer->getFeatures();
     while (it.nextFeature(f)) {
         // Attributes (e.g. city name)
         QVariant name = f.attribute("name");   // use the actual field name
         // or by index: f.attribute(0)

         // Geometry -> coordinates
         QgsGeometry g = f.geometry();

         if (g.type() == Qgis::GeometryType::Point) {
             QgsPointXY pt = g.asPoint();

             double lon = pt.x();
             double lat = pt.y();

             qDebug() << name.toString() << lon << lat;
         }


     }




    return a.exec();
}
