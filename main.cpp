#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include <string>
#include <math.h>
#include <queue>

void typer(sf::Text& text)
{
    std::string x;

    std::cin >> x;

    sf::Font font;
    font.loadFromFile("arial.ttf");
    text.setFont(font);
    text.setString(x);

}



void primeFactor(std::vector<int>*primeList, int input)
{
    for(int i = 2; i <= sqrt(input); i++ )
    {
        while (input%i == 0)
        {
            input/=i;
            primeList->push_back(i);
        }
    }
    primeList->push_back(input);
}

void allPrimeFactor(std::vector<std::vector<int>>* primefactorization)
{
    std::queue<std::thread*> threads;
    int i = 0;
    while(i != 1000000)
    {
        if(i > primefactorization->size())
        primefactorization->resize(2*i);
        threads.push(new std::thread(&primeFactor, &primefactorization->at(i), i));
        i++;
        if(threads.size() == 10)
        {
            threads.front()->join();
            threads.pop();
        }
    }
}
//std::thread t(&primeFactor, &primefactorization->at(i), i)
void printList(std::vector<int>& primeList)
{
    for(int i=0; i < primeList.size(); i++)
        std::cout << primeList[i] << std::endl;
}

int main()
{
    std::vector<std::vector<int>> primefactorization;
    std::thread thecreator(&allPrimeFactor, &primefactorization);

    std::vector<int> primeList;
    int input = 1;
    std::cout << "insert number to find prime factor" << std::endl;
    while(input > 0)
    {
        std::cin >> input;
        if(primefactorization.size() < input)
        {
            primeFactor(primeList, input)
        }
    }


    std::thread thing (&primeFactor, &primeList, input);
    thing.join();

    printList(primeList);

    std::cout << std::endl;

    /*sf::Text text;
    sf::Thread t(&typer, text);
    t.launch();
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML window");

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("cb.bmp"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        // Clear screen
        app.clear();

        // Draw the sprite
        app.draw(text);

        // Update the window
        app.display();
    }*/

    return EXIT_SUCCESS;
}
