#include "modelingmodel.h"

ModelingModel::ModelingModel()
    :isPlaying(false),
      matPoints(QVector<MaterialPoint*>()),
      springs(QVector<Spring*>()),
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

QVector<MaterialPoint*> ModelingModel::getMaterialPoints(){

    return matPoints;

}

QVector<Spring*> ModelingModel::getSprings(){

    return springs;

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

        if (first->getType() == SPRING){

            incompletedSpring = (Spring*) first;

        }

        if (second->getType() == MATERIAL_POINT){

            materialPoint = (MaterialPoint*) second;

        }

    }
    else{

        if (second->getType() == SPRING){

            incompletedSpring = (Spring*) second;

        }

        if (first->getType() == MATERIAL_POINT){

            materialPoint = (MaterialPoint*) first;

        }

    }

    incompletedSpring->splitWith(materialPoint);

}
