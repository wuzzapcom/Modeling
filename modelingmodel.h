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
//    DrawableObject* draw();
    QVector<MaterialPoint*> getMaterialPoints();
    QVector<Spring*> getSprings();

    void setSelectedObject(DrawableObject *obj){selectedObject = obj;}
    DrawableObject *getSelectedObject(){return selectedObject;}

    bool isObjectSelected(){return selectedObject != nullptr;}

private:
    bool isPlaying;

    QVector<MaterialPoint*> matPoints;
    QVector<Spring*> springs;

    DrawableObject* selectedObject;

//    DrawableObject *entryObject;
//    DrawableObject **getLastObject();
};

#endif // MODELINGMODEL_H
