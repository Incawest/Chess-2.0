#pragma once

#include "BaseEdgeConnector.h"

class TopEdgeConnector : public BaseEdgeConnector
{
public:
    using BaseEdgeConnector::BaseEdgeConnector;
    virtual void DrawCell(int line) const override;
};