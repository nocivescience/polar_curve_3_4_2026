#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

int main() {
    // SFML 3 usa sf::Vector2u para el tamaño de la ventana
    const unsigned int width = 800;
    const unsigned int height = 800;
    
    sf::RenderWindow window(sf::VideoMode({width, height}), "Animacion de Curva Polar SFML 3");
    window.setFramerateLimit(60);

    float theta = 0.0f;
    float k = 5.0f;       
    float a = 300.0f;     
    float speed = 0.05f;  

    std::vector<sf::Vertex> points;

    while (window.isOpen()) {
        // En SFML 3, pollEvent() devuelve un std::optional
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            // Se usa is<T>() para verificar el tipo de evento
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (theta < 2 * M_PI * 5) {
            float r = a * std::cos(k * theta);
            
            float x = r * std::cos(theta) + width / 2.0f;
            float y = r * std::sin(theta) + height / 2.0f;

            // SFML 3 inicializa Vertex de forma más estricta
            sf::Vertex v;
            v.position = {x, y};
            v.color = sf::Color::Cyan;
            points.push_back(v);
            
            theta += speed;
        }

        window.clear(sf::Color(20, 20, 20));
        
        if (!points.empty()) {
            // Se usa sf::PrimitiveType::Points explícitamente
            window.draw(points.data(), points.size(), sf::PrimitiveType::Points);
        }

        window.display();
    }

    return 0;
}