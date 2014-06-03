
#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "objects.h"

enum TypeCharacter {
    TYPE_CHARACTER_MAN,
    TYPE_CHARACTER_ENEMY
};

/* BodyComplex
* This class for defining and creating the body of the object.
*
*/
typedef std::vector<std::vector<int> >  bodyComplexItems;
typedef std::vector<int> widthBodyItems;

// Contain game object.
struct ContainsComplexObject {
    ContainsComplexObject(const DQ::SizeI& _size, const std::string& _contains, const std::string& _separator = ",") 
        : m_szSizeObject(_size), m_sContainsData(_contains), m_sSeparator(_separator)
    {
    }
    // Size complex object.
    DQ::SizeI   m_szSizeObject;

    // Data object.
    std::string m_sContainsData;

    // Separator (for parsing from string).
    std::string m_sSeparator;
};

/* BodyComplex
* Template complex body for using in game.
*
* Example using the class
* BodyComplex body(ContainsComplexObject(DQ::SizeI(2,2),"1,1,2,2",","));
* Make array int[][]
 */
class BodyComplex {
public:
    // @param Set existing body.
    BodyComplex(const ContainsComplexObject& );

    // Rebuilding the existing body.
    void reBuildBody(const ContainsComplexObject& );

    bodyComplexItems getBodyItems() const;
    widthBodyItems getWidthBodyItems(int _height);
private:
    // Multidimensional array.
    bodyComplexItems m_vBodyItmes;
};

/* GameCharacter
* Class template characters and enemies.
*
*/
class GameCharacter : public IDrawaibleObjects {
public:

    // @param Position character(in system of calculation grid).
    GameCharacter(const DQ::PointI&, BodyComplex& );

    // For modify need struct BodyComplex.
    void modifyCharacter( BodyComplex& );

    // @override method for render to scene.
    void Render(const DQ::PointF& _ptOffset = DQ::PointF());

    // @override method for processing object.
    void Process();

    void moveVectorCharacter(const DQ::PointI& );

    // @return Position (System of calculation grid).
    DQ::PointI position() const;
private:
    // Clear sprite of contains, and all settings set in default.
    void    clean();

    // Position in system of calculation grid.
    DQ::PointI              m_ptPosition;

    // Contains of body character.
    std::vector<GameBlock*> m_vBlocks;
};

#endif //CHARACTERS_H