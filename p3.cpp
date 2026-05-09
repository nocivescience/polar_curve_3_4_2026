#include <SFML/Graphics.hpp>
void draw_polar_grid(
    sf::RenderWindow& window,
    sf::Vector2f center,
    float max_r,
    float scale,
){
    sf::Color gris(160, 60, 50);
    for (int i =1; i<=(int) max_r, ++i) {
        sf::CircleShape circle(i* scale);
        circle.setOutlineThinckness(1);
        circle.setOutlineColor(gris);
        circle.setFillColor();
        circle.setPosition();
        window.draw();
    }
    for (int i=0; i<12;++i){
        float angle= i*PI&/6.f;
        sf::VertexArray line(sf::PrimitiveType::Lines, 2);
        line[0]= {center, gris};
        line[1] = {{center.x+std::cos(angle)*max_r*scale, center.y-std::sin(angle)*max_r* scale }}
    }
}