#include "Player.h"
#include "TextureHolder.h"
Player::Player() 
{
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;

	//Associate a texture with the sprite
	//m_Texture.loadFromFile("graphics/player.png");
	////m_Texture.loadFromFile("graphics/space-invaders.png");
	//m_Sprite.setTexture(m_Texture);
	m_Sprite = Sprite(TextureHolder::GetTexture("graphics/player.png"));

	//Set the origin of the sprite to the centre, for smooth rotation
	//เดิมรูปของ player มีขนาด 50X50
	m_Sprite.setOrigin(25,25);
	
}
void Player::spawn(IntRect arena, Vector2f resolution, int tileSize)
{
	//Place the player in the middle of the arena
	m_Position.x = arena.width / 2;
	m_Position.y = arena.height / 2;

	//Copy the detail of the arena to the player's m_Arena
	// - coppy all the coordinate and dimensions of the past arena to the member object in the same type
	m_Arena.left = arena.left;
	m_Arena.width = arena.width;
	m_Arena.top = arena.top;
	m_Arena.height = arena.height;

	//Remember how big the tiles are in arena
	m_TileSize = tileSize;

	//Store resolution for future use
	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;
}

//when player dies we will use it to reset any upgrade, they might have use
//ยังเขียนฟังก์ชั่นนี้ไม่เสร็จ จนกว่าจะใกล้เขียนจบ
void Player::resetPlayerStats()
{
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;
}

Time Player::getLastHitTime()
{
	return m_LastHit;
}

bool Player::hit(Time timeHit)
{
	if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 200) 
	{
		m_LastHit = timeHit;
		m_Health -= 10;
		return true;
	}
	else
	{
		return false;
	}
}

FloatRect Player::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f Player::getCenter()
{
	return m_Position;
}

float Player::getRotation()
{
	return m_Sprite.getRotation();
}

Sprite Player::getSprite()
{
	return m_Sprite;
}

int Player::getHealth()
{
	return m_Health;
}

void Player::moveLeft()
{
	m_LeftPressed = true;
}
void Player::moveRight()
{
	m_RightPressed = true;
}
void Player::moveUp()
{
	m_UpPressed = true;
}
void Player::moveDown()
{
	m_DownPressed = true;
}

void Player::stopLeft()
{
	m_LeftPressed = false;
}
void Player::stopRight()
{
	m_RightPressed = false;
}
void Player::stopUp()
{
	m_UpPressed = false;
}
void Player::stopDown()
{
	m_DownPressed = false;
}

//update function Will be call once on every single frame of our game loop
void Player::update(float elapsedTime, Vector2i mousePosition)
{
	if (m_UpPressed)
	{
		m_Position.y -= m_Speed * elapsedTime;
	}
	if (m_DownPressed)
	{
		m_Position.y += m_Speed * elapsedTime;
	}
	if (m_RightPressed) 
	{
		m_Position.x += m_Speed * elapsedTime;
	}
	if (m_LeftPressed)
	{
		m_Position.x -= m_Speed * elapsedTime;
	}
	m_Sprite.setPosition(m_Position);

	//Keep the player in the arena
	//Check whether m_Position.x or m_Position.y are beyond any of edges of current arena
	if (m_Position.x > m_Arena.width - m_TileSize)
	{
		m_Position.x = m_Arena.width - m_TileSize;
	}
	if (m_Position.x  < m_Arena.left + m_TileSize) 
	{
		m_Position.x = m_Arena.left + m_TileSize;
	}
	if (m_Position.y > m_Arena.height - m_TileSize)
	{
		m_Position.y = m_Arena.height - m_TileSize;
	}
	if (m_Position.y < m_Arena.top + m_TileSize)
	{
		m_Position.y = m_Arena.top + m_TileSize;
	}

	//Calculate the angle that player is facing
	//set the angle that playersprite is rotated to
	float angle = (atan2(mousePosition.y - m_Resolution.y / 2,
		mousePosition.x - m_Resolution.x / 2)
		* 180) / 3.141;

	m_Sprite.setRotation(angle);

}

void Player::upgradeSpeed()
{
	//20% speed upgrade
	m_Speed += (START_SPEED * .2);
}
void Player::upgradeHealth()
{
	// 20% max health upgrade
	m_MaxHealth += (START_HEALTH * .2);
}
void Player::increaseHealthLevel(int amount) // amount will be provided by a class call pickup (that we will write in section 9)
{
	m_Health += amount;
	//But not beyond the maximum
	if (m_Health > m_MaxHealth) 
	{
		m_Health = m_MaxHealth;
	}
}

//definition