#include "Player.h"
#include "AssetManager.h"

enum class PhysicsType
{
    FORWARD_EULER,
    BACKWARD_EULER,
    SYMPLECTIC_EULER,
    POSITION_VERLET,
    VELOCITY_VERLET
};

Player::Player()
	: SpriteObject()
    , oldPosition(100.0f, 300.0f)
	, velocity()
	, acceleration(100.0f, 100.0f)
{
	sprite.setTexture(AssetManager::RequestTexture("PlayerStand"));
    collisionOffset = sf::Vector2f(0, 30.0f);
    collisionScale = sf::Vector2f(0.5f, 0.5f);
    collisionType = CollisionType::CIRCLE;
}

void Player::Update(sf::Time frameTime)
{
    const float DRAG = 10.0f;
    const PhysicsType physics = PhysicsType::FORWARD_EULER;
    sf::Vector2f lastFramePos = GetPosition();

    switch (physics)
    {
    case PhysicsType::FORWARD_EULER:
    {
        // EXPLICIT EULER (FORWARD EULER)

        SetPosition(GetPosition() + velocity * frameTime.asSeconds());
        velocity += acceleration * frameTime.asSeconds();

        // Drag Calculation
        velocity.x -= velocity.x * DRAG * frameTime.asSeconds();

        // Update Acceleration
        UpdateAcceleration();

        break;
    }

    case PhysicsType::BACKWARD_EULER:
    {
        // IMPLICIT EULER (BACKWARD EULER)
        
        // Update Acceleration
        UpdateAcceleration();

        velocity += acceleration * frameTime.asSeconds();

        // Drag Calculation
        velocity.x -= velocity.x * DRAG;

        SetPosition(GetPosition() + velocity * frameTime.asSeconds());

        break;
    }

    case PhysicsType::SYMPLECTIC_EULER:
    {
        // SEMI-IMPLICIT EULER (SYMPLECTIC EULER)

        velocity += acceleration * frameTime.asSeconds();

        // Drag Calculation
        velocity.x -= velocity.x * DRAG;

        SetPosition(GetPosition() + velocity * frameTime.asSeconds());

        // Update Acceleration
        UpdateAcceleration();

        break;
    }

    case PhysicsType::POSITION_VERLET:
    {
        // POSITION VERLET - NO DRAG
        
        // Update Acceleration
        UpdateAcceleration();

        // Current frame's position
        SetPosition(2.0f * GetPosition() - oldPosition + acceleration * frameTime.asSeconds() * frameTime.asSeconds());

        break;
    }

    case PhysicsType::VELOCITY_VERLET:
    {
        // VELOCITY VERLET

        // Get half frame velocity using previous frame's acceleration
        sf::Vector2f halfFrameVel = velocity + acceleration * frameTime.asSeconds() / 2.0f;

        // Get new frame's position using half frame velocity
        SetPosition(GetPosition() + halfFrameVel * frameTime.asSeconds());

        // Update Acceleration
        UpdateAcceleration();

        // Get new frame's velocity using half frame velocity and updated acceleration
        velocity = halfFrameVel + acceleration * frameTime.asSeconds() / 2.0f;

        // Drag Calculation
        velocity.x -= velocity.x * DRAG;

        break;
    }

    default:
        break;
    }

    // Two frames ago (on next frame)
    oldPosition = lastFramePos;
}


void Player::HandleCollision(SpriteObject& other)
{
    const float JUMPSPEED = 800;
    sf::Vector2f depth = GetCollisionDepth(other);
    sf::Vector2f newPos = GetPosition();

    if (abs(depth.x) < abs(depth.y))
    {
        // Move in x direction
        newPos.x += depth.x;
        velocity.x = 0;
        acceleration.x = 0;
    }
    else
    {
        // Move in y direction
        newPos.y += depth.y;
        velocity.y = 0;
        acceleration.y = 0;

        // If we collided from above
        if (depth.y < 0)
        {
            velocity.y = -JUMPSPEED;
        }
    }

    SetPosition(newPos);
}

void Player::UpdateAcceleration()
{
    const float ACCEL = 3000;
    const float GRAVITY = 1000;

    // Update acceleration
    acceleration.x = 0;
    acceleration.y = GRAVITY;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        acceleration.x = -ACCEL;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        acceleration.x = ACCEL;
    }
}