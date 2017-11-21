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
    ~ModelingModel();

    void setPlaying(bool playing);
    bool getIsPlaying();
    void addMaterialPoint();
    void addSpring();
    void addStationalPoint();
    void addRod();

    void completeModel();
    bool isModelCompleted();
    bool isModelCorrect();

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

    void updateSpringsAndRods(bool isMovedByUser);

    void removeObjectFromVectors(DrawableObject *drawable);

    QVector<std::function<float(std::valarray<float>)>> createAccelerations();
    //Order matters! First is x, then y and phi lambdas
    QVector<std::function<float(std::valarray<float>)>> createSpringAccelerations(
                                                            std::function<float(std::valarray<float>)> xAccs,
                                                            std::function<float(std::valarray<float>)> yAccs,
                                                            std::function<float(std::valarray<float>)> phiAccs,
                                                            int externalIndex,
                                                            int internalIndex
                                                            );
    QVector<std::function<float(std::valarray<float>)>> createRodAccelerations(
                                                            std::function<float(std::valarray<float>)> xAccs,
                                                            std::function<float(std::valarray<float>)> yAccs,
                                                            std::function<float(std::valarray<float>)> phiAccs,
                                                            int externalIndex,
                                                            int internalIndex
                                                            );
    QVector<std::function<float(std::valarray<float>)>> createSpringAndRodAccelerations(
                                                            std::function<float(std::valarray<float>)> xAccs,
                                                            std::function<float(std::valarray<float>)> yAccs,
                                                            std::function<float(std::valarray<float>)> phiAccs,
                                                            int externalIndex,
                                                            int internalIndex
                                                            );

    float countSystemEnergy();
    float countKineticEnergy();
    float countPotentialEnergy();

    int findIndexOfDrawableByHash(DrawableObject *conn);
    std::valarray<float> getConnectablesPosition();
    void resetMaterialPointsSpeeds();
    void applySpeedsAndCoordinatesToModel(std::valarray<float> arr);

    float countPhi(Rod *rod);
    float countPhiSpeed(Rod *rod, float phi);

    void save();
    void load();

private:
    bool isPlaying;
    float modelG = 10.0f;//10.0f;

//    QVector<std::function<float(std::valarray<float>)>> accelerations;
    QVector<ConnectableObject*> connectables;
//    std::valarray<float> systemPosition;

    QVector<MaterialPoint*> matPoints;
    QVector<Spring*> springs;
    QVector<StationaryPoint*> statPoints;
    QVector<Rod*> rods;

    DrawableObject* selectedObject;
    DrawableObject* incompletedObject;
    Arrow *speedVectorArrow;

};


#endif // MODELINGMODEL_H
