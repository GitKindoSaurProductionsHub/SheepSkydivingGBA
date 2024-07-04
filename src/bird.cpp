#include "bird.hpp"

BirdObj::BirdObj() : sprite(bn::sprite_items::bird.create_sprite(0, 0)), spriteAnimation(bn::create_sprite_animate_action_forever(sprite, 16, bn::sprite_items::bird.tiles_item(), 0, 1))
{
    SetupSizeDimensions();
    SetupMinMaxFlyHeight();

    collider.x = position.x + 3;
    collider.y = position.y + 3;
    position.y = -halfScreenHeight - size.halfHeight;
}

BirdObj::~BirdObj()
{
}

void BirdObj::SetupMinMaxFlyHeight()
{
    minMaxFlyHeight.min = -halfScreenWidth + ReturnSize().halfWidth;
    minMaxFlyHeight.max = halfScreenWidth - ReturnSize().halfWidth - topScreenOffset;
}

void BirdObj::SetupSizeDimensions()
{
    size.width = sprite.shape_size().width();
    size.height = sprite.shape_size().height();
    size.halfWidth = size.width.division(2);
    size.halfHeight = size.height.division(2);
}

void BirdObj::Update()
{
    position.y += comeFromLeft ? flySpeed : -flySpeed;
    sprite.set_position(position.x, position.y);

    collider.x = position.x + 3;
    collider.y = position.y + 3;

    spriteAnimation.update();
}

void BirdObj::Respawn(int randomDirection, bn::fixed randomPosition, bn::fixed randomFlySpeed)
{
    comeFromLeft = randomDirection < 50 ? true : false;
    
    sprite.set_vertical_flip(!comeFromLeft);
    
    position.x = randomPosition;
    position.y = comeFromLeft ? -halfScreenHeight : halfScreenHeight;

    flySpeed = randomFlySpeed;
}

BirdObj::Position BirdObj::ReturnPosition()
{
    return position;
}

BirdObj::Size BirdObj::ReturnSize()
{
    return size;
}

BirdObj::Collider BirdObj::ReturnCollider()
{
    return collider;
}

BirdObj::MinMaxFlySpeed BirdObj::ReturnMinMaxFlySpeed()
{
    return minMaxFlySpeed;
}

BirdObj::MinMaxFlyHeight BirdObj::ReturnMinMaxFlyHeight()
{
    return minMaxFlyHeight;
}