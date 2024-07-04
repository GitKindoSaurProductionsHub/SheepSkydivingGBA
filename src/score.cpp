#include "score.hpp"

ScoreObj::ScoreObj() : textGenerator(common::variable_8x16_sprite_font)
{
}

ScoreObj::~ScoreObj()
{
}

void ScoreObj::UpdateScore(bn::fixed add)
{
    if (currentScore + add >= MAX_SCORE)
        return;

    currentScore += add;
}

void ScoreObj::UpdateVisuals()
{
    bn::string<6> valueString = bn::to_string<6>(currentScore.floor_integer());

    textSprites.clear();

    textGenerator.generate(0, 0, valueString, textSprites);

    int id = 0;
    for (bn::sprite_ptr &characterSprite : textSprites)
    {
        characterSprite.set_rotation_angle(displayAngle);
        characterSprite.set_position(90 + (characterSprite.shape_size().width() * id), 0);
        id += 1;
    }
}
