#ifndef HELPERS_H
#define HELPERS_H

#include <sstream>
#include <vector>

#include "hge/hge.h"
#include "hge/hgeanim.h"

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

    /*
    example
    std::vector< DQ::RectF > rectangle = calculationRectangleFrames(Size<float>(30,30),3);
    */
    extern inline std::vector< RectF > calculationRectangleFrames(Size<float>& ,int );

    inline HGE* cloneHGE() {
        HGE* hge = hgeCreate(HGE_VERSION);
            if (!hge){
                MessageBox(NULL, (LPCTSTR)hge->System_GetErrorMessage(), (LPCTSTR)"Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
                return 0;
            }
        return hge;
    }

    /*
    * Class to work whit RGB variables.
    */
    struct color {
        unsigned R, G, B;

        color(unsigned r, unsigned g, unsigned b) 
            : R(r), G(g), B(b)
        {}
        void fill(unsigned r, unsigned g, unsigned b) {
            R = r;
            G = g;
            B = b;
        }

        // Convert RGB number to DWORD (0xff000000), first element alpha channel.
        DWORD convertToDword(unsigned _alpha = 0xff) {
            return (_alpha << 24) | (R << 16) | (G << 8) | (B);
        }
    };

    inline color colorConvert(const std::string sColor ) {
        if (sColor == "black")
            return color(0, 0, 0);
        if (sColor == "white")
            return color(255, 255, 255);
        if (sColor == "yellow")
            return color(255, 255, 0);
        if (sColor == "blue")
            return color(0, 0, 255);
        if (sColor == "red")
            return color(255, 0, 0);
        if (sColor == "green")
            return color(0, 255, 0);
        if (sColor == "gray")
            return color(192, 192, 192);

        return color(0, 0, 0);
    }
}
#endif // HELPERS_H
