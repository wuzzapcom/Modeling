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

    matPoints.append(new MaterialPoint(Point(0.0, 0.0), 0.1f));
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
        DrawableObject *drawable = nullptr;

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
QVector<std::function<double(std::valarray<double>)>> ModelingModel::createAccelerations()
{
    QVector<std::function<double(std::valarray<double>)>> accs;
    double g = this->gravitation;

    for(int i = 0; i < matPoints.size(); i++)
    {
        std::function<double(std::valarray<double>)> xAcceleration = [](std::valarray<double>){return 0;};
        std::function<double(std::valarray<double>)> yAcceleration = [g](std::valarray<double>){return -g;};
        std::function<double(std::valarray<double>)> phiAcceleration = [](std::valarray<double>){return 0;};

        for(int j = 0; j < matPoints[i]->getPointableObjects().size(); j++)
        {
            QVector<std::function<double(std::valarray<double>)>> accs;

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

QVector<std::function<double(std::valarray<double>)>> ModelingModel::createSpringAccelerations(
                                                        std::function<double(std::valarray<double>)> xAcc,
                                                        std::function<double(std::valarray<double>)> yAcc,
                                                        std::function<double(std::valarray<double>)> phiAcc,
                                                        int externalIndex,
                                                        int internalIndex
                                                        )
{
    QVector<std::function<double(std::valarray<double>)>> result;

    Spring* spring = (Spring*) matPoints[externalIndex]->getPointableObjects()[internalIndex];

    spring->setRestingLength(spring->getDefaultLength());

    double k = spring->getRigidity();
    double m = matPoints[externalIndex]->getWeight();
    double L0 = this->countSpringDefaultLength(spring); //spring->getRestingLength();//spring->getDefaultLength();

    std::function<double(std::valarray<double>)> capturingAccelerationX = xAcc;
    std::function<double(std::valarray<double>)> capturingAccelerationY = yAcc;

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
        //double L0 = spring->getRestingLength() + matPoints[externalIndex]->getRadius();
        double x1 = statPoint->getCenter().x;
        double y1 = statPoint->getCenter().y;
        result.push_back(
                [capturingAccelerationX, k, m, L0, x2Index, x1, y1](std::valarray<double> args)
                    {
                        double x2 = args[6*x2Index];
                        double y2 = args[6*x2Index + 2];
                        double square = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
                        return capturingAccelerationX(args) + (-1.0) / m * k * (square - L0) * (x2 - x1)  / square;
                    }
                );
        result.push_back(
                [capturingAccelerationY, k, m, L0, x2Index, x1, y1](std::valarray<double> args){
                        double x2 = args[6*x2Index];
                        double y2 = args[6*x2Index + 2];
                        double square = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
                        return capturingAccelerationY(args) + (-1.0) / m * k * (square - L0) * (y2 - y1) / square;
                    }
                );

    }
    else
    {
        //double L0 = this->countSpringDefaultLength(spring);
//        double L0 = spring->getRestingLength() + ((MaterialPoint*)spring->getFirstConnectable())->getRadius() + ((MaterialPoint*)spring->getSecondConnectable())->getRadius();
//        logger.logLengths(L0,
//                           spring->getFirstConnectable()->getCenter().x,
//                           spring->getFirstConnectable()->getCenter().y,
//                           spring->getSecondConnectable()->getCenter().x,
//                           spring->getSecondConnectable()->getCenter().y
//                           );
        if (index1 != externalIndex)
            x1Index = index1;
        else
            x1Index = index2;

        result.push_back(
                [capturingAccelerationX, k, m, L0, x2Index, x1Index](std::valarray<double> args)
                    {
                        double x2 = args[6*x2Index];
                        double y2 = args[6*x2Index + 2];
                        double x1 = args[6*x1Index];
                        double y1 = args[6*x1Index + 2];
                        double square = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
                        return capturingAccelerationX(args) + (-1.0) / m * k * (square - L0) * (x2 - x1)  / square;
                    }
                );
        result.push_back(
                [capturingAccelerationY, k, m, L0, x2Index, x1Index](std::valarray<double> args){
                        double x2 = args[6*x2Index];
                        double y2 = args[6*x2Index + 2];
                        double x1 = args[6*x1Index];
                        double y1 = args[6*x1Index + 2];
                        double square = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
                        return capturingAccelerationY(args) + (-1.0) / m * k * (square - L0) * (y2 - y1) / square;
                    }
                );
    }
    result.push_back(
            phiAcc
            );
    return result;
}

QVector<std::function<double(std::valarray<double>)>> ModelingModel::createRodAccelerations(
                                                        std::function<double(std::valarray<double>)> xAcc,
                                                        std::function<double(std::valarray<double>)> yAcc,
                                                        std::function<double(std::valarray<double>)> phiAcc,
                                                        int externalIndex,
                                                        int internalIndex
                                                        )
{
    QVector<std::function<double(std::valarray<double>)>> result;

    double g = this->gravitation;
    Rod *rod = (Rod*) matPoints[externalIndex]->getPointableObjects()[internalIndex];
    std::function<double(std::valarray<double>)> capturingAccelerationPhi = phiAcc;

    double l = rod->getDefaultLength() + matPoints[externalIndex]->getRadius();
    int phiIndex = findIndexOfDrawableByHash(matPoints[externalIndex]);

    if (phiIndex == -1)
        return result;

    result.push_back(xAcc);
    result.push_back(yAcc);
    result.push_back(
            [capturingAccelerationPhi, l, g, phiIndex](std::valarray<double> args)
                {
                    return capturingAccelerationPhi(args) + (-1.0) / l * g * std::sin(args[6*phiIndex + 4]);
                }
             );
    return result;
}

QVector<std::function<double(std::valarray<double>)>> ModelingModel::createSpringAndRodAccelerations(
                                                        std::function<double(std::valarray<double>)> xAcc,
                                                        std::function<double(std::valarray<double>)> yAcc,
                                                        std::function<double(std::valarray<double>)> phiAcc,
                                                        int externalIndex,
                                                        int internalIndex
                                                        )
{
    QVector<std::function<double(std::valarray<double>)>> result;

    std::function<double(std::valarray<double>)> capturingAccelerationPhi = phiAcc;

    double x_i0 = 0.0;
    double y_i0 = 0.0;
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

    double l = std::sqrt(std::pow(matPoints[externalIndex]->getCenter().x - x_i0, 2.0) + std::pow(matPoints[externalIndex]->getCenter().y - y_i0, 2.0));//matPoints[externalIndex]->getRod()->getDefaultLength() + matPoints[externalIndex]->getRadius();

    Spring* spring = (Spring*) matPoints[externalIndex]->getPointableObjects()[internalIndex];
    spring->setRestingLength(spring->getDefaultLength());

    double m = matPoints[externalIndex]->getWeight();
    double L0 = this->countSpringDefaultLength(spring);//spring->getDefaultLength() + matPoints[externalIndex]->getRadius();
    double k = spring->getRigidity();

    int x1Index = 0;
    int x2Index = externalIndex;
    int index1 = findIndexOfDrawableByHash(spring->getFirstConnectable());
    int index2 = findIndexOfDrawableByHash(spring->getSecondConnectable());

    if (index1 == -1 || index2 == -1)
    {
        int iIndex;
        double x_j;
        double y_j;
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
            [capturingAccelerationPhi, m, l, k, x_i0, y_i0, L0, iIndex, x_j, y_j](std::valarray<double> args){
                    double phi = args[6 * iIndex + 4];
                    double square = std::sqrt(std::pow(x_i0 + l * std::sin(phi) - x_j, 2) + std::pow(y_i0 + l * std::cos(phi) - y_j, 2));
                    return capturingAccelerationPhi(args) + (/*-*/ 1.0) / (l * l * m) //TODO CHECK SIGN HERE
                            * k * (square - L0)
                            * (2 * (l * std::cos(phi) * (l*std::sin(phi) + x_i0 - x_j)
                                    - l * std::sin(phi) * (l * std::cos(phi) + y_i0 - y_j)))
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
                [capturingAccelerationPhi, m, l, k, x_i0, y_i0, L0, iIndex, jIndex](std::valarray<double> args){
                        double phi = args[6 * iIndex + 4];
                        double x_j = args[6 * jIndex];
                        double y_j = args[6 * jIndex + 2];
                        double square = std::sqrt(std::pow(x_i0 + l * std::sin(phi) - x_j, 2) + std::pow(y_i0 + l * std::cos(phi) - y_j, 2));
                        return capturingAccelerationPhi(args) + (/*-*/ 1.0) / (l * l * m) //TODO CHECK SIGN HERE
                                * k * (square - L0)
                                * (2 * (l * std::cos(phi) * (l*std::sin(phi) + x_i0 - x_j)
                                        - l * std::sin(phi) * (l * std::cos(phi) + y_i0 - y_j)))
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
    return -1;
}

std::valarray<double> ModelingModel::getConnectablesPosition()
{
    std::valarray<double> result(matPoints.size() * 6);
    for (int i = 0; i < matPoints.size(); i++)
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
            result[i * 6 + 5] = matPoints[i]->getAngularSpeed();
        }else
        {
            result[i * 6 + 4] = 0.0;
            result[i * 6 + 5] = 0.0;
        }
    }
    return result;
}

double ModelingModel::countPhi(Rod *rod)
{
    qInfo() << "phi = " << rod->getAngle() * PI / 180.0;
    return rod->getAngle() * PI / 180.0;
}

double ModelingModel::countPhiSpeed(Rod *, double)
{
    qWarning() << "Not implemented";
    return 0.0;
}

void ModelingModel::resetMaterialPointsSpeeds()
{
    for (int i = 0; i < matPoints.size(); i++)
    {
        matPoints[i]->setSpeedX(0.0);
        matPoints[i]->setSpeedY(0.0);
        matPoints[i]->setAngularSpeed(0.0);
    }
}

void ModelingModel::applySpeedsAndCoordinatesToModel(std::valarray<double> arr)
{
    for (int i = 0; i < matPoints.size(); i++)
    {
        if (arr[i * 6 + 4] == 0.0 && arr[i * 6 + 5] == 0.0)
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
            double length = rod->getDefaultLength();
            double x = statPoint->getCenter().x - std::sin(arr[i * 6 + 4]) * (length + matPoint->getRadius());
            double y = statPoint->getCenter().y + std::sin((arr[i * 6 + 4] - PI / 2.0)) * (length + matPoint->getRadius());
            double angularSpeed = arr[i * 6 + 5];
            qInfo() << "Angular speed =" << angularSpeed;
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

double ModelingModel::countSystemEnergy()
{
    return countKineticEnergy() + countPotentialEnergy();
}

double ModelingModel::countSpringDefaultLength(Spring *spring)
{
    StationaryPoint *statPoint = nullptr;
    MaterialPoint *matPoint1 = nullptr;
    MaterialPoint *matPoint2 = nullptr;
    if (spring->getFirstConnectable()->getType() == STATIONARY_POINT)
    {
        statPoint = (StationaryPoint*) spring->getFirstConnectable();
        matPoint1 = (MaterialPoint*) spring->getSecondConnectable();
    }
    else if (spring->getSecondConnectable()->getType() == STATIONARY_POINT)
    {
        statPoint = (StationaryPoint*) spring->getSecondConnectable();
        matPoint1 = (MaterialPoint*) spring->getFirstConnectable();
    }
    else
    {
        matPoint1 = (MaterialPoint*) spring->getFirstConnectable();
        matPoint2 = (MaterialPoint*) spring->getSecondConnectable();
    }

    if (statPoint == nullptr)
    {
        double length1 = spring->getRestingLength() + matPoint1->getRadius() + matPoint2->getRadius();
        double length2 = std::sqrt(std::pow(matPoint1->getCenter().x - matPoint2->getCenter().x, 2.0) + std::pow(matPoint1->getCenter().y - matPoint2->getCenter().y, 2.0));
        qInfo() << "length1" << length1;
        qInfo() << "length2" << length2;
        return length2;
    }else
    {
        double length1 = spring->getRestingLength() + matPoint1->getRadius();
        double length2 = std::sqrt(std::pow(matPoint1->getCenter().x - statPoint->getCenter().x, 2.0) + std::pow(matPoint1->getCenter().y - statPoint->getCenter().y, 2.0));
        qInfo() << "length1" << length1;
        qInfo() << "length2" << length2;
        return length2;
    }
}

double ModelingModel::countKineticEnergy()
{
    double energy = 0.0;
    for (int i = 0; i < matPoints.size(); i++)
    {
        if (matPoints[i]->getRod() == nullptr)
        {
            double squareV = std::pow(matPoints[i]->getSpeedX(), 2) + std::pow(matPoints[i]->getSpeedY(), 2);
            energy += matPoints[i]->getWeight() * squareV / 2;
        }
        else
        {
            double w = matPoints[i]->getAngularSpeed();
            energy += matPoints[i]->getWeight() * std::pow(matPoints[i]->getRod()->getDefaultLength() + matPoints[i]->getRadius(), 2) * std::pow(w, 2) / 2.0;
        }
    }
    return energy;
}

double ModelingModel::countPotentialEnergy()
{
    double energy = 0.0;
    for (int i = 0; i < springs.size(); i++)
    {
        energy += springs[i]->getRigidity() * std::pow(springs[i]->getDefaultLength() - springs[i]->getRestingLength(), 2) / 2;
    }
    for (int i = 0; i < matPoints.size(); i++)
    {
//        if (matPoints[i]->getRod() == nullptr)
//        {
            energy += matPoints[i]->getWeight() * this->gravitation * matPoints[i]->getCenter().y;
//        }
//        else
//        {
//            energy += matPoints[i]->getWeight() * this->gravitation * (matPoints[i]->getRod()->getDefaultLength() + matPoints[i]->getRadius()) *
//                    (1.0 - std::cos(((Rod*)matPoints[i]->getRod())->getAngle() * PI / 180.0));
//        }
    }
    return energy;
}

void ModelingModel::switchGravitation()
{
    if (this->gravitation == ENABLED_GRAVITATION_VALUE)
        this->gravitation = DISABLED_GRAVITATION_VALUE;
    else if (this->gravitation == DISABLED_GRAVITATION_VALUE)
        this->gravitation = ENABLED_GRAVITATION_VALUE;
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









