#include "rungecutta.h"

RungeCutta::RungeCutta(
        QVector<std::function<float (std::valarray<float>)>> accs,
        std::valarray<float> startState
        )
{
    accelerations = accs;
    countedModelStates.push_back(startState);
}

std::valarray<float> RungeCutta::getNextState()
{
    if (countedModelStates.size() == 0){
        qDebug() << "FUCK THIS COUNTEDMODEL IS EMPTY";
        return std::valarray<float>(0);
    }
    else if (countedModelStates.size() == 1)
    {
        return countedModelStates.first();
    }
    else
    {
        std::valarray<float> l = countedModelStates.first();
        countedModelStates.pop_front();
        return l;
    }
}

void RungeCutta::resetState(
        QVector<std::function<float (std::valarray<float>)>> accs,
        std::valarray<float> startState
        )
{
    accelerations = accs;
    countedModelStates.clear();
    countedModelStates.push_back(startState);
}

void RungeCutta::updateStates(std::valarray<float> startState)
{
    countedModelStates.clear();
    countedModelStates.push_back(startState);
}

std::valarray<float> RungeCutta::applyPositionsToAccelerations(std::valarray<float> args)
{
    std::valarray<float> result(countedModelStates.first().size());
    for (int i = 0; i < accelerations.size(); i++)
    {
        result[2*i + 1] = accelerations[i](args);
        result[2*i] = args[2*i + 1];
    }
    return result;
}

std::valarray<float> RungeCutta::rungeCutta()
{
    if (this->accelerations.size() == 0)
        return countedModelStates.last();
    if (this->countedModelStates.size() > 60)
        return countedModelStates.last();
    float h = 1.0f / 60.0f;
    std::valarray<float> k1 = applyPositionsToAccelerations(countedModelStates.last());
    std::valarray<float> k2 = applyPositionsToAccelerations(countedModelStates.last() + h / 2 * k1);
    std::valarray<float> k3 = applyPositionsToAccelerations(countedModelStates.last() + h / 2 * k2);
    std::valarray<float> k4 = applyPositionsToAccelerations(countedModelStates.last() + h * k3);

//    countedModelStates.push_back(countedModelStates.last() + h / 6 * (k1 + 2.0f * k2 + 2.0f * k3 + k4));
    return countedModelStates.last() + h / 6 * (k1 + 2.0f * k2 + 2.0f * k3 + k4);
}
