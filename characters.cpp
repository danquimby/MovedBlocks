#include "characters.h"

BodyComplex::BodyComplex(const ContainsComplexObject& _template) {
    reBuildBody(_template);
}

void BodyComplex::reBuildBody(const ContainsComplexObject& _template) {
    m_vBodyItmes.clear();
    DQ::strings content = DQ::parserFromString(_template.m_sContainsData, _template.m_sSeparator);
    for (int h = 0, i = 0; h < (int) _template.m_szSizeObject.height(); ++h)
    {
        widthBodyItems widthBody;
        for (int w = 0; w < (int) _template.m_szSizeObject.width(); ++w, ++i)
        {
            widthBody.push_back(atoi(content[i].c_str()));
        }
        m_vBodyItmes.push_back(widthBody);
    }
}

bodyComplexItems 
BodyComplex::getBodyItems() const {
    return m_vBodyItmes;
}

widthBodyItems 
BodyComplex::getWidthBodyItems(int _height) {
    if (_height > (int)m_vBodyItmes.size()) return widthBodyItems();

    return m_vBodyItmes.at(_height);
}

////////////////////////////////////////////////////////////////////////////////////////
GameCharacter::GameCharacter(const DQ::PointI& _ptPosition, BodyComplex& _body) {
    m_ptPosition = _ptPosition;
    modifyCharacter(_body);
}

void GameCharacter::modifyCharacter(BodyComplex& body) {
    clean();
    DQ::PointI posVector;
    for (int h = 0; h < (int)body.getBodyItems().size() ; ++h)
    {
        posVector.setX(0);
        for (int w = 0; w < (int)body.getWidthBodyItems(h).size(); ++w)
        {
            m_vBlocks.push_back(createBlock(GAME_BLOCK_GROUND,m_ptPosition + posVector));
            posVector.setX(posVector.X() + 1);
        }
        posVector.setY(posVector.Y() + 1);
    }
    
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

void GameCharacter::clean() {
    for (int i = 0; i < (int)m_vBlocks.size(); ++i)
    {
        delete m_vBlocks[i];
    }
    m_vBlocks.clear();
}
