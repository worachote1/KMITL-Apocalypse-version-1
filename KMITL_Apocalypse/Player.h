#pragma once
#include<sfml/Graphics.hpp>
using namespace sf;
class Player
{
private:
	const float START_SPEED = 200;
	const float START_HEALTH = 100;
	//where is the player
	Vector2f m_Position;
	 
	//Of course we will need a sprite
	Sprite m_Sprite;

	//And a texture
	Texture m_Texture;

	//what is the screen resolution
	Vector2f m_Resolution;

	//what size is the current arena
	IntRect m_Arena;

	//How big is each tile of the arena
	int m_TileSize;

	//Which directions is the player currently moving
	bool m_UpPressed;
	bool m_DownPressed;
	bool m_LeftPressed;
	bool m_RightPressed;

	//How much health has the player got?
	int m_Health;

	//What is the maximum health the player can have
	int m_MaxHealth;
	
	//When was the player last hit
	Time m_LastHit;

	//Speed in pixel per second
	float m_Speed;

	//All public function will come next
public:
	//constructor
	Player();
	
	//prepare the object ready or use ,including putting it in start location
	//IntRect will be the size and location at the current level
	//Vector2f will contain screen resolution
	//int will hold the size of backgroud
	void spawn(IntRect arena, Vector2f resolution, int titleSize);

	//Call this at the end of every game
	void resetPlayerStats();

	//Handle the player getting hit by a zombie
	bool hit(Time timeHit);

	// How long ago was the player last hit
	Time getLastHitTime();

	//Where is the player
	//return floatRect that describes the horizontal and vertical floating point coordinate of the rectangle which contain the player graphics
	FloatRect getPosition();
	
	//Where is the center of the player
	//contain just X and Y loacation of the player graphics
	Vector2f getCenter();
	
	//Which angle is the player facing
	float getRotation();

	//Send a coppy of sprite to main
	Sprite getSprite();

	// How much health has the player currently got?
	int getHealth();

	//The next four functions move the player
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	//Stop the player moving in specific direction
	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();

	//we will call this function once every frame
	//it will do everything to make sure the player object data is update ready for collision and draw
	void update(float elapsedTime,Vector2i mousePosition);

	//Give player a speed boost
	void upgradeSpeed();

	//Give the player some health
	void upgradeHealth();

	// Increase the maximum amount of health the player can have
	void increaseHealthLevel(int amount);
	
};
