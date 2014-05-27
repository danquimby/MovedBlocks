#include "helpers.h"
#include "tinyxml.h"
#include <assert.h>

namespace DQ 
{

    std::vector< RectF > calculationRectangleFrames(Size<float>& _rectObject,int _nFrames) {
        std::vector< RectF > result;
        RectF rect;
        rect.setWidth(_rectObject.Width());
        rect.setHeight(_rectObject.Height());
        for (int i = 0; i < _nFrames; ++i)
        {
            rect.setX(_rectObject.Width() * i);
            result.push_back(rect);
        }
        return result;
    }

    //--------------------------------------------------------
    Grid::Grid(Size<int> _area, Size<int> _szCell) 
        : m_szRectArea(_area),m_szRectCell(_szCell) 
    {

    }
    Rect<int> Grid::getCell(int _row, int _col) {
        Rect<int> result;
        result = m_szRectCell;
        result.setX(result.Width() * _row);
        result.setY(result.Height() * _col);
        return result;
    }
//--------------------------------------------------------

}
