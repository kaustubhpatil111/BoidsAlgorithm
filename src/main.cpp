#include <SFML/Graphics.hpp>

#include <vector>
#include <random>
#include <cmath>

#include "Boid.h"


int main()

{   //visual setting
    const float scale =40.0f;
    const float boidSize =5.0f;


    //window
    sf::VideoMode desktop=sf::VideoMode::getDesktopMode();


    //window creation
    
    const unsigned int windowWidth=desktop.width;
    const unsigned int windowHeight=desktop.height;

    sf::RenderWindow window(
        sf::VideoMode(windowWidth,windowHeight),
        "Boids Learning"
    );

    window.setFramerateLimit(60);

    //actual window size
    const float actualWidth=static_cast<float>(window.getSize().x);
    const float actualHeight=static_cast<float>(window.getSize().y);

    


    //world setting
    //automatic calculate world size
    const float worldHalfWidth=
    actualWidth/(2.0f*scale);

    const float worldHalfHeight=
    actualHeight/(2.0f*scale);

    //center around 0,0
    const float worldMinX=
    -worldHalfWidth;

    const float worldMaxX=
    worldHalfWidth;

    const float worldMinY=
    -worldHalfHeight;

    const float worldMaxY=
    worldHalfHeight;

    //simulation setting 

    const float deltaTime =0.016f;

    //screen center
    const float screenCenterX= windowWidth/2.0f;
    const float screenCenterY= windowHeight/2.0f;


    
    int noOfBoids=40;

    //random generator
    std::random_device rd;
    std::mt19937 generator(rd());

    std::uniform_real_distribution<float> xDistribution(worldMinX,worldMaxX);
    std::uniform_real_distribution<float> yDistribution(worldMinY,worldMaxY);
    
    std::uniform_real_distribution<float> velocityDistribution(-1.0f,1.0f);


    //boids generation
    std::vector<Boid>boids;
    for(int i =0;i<noOfBoids;i++){

        float x=xDistribution(generator);
        float y=yDistribution(generator);

        float vx=velocityDistribution(generator);
        float vy=velocityDistribution(generator);

        boids.emplace_back(
            Vector2(x,y),
            Vector2(vx,vy),
            Vector2(0.0f,0.0f)
        );
    }
    

   
    window.clear(sf::Color::Black);
    window.display();

    while (window.isOpen()){

        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        //1. calculate steering for all

        for (Boid& boid:boids){
            boid.acceleration= boid.steeringFrom(boids);
        }

        //update all
        for (Boid& boid:boids){
            boid.update(deltaTime);

            boid.wrapAround(
                worldMinX,
                worldMaxX,
                worldMinY,
                worldMaxY
            );
        }

        //draw

        

        sf::RectangleShape fade(
            sf::Vector2f(
                static_cast<float>(windowWidth),
                static_cast<float>(windowHeight)
            )
        );

        fade.setFillColor(
            sf::Color(0,0,0,30)
        );

        window.draw(fade);

        for(Boid& boid:boids){
            float screenX =
               screenCenterX + boid.position.x * scale;
            
            float screenY =
                screenCenterY - boid.position.y * scale;

            //create triangle
            sf::CircleShape triangle(
                boidSize,
                3);

            triangle.setOrigin(
                boidSize,
                boidSize
            );

            triangle.setPosition(screenX,screenY);

            //rotation of triangle according to velocity

            float angle = std::atan2(
                -boid.velocity.y,
                boid.velocity.x);

            float degrees = 
                angle* 180.0f / 3.14159265f;

            triangle.setRotation(
                degrees+90.0f);

            triangle.setFillColor(
                sf::Color::White);

            window.draw(triangle);
        }
        


        window.display();
    }

    return 0;
}