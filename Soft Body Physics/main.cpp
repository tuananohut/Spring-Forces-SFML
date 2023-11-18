#include <SFML/Graphics.hpp>
#include <chrono>

#include "Vec2.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 10;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Spring Forces", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    sf::CircleShape circle;
    circle.setFillColor(sf::Color(12, 197, 244));
    circle.setRadius(50.0f);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setOutlineThickness(5.0f);
    circle.setOutlineColor(sf::Color::White);
    
    sf::CircleShape anchor;
    anchor.setFillColor(sf::Color(12, 197, 244));
    anchor.setRadius(25.0f);
    anchor.setOrigin(anchor.getRadius(), anchor.getRadius());
    anchor.setOutlineThickness(5.0f);
    anchor.setOutlineColor(sf::Color::White);

    Vec2 vCircle(350.0f, 50.0f);
    Vec2 vAnchor(static_cast<float>(window.getSize().x) / 2.0f, 25.0f);

    circle.setPosition(vCircle.x, vCircle.y);
    anchor.setPosition(vAnchor.x, vAnchor.y);

    float restLength = 300.0f;
    float k = 0.01f;
    Vec2 gravity(0.0f, 0.1f);
    Vec2 velocity(0.0f, 0.0f);

    while (window.isOpen())
    {
        const auto start{ std::chrono::steady_clock::now() };
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                Vec2 mousePosition(static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y));
                vCircle = mousePosition;
                circle.setPosition(vCircle.x, vCircle.y);

                velocity.x = 0.0f;
                velocity.y = 0.0f;
            }
        }
        circle.setPosition(vCircle.x, vCircle.y);
        
        Vec2 force = vCircle - vAnchor;
        float x = force.length() - restLength;
        force.normalize();
        force *= k * -1.0f * x;
        velocity += force;
        velocity += gravity;
        vCircle += velocity;
        velocity *= 0.99f;
        
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(vAnchor.x, vAnchor.y)),
            sf::Vertex(sf::Vector2f(vCircle.x, vCircle.y))
        };

        line[0].color = sf::Color::White;
        line[1].color = sf::Color::White;
        
        window.clear(sf::Color(101, 40, 110));

        window.draw(circle);
        window.draw(anchor);
        window.draw(line,2, sf::Lines);

        window.display();

        const auto end{ std::chrono::steady_clock::now() };
        const std::chrono::duration<double> elapsed_seconds{ end - start };
        sf::sleep(sf::milliseconds(static_cast<int>((1.0 / 60.0 - elapsed_seconds.count()) * 1000)));  
    }

    return 0;
}
