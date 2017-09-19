#ifndef MODELINGMODEL_H
#define MODELINGMODEL_H
#include "drawableobject.h"
#include "materialpoint.h"
#include "spring.h"

class ModelingModel
{
public:
    ModelingModel();

    void setPlaying(bool playing);
    bool getIsPlaying();
    void addMaterialPoint();
    void addSpring();
    DrawableObject* draw();

private:
    bool isPlaying;
    DrawableObject *entryObject;

    DrawableObject **getLastObject();
};

#endif // MODELINGMODEL_H
