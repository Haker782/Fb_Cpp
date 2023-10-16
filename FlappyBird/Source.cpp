#include<SFML/Graphics.hpp>
#include<iostream>
#include<sstream>
#include <string>

class Tower {
public:
	sf::Texture t , t1;
	sf::Image i , i1;
	float dx;
	int x, y ,y1;
	int score;
	sf::Sprite s ,s1;

	Tower(int x ,int y , int y1) {
		this->x = x;
		this->y = y; this->y1 = y1;
		dx = 2;
		score = 0;
		s.setPosition(x, y);
		s1.setPosition(x, y1);
		s.setTextureRect(sf::IntRect(0, 968, 172,-968));
		s1.setTextureRect(sf::IntRect(0, 0, 172, 968));
		i.loadFromFile("Tower.png");
		i1.loadFromFile("Tower.png");
		t.loadFromImage(i); s.setTexture(t);
		t1.loadFromImage(i1); s1.setTexture(t1);
	}
	void update(float time) {
		if (x < -172) { x = 1980+172; y = -850 + rand() % (-150 +850 + 1) ; score++; y1 = y + 968 + 200;
	
		}
		
		x += -dx * time ;
		

		s.setPosition(x, y);

		s1.setPosition(x, y1);
	}
	sf::FloatRect getRect() {
		return sf::FloatRect(this->x, this->y , 172, 968);
	}
	sf::FloatRect getRect1() {
		return sf::FloatRect(this->x, this->y1, 172, 968);
	}
};


class bird {
public:
	bool life;
	sf::Image i;
	sf::Texture t;
	float dy;
	int x, y;
	int CurentFrame;
	sf::Sprite s;
	bool isSpace = 0;
	bird() {
		x = 100;
		y = 500;
		dy = 0;
		CurentFrame = 0;
		s.setPosition(x, y);
		i.loadFromFile("bird0.png");
		i.createMaskFromColor(sf::Color::Blue);
		t.loadFromImage(i); s.setTexture(t);
		this->s.setTextureRect(sf::IntRect(0, 0, 98,70));
	}
	void anim() {
		CurentFrame += 1;

		if (CurentFrame > 299) CurentFrame = 0;

		s.setTextureRect(sf::IntRect(int(CurentFrame / 100) * 98, 0, 98, 70));
	}
	int update(float time) {
		

		
		if (y > 1080) { return 0; }
		
		dy = dy + 0.005 * time;
		y += dy * time;
		
		

		s.setPosition(x, y);
		return 1;

	}
	sf::FloatRect getRect() {
		return sf::FloatRect(this->x, this->y, 100, 70);
	}

};
int game() {
	
	sf::RenderWindow window(sf::VideoMode(), "Flappy Bird", sf::Style::Fullscreen);
	Tower t(1980+172 , -800,1000);
	Tower t1(1980 + 172 +1200 ,-600,700 );
	bird b;
	sf::Clock clock;

	float want_fps = 1000;
	sf::Clock loop_timer;

	bool start = 0;

	sf::Font font;
	font.loadFromFile("text.ttf");
	sf::Text text("", font, 200);
	text.setFillColor(sf::Color::White);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	text.setStyle(sf::Text::Bold);


	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 1200;




		b.anim();
		if (start) {
			if (!b.update(time) ) {
				start = 0;
				t.x = 1980; b.y = 500; t.score = 0; t1.score = 0;
				t1.x = 1980 + 1200;
			}

			t.update(time);
			t1.update(time);
		}
		

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && b.isSpace == 0) {

			b.dy = -0.9;
			//event.type = sf::Event::KeyReleased;
			b.isSpace = 1;
			start = 1;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))	b.isSpace = 0;


		if (b.getRect().intersects(t.getRect()) || b.getRect().intersects(t1.getRect())) {
			 start = 0;
			 t.x = 1980; b.y = 500; t.score = 0; t1.score = 0;
			 t1.x = 1980 + 1200;
			//window.close();
		}
		if (b.getRect().intersects(t.getRect1()) || b.getRect().intersects(t1.getRect1())) {
			 start = 0;
			 t.x = 1980; b.y = 500; t.score = 0;
			 t1.x = 1980 + 1200; b.y = 500; t1.score = 0;
			//window.close();
		}


		window.clear(sf::Color(153, 217, 234));

		sf::Vector2f center = window.getView().getCenter();
		sf::Vector2f size = window.getView().getSize();
		std::ostringstream playerScore;

		playerScore << t.score + t1.score;
		text.setString("Score:" + playerScore.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
		text.setPosition(700, 100);//задаем позицию текста



		window.draw(text);//рисую этот текст

		window.draw(b.s);
		window.draw(t.s); window.draw(t.s1);
		window.draw(t1.s); window.draw(t1.s1);
		window.display();
		sf::Int64 frame_duration = loop_timer.getElapsedTime().asMilliseconds();

		sf::Int64 time_to_sleep = int(1000.f / want_fps) - frame_duration;
		if (time_to_sleep > 0) {
			sf::sleep(sf::milliseconds(time_to_sleep));
		}
		loop_timer.restart();
	}
	return 0;
}
int main() {
	game();

	
}
