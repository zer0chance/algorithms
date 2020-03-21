#include <SFML/Graphics.hpp>
#include <cmath>

#define WIDTH 900
#define HEIGHT 900
#define SCALE_SIZE 100
#define GRAPH_POS 450

#define N 5

double X[N] = {-1.5, -0.75, 0, 0.75, 1.5};
double Y[N] = {tan(-1.5), tan(-0.75), tan(0), tan(0.75), tan(1.5)};


double P(double x)
{
    double result = 0;

    for (int i = 0; i < N; i++)
    {
        double fraction = 1;  
        for (int j = 0; j < N; j++)
        {
            if (i != j)
                fraction *= (x - X[j]) / (X[i] - X[j]);    
        } 
        result += Y[i] * fraction;
    }

    return result;    
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Graphic");

    sf::Vertex Ox[2]
    {
        sf::Vertex(sf::Vector2f(0, HEIGHT / 2)),
        sf::Vertex(sf::Vector2f(WIDTH, HEIGHT / 2))
    };
    sf::Vertex Oy[2]
    {
        sf::Vertex(sf::Vector2f(WIDTH / 2, 0)),
        sf::Vertex(sf::Vector2f(WIDTH / 2, HEIGHT))
    };

    window.draw(Ox, 2, sf::LineStrip);
    window.draw(Oy, 2, sf::LineStrip);


    sf::Vertex root[2];
    sf::Vertex lagr[2];
    root[0] = sf::Vertex(sf::Vector2f(X[0] * SCALE_SIZE + GRAPH_POS, HEIGHT - Y[0] * SCALE_SIZE - GRAPH_POS));
    lagr[0] = sf::Vertex(sf::Vector2f(X[0] * SCALE_SIZE + GRAPH_POS, HEIGHT - P(X[0]) * SCALE_SIZE - GRAPH_POS));
 

    for (double i = -1.5; i <= 1.5; i += 0.01)
    {
        root[1] = sf::Vertex(sf::Vector2f(i * SCALE_SIZE + GRAPH_POS, HEIGHT - tan(i) * SCALE_SIZE - GRAPH_POS));
        lagr[1] = sf::Vertex(sf::Vector2f(i * SCALE_SIZE + GRAPH_POS, HEIGHT - P(i) * SCALE_SIZE - GRAPH_POS));

        window.draw(root, 2, sf::LineStrip);
        window.draw(lagr, 2, sf::LineStrip);

        root[0] = root[1];
        lagr[0] = lagr[1];
    }

    window.display();
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //window.clear();
        // window.draw(root, 5, sf::LineStrip);
        // window.draw(lagr, 5, sf::LineStrip);
        
    }

    return 0;
}   




// sf::RectangleShape line(sf::Vector2f(150, 3));

//     line.setFillColor(sf::Color::Green);
//     line.setPosition(sf::Vector2f(50, 50));
//     line.rotate(90);
    
//     sf::Vertex vertices[2] =
//     {
//         sf::Vertex(sf::Vector2f(10, 10)),
//         sf::Vertex(sf::Vector2f(500, 500))
//     };
