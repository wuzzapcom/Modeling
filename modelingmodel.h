#ifndef MODELINGMODEL_H
#define MODELINGMODEL_H
#include "drawableobject.h"
#include "materialpoint.h"

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
};

#endif // MODELINGMODEL_H
