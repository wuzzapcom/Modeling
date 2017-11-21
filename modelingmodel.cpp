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

bool ModelingModel::isModelCorrect()
{
    if (this->isModelCompleted())
        return false;
    if (this->matPoints.size() == 0 && this->statPoints.size() == 0)
        return false;
    for (int i = 0; i < rods.size(); i++)
    {
        if (!(rods[i]->getFirstConnectable()->getType() == STATIONARY_POINT || rods[i]->getSecondConnectable()->getType() == STATIONARY_POINT))
        {
            return false;
        }
    }
    for (int i = 0; i < matPoints.size(); i++)
    {
        int numberOfRods = 0;
        for (int j = 0; j < matPoints[i]->getPointableObjects().size(); j++)
        {
            if (matPoints[i]->getPointableObjects()[j]->getType() == ROD)
            {
                numberOfRods++;
            }
        }
        if (numberOfRods > 1)
            return false;
    }
    return true;
}

void ModelingModel::setPlaying(bool playing)
{
     isPlaying = playing;
}

bool ModelingModel::getIsPlaying()
{
    return isPlaying;
}

void ModelingModel::addMaterialPoint()
{
    qInfo("addMaterialPoint()");

    matPoints.append(new MaterialPoint(Point(0.0f, 0.0f), 0.1f));
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

void ModelingModel::completeModel()
{
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

bool ModelingModel::isModelCompleted()
{
    for (int i = 0; i < springs.size(); i++)
    {
        if (springs[i]->isModelIncompleted())
            return true;
    }
    for (int i = 0; i < rods.size(); i++)
    {
        if (rods[i]->isModelIncompleted())
            return true;
    }
    return false;
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


/*
 * TODO
 * CHECK WEIGHTS(did captured value from correct matPoint)
 * FIX PROBLEM WITH DEFAULT LENGTH
 * ADDING CONNECTION SPRING TO STAT POINT: two variants of lambda. If connected to statPoint, then capture its position,
 *  else use current lambda.
 * */
QVector<std::function<float(std::valarray<float>)>> ModelingModel::createAccelerations()
{
    QVector<std::function<float(std::valarray<float>)>> accs;
    float g = this->modelG;

    for(int i = 0; i < matPoints.size(); i++)
    {
        std::function<float(std::valarray<float>)> xAcceleration = [](std::valarray<float>){return 0;};
        std::function<float(std::valarray<float>)> yAcceleration = [g](std::valarray<float>){return -g;};
        std::function<float(std::valarray<float>)> phiAcceleration = [](std::valarray<float>){return 0;};

        for(int j = 0; j < matPoints[i]->getPointableObjects().size(); j++)
        {
            QVector<std::function<float(std::valarray<float>)>> accs;

            if (matPoints[i]->getPointableObjects()[j]->getType() == SPRING)
            {
                if (matPoints[i]->isConnectedToRods())
                {
                    accs = createSpringAndRodAccelerations(
                                xAcceleration,
                                yAcceleration,
                                phiAcceleration,
                                i,
                                j
                                );
                }else
                {
                    accs = createSpringAccelerations(
                                xAcceleration,
                                yAcceleration,
                                phiAcceleration,
                                i,
                                j
                                );
                }
            }
            else if (matPoints[i]->getPointableObjects()[j]->getType() == ROD)
            {
                accs = createRodAccelerations(
                                xAcceleration,
                                yAcceleration,
                                phiAcceleration,
                                i,
                                j
                                );
            }
            xAcceleration = accs[0];
            yAcceleration = accs[1];
            phiAcceleration = accs[2];
        }
        accs.push_back(xAcceleration);
        accs.push_back(yAcceleration);
        accs.push_back(phiAcceleration);
    }
    return accs;
}

QVector<std::function<float(std::valarray<float>)>> ModelingModel::createSpringAccelerations(
                                                        std::function<float(std::valarray<float>)> xAcc,
                                                        std::function<float(std::valarray<float>)> yAcc,
                                                        std::function<float(std::valarray<float>)> phiAcc,
                                                        int externalIndex,
                                                        int internalIndex
                                                        )
{
    QVector<std::function<float(std::valarray<float>)>> result;

    Spring* spring = (Spring*) matPoints[externalIndex]->getPointableObjects()[internalIndex];

    spring->setRestingLength(spring->getDefaultLength());

    float k = spring->getRigidity();
    float m = matPoints[externalIndex]->getWeight();
    float L0 = spring->getDefaultLength();

    std::function<float(std::valarray<float>)> capturingAccelerationX = xAcc;
    std::function<float(std::valarray<float>)> capturingAccelerationY = yAcc;

    int x1Index = 0;
    int x2Index = externalIndex;
    int index1 = findIndexOfDrawableByHash(spring->getFirstConnectable());
    int index2 = findIndexOfDrawableByHash(spring->getSecondConnectable());

    if (index1 == -1 || index2 == -1)
    {
        StationaryPoint *statPoint;
        if (index1 == -1 && spring->getFirstConnectable()->getType() == STATIONARY_POINT)
            statPoint = (StationaryPoint*) spring->getFirstConnectable();
        else if (index2 == -1 && spring->getSecondConnectable()->getType() == STATIONARY_POINT)
            statPoint = (StationaryPoint*) spring->getSecondConnectable();
        else
        {
            qInfo() << "No stationary point found";
            return result;
        }
        float x1 = statPoint->getCenter().x;
        float y1 = statPoint->getCenter().y;
        result.push_back(
                [capturingAccelerationX, k, m, L0, x2Index, x1, y1](std::valarray<float> args)
                    {
                        float x2 = args[6*x2Index];
                        float y2 = args[6*x2Index + 2];
                        float square = sqrtf(powf(x2 - x1, 2) + powf(y2 - y1, 2));
                        return capturingAccelerationX(args) + (-1.0f) / m * k * (square - L0) * (x2 - x1)  / square;
                    }
                );
        result.push_back(
                [capturingAccelerationY, k, m, L0, x2Index, x1, y1](std::valarray<float> args){
                        float x2 = args[6*x2Index];
                        float y2 = args[6*x2Index + 2];
                        float square = sqrtf(powf(x2 - x1, 2) + powf(y2 - y1, 2));
                        return capturingAccelerationY(args) + (-1.0f) / m * k * (square - L0) * (y2 - y1) / square;
                    }
                );

    }
    else
    {
        if (index1 != externalIndex)
            x1Index = index1;
        else
            x1Index = index2;

        result.push_back(
                [capturingAccelerationX, k, m, L0, x2Index, x1Index](std::valarray<float> args)
                    {
                        float x2 = args[6*x2Index];
                        float y2 = args[6*x2Index + 2];
                        float x1 = args[6*x1Index];
                        float y1 = args[6*x1Index + 2];
                        float square = sqrtf(powf(x2 - x1, 2) + powf(y2 - y1, 2));
                        return capturingAccelerationX(args) + (-1.0f) / m * k * (square - L0) * (x2 - x1)  / square;
                    }
                );
        result.push_back(
                [capturingAccelerationY, k, m, L0, x2Index, x1Index](std::valarray<float> args){
                        float x2 = args[6*x2Index];
                        float y2 = args[6*x2Index + 2];
                        float x1 = args[6*x1Index];
                        float y1 = args[6*x1Index + 2];
                        float square = sqrtf(powf(x2 - x1, 2) + powf(y2 - y1, 2));
                        return capturingAccelerationY(args) + (-1.0f) / m * k * (square - L0) * (y2 - y1) / square;
                    }
                );
    }
    result.push_back(
            phiAcc
            );
    return result;
}

QVector<std::function<float(std::valarray<float>)>> ModelingModel::createRodAccelerations(
                                                        std::function<float(std::valarray<float>)> xAcc,
                                                        std::function<float(std::valarray<float>)> yAcc,
                                                        std::function<float(std::valarray<float>)> phiAcc,
                                                        int externalIndex,
                                                        int internalIndex
                                                        )
{
    QVector<std::function<float(std::valarray<float>)>> result;

    float g = this->modelG;
    Rod *rod = (Rod*) matPoints[externalIndex]->getPointableObjects()[internalIndex];
    std::function<float(std::valarray<float>)> capturingAccelerationPhi = phiAcc;

    float l = rod->getDefaultLength();
    int phiIndex = findIndexOfDrawableByHash(matPoints[externalIndex]);

    if (phiIndex == -1)
        return result;

    result.push_back(xAcc);
    result.push_back(yAcc);
    result.push_back(
            [capturingAccelerationPhi, l, g, phiIndex](std::valarray<float> args)
                {
                    return capturingAccelerationPhi(args) + (-1.0f) / l * g * sin(args[6*phiIndex + 4] * M_PI / 180);
                }
             );
    return result;
}

QVector<std::function<float(std::valarray<float>)>> ModelingModel::createSpringAndRodAccelerations(
                                                        std::function<float(std::valarray<float>)> xAcc,
                                                        std::function<float(std::valarray<float>)> yAcc,
                                                        std::function<float(std::valarray<float>)> phiAcc,
                                                        int externalIndex,
                                                        int internalIndex
                                                        )
{
    QVector<std::function<float(std::valarray<float>)>> result;

    std::function<float(std::valarray<float>)> capturingAccelerationPhi = phiAcc;

    float l = matPoints[externalIndex]->getRod()->getDefaultLength();

    float x_i0 = 0.0f;
    float y_i0 = 0.0f;
    if (matPoints[externalIndex]->getRod()->getFirstConnectable()->getType() == STATIONARY_POINT)
    {
        x_i0 = matPoints[externalIndex]->getRod()->getFirstConnectable()->getCenter().x;
        y_i0 = matPoints[externalIndex]->getRod()->getFirstConnectable()->getCenter().y;
    }else if (matPoints[externalIndex]->getRod()->getSecondConnectable()->getType() == STATIONARY_POINT)
    {
        x_i0 = matPoints[externalIndex]->getRod()->getSecondConnectable()->getCenter().x;
        y_i0 = matPoints[externalIndex]->getRod()->getSecondConnectable()->getCenter().y;
    }
    else
        return result;

    Spring* spring = (Spring*) matPoints[externalIndex]->getPointableObjects()[internalIndex];
    spring->setRestingLength(spring->getDefaultLength());

    float m = matPoints[externalIndex]->getWeight();
    float L0 = spring->getDefaultLength();
    float k = spring->getRigidity();

    /*if (spring->getFirstConnectable()->getHash() == matPoints[externalIndex]->getHash())
        m = ((MaterialPoint*) spring->getSecondConnectable())->getWeight();
    else
        m = ((MaterialPoint*) spring->getFirstConnectable())->getWeight();*/

    int x1Index = 0;
    int x2Index = externalIndex;
    int index1 = findIndexOfDrawableByHash(spring->getFirstConnectable());
    int index2 = findIndexOfDrawableByHash(spring->getSecondConnectable());

    if (index1 == -1 || index2 == -1)
    {
        int iIndex;
        float x_j;
        float y_j;
        StationaryPoint *statPoint;
        if (spring->getFirstConnectable()->getType() == STATIONARY_POINT)
        {
            statPoint = (StationaryPoint*)spring->getFirstConnectable();
        }
        else if (spring->getSecondConnectable()->getType() == STATIONARY_POINT)
        {
            statPoint = (StationaryPoint*)spring->getFirstConnectable();
        }
        else
        {
            qWarning() << "Stationary point not found";
            return result;
        }
        iIndex = x2Index;
        x_j = statPoint->getCenter().x;
        y_j = statPoint->getCenter().y;
        result.push_back(xAcc);
        result.push_back(yAcc);
        result.push_back(
            [capturingAccelerationPhi, m, l, k, x_i0, y_i0, L0, iIndex, x_j, y_j](std::valarray<float> args){
                    float phi = args[6 * iIndex + 4] * M_PI / 180;
                    float square = sqrtf(powf(x_i0 + l * cosf(phi) - x_j, 2) + powf(y_i0 + l * sinf(phi) - y_j, 2));
                    return capturingAccelerationPhi(args) + (/*-*/ 1.0f) / (l * l * m) //TODO CHECK SIGN HERE
                            * k * (square - L0)
                            * (2 * (l * cosf(phi) * (l*sinf(phi) + x_i0 - x_j)
                                    - l * sinf(phi) * (l * cosf(phi) + y_i0 - y_j)))
                            / square;
        });
    }
    else
    {
        if (index1 != externalIndex)
            x1Index = index1;
        else
            x1Index = index2;
        int iIndex = x2Index;
        int jIndex = x1Index;

        result.push_back(xAcc);
        result.push_back(yAcc);
        result.push_back(
                [capturingAccelerationPhi, m, l, k, x_i0, y_i0, L0, iIndex, jIndex](std::valarray<float> args){
                        float phi = args[6 * iIndex + 4] * M_PI / 180;
                        float x_j = args[6 * jIndex];
                        float y_j = args[6 * jIndex + 2];
                        float square = sqrtf(powf(x_i0 + l * cosf(phi) - x_j, 2) + powf(y_i0 + l * sinf(phi) - y_j, 2));
                        return capturingAccelerationPhi(args) + (/*-*/ 1.0f) / (l * l * m) //TODO CHECK SIGN HERE
                                * k * (square - L0)
                                * (2 * (l * cosf(phi) * (l*sinf(phi) + x_i0 - x_j)
                                        - l * sinf(phi) * (l * cosf(phi) + y_i0 - y_j)))
                                / square;
                    }
                        );
    }
    return result;
}

int ModelingModel::findIndexOfDrawableByHash(DrawableObject *conn)
{
    for (int i = 0; i < matPoints.size(); i++)
    {
        if (matPoints[i]->getHash() == conn->getHash())
        {
            return i;
        }
    }
//    for (int i = 0; i < rods.size(); i++)
//    {
//        if (rods[i]->getHash() == conn->getHash())
//        {
//            return i;
//        }
//    }
    return -1;
}

std::valarray<float> ModelingModel::getConnectablesPosition()
{
//    std::valarray<float> result(matPoints.size() * 4 + rods.size() * 2);
//    for (size_t i = 0; i < matPoints.size() * 4; i += 4)
//    {
//        result[i] = matPoints[i/4]->getCenter().x;
//        result[i+1] = matPoints[i/4]->getSpeedX();
//        result[i+2] = matPoints[i/4]->getCenter().y;
//        result[i+3] = matPoints[i/4]->getSpeedY();
//    }
//    for (size_t i = 0; i < rods.size(); i++)
//    {
//        result[matPoints.size() * 4 + i * 2] = countPhi(rods[i]);
//        result[matPoints.size() * 4 + i * 2 + 1] = countPhiSpeed(rods[i]);
//    }
//    return result;
    std::valarray<float> result(matPoints.size() * 6);
    for (size_t i = 0; i < matPoints.size(); i++)
    {
        result[i * 6] = matPoints[i]->getCenter().x;
        result[i * 6 + 1] = matPoints[i]->getSpeedX();
        result[i * 6 + 2] = matPoints[i]->getCenter().y;
        result[i * 6 + 3] = matPoints[i]->getSpeedY();
        if (matPoints[i]->isConnectedToRods())
        {
            result[i * 6 + 4] = countPhi(
                        (Rod*) matPoints[i]->getRod()
                        );
            result[i * 6 + 5] = matPoints[i]->getAngularSpeed();/*countPhiSpeed(
                        (Rod*) matPoints[i]->getRod(),
                        result[i * 6 + 4]
                        );*/
        }else
        {
            result[i * 6 + 4] = 0.0f;
            result[i * 6 + 5] = 0.0f;
        }
    }
    return result;
}

float ModelingModel::countPhi(Rod *rod)
{
    qInfo() << "phi = " << rod->getAngle();
    return rod->getAngle();
}

float ModelingModel::countPhiSpeed(Rod *rod, float phi)
{
    qWarning() << "Not implemented";
    return 0.0f;
}

void ModelingModel::resetMaterialPointsSpeeds()
{
    for (int i = 0; i < matPoints.size(); i++)
    {
        matPoints[i]->setSpeedX(0.0f);
        matPoints[i]->setSpeedY(0.0f);
        matPoints[i]->setAngularSpeed(0.0f);
    }
}

void ModelingModel::applySpeedsAndCoordinatesToModel(std::valarray<float> arr)
{
    for (int i = 0; i < matPoints.size(); i++)
    {
        if (arr[i * 6 + 4] == 0.0f && arr[i * 6 + 5] == 0.0f)
        {
            matPoints[i]->setX(arr[i * 6]);
            matPoints[i]->setSpeedX(arr[i * 6 + 1]);
            matPoints[i]->setY(arr[i * 6 + 2]);
            matPoints[i]->setSpeedY(arr[i * 6 + 3]);
        }else
        {
            Rod *rod = (Rod*) matPoints[i]->getRod();
            MaterialPoint *matPoint;
            StationaryPoint *statPoint;
            if (rod->getFirstConnectable()->getType() == MATERIAL_POINT)
            {
                matPoint = (MaterialPoint*) rod->getFirstConnectable();
                statPoint = (StationaryPoint*) rod->getSecondConnectable();
            }
            if (rod->getSecondConnectable()->getType() == MATERIAL_POINT)
            {
                matPoint = (MaterialPoint*) rod->getSecondConnectable();
                statPoint = (StationaryPoint*) rod->getFirstConnectable();
            }
            float length = rod->getDefaultLength();
            float x = statPoint->getCenter().x - sinf(arr[i * 6 + 4] * M_PI / 180) * (length + matPoint->getRadius());
            float y = statPoint->getCenter().y + sinf((arr[i * 6 + 4] - 90) * M_PI / 180) * (length + matPoint->getRadius());
            float angularSpeed = arr[i * 6 + 5];
            matPoint->setX(x);
            matPoint->setY(y);
            matPoint->setAngularSpeed(angularSpeed);
        }
    }
}

void ModelingModel::updateSpringsAndRods(bool isMovedByUser)
{
    for (int i = 0; i < springs.size(); i++)
        springs[i]->update(isMovedByUser);

    for (int i = 0; i < rods.size(); i++)
        rods[i]->update(isMovedByUser);
}

float ModelingModel::countSystemEnergy()
{
    return /*countKineticEnergy() + */countPotentialEnergy();
}

float ModelingModel::countKineticEnergy()
{
    float energy = 0.0f;
    for (int i = 0; i < matPoints.size(); i++)
    {
        if (matPoints[i]->getRod() == nullptr)
        {
            float squareV = powf(matPoints[i]->getSpeedX(), 2) + powf(matPoints[i]->getSpeedY(), 2);
            energy += matPoints[i]->getWeight() * squareV / 2;
        }
        else
        {
            float w = matPoints[i]->getAngularSpeed();
            energy += matPoints[i]->getWeight() * powf(matPoints[i]->getRod()->getDefaultLength() + matPoints[i]->getRadius(), 2) * powf(w, 2) / 2;
        }
    }
    return energy;
}

float ModelingModel::countPotentialEnergy()
{
    float energy = 0.0f;
    for (int i = 0; i < springs.size(); i++)
    {
        energy += springs[i]->getRigidity() * powf(springs[i]->getDefaultLength() - springs[i]->getRestingLength(), 2) / 2;
    }

    float zeroForPotentionalEnergy = -1000.0f;
    for (int i = 0; i < matPoints.size(); i++)
    {
        if (matPoints[i]->getRod() == nullptr)
        {
            energy += matPoints[i]->getWeight() * this->modelG * (matPoints[i]->getCenter().y - zeroForPotentionalEnergy);
        }
        else
        {
            energy += matPoints[i]->getWeight() * this->modelG * (matPoints[i]->getRod()->getDefaultLength() + matPoints[i]->getRadius()) * (1 - cosf(((Rod*)matPoints[i]->getRod())->getAngle() * M_PI / 180));
        }
    }
    return energy;
}

ModelingModel::~ModelingModel()
{
    for (int i = 0; i < matPoints.size(); i++)
        delete matPoints[i];
    for (int i = 0; i < springs.size(); i++)
        delete springs[i];
    for (int i = 0; i < statPoints.size(); i++)
        delete statPoints[i];
    for (int i = 0; i < rods.size(); i++)
        delete rods[i];

    if (speedVectorArrow != nullptr)
        delete speedVectorArrow;
}









