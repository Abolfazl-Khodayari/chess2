#include <SFML/Graphics.hpp>
using namespace sf;

int main(){
    RenderWindow window(VideoMode(800 ,600), "Hi Sina", Style::Titlebar | Style::Close);
	//CircleShape shape(50);
	RectangleShape rectangle(Vector2f(120, 50));
	//RectangleShape shape(50);
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event))
			if (event.type == Event::Closed)
				window.close();
		window.clear();
		window.draw(rectangle);
		window.display();
	}
	return 0;
}
