#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
using namespace sf;

int main()
{
    srand(time(NULL));
    RenderWindow window(VideoMode(800, 600), "BimBimBamBam");

    RectangleShape goal1(Vector2f(20, 600));
    goal1.setFillColor(Color::White);
    goal1.setPosition(0, 0);

    RectangleShape goal2(Vector2f(20, 600));
    goal2.setFillColor(Color::White);
    goal2.setPosition(780, 0);

    RectangleShape player1(Vector2f(15, 140));
    player1.setFillColor(Color::Blue);
    player1.setPosition(25, 250);

    RectangleShape player2(Vector2f(15, 140));
    player2.setFillColor(Color::Yellow);
    player2.setPosition(755, 250);

    RectangleShape goal(Vector2f(20, 600));
    goal.setFillColor(Color::White);
    goal.setPosition(0, 0);

    CircleShape ball(12.5);
    ball.setFillColor(Color::Red);
    ball.setPosition(375, 275);


    RectangleShape Barrikade1(Vector2f(20, 100));
    Barrikade1.setFillColor(Color::Blue);
    Barrikade1.setPosition(25, 0);


    RectangleShape Barrikade2(Vector2f(20, 100));
    Barrikade2.setFillColor(Color::Yellow);
    Barrikade2.setPosition(755, 0);

    RectangleShape Barrikade3(Vector2f(20, 100));
    Barrikade3.setFillColor(Color::Blue);
    Barrikade3.setPosition(25, 510);

    RectangleShape Barrikade4(Vector2f(20, 100));
    Barrikade4.setFillColor(Color::Yellow);
    Barrikade4.setPosition(755, 510);

    Font TextesFont;
    TextesFont.loadFromFile("PicsAndTetxts/EpilepsySansBold.ttf");

    Text PauseText;
    PauseText.setFont(TextesFont);
    PauseText.setCharacterSize(50);
    PauseText.setFillColor(sf::Color::White);
    PauseText.setString("TO CONTINUE PRESS 'Y' ");
    PauseText.setPosition(157.5, 340);
    Text Unpause1;
    Unpause1.setFont(TextesFont);
    Unpause1.setCharacterSize(50);
    Unpause1.setFillColor(Color::White);
    Unpause1.setString("3");
    Unpause1.setPosition(0, 0);
    Text Unpause2;
    Unpause2.setFont(TextesFont);
    Unpause2.setCharacterSize(50);
    Unpause2.setFillColor(Color::Yellow);
    Unpause2.setString("2");
    Unpause2.setPosition(0, 0);
    Text Unpause3;
    Unpause3.setFont(TextesFont);
    Unpause3.setCharacterSize(50);
    Unpause3.setFillColor(Color::Red);
    Unpause3.setString("1");
    Unpause3.setPosition(0, 0);


    int BounceCounter = 0;
    const float pi = 3.14159f;
    float ballAngle = 0.f;
    float ballRadius = 11.5;
    float bollspeed = 0.35;
    ballAngle = (std::rand() % 360) * 2 * pi / 360;
    Clock clock;
    Time timerate;
    float time;
    bool PauseTrigger = true;
    bool WasUsed = false;
    int g = 0;
    
    while (window.isOpen())
    {
            time = clock.getElapsedTime().asMicroseconds();
            clock.restart();
            time = time / 800;
            Event event;
            if(PauseTrigger == false){
            while (window.pollEvent(event))
            {

                if (event.type == Event::Closed)
                    window.close();
                if (Keyboard::isKeyPressed(Keyboard::Y)) {
                    PauseTrigger = true;
                }
                if (Keyboard::isKeyPressed(Keyboard::Key::W) && player1.getPosition().y > 0) {
                    player1.move(0, -10);
                }

                if (Keyboard::isKeyPressed(Keyboard::Key::S) && player1.getPosition().y < 600 - player1.getSize().y) {
                    player1.move(0, 10);
                }

                if (Keyboard::isKeyPressed(Keyboard::Key::Up) && player2.getPosition().y > 0) {
                    player2.move(0, -10);
                }

                if (Keyboard::isKeyPressed(Keyboard::Key::Down) && player2.getPosition().y < 600 - player2.getSize().y) {
                    player2.move(0, 10);
                }
            }

            float fact = bollspeed * time;
            ball.move(cos(ballAngle) * fact, sin(ballAngle) * fact);

            FloatRect ballBounds = ball.getGlobalBounds();
            FloatRect goalBounds = goal.getGlobalBounds();
            FloatRect goal2Bounds = goal2.getGlobalBounds();
            FloatRect player1Bounds = player1.getGlobalBounds();
            FloatRect player2Bounds = player2.getGlobalBounds();

            if (ball.getPosition().y - ballRadius < 0.f)
            {
                ballAngle = -ballAngle;
                ball.setPosition(ball.getPosition().x, ballRadius + 0.1f);
            }
            if (ball.getPosition().y + ballRadius > 600)
            {
                ballAngle = -ballAngle;
                ball.setPosition(ball.getPosition().x, 600 - ballRadius - 0.1f);
            }

            if
                (ball.getGlobalBounds().intersects(player1.getGlobalBounds()))
            {
                if (ball.getPosition().y > player1.getPosition().y)
                    ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
                else
                    ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;
                ball.setPosition(player1.getPosition().x - ballRadius - player1.getSize().x / 2 + 40.f, ball.getPosition().y);
                BounceCounter = rand() % 2;

            }

            if (ball.getGlobalBounds().intersects(player2.getGlobalBounds()))
            {
                if (ball.getPosition().y > player2.getPosition().y)
                    ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
                else
                    ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;
                ball.setPosition(player2.getPosition().x - ballRadius - player2.getSize().x / 2 - 15.f, ball.getPosition().y);
                BounceCounter = rand() % 2;
            }


            if (ball.getPosition().x >= 750 && ball.getPosition().y >= goal2.getPosition().y && ball.getPosition().y <= goal2.getPosition().y + 200)
                window.close();

            if (ballBounds.intersects(goal2Bounds) || ballBounds.intersects(goalBounds)) {
                window.close();
            }

            if (ball.getPosition().x >= 750 && ball.getPosition().y >= goal.getPosition().y && ball.getPosition().y <= goal.getPosition().y + 200)
                window.close();
            window.clear();
            if (BounceCounter % 2 == 0) {
                window.draw(Barrikade1);
                window.draw(Barrikade2);
                window.draw(Barrikade3);
                window.draw(Barrikade4);
                if (ball.getGlobalBounds().intersects(Barrikade1.getGlobalBounds())) {
                    if (ball.getPosition().y > Barrikade1.getPosition().y)
                        ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
                    else
                        ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;
                    ball.setPosition(Barrikade1.getPosition().x - ballRadius - Barrikade1.getSize().x / 2 + 30.f, ball.getPosition().y);
                }
                if (ball.getGlobalBounds().intersects(Barrikade2.getGlobalBounds())) {
                    if (ball.getPosition().y > Barrikade2.getPosition().y)
                        ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
                    else
                        ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;
                    ball.setPosition(Barrikade2.getPosition().x - ballRadius - Barrikade2.getSize().x / 2 - 8.f, ball.getPosition().y);
                }
                if (ball.getGlobalBounds().intersects(Barrikade3.getGlobalBounds())) {
                    if (ball.getPosition().y > Barrikade3.getPosition().y)
                        ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
                    else
                        ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;
                    ball.setPosition(Barrikade3.getPosition().x - ballRadius - Barrikade3.getSize().x / 2 + 30.f, ball.getPosition().y);
                }
                if (ball.getGlobalBounds().intersects(Barrikade4.getGlobalBounds())) {
                    if (ball.getPosition().y > Barrikade4.getPosition().y)
                        ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
                    else
                        ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;
                    ball.setPosition(Barrikade4.getPosition().x - ballRadius - Barrikade4.getSize().x / 2 - 8.f, ball.getPosition().y);
                }
            }
            window.draw(player1);
            window.draw(player2);
            window.draw(goal);
            window.draw(goal2);
            window.draw(ball);
            window.display();
        }
        if(PauseTrigger == true ) {
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
                if (Keyboard::isKeyPressed(Keyboard::Y)) {
                    PauseTrigger = false;
                    window.clear();
                }
            }
            window.draw(player1);
            window.draw(player2);
            window.draw(goal);
            window.draw(goal2);
            if (WasUsed == false) {
                window.draw(ball);
            }
            window.draw(PauseText);
            window.draw(Barrikade1);
            window.draw(Barrikade2);
            window.draw(Barrikade3);
            window.draw(Barrikade4);
            window.display();
        }
    }
    return 0;
}