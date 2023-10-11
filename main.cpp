#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Particle {
	public:
	sf::RectangleShape rect;
	float x, y, vx, vy;

	Particle(vector<int> area) {
		rect = sf::RectangleShape();
		rect.setSize(sf::Vector2f(2,2));
		x = rand() % area[0];
		y = rand() % area[1];
		rect.setPosition(x, y);
		vx = 0;
		vy = 0;
	}

	void update() {
		rect.setPosition(x,y);
	}
};

vector<Particle> createParticleGroup(sf::Color color, int count, vector<int> area) {
	vector<Particle> particles;
	for (int i = 0; i < count; i++) {
		Particle p(area);
		p.rect.setFillColor(color);
		particles.push_back(p);
	}
	return particles;
}

void rule(vector<Particle> &group1, vector<Particle> &group2, float g, vector<int> size) {
    for (auto &i : group1) {
        float fx = 0.0;
        float fy = 0.0;
        for (auto &j : group2) {
            float dx = i.x - j.x;
            float dy = i.y - j.y;
            float d = sqrt(dx * dx + dy * dy);
            if (d > 0 && d < 80) {
                float F = g * 1 / d;
                fx += (F * dx);
                fy += (F * dy);
            }
        }
        i.vx = (i.vx + fx) * 0.5;
        i.vy = (i.vy + fy) * 0.5;
        i.x += i.vx;
        i.y += i.vy;
        if (i.x <= 0 || i.x >= size[0]) i.vx *= -1;
        if (i.y <= 0 || i.y >= size[1]) i.vy *= -1;
    }
}

// Main function of the program
int main()
{
	vector<int> size(2, 800);

        // create the window
        sf::RenderWindow window(sf::VideoMode(size[0], size[1]), "Dots!");
	window.setFramerateLimit(60);

	vector<vector<Particle>> all_particles;
	vector<Particle> red = createParticleGroup(sf::Color::Red, 200, size);
	all_particles.push_back(red); // red = all_particles[0]
	vector<Particle> blue = createParticleGroup(sf::Color::Blue, 200, size);
	all_particles.push_back(blue); // blue = all_particles[1]
	vector<Particle> green = createParticleGroup(sf::Color::Green, 200, size);
	all_particles.push_back(green); // green = all_particles[2]
	//vector<Particle> white = createParticleGroup(sf::Color::White, 200, size);
	//all_particles.push_back(white); // white = 3
	//vector<Particle> yellow = createParticleGroup(sf::Color::Yellow, 200, size);
	//all_particles.push_back(yellow); // yellow = 4
	//vector<Particle> magenta = createParticleGroup(sf::Color::Magenta, 200, size);
	//all_particles.push_back(magenta); // magenta = 5
	//vector<Particle> cyan = createParticleGroup(sf::Color::Cyan, 200, size);
	//all_particles.push_back(cyan); // cyan = 6

        // run the program as long as the window is open
        while (window.isOpen())
        {
                // check all the window's events that were triggered since the last iteration of the loop
                sf::Event event;
                while (window.pollEvent(event))
                {
                    // "close requested" event: we close the window
                    if (event.type == sf::Event::Closed)
                        window.close();
                }

		rule(all_particles[2],all_particles[2],0.32, size);
	    	rule(all_particles[2],all_particles[0],-0.17, size);
	    	rule(all_particles[2],all_particles[1],0.34, size);
	    	rule(all_particles[0],all_particles[0],-0.10, size);
	    	rule(all_particles[0],all_particles[2],-0.34, size);
	    	rule(all_particles[1],all_particles[1],0.15, size);
	    	rule(all_particles[1],all_particles[2],-0.20, size);
	    	//rule(all_particles[3],all_particles[3],0.10, size);
	    	//rule(all_particles[4],all_particles[4],-0.20, size);
	    	//rule(all_particles[5],all_particles[5],-0.20, size);
	    	//rule(all_particles[6],all_particles[6],-0.20, size);
	    	//rule(all_particles[3],all_particles[0],-0.18, size);
	    	//rule(all_particles[4],all_particles[0],-0.12, size);
	    	//rule(all_particles[5],all_particles[0],-0.14, size);
	    	//rule(all_particles[6],all_particles[0],-0.30, size);
	    	//rule(all_particles[6],all_particles[3],0.20, size);
	    	//rule(all_particles[3],all_particles[6],0.16, size);
	    	//rule(all_particles[0],all_particles[3],-0.30, size);

                // clear the window with black color
                window.clear(sf::Color::Black);

                // draw everything here...
                // window.draw(...);
		for ( auto group : all_particles) {
			for ( auto particle : group) {
				particle.update();
				window.draw(particle.rect);
			}
		}

                // end the current frame
                window.display();
        }
        return 0;
}
