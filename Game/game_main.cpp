#include <time.h>
#include <iostream>
#include <queue>
#include <SFML/Graphics.hpp>

// Nicholas A Moore
// Intro to Game Programming
// Assignment One

enum class gameState { menu, optionMenu, playing, end };
enum class optionState { none, name, difficulty };
enum class difficulty { easy, normal, hard, epic };
enum class powerups { oversizedSlide, oversizedBall, extraLife };

gameState state;
optionState oState;

int N = 70, M = 40;
int size = 16;
int w = size * N;
int h = size * M;
int middle = w / 2;

int dir = 0;

int roll = 0;

class Player {
public:
	Player(std::string name = "Player One") { name_ = name; score_ = 0; displayScore_ = "0"; slider_.setSize(origSize_);
	slider_.setFillColor(sf::Color(200, 200, 200)); slider_.setPosition(middle - getSlider().getSize().x / 2, h - getSlider().getSize().y - 5);
	};

	void reset() {
		slider_.setPosition(middle - getSlider().getSize().x / 2, h - getSlider().getSize().y - 5); // -5 for space
		slider_.setSize(origSize_);
		lives_ = 3;
		score_ = 0;
		displayScore_ = "0";
	}

	void revertSize() {
		slider_.setSize(origSize_);
	}

	// mutator
	sf::RectangleShape& getSlider() { return slider_; }; // Used to edit position


	// accessors
	std::string getName() const { return name_; };
	std::string getDisplayScore() const { return displayScore_; };
	int getScore() const { return score_; };
	int getLives() const { return lives_; };

	// mutators
	std::string& setName() { return name_; };
	int& changeScore() { return score_; };
	void setDisplayScore(int score) { displayScore_ = std::to_string(score); };
	void move(int x, int y) { getSlider().move(x, y); std::cout << "moving\n" << "x: " << getSlider().getPosition().x << " y: " << getSlider().getPosition().y << std::endl; };
	int& setLives() { return lives_; };


private:
	std::string name_;
	std::string displayScore_;
	sf::Vector2f origSize_ = { 110, 5 };
	int score_;
	sf::RectangleShape slider_;
	int lives_ = 3;
};

Player user;

class Ball {
public:
	Ball() {
		life_.setRadius(startRadius_); life_.setFillColor(sf::Color(255, 255, 255));
		life_.setPosition(middle - life_.getOrigin().x / 2, h - user.getSlider().getSize().y - life_.getOrigin().y - 15);
	};

	void reset() {
		//life_.setPosition(middle - life_.getOrigin().x / 2, h - user.getSlider().getSize().y - life_.getOrigin().y - 15);
		life_.setPosition(user.getSlider().getPosition().x + user.getSlider().getSize().x / 2, h - user.getSlider().getSize().y - getBall().getOrigin().y - 15);
		life_.setRadius(startRadius_); life_.setFillColor(sf::Color(255, 255, 255));
		setSticky() = true;
	}

	void update() {
		if (mode_ == difficulty::easy) {
			velX_ = -15;
			velY_ = -15;
		}
		if (mode_ == difficulty::normal) {
			velX_ = -30;
			velY_ = -30;
		}
		if (mode_ == difficulty::hard) {
			velX_ = -45;
			velY_ = -45;
		}
		if (mode_ == difficulty::epic) {
			velX_ = -60;
			velY_ = -60;
		}
	};

	// Mutators
	sf::CircleShape& getBall() { return life_; };
	int& setVelX() { return velX_; };
	int& setVelY() { return velY_; };
	difficulty& setDifficulty() { return mode_; };
	bool& setSticky() { return sticky_; };

	// Accessors
	int getVelX() const { return velX_; };
	int getVelY() const { return velY_; };
	difficulty getDifficulty() const { return mode_; };
	bool getSticky() const { return sticky_; };

private:
	sf::CircleShape life_;
	int velX_ = -30;
	int velY_ = -30;
	int startRadius_ = 5;

	bool sticky_ = true;
	difficulty mode_ = difficulty::normal;
};

Ball ball;

class Block {
public:
	Block() {
		block_.setSize(sf::Vector2f(100, 50));
		block_.setFillColor(sf::Color(200, 200, 200));
	}

	void reset(int rows = 3, int columns = 7) {
		blocks_.erase(blocks_.begin(), blocks_.end());
		int offsetX = offsetX_;
		int offsetY = offsetY_;

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) { 
				sf::RectangleShape temp;
				temp.setSize(sf::Vector2f(100, 50));
				temp.setFillColor(sf::Color(200, 200, 200));
				temp.setPosition(i + offsetX + temp.getSize().x, j + offsetY + temp.getSize().y);
				blocks_.push_back(temp);
				offsetX += 125;
		}
			offsetY += 100;
			offsetX = 0;
		}
	};

	// Mutator
	std::vector<sf::RectangleShape>& getBlocks() { return blocks_; };

private:
	sf::RectangleShape block_;
	std::vector<sf::RectangleShape> blocks_;
	int offsetX_ = 0;
	int offsetY_ = 0;
};

Block field;


class GameManager {
public:
	GameManager() {};

	void resetGame(Player& user, Block& field, Ball& ball) {
		user.reset();
		field.reset();
		ball.reset();

		state = gameState::menu;
		oState = optionState::none;
		// Resets all but difficulty
	}

	int roll() { return rand() % 100 + 1; }; // return rand num 1-100

	void rollForPowerup() {
		int roll = this->roll();

		if (roll == 1) {
			powerups_.push(powerups::oversizedSlide);
		}
		else if (roll == 2) {
			powerups_.push(powerups::oversizedBall);
		}
		else if (roll == 3) {
			powerups_.push(powerups::extraLife);
		}

	};

	// Activate Powerups
	void activate(Player& user, Ball& ball) {
		while (!powerups_.empty()) {
			auto powerup = powerups_.front();
			if (powerup == powerups::oversizedSlide) {
				sf::Vector2f newSize;
				newSize.x = 220;
				newSize.y = 5;
				user.getSlider().setSize(newSize);
				std::cout << "Powerup! [Oversized Slide]" << std::endl;
			}
			else if (powerup == powerups::oversizedBall) {
				ball.getBall().setRadius(20);
				std::cout << "Powerup! [Oversized Ball]" << std::endl;
			}
			else if (powerup == powerups::extraLife) {
				if (user.getLives() < 5) {
					user.setLives() += 1;
					std::cout << "Powerup! [Extra Life]" << std::endl;
				}
				else {
					std::cout << "Powerup! [Extra Life] (Lives Full)" << std::endl;
				}
			}
			powerups_.pop();
		}
	};


private:
	std::queue<powerups> powerups_;
};

GameManager hub;

void Tick() {

	if (state == gameState::playing) {

		// slider
		if (dir == 1) {
			user.getSlider().move(50, 0);
			if (ball.getSticky())
				ball.getBall().move(50, 0);
			dir = 0;
		}
		if (dir == 2) {
			user.getSlider().move(-50, 0);
			if (ball.getSticky())
				ball.getBall().move(-50, 0);
			dir = 0;
		}

		if (user.getSlider().getPosition().x <= 0) {
			user.getSlider().setPosition(0, user.getSlider().getPosition().y);
			if (ball.getSticky()) {
				ball.getBall().setPosition(user.getSlider().getPosition().x + user.getSlider().getSize().x / 2, h - user.getSlider().getSize().y - ball.getBall().getOrigin().y - 15);
			}
		}

		if (user.getSlider().getPosition().x + user.getSlider().getSize().x >= w) {
			user.getSlider().setPosition(w - user.getSlider().getSize().x, user.getSlider().getPosition().y);
			if (ball.getSticky()) {
				ball.getBall().setPosition(user.getSlider().getPosition().x + user.getSlider().getSize().x / 2, h - user.getSlider().getSize().y - ball.getBall().getOrigin().y - 15);
			}
		}

		// blocks
		for (int i = 0; i < field.getBlocks().size(); ++i) {
			if (field.getBlocks()[i].getPosition().x <= ball.getBall().getPosition().x
				&& field.getBlocks()[i].getPosition().x + field.getBlocks()[i].getSize().x >= ball.getBall().getPosition().x
				&& field.getBlocks()[i].getPosition().y <= ball.getBall().getPosition().y
				&& field.getBlocks()[i].getPosition().y + field.getBlocks()[i].getSize().y >= ball.getBall().getPosition().y) {

				field.getBlocks().erase(field.getBlocks().begin() + i);
				user.changeScore() += 100;
				user.setDisplayScore(user.getScore());
				
				hub.rollForPowerup();
				hub.activate(user, ball);

				ball.setVelY() *= -1;
			}
		}

		// ball
		if (!ball.getSticky()) {
			ball.getBall().move(ball.getVelX(), ball.getVelY());


			if (ball.getBall().getPosition().x <= 0) {
				ball.setVelX() *= -1;
			}

			if (ball.getBall().getPosition().x >= w) {
				ball.setVelX() *= -1;
			}

			if (ball.getBall().getPosition().y <= 0 + (ball.getBall().getRadius() * 2)) {
				ball.setVelY() *= -1;
			}

			if (ball.getBall().getPosition().x >= user.getSlider().getPosition().x
				&& ball.getBall().getPosition().x <= user.getSlider().getPosition().x + user.getSlider().getSize().x
				&& ball.getBall().getPosition().y >= user.getSlider().getPosition().y) {

				ball.setVelY() *= -1;
			}

			if (ball.getBall().getPosition().y >= h + 100) { // +100 for buffer
				user.setLives() -= 1;
				ball.reset();
				user.revertSize();

				if (user.getLives() <= 0) {
					state = gameState::end;
					ball.getBall().setPosition(middle - ball.getBall().getOrigin().x / 2, h - user.getSlider().getSize().y - ball.getBall().getOrigin().y - 15);
				}

			}
		}
	}

}


int main() {
	srand(time(nullptr));

	state = gameState::menu;
	oState = optionState::none;
	hub.resetGame(user, field, ball);

	// Preparing in-game messages
	//
	// 
	// 
	// Font Credit: https://www.dafont.com/sunday-grapes.font
	// Author: Khurasan
	sf::Font font;

	if (!font.loadFromFile("sunday_grapes/sunday_grapes.ttf"))
		std::cout << "Error Loading Font" << std::endl;

	sf::Text title, options, instructions, end, oPrompt, newName, difficult, releaseBall, score, scoreString, overSizeBall, overSizeSlider, name, life, lifeCount;
	title.setString("Block Grid");
	title.setFont(font);
	title.setCharacterSize(128);
	title.setFillColor(sf::Color::White);
	
	options.setString("Options [Press O]");
	options.setFont(font);
	options.setCharacterSize(48);
	options.setFillColor(sf::Color::White);
	options.setPosition(0, 140);

	instructions.setString("Ready? Press Space Bar!");
	instructions.setFont(font);
	instructions.setCharacterSize(54);
	instructions.setFillColor(sf::Color::White);
	instructions.setPosition(0, h - 100);

	end.setString("Game Over\nKeep Playing?\nY for Yes\nN for No");
	end.setFont(font);
	end.setCharacterSize(54);
	end.setFillColor(sf::Color::White);

	oPrompt.setString("Change Name? [X]\nChange Difficulty? [D]\n Exit? (Main Menu) [E]\n");
	oPrompt.setFont(font);
	oPrompt.setCharacterSize(54);
	oPrompt.setFillColor(sf::Color::White);

	newName.setString("Enter new name in console\n[E] to exit");
	newName.setFont(font);
	newName.setCharacterSize(54);
	newName.setFillColor(sf::Color::White);

	difficult.setString("[L] Easy\n[N] Normal (Default)\n[H] Hard\n[Z] Epic (Good Luck)\n[E] Exit");
	difficult.setFont(font);
	difficult.setCharacterSize(54);
	difficult.setFillColor(sf::Color::White);

	releaseBall.setString("Press [X] to release the Ball!");
	releaseBall.setFont(font);
	releaseBall.setCharacterSize(27);
	releaseBall.setFillColor(sf::Color::White);
	releaseBall.setPosition(0, h-50);

	score.setString("Score: ");
	score.setFont(font);
	score.setCharacterSize(27);
	score.setFillColor(sf::Color::White);
	score.setPosition(w - 180, 0);

	scoreString.setString(user.getDisplayScore());
	scoreString.setFont(font);
	scoreString.setCharacterSize(27);
	scoreString.setFillColor(sf::Color::White);
	scoreString.setPosition(w - 80, 0);

	name.setString(user.getName());
	name.setFont(font);
	name.setCharacterSize(27);
	name.setFillColor(sf::Color::White);
	name.setPosition(0, 0);

	life.setString("Lives: ");
	life.setFont(font);
	life.setCharacterSize(27);
	life.setFillColor(sf::Color::White);
	life.setPosition(w - 180, h - 50);

	lifeCount.setString(std::to_string(user.getLives()));
	lifeCount.setFont(font);
	lifeCount.setCharacterSize(27);
	lifeCount.setFillColor(sf::Color::White);
	lifeCount.setPosition(w - 80, h - 50);

	// End in-game message preparation
	//
	//
	//

	// Setup window
	sf::RenderWindow window(sf::VideoMode(w, h), "Nicholas A Moore (810739153)");
	sf::Texture t1;

	t1.loadFromFile("images/deepPurple.png");
	sf::Sprite sprite1(t1); // background

	sf::Clock clock;
	float timer = 0., delay = .05;

	while (window.isOpen()) {
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				window.close();
			}
		}

		// Controls
		// Movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			dir = 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			dir = 2;

		// Enter Pregame
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			state = gameState::playing;
		}
		// Release ball
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && state == gameState::playing) {
			ball.setSticky() = false;
		}
		// Play again (yes)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) && state == gameState::end) {
			hub.resetGame(user, field, ball);
		}
		// Play again (no)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) && state == gameState::end)
			window.close();
		// Open options menu
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::O) && state == gameState::menu)
			state = gameState::optionMenu;
		// Open name editor
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && state == gameState::optionMenu) {
			oState = optionState::name;
		}
		// Open difficulty select
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && state == gameState::optionMenu) {
			oState = optionState::difficulty;
		}
		// Return to main menu from options
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && state == gameState::optionMenu) {
			state = gameState::menu;
		}

		// To help with smoothness
		if (timer > delay) {
			timer = 0;
			Tick(); 
		}



		///// Drawing //////
		// background
		window.clear();
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				sprite1.setPosition(i * size, j * size);
				window.draw(sprite1);
			}
		}


		// Playing
		if (state == gameState::playing) {
			if (ball.getSticky())
				window.draw(releaseBall);

			// UI
			window.draw(score);

			scoreString.setString(user.getDisplayScore());
			window.draw(scoreString);

			name.setString(user.getName());
			window.draw(name);

			window.draw(life);

			lifeCount.setString(std::to_string(user.getLives()));
			window.draw(lifeCount);

			window.draw(ball.getBall());
			window.draw(user.getSlider());
			// End UI

			// Blocks
			for (int i = 0; i < field.getBlocks().size(); ++i)
				window.draw(field.getBlocks()[i]);
		}

		// Menu
		if (state == gameState::menu) {
			window.draw(title);
			window.draw(options);
			window.draw(instructions);
		}

		// End
		if (state == gameState::end) {
			window.draw(end);
			window.draw(score);

			scoreString.setString(user.getDisplayScore());
			window.draw(scoreString);
		}

		// Options
		if (state == gameState::optionMenu) {
			window.draw(oPrompt);
			if (oState == optionState::name) {
				window.draw(newName);
				std::cout << "Enter new name" << std::endl;
				std::string name = "";
				std::cin >> name;
				user.setName() = name;
				oState = optionState::none;
			}
			else if (oState == optionState::difficulty) {
				window.clear();

				// redraw background
				for (int i = 0; i < N; ++i) {
					for (int j = 0; j < M; ++j) {
						sprite1.setPosition(i * size, j * size);
						window.draw(sprite1);
					}
				}
				// end background

				window.draw(difficult);

				// Controls
				// Diffculty selection
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
					oState = optionState::none;
					state = gameState::menu;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
					ball.setDifficulty() = difficulty::normal;
					oState = optionState::none;
					state = gameState::menu;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
					ball.setDifficulty() = difficulty::hard;
					oState = optionState::none;
					state = gameState::menu;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
					ball.setDifficulty() = difficulty::epic;
					oState = optionState::none;
					state = gameState::menu;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
					ball.setDifficulty() = difficulty::easy;
					oState = optionState::none;
					state = gameState::menu;
				}
			}
			ball.update();
		}

		window.display();
		////// End Drawing //////

		// Reset for next round
		if (field.getBlocks().empty()) {
			field.reset();
			ball.reset();
			user.revertSize();
		}

	}

	return 0;
}
