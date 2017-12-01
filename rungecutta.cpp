#include "rungecutta.h"

RungeCutta::RungeCutta()
{
}

void RungeCutta::resetState(
        QVector<std::function<double (std::valarray<double>)>> accs,
        std::valarray<double> startState
        )
{
    accelerations = accs;
    modelState = startState;
}

void RungeCutta::updateStates(std::valarray<double> startState)
{
    modelState = startState;
}

std::valarray<double> RungeCutta::applyPositionsToAccelerations(std::valarray<double> args)
{
    std::valarray<double> result(modelState.size());
    for (int i = 0; i < accelerations.size(); i++)
    {
        result[2*i + 1] = accelerations[i](args);
        result[2*i] = args[2*i + 1];
    }
    return result;
}

std::valarray<double> RungeCutta::rungeCutta()
{
    double h = 1.0 / 60.0;
    std::valarray<double> k1 = applyPositionsToAccelerations(modelState);
    std::valarray<double> k2 = applyPositionsToAccelerations(modelState + h / 2 * k1);
    std::valarray<double> k3 = applyPositionsToAccelerations(modelState + h / 2 * k2);
    std::valarray<double> k4 = applyPositionsToAccelerations(modelState + h * k3);

    return modelState + h / 6 * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
}
