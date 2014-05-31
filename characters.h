
#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "objects.h"

enum TypeCharacter {
    TYPE_CHARACTER_MAN,
    TYPE_CHARACTER_ENEMY
};

/*
* Class template characters and enemies.
*
*/
class GameCharacter : public IDrawaibleObjects {
public:

    // @param Position character(in system of calculation grid).
    GameCharacter(const DQ::PointI& , const TypeCharacter);

    void modifyCharacter(const TypeCharacter);

    // @override method for render to scene.
    void Render(const DQ::PointF& _ptOffset = DQ::PointF());

    // @override method for processing object.
    void Process();

    void moveVectorCharacter(const DQ::PointI& );

    // @return Position (System of calculation grid).
    DQ::PointI position() const;
private:
    void    _init(const TypeCharacter );

    // Position in system of calculation grid.
    DQ::PointI              m_ptPosition;

    // Contains of body character.
    // Default size equal 2.
    std::vector<GameBlock*> m_vBlocks;
};

#endif //CHARACTERS_H