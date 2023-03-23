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
	sprite.setTexture(AssetManager::RequestTexture("PlayerStand.png"));
    collisionOffset = sf::Vector2f(0, 30.0f);
    collisionScale = sf::Vector2f(0.5f, 0.5f);
    collisionType = CollisionType::CIRCLE;
}

void Player::Update(sf::Time frameTime)
{
    const float DRAG = 8.0f;
    const PhysicsType physics = PhysicsType::FORWARD_EULER;

    switch (physics)
    {
    case PhysicsType::FORWARD_EULER:
    {
        // EXPLICIT EULER (FORWARD EULER)

        SetPosition(GetPosition() + velocity * frameTime.asSeconds());
        velocity += acceleration * frameTime.asSeconds();

        // Drag Calculation
        velocity -= velocity * DRAG * frameTime.asSeconds();

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
        velocity -= velocity * DRAG;

        SetPosition(GetPosition() + velocity * frameTime.asSeconds());

        break;
    }

    case PhysicsType::SYMPLECTIC_EULER:
    {
        // SEMI-IMPLICIT EULER (SYMPLECTIC EULER)

        velocity += acceleration * frameTime.asSeconds();

        // Drag Calculation
        velocity -= velocity * DRAG;

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

        sf::Vector2f lastFramePos = GetPosition();

        // Current frame's position
        SetPosition(2.0f * GetPosition() - oldPosition + acceleration * frameTime.asSeconds() * frameTime.asSeconds());

        // Two frames ago (on next frame)
        oldPosition = lastFramePos;

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
        velocity -= velocity * DRAG;

        break;
    }

    default:
        break;
    }
}

void Player::UpdateAcceleration()
{
    const float ACCEL = 3000.0f;

    // Update acceleration
    acceleration.x = 0;
    acceleration.y = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        acceleration.x = -ACCEL;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        acceleration.x = ACCEL;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        acceleration.y = -ACCEL;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        acceleration.y = ACCEL;
    }
}