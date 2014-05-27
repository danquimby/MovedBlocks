#ifndef HELPERS_H
#define HELPERS_H

#include "hge/hge.h"

#include <Windows.h>
#include <iostream>
#include <sstream>
#include <iostream>

#include "hge/hgeanim.h"
#include <map>
#include <vector>

#define DBOUT( s )            \
{                             \
    std::ostringstream os_;    \
    os_ << s;                   \
    OutputDebugString( os_.str().c_str() );  \
}

namespace DQ
{

    enum ResourceTypeDate
    {
        TYPE_MAIN_DATA,
        TYPE_BUTTON_DATA,
        TYPE_TEXT_DATA,
        TYPE_LABEL_TEXT_DATA,
        TYPE_OBJECT_DATA,
        TYPE_OBJECT_DRUM_DATA,
        NONE = -1
    };

    template<class T>
    class Point
    {
    public:
        Point()
        {
            clean();
        }
        Point(T _x,T _y) 
            : x(_x) , y(_y)	{}
        void clean() 
        {
            x = y = 0;
        }
        void set(T _x,T _y)
        {
            setX(_x);
            setY(_y);
        }
        T X()const {return x;}
        T Y()const {return y;}
        void setX(T _x){x = _x;}
        void setY(T _y){y = _y;}
        bool isNull() const  
        {
            return x == (T)NULL_VALUE && y == (T)NULL_VALUE;
        }
        bool operator == (const Point& _pt) 
        {
            return _pt.X() == X() && _pt.Y() == Y();
        }
    protected:
        T x,y;
    };

    template<class T>
    class Size
    {
    public:
        Size()
        {
            w = 0; 
            h = 0;
        }
        Size(T _w,T _h)
            : w(_w), h(_h) {}
        T Width()const {return w;}
        T Height()const {return h;}
        void setWidth(T _w){w = _w;}
        void setHeight(T _h){h = _h;}
    protected:
        T w,h;
    };

    template<class T>
    class Rect : public Point<T> , public Size<T>
    {
    public:
        Rect<T>() : Point<T>(), Size<T>(){}
        Rect<T>(Point<T> _point,Size<T> _size) 
            : Point<T>(_point), Size<T>(_size) {}

        Rect<T>(T _x, T _y, T _w, T _h) 
            : Point<T>(_x, _y), Size<T>(_w, _h) {}
        Rect<T> operator= (const Size<T> & _size) 
        {
            setWidth(_size.Width());
            setHeight(_size.Height());
            return *this;
        }
        Rect<T> operator= (const Point<T> & _point) 
        {
            setX(_point.X());
            setY(_point.Y());
            return *this;
        }
        Rect<T> operator+= (const Rect<T> & _rt)
        {
            x += _rt.X();
            y += _rt.Y();
            w += _rt.Width();
            h += _rt.Height();
            return *this;
        }
        Point<T> toPoint()
        {
            return Point<T>(x,y);
        }
        // if they have hit a point in the rectangle 
        bool entrance (const Point<T> & _pt)
        {
            if (w == 0 || h == 0) return false;
            T x1 = x + w;
            T y1 = y + h;
            if ( _pt.Y() >= y && _pt.Y() <= y1)
                if ( _pt.X() >= x && _pt.X() <= x1)
                    return true;
            return false;
        }
    };
    // typedefs
    typedef Rect<float> RectF;
    typedef Rect<int> RectI;
    typedef Point<float> PointF;
    typedef Point<int> PointI;

    /*
    class Grid is to work automatic distribution of cell coordinates 
    example
    DQ::Grid grid(DQ::Size<int>(100,100),DQ::Size<int>(10,10));
    DQ::Rect<int> rt = grid.getCell(3,1);

    */
    class Grid {
    public:
        Grid(Size<int> area, Size<int> szCell);
        Rect<int> getCell(int _row, int _col);
    private:
        Size<int> m_szRectArea;
        Size<int> m_szRectCell;
    };


    struct ResourceItem {
        enum {TYPE_BUTTON,TYPE_TEXT,TYPE_OBJECT,NONE};

        ResourceItem()
            : m_nType(NONE) , m_nId(-1) {}
        int m_nType;// type 
        int m_nId;// for game object instead of a name property 
        PointF  m_ptPosition;// move to object (for text_edit)
        RectF	m_rtArea;// area object
        RectF	m_rtTextArea; // area for text view
        std::string m_sFileName;// file name to resource if exist property

    };
    struct ResourceMainItems{
        std::string	m_strFileNameTile;
        std::string	m_strFileNameBackground;
        std::string	m_strFileNameFont;

    };

    /*
    example
    std::vector< DQ::RectF > rectangle = calculationRectangleFrames(Size<float>(30,30),3);
    */
    extern inline std::vector< RectF > calculationRectangleFrames(Size<float>& ,int );
}
#endif // HELPERS_H
