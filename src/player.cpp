#include "player.hpp"
#include "bn_display.h"

PlayerObj::PlayerObj() : sheepSprite(bn::sprite_items::player.create_sprite(0, 0)),
                         parachuteSprite(bn::sprite_items::parachute.create_sprite(0, 0))

{
    SetupSizeDimensions();
    SetupMinMaxFlyHeight();

    position.x = ReturnMinMaxFlyHeight().max;
}

void PlayerObj::SetupMinMaxFlyHeight()
{
    minMaxFlyHeight.min = -halfScreenWidth + ReturnSize().halfWidth;
    minMaxFlyHeight.max = halfScreenWidth - ReturnSize().halfWidth - topScreenOffset;
}

void PlayerObj::SetupSizeDimensions()
{
    size.width = sheepSprite.shape_size().width();
    size.height = sheepSprite.shape_size().height();
    size.halfWidth = size.width.division(2);
    size.halfHeight = size.height.division(2);
}

PlayerObj::~PlayerObj()
{
}

void PlayerObj::Update()
{
    if (bn::keypad::select_held())
    {
        parachuteActive = true;
        position.x += maxParachuteSpeed;
        parachuteSprite.set_visible(true);
        currentFallSpeed = 0;
    }
    else
    {
        currentFallSpeed += fallAccelaration;
        if (currentFallSpeed >= maxFallSpeed)
            currentFallSpeed = maxFallSpeed;
        position.x += -currentFallSpeed;

        parachuteActive = false;
        parachuteSprite.set_visible(false);
    }

    if (position.x <= -halfScreenWidth + size.halfWidth)
        position.x = -halfScreenWidth + size.halfWidth;
    else if (position.x >= minMaxFlyHeight.max)
        position.x = minMaxFlyHeight.max;

    if (bn::keypad::up_held())
        position.y -= maxDriftSpeed;
    else if (bn::keypad::down_held())
        position.y += maxDriftSpeed;

    if (position.y <= -halfScreenHeight - size.halfHeight)
        position.y += bn::display::height() + size.halfHeight;
    else if (position.y >= halfScreenHeight + size.halfHeight)
        position.y -= bn::display::height() + size.halfHeight;

    sheepSprite.set_position(position.x, position.y);
    parachuteSprite.set_position(position.x + size.width, position.y);
}

bool PlayerObj::IsColliding(BirdObj &b)
{
    if (
        ReturnPosition().x < b.ReturnCollider().x + b.ReturnCollider().width &&
        ReturnPosition().x + ReturnSize().width > b.ReturnCollider().x &&
        ReturnPosition().y < b.ReturnCollider().y + b.ReturnCollider().height &&
        ReturnPosition().y + ReturnSize().height > b.ReturnCollider().y)
    {
        isPlayerAlive = false;
        return true;
    }

    return false;
}

bool PlayerObj::ReturnParachuteActive()
{
    return parachuteActive;
}

PlayerObj::Position PlayerObj::ReturnPosition()
{
    return position;
}

PlayerObj::Size PlayerObj::ReturnSize()
{
    return size;
}

PlayerObj::MinMaxFlyHeight PlayerObj::ReturnMinMaxFlyHeight()
{
    return minMaxFlyHeight;
}

bool PlayerObj::ReturnIsPlayerAlive()
{
    return isPlayerAlive;
}
