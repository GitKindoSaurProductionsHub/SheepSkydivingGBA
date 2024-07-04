#ifndef SCORE_HPP
#define SCORE_HPP

#include "bn_string.h"
#include "bn_vector.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "misc.hpp"

#include "common_variable_8x16_sprite_font.h"

class ScoreObj
{
private:
    bn::fixed currentScore = 0;
    const bn::fixed MAX_SCORE = 99999; 

    bn::sprite_text_generator textGenerator;
    bn::vector<bn::sprite_ptr, 32> textSprites;

public:
    ScoreObj();
    ~ScoreObj();

    void UpdateScore(bn::fixed add);
    void UpdateVisuals();
};

#endif // SCORE_HPP