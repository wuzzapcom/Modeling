#ifndef MODELINGMODEL_H
#define MODELINGMODEL_H
//#include "drawableobject.h"
#include "materialpoint.h"
//#include "rectangle.h"
//#include "spring.h"

class ModelingModel
{
public:
    ModelingModel();

    void setPlaying(bool playing);
    bool getIsPlaying();
    void addMaterialPoint();
    void addSpring();

    void completeModel();

    QVector<MaterialPoint*> getMaterialPoints();
    QVector<Spring*> getSprings();

    void setSelectedObject(DrawableObject *obj){selectedObject = obj;}
    DrawableObject *getSelectedObject(){return selectedObject;}

    bool isObjectSelected(){return selectedObject != nullptr;}

    void setIncompletedObjecT(DrawableObject *obj){incompletedObject = obj;}
    DrawableObject *getIncompletedObject(){return incompletedObject;}

    void connectObjects(DrawableObject *first, DrawableObject *second);

private:
    bool isPlaying;

    QVector<MaterialPoint*> matPoints;
    QVector<Spring*> springs;

    DrawableObject* selectedObject;
    DrawableObject* incompletedObject;

};

#endif // MODELINGMODEL_H
