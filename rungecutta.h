#ifndef RUNGECUTTA_H
#define RUNGECUTTA_H
#include <QVector>
#include <valarray>
#include <QDebug>

class RungeCutta
{
public:
    RungeCutta(
            QVector<std::function<double(std::valarray<double>)>> accs,
            std::valarray<double> startState
            );
    std::valarray<double> getNextState();
    void resetState(
            QVector<std::function<double(std::valarray<double>)>> accs,
            std::valarray<double> startState
            );
    void updateStates(
            std::valarray<double> startState
            );
    std::valarray<double> rungeCutta();
private:

    QMutex mutex;
    std::valarray<double> applyPositionsToAccelerations(std::valarray<double> args);

    QVector<std::valarray<double>> countedModelStates;
    QVector<std::function<double(std::valarray<double>)>> accelerations;

};

#endif // RUNGECUTTA_H
