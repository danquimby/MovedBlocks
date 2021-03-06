#include "helpers.h"
#include "tinyxml.h"
#include <assert.h>

namespace DQ 
{

    std::vector< RectF > calculationRectangleFrames(Size<float>& _rectObject,int _nFrames) {
        std::vector< RectF > result;
        RectF rect;
        rect.setWidth(_rectObject.width());
        rect.setHeight(_rectObject.height());
        for (int i = 0; i < _nFrames; ++i)
        {
            rect.setX(_rectObject.width() * i);
            result.push_back(rect);
        }
        return result;
    }

    //--------------------------------------------------------
    Grid::Grid(Size<int> _area, Size<int> _szCell) 
        : m_szRectArea(_area),m_szRectCell(_szCell) 
    {    }

    RectI Grid::getCell(const PointI& _ptGrid) {
        return getCell(_ptGrid.X(), _ptGrid.Y());
    }

    RectI Grid::getCell(int _row, int _col) {
        RectI result;
        result = m_szRectCell;
        result.setX(result.width() * _row);
        result.setY(result.height() * _col);
        return result;
    }

//--------------------------------------------------------

}
