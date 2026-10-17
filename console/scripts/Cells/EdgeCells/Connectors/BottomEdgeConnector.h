#pragma once

#include "BaseEdgeConnector.h"

class BottomEdgeConnector : public BaseEdgeConnector
{
public:
    using BaseEdgeConnector::BaseEdgeConnector;
    virtual void DrawCell(int line) const override;
};