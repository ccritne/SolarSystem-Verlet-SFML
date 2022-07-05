#include <SFML/Graphics.hpp>
#include "nLib.hpp"
using namespace std;
using namespace sf;

int windowX = 1920;
int windowY = 1080;

float viewX = windowX*100;
float viewY = windowY*100;

float graphicX = viewX*0.95;
float graphicY = viewY*0.95;

int nbody = 9;
long double G = 6.673E-11;

long double maxHeight = 4.7E12;
long double maxWidth = 4.7E12;

int radius = 300;

vector<CircleShape> planets(9, CircleShape(radius));

vector<long double> mass(9);

vector<coord> pos(9, {0, 0, 0});
vector<coord> vel(9, {0, 0, 0});
vector<coord> f(9, {0, 0, 0});

vector<vector<Vertex>> path;

void interaction(){
   coord posij;
   long double rij;
  
   f = zero();

   for(int i = 0; i < nbody; i++)
      for(int j = 0;j < nbody; j++){
         if( i != j){
               posij = sum(pos[j], mul(pos[i], -1));
               rij = pow(sqrt(dotProduct(posij)), 3);
               f[i] = sum(f[i], mul(posij, ((G*mass[i]*mass[j]))/rij));
         }
      }
}

void frontSets(){
      float translationX = viewX/graphicX;
      float translationY = viewY/graphicY;
      float width = graphicX*0.95;
      float height = graphicY*0.95;
      float xStart = graphicX*0.5;
      float yStart = graphicY*0.5;
      float positionPlanetsI; 
      for(int i = 0; i < nbody; i++){
         positionPlanetsI = xStart*translationX + ((width/2)*pos[i].x)/maxWidth;
         planets[i].setPosition(Vector2f(positionPlanetsI, yStart*translationY));
      }

      planets[0].setFillColor(Color::Yellow);
      planets[1].setFillColor(Color(26,26,26));
      planets[2].setFillColor(Color(230,230,230));
      planets[3].setFillColor(Color(47,106,105));
      planets[4].setFillColor(Color(153,61,0));
      planets[5].setFillColor(Color(176,127,53));
      planets[6].setFillColor(Color(176,143,54));
      planets[7].setFillColor(Color(85,128,170));
      planets[8].setFillColor(Color(54,104,150));
}

void backSets(){

      float translationX = viewX/graphicX;
      float translationY = viewY/graphicY;
      float width = graphicX*0.95;
      float height = graphicY*0.95;
      float xStart = graphicX*0.5;
      float yStart = graphicY*0.5;
      float positionPlanets_x_I; 
      float positionPlanets_y_I; 
      for(int i = 0; i < nbody; i++){
         positionPlanets_x_I = xStart*translationX + ((width/2)*pos[i].x)/maxWidth;
         positionPlanets_y_I = yStart*translationY + ((height/2)*pos[i].y)/maxHeight;
         vector<Vertex> track{
            Vertex(Vector2f(planets[i].getPosition().x + radius, planets[i].getPosition().y + radius)),
            Vertex(Vector2f(positionPlanets_x_I + radius , positionPlanets_y_I + radius))
         };
         path.push_back(track);   
         planets[i].setPosition(Vector2f(positionPlanets_x_I, positionPlanets_y_I));
      }
}

int main(){

   
   mass[0] = 1988500.0E24;
   mass[1] = 0.330E24;
   mass[2] = 4.87E24;
   mass[3] = 5.97E24;
   mass[4] = 0.64E24;
   mass[5] = 1898E24;
   mass[6] = 568E24;
   mass[7] = 86.8E24;
   mass[8] = 102E24;

   //Initial velocity of Planets on Y axis;
   vel[0].y = 0;
   vel[1].y = 47.4E3;
   vel[2].y = 35.0E3;
   vel[3].y = 29.8E3;
   vel[4].y = 24.1E3;
   vel[5].y = 13.1E3;
   vel[6].y = 9.7E3;
   vel[7].y = 6.8E3;
   vel[8].y = 5.4E3;

   // Distance from Sun

   pos[0].x = 0.0E9;           //Sun
   pos[1].x = 69.8E9;          //Mercury
   pos[2].x = 108.9E9;         //Venus
   pos[3].x = 152.1E9;         //Earth
   pos[4].x = 249.3E9;         //Mars
   pos[5].x = 816.4E9;         //Jupiter
   pos[6].x = 1506.5E9;        //Sapturn
   pos[7].x = 3001.4E9;        //Uranus
   pos[8].x = 4558.9E9;        //Neptune

   long double dt = 86400;
   
	ContextSettings settings;
	settings.antialiasingLevel = 8;

   RenderWindow window(VideoMode(windowX, windowY), "Solar System", Style::Default, settings);
	window.setFramerateLimit(60);

   View view(FloatRect(0.f, 0.f, viewX, viewY));
   window.setView(view);
    
   int nstep = 0;
   ofstream fout("data.txt");

   interaction();

   Font font;
   if(!font.loadFromFile("arial.ttf")) cout<<"Errore Font!"<<endl;
   Text text("0", font, 3000);
   text.setPosition(100, 100);
   text.setOutlineColor(Color::White);
   text.setFillColor(Color::White);

   frontSets();

   bool drag = false;

   while(window.isOpen()){
		Event event;

		while (window.pollEvent(event)){
			if (event.type == Event::Closed)
				window.close();
         if (event.type == sf::Event::MouseWheelMoved){
               if(event.mouseWheel.delta == 1)
                  view.zoom(0.9f);
               else
                  view.zoom(1.1f);

               window.setView(view);
            }
      }

      for(int j = 0; j < nbody; j++){
         pos[j] = sum(pos[j], sum(mul(vel[j], dt), mul(mul(mul(f[j], double(1)/mass[j]), 0.5), dt*dt)));
         vel[j] = sum(vel[j], mul(mul(f[j], double(1)/mass[j]), 0.5*dt));
      }
            
      interaction();

      for(int j = 0; j < nbody; j++)
         vel[j] = sum(vel[j], mul(mul(f[j], double(1)/mass[j]), 0.5*dt));

      backSets();

      text.setString(to_string(nstep));

      window.clear();
      window.draw(text);

      for(auto x: path)
         window.draw(&x[0], x.size(), Lines);
      
      for(auto x : planets)
         window.draw(x);

      window.display();
      nstep++;
   }
   
   
   return 0;
}