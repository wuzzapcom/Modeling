#ifndef MODELINGMODEL_H
#define MODELINGMODEL_H
#include "materialpoint.h"
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <math.h>

class ModelingModel
{
public:
    ModelingModel();

    void setPlaying(bool playing);
    bool getIsPlaying();
    void addMaterialPoint();
    void addSpring();
    void addStationalPoint();
    void addRod();

    void completeModel();

    QVector<MaterialPoint*> getMaterialPoints();
    QVector<Spring*> getSprings();
    QVector<StationaryPoint*> getStatPoints();
    QVector<Rod*> getRods();

    QVector<DrawableObject*> getDrawableObjects();

    void setSelectedObject(DrawableObject *obj){selectedObject = obj;}
    DrawableObject *getSelectedObject(){return selectedObject;}

    bool isObjectSelected(){return selectedObject != nullptr;}

    void setIncompletedObject(DrawableObject *obj){incompletedObject = obj;}
    DrawableObject *getIncompletedObject(){return incompletedObject;}

    void setSpeedVectorArrow(Arrow *a);
    Arrow *getSpeedVectorArrow(){return speedVectorArrow;}

    void connectObjects(DrawableObject *first, DrawableObject *second);

    void removeObjectFromVectors(DrawableObject *drawable);

    void createAccelerations();
    int findIndexOfConnectableByHash(const QVector<ConnectableObject*> &connectables, ConnectableObject *conn);
    void setConnectablesPosition();
    std::valarray<float> rungeKutta();
    std::valarray<float> applyPositionsToAccelerations(std::valarray<float> args);

    void save();
    void load();

private:
    bool isPlaying;
    float modelG = 9.8;

    QVector<std::function<float(std::valarray<float>)>> accelerations;
    QVector<ConnectableObject*> connectables;
    std::valarray<float> systemPosition;

    QVector<MaterialPoint*> matPoints;
    QVector<Spring*> springs;
    QVector<StationaryPoint*> statPoints;
    QVector<Rod*> rods;

    DrawableObject* selectedObject;
    DrawableObject* incompletedObject;
    Arrow *speedVectorArrow;

};


#endif // MODELINGMODEL_H
