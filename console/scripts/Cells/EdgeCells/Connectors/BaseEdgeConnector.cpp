#include "BaseEdgeConnector.h"

BaseEdgeConnector::BaseEdgeConnector(wchar_t edgeChar, const RGB* cellColor):
    BaseEdgeCell{[this](){
        for (std::size_t i = 0; i < WIDTH; ++i)
            std::wcout << _EDGE_CHAR;
    }, edgeChar, cellColor}
{
}

BaseEdgeConnector::BaseEdgeConnector(wchar_t edgeChar) : BaseEdgeConnector{edgeChar, nullptr}
{
}