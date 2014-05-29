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
    OutputDebugString( os_.str().c_str() ); \
}

// Default size all sprites in game
#define SPRITE_WIDTH    64
#define SPRITE_HEIGHT   64

#define MAP_WIDTH    30
#define MAP_HEIGHT   100

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
        Point<T> positive() {
            x = abs(x);
            y = abs(y);
            return *this;
        }
        Point<T> negative() {
            x = -x;
            y = -y;
            return *this;
        }
        bool isNull() const  
        {
            return x == 0 && y == 0;
        }
        bool operator == (const Point& _pt) 
        {
            return _pt.X() == X() && _pt.Y() == Y();
        }
        Point<T> operator+= (const Point<T> & _pt) 
        {
            x += _pt.X();
            y += _pt.Y();
            return *this;
        }
        Point<T> operator+ (const Point<T> & _pt) 
        {
            return Point<T>(x + _pt.X(), y + _pt.Y());
        }
        Point<T> operator- (const Point<T> & _pt) 
        {
            return Point<T>(x - _pt.X(), y - _pt.Y());
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
        Rect<T> operator= (const Point<T> & _pt) 
        {
            setX(_pt.X());
            setY(_pt.Y());
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
        Rect<T> operator+= (const Point<T> & _pt)
        {
            x += _pt.X();
            y += _pt.Y();
            return *this;
        }
        Point<T> toPoint()
        {
            return Point<T>(x,y);
        }
        // If they have hit a point in the rectangle.
        // @return If hit a point in the rectangle <code>true</code> otherwise <code>false</code>.
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
    typedef Size<int> SizeI;

    /*
    class Grid is to work automatic distribution of cell coordinates 
    example
    DQ::Grid grid(DQ::SizeI(100,100),DQ::SizeI(10,10));
    DQ::RectI rt = grid.getCell(3,1);
    */
    class Grid {
    public:
        Grid(SizeI area, SizeI szCell);
        RectI getCell(int _row, int _col);
        RectI getCell(const PointI& );
    private:
        SizeI m_szRectArea;
        SizeI m_szRectCell;
    };

    // Default size.
    // @return Rectangle current from grid.
    inline RectI getCell(const PointI& _pt) {
        PointI res;
        Grid grid(DQ::SizeI(MAP_WIDTH, MAP_HEIGHT),DQ::SizeI(SPRITE_WIDTH, SPRITE_HEIGHT));
        return grid.getCell(_pt.X(), _pt.Y());
    }

    /*
    example
    std::vector< DQ::RectF > rectangle = calculationRectangleFrames(Size<float>(30.f,30.f),3);
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
