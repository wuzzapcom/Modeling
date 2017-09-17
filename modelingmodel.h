#ifndef MODELINGMODEL_H
#define MODELINGMODEL_H


class ModelingModel
{
public:
    ModelingModel();

    void setPlaying(bool playing);
    bool getIsPlaying();

private:
    bool isPlaying;
};

#endif // MODELINGMODEL_H
