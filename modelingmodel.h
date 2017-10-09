#ifndef MODELINGMODEL_H
#define MODELINGMODEL_H
//#include "drawableobject.h"
#include "materialpoint.h"
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
//#include "rectangle.h"
//#include "spring.h"

class ModelingModel
{
public:
    ModelingModel();

    void setPlaying(bool playing);
    bool getIsPlaying();
    void addMaterialPoint();
    void addSpring();
    void addStationalPoint();

    void completeModel();

    QVector<MaterialPoint*> getMaterialPoints();
    QVector<Spring*> getSprings();
    QVector<StationaryPoint*> getStatPoints();

    QVector<DrawableObject*> getDrawableObjects();

    void setSelectedObject(DrawableObject *obj){selectedObject = obj;}
    DrawableObject *getSelectedObject(){return selectedObject;}

    bool isObjectSelected(){return selectedObject != nullptr;}

    void setIncompletedObjecT(DrawableObject *obj){incompletedObject = obj;}
    DrawableObject *getIncompletedObject(){return incompletedObject;}

    void connectObjects(DrawableObject *first, DrawableObject *second);

    void save();

private:
    bool isPlaying;

    QVector<MaterialPoint*> matPoints;
    QVector<Spring*> springs;
    QVector<StationaryPoint*> statPoints;
    QVector<Rod*> rods;

    DrawableObject* selectedObject;
    DrawableObject* incompletedObject;

};

#endif // MODELINGMODEL_H
