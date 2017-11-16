#ifndef RUNGECUTTA_H
#define RUNGECUTTA_H
#include <QVector>
#include <valarray>
#include <QDebug>

class RungeCutta
{
public:
    RungeCutta(
            QVector<std::function<float(std::valarray<float>)>> accs,
            std::valarray<float> startState
            );
    std::valarray<float> getNextState();
    void resetState(
            QVector<std::function<float(std::valarray<float>)>> accs,
            std::valarray<float> startState
            );
    void updateStates(
            std::valarray<float> startState
            );
    std::valarray<float> rungeCutta();
private:

    QMutex mutex;
    std::valarray<float> applyPositionsToAccelerations(std::valarray<float> args);

    QVector<std::valarray<float>> countedModelStates;
    QVector<std::function<float(std::valarray<float>)>> accelerations;

};

#endif // RUNGECUTTA_H
