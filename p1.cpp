#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

const float PI =3.14159265358979323846f;
const float TAU = 2.0f * PI;

float get_r(float theta, float t){
    return std::cos(theta+t) +std::cos(theta*t*2.f);
}

void draw_polar_grid(sf::RenderWindow& window, sf::Vector2f center, float max_r, float scale){
    sf::Color grid_color(60, 60, 60);
    for (int i=1; i<= (int)max_r; ++i){
        sf::CircleShape circle(i*scale);

    }
}
void draw_cartesian_grid(sf::RenderWindow& window, sf::Vector2f origin, float scale){
    sf::Color mi_color(40, 60, 80);
    sf::VertexArray axes(sf::PrimitiveType::Lines, 4);
    axes[0] = {{origin.x, origin.y}, mi_color};
    for (float y= -2.f; y <= 2.0f; y+= 1.f){
        sf::VertexArray line(sf::PrimitiveType::Lines, 2)
    }
}

int main(){
    sf::RenderWindow window(sf::VideoMode({800, 600}), "La Gran Ventana");
    window.setFramerateLimit(60);
    while(window.isOpen()){
        while (const std::optional event= window.pollEvent())
        {
            if(event->is<sf::Event::Closed>()) window.close();
        }
        time+= clock.restart.asSecond()*0.4f;
        
    }
    return 0;
}