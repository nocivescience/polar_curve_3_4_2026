#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

const float PI = 3.14159265358979323846f;
const float TAU = 2.0f * PI;

// Función de radio dinámico
float get_r(float theta, float t) {
    return std::cos(theta + t) + std::cos(theta * t * 2.0f);
}

// --- FUNCIONES DE DIBUJO DE ESCENA ---

void draw_polar_grid(sf::RenderWindow& window, sf::Vector2f center, float max_r, float scale) {
    sf::Color grid_color(60, 60, 60);

    // 1. Círculos concéntricos (Radio)
    for (int i = 1; i <= (int)max_r; ++i) {
        sf::CircleShape circle(i * scale);
        circle.setOutlineThickness(1);
        circle.setOutlineColor(grid_color);
        circle.setFillColor(sf::Color::Transparent);
        circle.setOrigin({i * scale, i * scale});
        circle.setPosition(center);
        window.draw(circle);
    }

    // 2. Líneas radiales (Ángulos)
    for (int i = 0; i < 12; ++i) { // Cada 30 grados
        float angle = i * PI / 6.0f;
        sf::VertexArray line(sf::PrimitiveType::Lines, 2);
        line[0] = {center, grid_color};
        line[1] = {{center.x + std::cos(angle) * max_r * scale, 
                    center.y - std::sin(angle) * max_r * scale}, grid_color};
        window.draw(line);
    }
}

void draw_cartesian_grid(sf::RenderWindow& window, sf::Vector2f origin, float scale) {
    sf::Color grid_color(60, 60, 60);
    sf::Color axis_color(120, 120, 120);

    // Ejes principales
    sf::VertexArray axes(sf::PrimitiveType::Lines, 4);
    // Eje X
    axes[0] = {{origin.x, origin.y}, axis_color};
    axes[1] = {{origin.x + TAU * scale * 2.5f, origin.y}, axis_color};
    // Eje Y
    axes[2] = {{origin.x, origin.y - 2.5f * scale}, axis_color};
    axes[3] = {{origin.x, origin.y + 2.5f * scale}, axis_color};
    window.draw(axes);

    // Cuadrícula horizontal (Valores de r)
    for (float y = -2.0f; y <= 2.0f; y += 1.0f) {
        sf::VertexArray line(sf::PrimitiveType::Lines, 2);
        line[0] = {{origin.x, origin.y - y * scale}, grid_color};
        line[1] = {{origin.x + TAU * scale * 2.5f, origin.y - y * scale}, grid_color};
        window.draw(line);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "Matematica SFML 3");
    window.setFramerateLimit(60);

    float time = 0.0f;
    sf::Clock clock;

    sf::Vector2f polar_center(600.f, 250.f);
    sf::Vector2f cartesian_origin(100.f, 600.f);
    float scale = 60.f; 

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        time += clock.restart().asSeconds() * 0.4f;
        window.clear(sf::Color(15, 15, 15));

        // DIBUJAR CUADRÍCULAS (Debajo de las curvas)
        draw_polar_grid(window, polar_center, 3.0f, scale);
        draw_cartesian_grid(window, cartesian_origin, scale);

        // Curva Polar
        sf::VertexArray polar_curve(sf::PrimitiveType::LineStrip);
        for (float theta = 0; theta <= TAU + 0.1f; theta += 0.02f) {
            float r = get_r(theta, time);
            float x = polar_center.x + (r * std::cos(theta) * scale);
            float y = polar_center.y - (r * std::sin(theta) * scale); 
            polar_curve.append({{x, y}, sf::Color::Cyan});
        }

        // Curva Cartesiana
        sf::VertexArray cartesian_curve(sf::PrimitiveType::LineStrip);
        for (float theta = 0; theta <= TAU + 0.1f; theta += 0.02f) {
            float r = get_r(theta, time);
            float x = cartesian_origin.x + (theta * scale * 2.5f); 
            float y = cartesian_origin.y - (r * scale);
            cartesian_curve.append({{x, y}, sf::Color::Red});
        }

        window.draw(polar_curve);
        window.draw(cartesian_curve);
        window.display();
    }
    return 0;
}