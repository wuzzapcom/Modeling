#include "rungecutta.h"

RungeCutta::RungeCutta(
        QVector<std::function<double (std::valarray<double>)>> accs,
        std::valarray<double> startState
        )
{
    accelerations = accs;
    countedModelStates.push_back(startState);
}

std::valarray<double> RungeCutta::getNextState()
{
    if (countedModelStates.size() == 0){
        qDebug() << "FUCK THIS COUNTEDMODEL IS EMPTY";
        return std::valarray<double>(0);
    }
    else if (countedModelStates.size() == 1)
    {
        return countedModelStates.first();
    }
    else
    {
        std::valarray<double> l = countedModelStates.first();
        countedModelStates.pop_front();
        return l;
    }
}

void RungeCutta::resetState(
        QVector<std::function<double (std::valarray<double>)>> accs,
        std::valarray<double> startState
        )
{
    accelerations = accs;
    countedModelStates.clear();
    countedModelStates.push_back(startState);
}

void RungeCutta::updateStates(std::valarray<double> startState)
{
    countedModelStates.clear();
    countedModelStates.push_back(startState);
}

std::valarray<double> RungeCutta::applyPositionsToAccelerations(std::valarray<double> args)
{
    std::valarray<double> result(countedModelStates.first().size());
    for (int i = 0; i < accelerations.size(); i++)
    {
        result[2*i + 1] = accelerations[i](args);
        result[2*i] = args[2*i + 1];
    }
    return result;
}

std::valarray<double> RungeCutta::rungeCutta()
{
    if (this->accelerations.size() == 0)
        return countedModelStates.last();
    if (this->countedModelStates.size() > 60)
        return countedModelStates.last();
    double h = 1.0 / 60.0;
    std::valarray<double> k1 = applyPositionsToAccelerations(countedModelStates.last());
    std::valarray<double> k2 = applyPositionsToAccelerations(countedModelStates.last() + h / 2 * k1);
    std::valarray<double> k3 = applyPositionsToAccelerations(countedModelStates.last() + h / 2 * k2);
    std::valarray<double> k4 = applyPositionsToAccelerations(countedModelStates.last() + h * k3);

//    countedModelStates.push_back(countedModelStates.last() + h / 6 * (k1 + 2.0 * k2 + 2.0 * k3 + k4));
    return countedModelStates.last() + h / 6 * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
}
