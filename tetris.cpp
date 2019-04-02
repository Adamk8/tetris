#include <SFML/Graphics.hpp>
#include <time.h>



const int HIEGHT = 20;
const int WIDTH = 10;

int gameboard[HIEGHT][WIDTH] = {0};

struct piece{
    int x,y;
} a[4], b[4];

int shapes[7][4]{
    //Shapes Laid out in 2x4 matrix
    1,3,5,7, //Straight block
    2,4,5,7, //Right zig
    3,5,4,6, //Left zig
    3,5,4,7, //T-block
    2,3,5,7, //Right L
    3,5,7,6,  //Left L
    2,3,4,5, //Square
};

int main(){
    sf::RenderWindow game(sf::VideoMode(900, 1600), "Tetris Window");

    sf::Texture squares;
    squares.loadFromFile("tiles.png");

    sf::Sprite block(squares);
    block.setTextureRect(sf::IntRect(0,0,18,18));


    while(game.isOpen()){
        sf::Event e;
        while (game.pollEvent(e)){
            if (e.type == sf::Event::Closed){
                game.close();
            }
        int n = 3;
        for (int i = 0; i<4; i++) {
            a[i].x = shapes[n][i] % 2;
            a[i].y = shapes[n][i] / 2;
        }


        }
        //Set Background
        game.clear(sf::Color::Black);
        for (int i = 0 ; i <4; i++){
            block.setPosition(a[i].x*18,a[i].y*18);
            game.draw(block);
        }
        game.display();
    }


    return 0;
}

//g++ -c tetris.cpp
//g++ tetris.o -o tetris -lsfml-graphics -lsfml-window -lsfml-system