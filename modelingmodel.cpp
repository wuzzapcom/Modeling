#include "modelingmodel.h"

ModelingModel::ModelingModel()
{

    entryObject = nullptr;

}

void ModelingModel::setPlaying(bool playing){
     isPlaying = playing;
}

bool ModelingModel::getIsPlaying(){
    return isPlaying;
}

void ModelingModel::addMaterialPoint()
{
    qInfo("addMaterialPoint()");

    DrawableObject *lastPointer = this->entryObject;

//    while (lastPointer != nullptr)
//        lastPointer = lastPointer->next;

    this->entryObject = new MaterialPoint(Point(0.0f, 0.0f), 0.5f);

}

DrawableObject *ModelingModel::draw()
{

    return entryObject;

}
