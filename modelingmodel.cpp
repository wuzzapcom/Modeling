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

    for (int i = 0; i < connectable->getPointableObjects().size(); i++)
    {
        if (pointable == connectable->getPointableObjects()[i])
            return;
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
        return;
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

    saveObj["ID_COUNTER"] = QString::number(DrawableObject::getCurrentID());

    saveObj["drawables"] = saveArray;

    QJsonDocument saveDoc(saveObj);

    saveFile.write(saveDoc.toJson());

    saveFile.close();

}

void ModelingModel::load()
{
    //There is a test in header
    QFile loadFile(QStringLiteral("save.json"));
    if (!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn`t open save file.");
        return;
    }

    QByteArray bytes = loadFile.readAll();

    QJsonDocument loadDocument(QJsonDocument::fromJson(bytes));

    QJsonObject loadObj = loadDocument.object();

    DrawableObject::setCurrentID(loadObj["ID_COUNTER"].toString().toLong());

    QJsonArray drawableObjects = loadObj["drawables"].toArray();

    QVector<DrawableObject*> drawables;

    for (QJsonValue drawableValue: drawableObjects)
    {
        QJsonObject obj = drawableValue.toObject();
        DrawableType type = static_cast<DrawableType>(obj["type"].toInt());
        qDebug() << "ModelingModel::load(). DrawableType = " << obj["type"].toString();
        DrawableObject *drawable;

        switch (type) {
        case MATERIAL_POINT:
            drawable = new MaterialPoint();
            break;
        case SPRING:
            drawable = new Spring();
            break;
        case STATIONARY_POINT:
            drawable = new StationaryPoint();
            break;
        case ROD:
            drawable = new Rod();
            break;
        default:
            qWarning() << "ModelingModel::load(). Not matched type.";
            break;
        }

        drawable->readHash(obj);
        drawables.push_back(drawable);
    }

    for (int i = 0; i < drawableObjects.size(); i++)
    {
        drawables[i]->read(drawableObjects.at(i).toObject(), drawables);
    }

    for (DrawableObject *drawable: drawables)
    {
        switch(drawable->getType()) {
        case MATERIAL_POINT:
            matPoints.append((MaterialPoint*)drawable);
            break;
        case SPRING:
            springs.append((Spring*)drawable);
            break;
        case STATIONARY_POINT:
            statPoints.append((StationaryPoint*)drawable);
            break;
        case ROD:
            rods.append((Rod*)drawable);
            break;
        default:
            qWarning() << "ModelingModel::load(). Not matched type.";
            break;
        }
    }
}
