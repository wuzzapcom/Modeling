#ifndef MODELINGMODEL_H
#define MODELINGMODEL_H
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include "drawable_objects.h"
#include "csvlogger.h"

const double ENABLED_GRAVITATION_VALUE = 3.0;
const double DISABLED_GRAVITATION_VALUE = 0.0;

class ModelingModel
{
public:
    ModelingModel();
    ~ModelingModel();

    /*
     * Interface methods
     * */
    void save();
    void load();
    void addMaterialPoint();
    void addSpring();
    void addStationalPoint();
    void addRod();
    void switchGravitation();

    /*
     * Updating model methods
     * */
    void completeModel();
    bool isModelCompleted();
    bool isModelCorrect();

    bool isObjectSelected(){return selectedObject != nullptr;}
    void connectObjects(DrawableObject *first, DrawableObject *second);
    void updateSpringsAndRods(bool isMovedByUser);
    void removeObjectFromVectors(DrawableObject *drawable);

    /*
     * Model methods
     * */
    int findIndexOfDrawableByHash(DrawableObject *conn);
    void resetMaterialPointsSpeeds();
    void applySpeedsAndCoordinatesToModel(std::valarray<double> arr);

    double countPhi(Rod *rod);
    double countPhiSpeed(Rod *rod, double phi);

    QVector<std::function<double(std::valarray<double>)>> createAccelerations();

    QVector<std::function<double(std::valarray<double>)>> createSpringAccelerations(
                                                            std::function<double(std::valarray<double>)> xAccs,
                                                            std::function<double(std::valarray<double>)> yAccs,
                                                            std::function<double(std::valarray<double>)> phiAccs,
                                                            int externalIndex,
                                                            int internalIndex
                                                            );
    QVector<std::function<double(std::valarray<double>)>> createRodAccelerations(
                                                            std::function<double(std::valarray<double>)> xAccs,
                                                            std::function<double(std::valarray<double>)> yAccs,
                                                            std::function<double(std::valarray<double>)> phiAccs,
                                                            int externalIndex,
                                                            int internalIndex
                                                            );
    QVector<std::function<double(std::valarray<double>)>> createSpringAndRodAccelerations(
                                                            std::function<double(std::valarray<double>)> xAccs,
                                                            std::function<double(std::valarray<double>)> yAccs,
                                                            std::function<double(std::valarray<double>)> phiAccs,
                                                            int externalIndex,
                                                            int internalIndex
                                                            );
    /*
     * Model testing
     * */
    double countSystemEnergy();
    double countKineticEnergy();
    double countPotentialEnergy();

    /*
     * Getters and setters
     * */
    void setPlaying(bool playing);
    bool getIsPlaying();
    QVector<MaterialPoint*> getMaterialPoints();
    QVector<Spring*> getSprings();
    QVector<StationaryPoint*> getStatPoints();
    QVector<Rod*> getRods();
    void setSpeedVectorArrow(Arrow *a);
    Arrow *getSpeedVectorArrow(){return speedVectorArrow;}
    QVector<DrawableObject*> getDrawableObjects();
    std::valarray<double> getConnectablesPosition();
    void setSelectedObject(DrawableObject *obj){selectedObject = obj;}
    DrawableObject *getSelectedObject(){return selectedObject;}
    void setIncompletedObject(DrawableObject *obj){incompletedObject = obj;}
    DrawableObject *getIncompletedObject(){return incompletedObject;}
    CsvLogger *getLogger(){return &logger;}

private:
    bool isPlaying;
    double gravitation = DISABLED_GRAVITATION_VALUE;

    QVector<ConnectableObject*> connectables;

    QVector<MaterialPoint*> matPoints;
    QVector<Spring*> springs;
    QVector<StationaryPoint*> statPoints;
    QVector<Rod*> rods;

    DrawableObject* selectedObject;
    DrawableObject* incompletedObject;
    Arrow *speedVectorArrow;

    CsvLogger logger;

};


#endif // MODELINGMODEL_H
