#ifndef MODELINGMODEL_H
#define MODELINGMODEL_H
#include "materialpoint.h"
#include <QDebug>
#include <QFile>
#include <QJsonDocument>

class ModelingModel
{
public:
    ModelingModel();

    void setPlaying(bool playing);
    bool getIsPlaying();
    void addMaterialPoint();
    void addSpring();
    void addStationalPoint();
    void addRod();

    void completeModel();

    QVector<MaterialPoint*> getMaterialPoints();
    QVector<Spring*> getSprings();
    QVector<StationaryPoint*> getStatPoints();
    QVector<Rod*> getRods();

    QVector<DrawableObject*> getDrawableObjects();

    void setSelectedObject(DrawableObject *obj){selectedObject = obj;}
    DrawableObject *getSelectedObject(){return selectedObject;}

    bool isObjectSelected(){return selectedObject != nullptr;}

    void setIncompletedObject(DrawableObject *obj){incompletedObject = obj;}
    DrawableObject *getIncompletedObject(){return incompletedObject;}

    void connectObjects(DrawableObject *first, DrawableObject *second);

    void save();
    void load();

private:
    bool isPlaying;

    QVector<MaterialPoint*> matPoints;
    QVector<Spring*> springs;
    QVector<StationaryPoint*> statPoints;
    QVector<Rod*> rods;

    DrawableObject* selectedObject;
    DrawableObject* incompletedObject;

};

/*
 * Test saveFile for loading:
{
    "ID_COUNTER": "17",
    "drawables": [
        {
            "hash": "0",
            "pointables": [
                {
                    "0": "0"
                }
            ],
            "radius": 0.10000000149011612,
            "type": 0,
            "weight": 5242988,
            "x": -0.09913045167922974,
            "y": 0.7858376502990723
        },
        {
            "hash": "1",
            "pointables": [
                {
                    "0": "0"
                }
            ],
            "radius": 0.20000000298023224,
            "type": 0,
            "weight": 5242988,
            "x": 0.6452174186706543,
            "y": -0.5785837173461914
        },
        {
            "hash": "8",
            "pointables": [
                {
                    "0": "0"
                },
                {
                    "1": "16"
                }
            ],
            "radius": 0.20000000298023224,
            "type": 0,
            "weight": 5242988,
            "x": -0.6104347705841064,
            "y": -0.4058722257614136
        },
        {
            "hash": "7",
            "pointables": [
                {
                    "0": "0"
                }
            ],
            "radius": 0,
            "type": 0,
            "weight": 0,
            "x": -0.5991304516792297,
            "y": 0.5369603037834167
        },
        {
            "hash": "6",
            "pointables": [
            ],
            "radius": 0,
            "type": 0,
            "weight": 0,
            "x": -0.5414910316467285,
            "y": 0.3370670974254608
        },
        {
            "angle": -28.614280700683594,
            "first": "0",
            "hash": "2",
            "height": 1.2542520761489868,
            "rigidiny": 0,
            "second": "1",
            "type": 1,
            "width": 0.10000000149011612,
            "x": 0.19909796118736267,
            "y": 0.7746461629867554
        },
        {
            "hash": "15",
            "height": 0.20000000298023224,
            "pointables": [
                {
                    "0": "16"
                }
            ],
            "type": 2,
            "width": 0.20000000298023224,
            "x": -0.8252174258232117,
            "y": 0.7269430160522461
        },
        {
            "angle": -7.0149688720703125,
            "first": "15",
            "hash": "16",
            "height": 0.7398506999015808,
            "second": "8",
            "type": 3,
            "width": 0.10000000149011612,
            "x": -0.7300389409065247,
            "y": 0.5297122001647949
        }
    ]
}

 * */

#endif // MODELINGMODEL_H
