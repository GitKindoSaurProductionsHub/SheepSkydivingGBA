#include "bn_core.h"
#include "bn_display.h"
#include "bn_sprite_ptr.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_string.h"
#include "bn_random.h"
#include "bn_vector.h"

#include "score.hpp"
#include "background.hpp"
#include "player.hpp"
#include "bird.hpp"

#include "common_variable_8x16_sprite_font.h"

bn::random randomizer;
const int AMOUNT_OF_BIRDS = 5;

void MenuScene();
void GameScene();

void SetupBirds(BirdObj birds[]);
void HandleBirdRespawn(BirdObj &bird);
bool IsColliding(PlayerObj &p, BirdObj &b);
void WriteText(bn::sprite_text_generator &generator, bn::vector<bn::vector<bn::sprite_ptr, 32>, 32> &storage, int yPos, int xPos, const char text[], int characterOffset);

int main()
{
    bn::core::init();

    while (true)
    {
        MenuScene();
        bn::core::update();

        GameScene();
        bn::core::update();
    }
}

void MenuScene()
{
    BackgroundObj BackgroundObj(0, 48);

    bn::sprite_text_generator textGenerator(common::variable_8x16_sprite_font);
    bn::vector<bn::vector<bn::sprite_ptr, 32>, 32> textStorage;

    WriteText(textGenerator, textStorage, -34, 80, "SHEEP SKYDIVING!", 28);
    WriteText(textGenerator, textStorage, -40, 60, "dont hit the birds!", 30);
    WriteText(textGenerator, textStorage, -42, 0, "Select = Parachute", 31);
    WriteText(textGenerator, textStorage, -38, -20, "Left/Right = Drift", 31);
    WriteText(textGenerator, textStorage, -48, -80, "press START to play", 28);

    BackgroundObj.SetIsParachuteActive(true);
    while (!bn::keypad::start_pressed())
    {
        randomizer.update();
        BackgroundObj.Update();
        bn::core::update();
    }
}

void GameScene()
{
    BackgroundObj background(0, 48);

    PlayerObj player;

    BirdObj birds[AMOUNT_OF_BIRDS];
    SetupBirds(birds);

    ScoreObj score;
    score.UpdateVisuals();

    while (player.ReturnIsPlayerAlive())
    {
        randomizer.update();
        player.Update();

        background.SetIsParachuteActive(player.ReturnParachuteActive());
        background.Update();

        for (int birdID = 0; birdID < AMOUNT_OF_BIRDS; birdID++)
        {
            birds[birdID].Update();
            HandleBirdRespawn(birds[birdID]);
            player.IsColliding(birds[birdID]);
        }

        score.UpdateScore(background.ReturnCurrentScrollSpeed());
        score.UpdateVisuals();

        bn::core::update();
    }
}

void SetupBirds(BirdObj birds[])
{
    for (int birdID = 0; birdID < AMOUNT_OF_BIRDS; birdID++)
    {
        HandleBirdRespawn(birds[birdID]);
    }
}

void HandleBirdRespawn(BirdObj &bird)
{
    if (bird.ReturnPosition().y + bird.ReturnSize().halfHeight > -halfScreenHeight && bird.ReturnPosition().y - bird.ReturnSize().halfHeight < halfScreenHeight)
        return;

    bird.Respawn(
        randomizer.get_unbiased_int(0, 100),
        randomizer.get_fixed(bird.ReturnMinMaxFlyHeight().min, bird.ReturnMinMaxFlyHeight().max),
        randomizer.get_unbiased_fixed(bird.ReturnMinMaxFlySpeed().min, bird.ReturnMinMaxFlySpeed().max));
}

void WriteText(bn::sprite_text_generator &generator, bn::vector<bn::vector<bn::sprite_ptr, 32>, 32> &storage, int yPos, int xPos, const char text[], int characterOffset)
{
    int id = 0;
    bn::vector<bn::sprite_ptr, 32> textSprites;
    generator.generate(0, 0, text, textSprites);

    for (bn::sprite_ptr &characterSprite : textSprites)
    {
        characterSprite.set_rotation_angle(displayAngle);
        characterSprite.set_position(xPos, yPos + (id * characterOffset));
        id += 1;
    }

    storage.push_back(textSprites);
}