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

    springs.append(new Spring(Rectangle(Point(), 0.1f, 0.5f)));
}

void ModelingModel::addStationalPoint()
{
    qInfo("addStationalPoint()");

    statPoints.append(new StationaryPoint(Rectangle(Point(), 0.2f, 0.2f)));
}

void ModelingModel::addRod()
{
    qInfo("addRod()");

    rods.append(new Rod(Rectangle(Point(), 0.1f, 0.5f)));
}

QVector<MaterialPoint*> ModelingModel::getMaterialPoints()
{
    return matPoints;
}

QVector<Spring*> ModelingModel::getSprings()
{
    return springs;
}

QVector<StationaryPoint*> ModelingModel::getStatPoints()
{
    return statPoints;
}

QVector<Rod*> ModelingModel::getRods()
{
    return rods;
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

    for (int i = 0; i < springs.size(); i++)
    {
        if (springs[i]->isModelIncompleted())
            this->incompletedObject = springs[i];
    }

    for (int i = 0; i < rods.size(); i++)
    {
        if (rods[i]->isModelIncompleted())
            this->incompletedObject = rods[i];
    }

}

void ModelingModel::connectObjects(DrawableObject *first, DrawableObject *second)
{

    PointableObject *pointable;
    ConnectableObject *connectable;

    if (first->isModelIncompleted()){

        switch (first->getType()) {
        case SPRING:
            pointable = (PointableObject*) first;
            break;
        case ROD:
            pointable = (PointableObject*) first;
            break;
        default:
            return;
            break;
        }

        switch (second->getType()) {
        case MATERIAL_POINT:
            connectable = (ConnectableObject*) second;
            break;
        case STATIONARY_POINT:
            connectable = (ConnectableObject*) second;
        default:
            return;
            break;
        }

    }
    else{

        switch (first->getType()) {
        case MATERIAL_POINT:
            connectable = (ConnectableObject*) first;
            break;
        case STATIONARY_POINT:
            connectable = (ConnectableObject*) first;
            break;
        default:
            return;
            break;
        }

        switch (second->getType()) {
        case SPRING:
            pointable = (PointableObject*) second;
            break;
        case ROD:
            pointable = (PointableObject*) second;
            break;
        default:
            return;
            break;
        }

    }

    if (pointable->getFirstConnectable() == nullptr)
        pointable->setFirstConnectable(connectable);
    else
        pointable->setSecondConnectable(connectable);

    connectable->addPointable(pointable);

}

void ModelingModel::save()
{
    /*
     * For macOS file will be created in applicationPackage/Contents/MacOS
     * */
    QFile saveFile(QStringLiteral("save.json"));

    if (!saveFile.open(QIODevice::WriteOnly))
    {
            qWarning("Couldn't open save file.");
    }

    QVector<DrawableObject*> objects = getDrawableObjects();

    QJsonObject saveObj;

    QJsonArray saveArray;

    for (int i = 0; i < objects.size(); i++)
    {
        QJsonObject obj;
        objects[i]->write(obj);
        saveArray.append(obj);
    }

    saveObj["drawables"] = saveArray;

    QJsonDocument saveDoc(saveObj);

    saveFile.write(saveDoc.toJson());

    saveFile.close();

}
