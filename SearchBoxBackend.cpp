#include "SearchBoxBackend.h"
#include "QDebug"

#include <qgsvectorlayer.h>
#include <qgsfeature.h>
#include <qgsgeometry.h>
#include <qgsfields.h> // Include iostream for printing
#include <qgsproject.h>
#include <QString>

#include <QDebug>
#include <QString>
#include <QVariant>

#include <qgsvectorlayer.h>
#include <qgsproject.h>
#include <qgsfields.h>
#include <qgsfeature.h>
#include <qgsfeatureiterator.h>
#include <qgsgeometry.h>
#include <qgscoordinatereferencesystem.h>
#include <qgswkbtypes.h>
#include <qgsfeaturerequest.h>

#include <qgsexpression.h>

SearchBoxBackend::SearchBoxBackend() {}

void SearchBoxBackend::run()
{
    QString searchText = "لاتیدان";
    bool fileIsExist;

    fileIsExist = readShapeFile1();
    qDebug() << "the reading result: " << fileIsExist;


    bool found = findSearchText(searchText);

    qDebug() << "Search result:" << found;
    //    findSearchTextLatitude();
    //    findSearchTextProvince();
}

bool SearchBoxBackend::findSearchText(const QString &searchText)
{
    if (!m_layer || !m_layer->isValid())
    {
        qDebug() << "Layer is not loaded.";
        return false;
    }

    QgsFeature feature;

    QgsFeatureRequest request;
    request.setFilterExpression(
        QgsExpression::quotedColumnRef("name") + " = " + QgsExpression::quotedValue(searchText.trimmed()));

    QgsFeatureIterator iterator = m_layer->getFeatures(request);

    if (iterator.nextFeature(feature))
    {

        QgsGeometry geometry = feature.geometry();

        if (!geometry.isNull() && !geometry.isEmpty())
        {
            QgsPointXY point = geometry.asPoint();

            double longitude = point.x();
            double latitude = point.y();

            qDebug() << "City:" << feature.attribute("name").toString();
            qDebug() << "Latitude:" << latitude;
            qDebug() << "Longitude:" << longitude;

            return true;
        }

        qDebug() << "City has no valid point geometry.";
        return false;
    }

    qDebug() << "City not found:" << searchText;
    return false;
}

// bool SearchBoxBackend::findSearchText(const QString &searchText)
// {
//     if (!m_layer || !m_layer->isValid()) {
//         qDebug() << "Layer is not loaded.";
//         return false;
//     }

//     QgsFeature feature;

//     QgsFeatureRequest request;
//     request.setFilterExpression(
//         QgsExpression::quotedColumnRef("name")
//         + " = "
//         + QgsExpression::quotedValue(searchText.trimmed())
//     );

//     QgsFeatureIterator iterator = m_layer->getFeatures(request);

//     if (iterator.nextFeature(feature)) {
//         qDebug() << "Found city:"
//                  << feature.attribute("name").toString();
//         return true;
//     }

//     qDebug() << "City not found:" << searchText;
//     return false;
// }

bool SearchBoxBackend::readShapeFile1()
{
    // QString path = "/home/northfinder/NorthFinder/Code/MapSource/iran-latest-free.shp/gis_osm_places_free_1.shp";

    QString path =
        "/home/northfinder/NorthFinder/Code/MapSource/"
        "iran-latest-free.shp/gis_osm_places_free_1.shp";

    QgsVectorLayer *layer =
        new QgsVectorLayer(path, "cities", "ogr");

    if (!layer->isValid())
    {
        qDebug() << "Failed to load shapefile:" << path;
        delete layer;
        return false;
    }

    // Add layer to the QGIS project.
    QgsProject::instance()->addMapLayer(layer);

    // Print available fields.
    const QgsFields fields = layer->fields();
    qDebug() << "Fields:" << fields.names();

    // Read and print features.
    QgsFeature feature;
    QgsFeatureIterator iterator = layer->getFeatures();

    while (iterator.nextFeature(feature))
    {
        QVariant name = feature.attribute("name");

        QgsGeometry geometry = feature.geometry();

        if (geometry.type() == Qgis::GeometryType::Point)
        {
            QgsPointXY point = geometry.asPoint();

            double lon = point.x();
            double lat = point.y();

            // qDebug() << name.toString() << lon << lat;
        }
    }
    qDebug() << "end of reading file" << "...................";

    m_layer = layer;
    return true;
}

void SearchBoxBackend::readShapeFile()
{
    QString path = "/home/northfinder/NorthFinder/Code/MapSource/iran-latest-free.shp/gis_osm_places_free_1.shp";

    QgsVectorLayer *layer = new QgsVectorLayer(path, "cities", "ogr");

    if (!layer->isValid())
    {
        qDebug() << "Failed to load shapefile:" << path;
        delete layer;
        //         return 1;
    }

    // Add to project so it shows up in the map canvas / layer tree
    QgsProject::instance()->addMapLayer(layer);

    // Reproject to WGS84 if needed (so x=lon, y=lat)
    if (layer->crs() != QgsCoordinateReferenceSystem("EPSG:4326"))
    {
        // For display you can just rely on the project CRS;
        // for true lat/lon values, transform each geometry (see below).
    }

    const QgsFields fields = layer->fields();
    qDebug() << "Fields:" << fields.names();

    QgsFeature f;
    QgsFeatureIterator it = layer->getFeatures();
    while (it.nextFeature(f))
    {
        // Attributes (e.g. city name)
        QVariant name = f.attribute("name"); // use the actual field name
        // or by index: f.attribute(0)

        // Geometry -> coordinates
        QgsGeometry g = f.geometry();

        if (g.type() == Qgis::GeometryType::Point)
        {
            QgsPointXY pt = g.asPoint();

            double lon = pt.x();
            double lat = pt.y();

            qDebug() << name.toString() << lon << lat;
        }

        qDebug() << "we are here";
    }
}
