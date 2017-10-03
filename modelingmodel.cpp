#include "modelingmodel.h"

ModelingModel::ModelingModel()
    :isPlaying(false),
      matPoints(QVector<MaterialPoint*>()),
      springs(QVector<Spring*>()),
      statPoints(QVector<StationaryPoint*>()),
      rods(QVector<Rod*>()),
      selectedObject(nullptr),
      incompletedObject(nullptr)
{}

void ModelingModel::setPlaying(bool playing){
     isPlaying = playing;
}

bool ModelingModel::getIsPlaying(){
    return isPlaying;
}

void ModelingModel::addMaterialPoint()
{
    qInfo("addMaterialPoint()");

    matPoints.append(new MaterialPoint(Point(0.0f, 0.0f), 0.5f));

}

void ModelingModel::addSpring()
{
    qInfo("addSpring()");

    springs.append(new Spring(Rectangle(Point(), 0.5f, 0.5f)));

}

void ModelingModel::addStationalPoint()
{

    qInfo("addStationalPoint()");

    statPoints.append(new StationaryPoint(Rectangle(Point(), 0.2f, 0.2f)));

}

QVector<MaterialPoint*> ModelingModel::getMaterialPoints(){

    return matPoints;

}

QVector<Spring*> ModelingModel::getSprings(){

    return springs;

}

QVector<StationaryPoint*> ModelingModel::getStatPoints(){

    return statPoints;

}

QVector<DrawableObject*> ModelingModel::getDrawableObjects()
{

    QVector<DrawableObject*> drawableObjects = QVector<DrawableObject*>();

    for(int i = 0; i < this->matPoints.length(); i++)
        drawableObjects.append((DrawableObject*) this->matPoints[i]);

    for(int i = 0; i < this->springs.length(); i++)
        drawableObjects.append((DrawableObject*) this->springs[i]);

    for(int i = 0; i < this->statPoints.length(); i++)
        drawableObjects.append((DrawableObject*) this->statPoints[i]);

    for(int i = 0; i < this->rods.length(); i++)
        drawableObjects.append((DrawableObject*) this->rods[i]);

    return drawableObjects;

}

void ModelingModel::completeModel(){

    for (int i = 0; i < springs.length(); i++){

        if (springs[i]->isModelIncompleted())
            this->incompletedObject = springs[i];

    }

}

void ModelingModel::connectObjects(DrawableObject *first, DrawableObject *second)
{

    Spring *incompletedSpring;
    MaterialPoint *materialPoint;

    if (first->isModelIncompleted()){

        switch (first->getType()) {
        case SPRING:
            incompletedSpring = (Spring*) first;
            break;
        default:
            return;
            break;
        }

        switch (second->getType()) {
        case MATERIAL_POINT:
            materialPoint = (MaterialPoint*) second;
            break;
        default:
            return;
            break;
        }

    }
    else{

        switch (first->getType()) {
        case MATERIAL_POINT:
            materialPoint = (MaterialPoint*) first;
            break;
        default:
            return;
            break;
        }

        switch (second->getType()) {
        case SPRING:
            incompletedSpring = (Spring*) second;
            break;
        default:
            return;
            break;
        }

    }

    incompletedSpring->splitWith(materialPoint);

    incompletedSpring->setFirstObject(materialPoint);
    materialPoint->addConnectedSpring(incompletedSpring);


}
