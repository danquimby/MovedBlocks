#include "characters.h"

GameCharacter::GameCharacter(const DQ::PointI& _ptPosition, const TypeCharacter _type) {
    m_ptPosition = _ptPosition;
    _init(_type);
}

void GameCharacter::modifyCharacter(const TypeCharacter) {

}

void GameCharacter::Render(const DQ::PointF& _ptOffset) {
    for (int i = 0; i < (int)m_vBlocks.size(); ++i)
    {
        m_vBlocks[i]->Render(_ptOffset);
    }
}

void GameCharacter::Process() {

}

void GameCharacter::moveVectorCharacter(const DQ::PointI& _vec) {
    for (int i = 0; i < (int)m_vBlocks.size(); ++i)
    {
        m_vBlocks[i]->moveObject(_vec);
    }
}

DQ::PointI GameCharacter::position() const {
    return m_ptPosition;
}

void GameCharacter::_init(const TypeCharacter _type) {
    DQ::PointI pos = m_ptPosition;
    m_vBlocks.resize(2);
    m_vBlocks[0] = createBlock(GAME_BLOCK_GROUND,pos);
    pos.setY(pos.Y() + 1);
    m_vBlocks[1] = createBlock(GAME_BLOCK_GROUND,pos);

    switch(_type) {
    case TYPE_CHARACTER_ENEMY:
        break;
    case TYPE_CHARACTER_MAN:
        break;
    }
}