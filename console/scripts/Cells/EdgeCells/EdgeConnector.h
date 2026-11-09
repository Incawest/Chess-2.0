#pragma once

#include "BaseEdgeCell.h"
#include "CellsConfiguration.h"
#include "Utilits.h"

class EdgeConnector : public BaseEdgeCell<CellsConfiguration::SPACE_BETWEEN_CELLS, CellsConfiguration::HORIZONTAL_EDGE_HEIGHT>
{
public:
    enum class Type{
        TOP,
        BOTTOM
    };
private:
    const Type CONNECTOR_TYPE;
    const std::size_t FILLED_LINE;
public:
    EdgeConnector(wchar_t edgeChar, const RGB* cellColor, Type connectorType):
        BaseEdgeCell{edgeChar, cellColor}, CONNECTOR_TYPE{connectorType}, FILLED_LINE{CONNECTOR_TYPE == Type::TOP ? HEIGHT - 1 : 0}
    {
    }

    EdgeConnector(wchar_t edgeChar, Type connectorType) : EdgeConnector{edgeChar, nullptr, connectorType}
    {
    }

    void DrawCell(std::size_t line) const override
    {
        if (line == FILLED_LINE)
            DrawEdgeChars(WIDTH);
        else
            DrawOutsideLine({}, WIDTH);
    }
};