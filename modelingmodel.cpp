#include "modelingmodel.h"

ModelingModel::ModelingModel()
{

    entryObject = nullptr;
    isPlaying = false;

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

    DrawableObject **lastPointer = getLastObject();

    *lastPointer = new MaterialPoint(Point(0.0f, 0.0f), 0.5f);

}

void ModelingModel::addSpring()
{
    qInfo("addSpring()");

    DrawableObject **lastPointer = getLastObject();

    *lastPointer = new Spring(Rectangle(Point(), 0.5f, 0.5f));

}

DrawableObject **ModelingModel::getLastObject()
{

    DrawableObject **lastPointer = &(this->entryObject);

    if (*lastPointer != nullptr){

        while ((*lastPointer)->next != nullptr)
            *lastPointer = (*lastPointer)->next;

        return &((*lastPointer)->next);
        //(*lastPointer)->next = new MaterialPoint(Point(0.0f, 0.0f), 0.5f);
    }
    else{
        return lastPointer;
//        *lastPointer = new MaterialPoint(Point(0.0f, 0.0f), 0.5f);

    }

}

DrawableObject *ModelingModel::draw()
{

    return entryObject;

}
