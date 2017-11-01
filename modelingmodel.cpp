#include "modelingmodel.h"

ModelingModel::ModelingModel()
    :isPlaying(false),
      matPoints(QVector<MaterialPoint*>()),
      springs(QVector<Spring*>()),
      statPoints(QVector<StationaryPoint*>()),
      rods(QVector<Rod*>()),
      selectedObject(nullptr),
      incompletedObject(nullptr),
      speedVectorArrow(nullptr)
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
    else if (pointable->getSecondConnectable() == nullptr)
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

void ModelingModel::setSpeedVectorArrow(Arrow *a)
{
//    if (this->speedVectorArrow != nullptr)
//        delete this->speedVectorArrow;

    this->speedVectorArrow = a;
}

void ModelingModel::removeObjectFromVectors(DrawableObject *drawable)
{
    this->matPoints.removeOne((MaterialPoint*) drawable);
    this->statPoints.removeOne((StationaryPoint*) drawable);
    this->springs.removeOne((Spring*) drawable);
    this->rods.removeOne((Rod*) drawable);
}

void ModelingModel::createAccelerations()
{
    QVector<ConnectableObject*> connectables;

    for(int i = 0; i < matPoints.size(); i++)
        connectables.push_back((ConnectableObject*)matPoints[i]);
    for(int i = 0; i < statPoints.size(); i++)
        connectables.push_back((ConnectableObject*)statPoints[i]);

    this->connectables = connectables;

    QVector<std::function<float(std::valarray<float>)>> accs;

    for(int i = 0; i < matPoints.size(); i++)
    {
        float g = this->modelG;
        std::function<float(std::valarray<float>)> xAcceleration = [](std::valarray<float>){return 0;};
        std::function<float(std::valarray<float>)> yAcceleration = [g](std::valarray<float>){return g;}; //TODO add mg to this start lambda
        int x2Index = i;
        for(int j = 0; j < matPoints[i]->getPointableObjects().size(); j++)
        {
            int x1Index = 0;
            if (matPoints[i]->getPointableObjects()[j]->getType() == SPRING)
            {
                Spring* spring = (Spring*) matPoints[i]->getPointableObjects()[j];
                float k = spring->getRigidity();
                float m = matPoints[i]->getWeight();
                float L0 = spring->getDefaultLength();
                std::function<float(std::valarray<float>)> capturingAccelerationX = xAcceleration;
                std::function<float(std::valarray<float>)> capturingAccelerationY = yAcceleration;

                int index1 = findIndexOfConnectableByHash(connectables, spring->getFirstConnectable());
                int index2 = findIndexOfConnectableByHash(connectables, spring->getSecondConnectable());
                if (index1 == -1 || index2 == -1) continue;
                if (index1 != x2Index) x1Index = index1;
                else x1Index = index2;
                xAcceleration = [capturingAccelerationX, k, m, L0, x2Index, x1Index](std::valarray<float> args){
                    float x2 = args[x2Index];
                    float y2 = args[x2Index + 1];
                    float x1 = args[x1Index];
                    float y1 = args[x1Index + 1];
                    float square = sqrtf(powf(x2 - x1, 2) + powf(y2 - y1, 2));
                    return capturingAccelerationX(args) + (-1) / m * k * (args[x2Index] - args[x1Index]) * powf(square - L0, 2) / square;
                };
                yAcceleration = [capturingAccelerationY, k, m, L0, x2Index, x1Index](std::valarray<float> args){
                    float x2 = args[x2Index];
                    float y2 = args[x2Index + 1];
                    float x1 = args[x1Index];
                    float y1 = args[x1Index + 1];
                    float square = sqrtf(powf(x2 - x1, 2) + powf(y2 - y1, 2));
                    return capturingAccelerationY(args) + (-1) / m * k * (args[x2Index] - args[x1Index]) * powf(square - L0, 2) / square;
                };
            }
        }
        accs.push_back(xAcceleration);
        accs.push_back(yAcceleration);
    }
    accelerations = accs;
}

int ModelingModel::findIndexOfConnectableByHash(const QVector<ConnectableObject *> &connectables, ConnectableObject *conn)
{
    for (int i = 0; i < connectables.size(); i++)
    {
        if (connectables[i]->getHash() == conn->getHash())
        {
            return i;
        }
    }
    return -1;
}

void ModelingModel::setConnectablesPosition()
{
    systemPosition = std::valarray<float>(connectables.size() * 4);
    for (size_t i = 0; i < systemPosition.size(); i += 4)
    {
        if (connectables[i/4]->getType() == MATERIAL_POINT){
            MaterialPoint* materialPoint = (MaterialPoint*) connectables[i/4];
            systemPosition[i] = materialPoint->getCenter().x;
            systemPosition[i+1] = materialPoint->getSpeedX();
            systemPosition[i+2] = materialPoint->getCenter().y;
            systemPosition[i+3] = materialPoint->getSpeedY();
        }
    }
}

std::valarray<float> ModelingModel::applyPositionsToAccelerations(std::valarray<float> args)
{
    std::valarray<float> result(systemPosition.size());
    for (size_t i = 0; i < accelerations.size(); i++)
    {
        result[2*i + 1] = accelerations[i](args);
        result[2*i] = result[2*i + 1];
    }
    return result;
}

std::valarray<float> ModelingModel::rungeKutta()
{
    float h = 1.0f/60.0f;
    std::valarray<float> k1 = applyPositionsToAccelerations(systemPosition);
    std::valarray<float> k2 = applyPositionsToAccelerations(systemPosition + h / 2 * k1);
    std::valarray<float> k3 = applyPositionsToAccelerations(systemPosition + h / 2 * k2);
    std::valarray<float> k4 = applyPositionsToAccelerations(systemPosition + h * k3);
    return systemPosition + h / 6 * (k1 + 2.0f * k2 + 2.0f * k3 + k4);
}

void ModelingModel::applySpeedsAndCoordinatesToModel(std::valarray<float> arr)
{
    for (int i = 0; i < connectables.size(); i++)
    {
        if (connectables[i]->getType() == MATERIAL_POINT){
            MaterialPoint* materialPoint = (MaterialPoint*) connectables[i];
            materialPoint->setX(arr[4*i]);
            materialPoint->setSpeedX(arr[4*i + 1]);
            materialPoint->setY(arr[4*i + 2]);
            materialPoint->setSpeedY(arr[4*i + 3]);
        }
    }
}












