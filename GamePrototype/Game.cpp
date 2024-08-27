#include "pch.h"
#include "Game.h"
#include "utils.h"
#include <ctime>
#include "Ballon.h"
#include "Square.h"
#include "Entity.h"
#include <iostream>
#include "time.h"
#include "Texture.h"
#include "AngrySquare.h"
using namespace utils;
using namespace std;

Game::Game(const Window& window)
	:BaseGame{ window }, TerritoryWidth(150), EnemyTerritory(50)
{
	LevelNum = 0;
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

bool Game::goNextBallon() {

	int firstAvail = -1;
	for (int i = 0; i < numBalls; ++i)
	{
		if (!dynamic_cast<Ballon*>(Entitys[i])->HasExited() && dynamic_cast<Ballon*>(Entitys[i])->GetState() != Entity::State::Dead)
		{
			firstAvail = i;
			break;
		}
	}
	//no ballss lef
	if (firstAvail == -1) {
		return false;
	}
	else { //have one ball, set as current and make it move

		//m_CurrentBallon->SetState(Entity::State::Calm);
		m_CurrentBallon = dynamic_cast<Ballon*>(Entitys[firstAvail]);
		m_CurrentBallon->SetState(Entity::State::Moving);
		m_CurrentBallon->setVelocity(Vector2f(rand() / RAND_MAX * (MaxVelocity - MinVelocity) + MinVelocity, 0));
		return true;
	}
}
void Game::Initialize()
{
	InitBalls();

	InitEnemy();

	if (!goNextBallon()) {
		std::cout << "no balls left" << std::endl;
	}

	for (int i = numBalls; i < Entitys.size(); i++) {
		Entitys[i]->SetState(Entity::State::Moving);
	}

	m_LeftBalls = new Texture(std::to_string(numBalls), "go3v2.ttf", 24, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	m_EscapedBalls = new Texture(std::to_string(NumSurvived()), "go3v2.ttf", 24, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
}
void Game::InitBalls()
{

	blockKeys = false;
	m_AbsoluteTime = 0;
	m_GOTexture = new Texture("You have lost your colony . To replicate we need at least 50 percent of balls alive", "go3v2.ttf", 20, Color4f(1.0f, 0.f, 0.f, 1.0f));
	//m_GOTexture = new Texture("Game Over!!!", "go3v2.ttf", 24, Color4f(0.1f, 0.f, 0.5f, 1.0f));
	m_CurrentBallon = nullptr;

	radMax = TerritoryWidth / 5;
	radMin = TerritoryWidth / 6;

	enCount = 6;

	int BallsCount = 0;



	bool isBallsGenerated = false;

	numBalls = round((float)rand() / RAND_MAX * (maxBalls - minBalls) + minBalls);


	std::cout << (float)rand() / RAND_MAX << std::endl;
	std::cout << numBalls << std::endl;

	Ballon* n;

	Entitys.reserve(numBalls + enCount);

	


	while (!isBallsGenerated) {
		bool isOverlap = false;
		//[H - EnemyTerritory - R, EnemyTerritory+r]
		float NewBallR = ((float)rand() / RAND_MAX) * (radMax - radMin) + radMin;
		float maxY = GetViewPort().height - EnemyTerritory - NewBallR;
		float minY = EnemyTerritory + NewBallR;
		float NewBallY = ((float)rand() / RAND_MAX) * (maxY - minY) + minY;
		float NewBallAlpha = ((float)rand() / RAND_MAX) * (1 - 0.3) + 0.3;
		float Red = 0;
		float Green = rand() / RAND_MAX * (0.9 - 0.3) + 0.3;//rand() / RAND_MAX * (0.5 - 0.3) + 0.3;
		float Blue = 0;
		n = new Ballon(this, Point2f{ TerritoryWidth / 2,NewBallY }, NewBallR, Color4f{ Red,Green,Blue,NewBallAlpha });
		for (auto& e : Entitys) {
			float r = dynamic_cast<Ballon*>(e)->getR();
			float y = e->GetPosition().y;

			float R = n->getR();
			float Y = n->GetPosition().y;

			if (!((y + r <= Y - R) || (y - r >= Y + R))) {
				isOverlap = true;
				break;
			}
		}
		if (isOverlap) continue;
		Entitys.push_back(n);
		BallsCount++;
		if (BallsCount == numBalls) {
			isBallsGenerated = true;
		}
	}
}
void Game::InitEnemy()
{

	float enTerritory = GetViewPort().width - 2 * TerritoryWidth;
	float enLoc = enTerritory / enCount;
	switch (LevelNum) {
	case (0):
	{
		for (int i = 0; i < enCount - 1; i++)
		{
			float enX = (i + 1) * enLoc + TerritoryWidth;
			//srand((unsigned)time(NULL));
			float Red = rand() / RAND_MAX * (0.9 - 0.5) + 0.5;
			//srand((unsigned)time(NULL));
			float Green = 0;//rand() / RAND_MAX * (0.5 - 0.3) + 0.3;
			//srand((unsigned)time(NULL));
			float Blue = 0; //rand() / RAND_MAX * (0.7 - 0.3) + 0.3;
			float Alpha = rand() / RAND_MAX * (0.9 - 0.8) + 0.8;
			Square* S1 = new Square(this, Point2f(enX, GetViewPort().height), 50, Color4f(Red, Green, Blue, Alpha), float(i));
			Entitys.push_back(S1);
		}
		break;
	}
	//m_CurrentBallon->setVelocity(Vector2f(rand() / RAND_MAX * (MaxVelocity - MinVelocity) + MinVelocity, 0));
	case (1):
	{
		for (int i = 0; i < enCount - 1; i++)
		{
			float enX = (i + 1) * enLoc + TerritoryWidth;
			//srand((unsigned)time(NULL));
			float Red = rand() / RAND_MAX * (0.9 - 0.5) + 0.5;
			//srand((unsigned)time(NULL));
			float Green = 0;//rand() / RAND_MAX * (0.5 - 0.3) + 0.3;
			//srand((unsigned)time(NULL));
			float Blue = 0; //rand() / RAND_MAX * (0.7 - 0.3) + 0.3;
			float Alpha = rand() / RAND_MAX * (0.9 - 0.8) + 0.8;
			AngrySquare* S1 = new AngrySquare(this, Point2f(enX, GetViewPort().height), 50, Color4f(Red, Green, Blue, Alpha), float(i));
			Entitys.push_back(S1);
		}
		break;
	}
	}
}

void Game::Cleanup()
{
	for (auto& Entity : Entitys)
	{
		delete Entity;
		Entity = nullptr;
	}
	Entitys.clear();
	delete m_GOTexture;// = new Texture("You have lost your colony . To replicate we need at 50% of balls alive !!!", "C:\Gameplay Scripting\gs - game - prototype - AlenMarat\inflating - colony\Resources\go3v2.ttf", 32, Color4f(0.1f, 0.f, 0.5f, 0.1f));
	m_GOTexture = nullptr;// new Texture("You have lost your colony . To replicate we need at 50% of balls alive !!!", "C:\Gameplay Scripting\gs - game - prototype - AlenMarat\inflating - colony\Resources\go3v2.ttf", 32, Color4f(0.1f, 0.f, 0.5f, 0.1f));

	delete m_EscapedBalls;
	m_EscapedBalls = nullptr;

	delete m_LeftBalls;
	m_LeftBalls = nullptr;
}

int Game::NumSurvived() {
	int alive = 0;

	for (int i = 0; i < numBalls; i++) {
		if (dynamic_cast<Ballon*>(Entitys[i])->GetState() != Entity::State::Dead)
		{
			alive++;
		}
	}
	return alive;
}

int Game::NumDead() {
	int dead = 0;

	for (int i = 0; i < numBalls; i++) {
		if (dynamic_cast<Ballon*>(Entitys[i])->GetState() == Entity::State::Dead)
		{
			dead++;
		}
	}
	return dead;
}

void Game::Update(float elapsedSec)
{
	m_AbsoluteTime += elapsedSec;
	if (!blockKeys) {
		int NS = NumSurvived();


		if (!(NS > numBalls / 2) && !blockKeys)
		{
			blockKeys = true;
			for (int i = 0; i < getNumpofBalls(); i++) {

				if (dynamic_cast<Ballon*>(Entitys[i])->GetState() != Entity::State::Dead) {
					dynamic_cast<Ballon*>(Entitys[i])->SetState(Entity::State::Calm);
				}


			}

		}

		

		//killings
		for (int i = getNumpofBalls(); i < Entitys.size(); i++) {
			if (m_CurrentBallon->GetState() != Entity::State::Dead) {
				switch (LevelNum)
				{
				case(0):
				{
					if ((dynamic_cast<Square*>(Entitys[i]))->IsHitting(m_CurrentBallon)) {
						m_CurrentBallon->SetState(Entity::State::Dead);
						NS--;
						delete m_EscapedBalls;
						//m_EscapedBalls = nullptr;
						delete m_LeftBalls;
						//m_LeftBalls = nullptr;
						//int ND = NumDead();
						m_LeftBalls = new Texture(std::to_string(numBalls - NS), "go3v2.ttf", 24, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
						m_EscapedBalls = new Texture(std::to_string(NS), "go3v2.ttf", 24, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
						goNextBallon();
					}
					break;
				}
				case(1):
				{
					if ((dynamic_cast<AngrySquare*>(Entitys[i]))->IsHitting(m_CurrentBallon)) {
						m_CurrentBallon->SetState(Entity::State::Dead);
						NS--;
						delete m_EscapedBalls;
						//m_EscapedBalls = nullptr;
						delete m_LeftBalls;
						//m_LeftBalls = nullptr;
						//int ND = NumDead();
						m_LeftBalls = new Texture(std::to_string(numBalls - NS), "go3v2.ttf", 24, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
						m_EscapedBalls = new Texture(std::to_string(NS), "go3v2.ttf", 24, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
						goNextBallon();
					}
					break;
				}
				}
			}

		}
		//update each entity
		for (auto& entity : Entitys)
		{
			entity->Update(elapsedSec);


			/*Ballon* ballon = dynamic_cast<Ballon*>(entity);
			if (ballon && ballon->HasExited())
			{
				std::cout << "Ballon has exited. Set to Calm state." << std::endl;
				ballon->SetState(Entity::State::Calm);
			}*/
		}
	}
}

int Game::getNumpofBalls() {
	return numBalls;
}

void Game::Draw() const
{
	if (!blockKeys) {
		ClearBackground();
		GameField();
		for (auto& entity : Entitys)
		{
			entity->Draw();
		}

		m_LeftBalls->Draw(Point2f{ TerritoryWidth / 2, GetViewPort().height - EnemyTerritory / 2 });
		m_EscapedBalls->Draw(Point2f{ TerritoryWidth / 2,  EnemyTerritory / 2 });
	}

	else {
		m_GOTexture->Draw(Point2f{ GetViewPort().width / 2 - 460, GetViewPort().height / 2 });
		//m_GOTexture->Draw(Point2f{ 0, 0 });
	}
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	if (m_CurrentBallon != nullptr)
	{
		if (!blockKeys) {
			switch (e.keysym.sym)
			{
			case SDLK_UP:

				m_CurrentBallon->setVelocity(Vector2f{ m_CurrentBallon->getVelocity().x, 250 });
				break;
			case SDLK_DOWN:

				m_CurrentBallon->setVelocity(Vector2f(m_CurrentBallon->getVelocity().x, -250));
				break;
			}
		}
		switch (e.keysym.sym)
		{
		case SDLK_r:
			blockKeys = true;
			for (int i = 0; i < numBalls; i++) {
				dynamic_cast<Ballon*>(Entitys[i])->setBlock(blockKeys);
			}
			switch (LevelNum)
			{
			case(0):
			{

				for (int i = numBalls; i < Entitys.size(); i++) {
					dynamic_cast<Square*>(Entitys[i])->setBlock(blockKeys);
				}
				break;
			}
			case(1):
			{
				for (int i = numBalls; i < Entitys.size(); i++) {
					dynamic_cast<AngrySquare*>(Entitys[i])->setBlock(blockKeys);
				}
				break;
			}
			}
			Cleanup();
			Initialize();
			blockKeys = false;

			break;
		}

	}
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}

}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}
float Game::getTerrWidth() {
	return TerritoryWidth;
}


void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Game::GameField() const
{

	SetColor(Color4f{ 0.8f, 0.8f, 0.8f, 1.0f });


	DrawLine(TerritoryWidth, 0, TerritoryWidth, GetViewPort().height, 2.0f);
	DrawLine(TerritoryWidth, EnemyTerritory, GetViewPort().width - TerritoryWidth, EnemyTerritory, 2.0f);
	DrawLine(TerritoryWidth, GetViewPort().height - EnemyTerritory, GetViewPort().width - TerritoryWidth, GetViewPort().height - EnemyTerritory, 2.0f);

	DrawLine(GetViewPort().width - TerritoryWidth, 0, GetViewPort().width - TerritoryWidth, GetViewPort().height, 2.0f);

}

float Game::getEnemyTerritoryWidth() {
	return EnemyTerritory;
}

float Game::getAbsoluteTime()
{
	return m_AbsoluteTime;
}