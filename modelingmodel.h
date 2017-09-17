#ifndef MODELINGMODEL_H
#define MODELINGMODEL_H


class ModelingModel
{
public:
    ModelingModel();

    void setPlaying(bool playing);
    bool getIsPlaying();
    void addMaterialPoint();
    void addSpring();

private:
    bool isPlaying;
};

#endif // MODELINGMODEL_H
