
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

    void moveVectorCharacter(const DQ::PointF& );

    // @return Position (System of calculation grid).
    DQ::PointF position() const;
private:

    // Position in system of calculation grid.
    DQ::PointF              m_ptPosition;

    // Contains of body character.
    std::vector<GameBlock*> m_vBlocks;
};

#endif //CHARACTERS_H