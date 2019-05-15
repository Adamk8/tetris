#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int HIEGHT = 20;
const int WIDTH = 10;

int gameboard[HIEGHT][WIDTH] = {0};

struct piece{
    int x,y;
} position[4], b[4];

int shapes[7][4]{
    //Shapes Laid out in 2x4 matrix
    1,3,5,7, //I piece
    2,4,5,7, //Right zig
    3,5,4,6, //Left zig
    3,5,4,7, //T-block
    2,3,5,7, //Right L
    3,5,7,6,  //Left L
    2,3,4,5, //Square
};

bool check(){
    for (int i = 0; i< 4; i++){
        if (position[i].x < 0 || position[i].x >= WIDTH || position[i].y >= HIEGHT ) return 0;
        else if (gameboard[position[i].y][position[i].x]) return 0;
    }
    return 1;
}

int main(){
    //set random seed
    srand(time(0));
    
    //create game window
    RenderWindow game(VideoMode(320, 480), "Tetris Window");
    
    //Load textures
    Texture squares;
    squares.loadFromFile("tiles.png");
    Sprite block(squares);
    block.setTextureRect(IntRect(0,0,18,18));

    int movement =  0, colour = 1;
    bool rotate = 0;
    float timer = 0, delay = 0;

    Clock clock;

    while(game.isOpen()){
        Event e;
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        while (game.pollEvent(e)){

            if (e.type == Event::Closed){
                game.close();  
            }
            //Keyboard Input Actions 
            if (e.type == Event::KeyPressed){
                if (e.key.code == Keyboard::Up) rotate = true;
                else if (e.key.code == Keyboard::Left) movement = -1;
                else if (e.key.code == Keyboard::Right) movement = 1;
            }
            if (Keyboard::isKeyPressed(Keyboard::Down))delay = 0.05;

            //Actions converted into commands
            //lateral movement 
            for (int i = 0 ; i < 4; i++){
                b[i] = position[i];
                position[i].x += movement;
            }   
            if (!check())for (int i = 0; i <4; i++)position[i] = b[i];

            //rotate pieces
            if (rotate){

                piece center = position[1];
                for (int i =0; i < 4; i++){
                    int x = position[i].y - center.y;
                    int y = position[i].x - center.x;
                    position[i].x = center.x - x;
                    position[i].y = center.y + y;
                }
                if (!check())for (int i = 0; i <4; i++)position[i] = b[i];
            }
            //Fallling mechanic
            if (timer > delay){
                for (int i=0; i < 4; i++){
                    b[i] = position[i];       
                    position[i].y += 1;
                }
                if (!check()){
                    for (int i = 0; i <4; i++)gameboard[b[i].y][b[i].x] = colour;
                    colour = 1 + rand()%7;
                    int n = rand()%7;
                    for (int i = 0; i <4; i++){
                        position[i].x = shapes[n][i] % 2;
                        position[i].y = shapes[n][i] / 2;
                    }
                }
                timer = 0;
            }

        //Reset controls
        movement = 0;
        rotate = 0;
        delay = 0.3;

        }

        //Draw Graphics
        game.clear(Color::Black);
        for (int i = 0; i <HIEGHT; i++){
            for (int j = 0; j < WIDTH; j++){
                if (gameboard[i][j] == 0 )continue;
                block.setTextureRect(IntRect(gameboard[i][j]*18,0,18,18));
                block.setPosition(j*18,i*18);
                game.draw(block);
            }
        }
        
        //Create Blocks
        for (int i =0; i < 4; i++){
            block.setTextureRect(IntRect(colour+18,0,18,18));
            block.setPosition(position[i].x*18, position[i].y*18);
            game.draw(block);
        }
        game.display();
    }


    return 0;
}

//g++ -c tetris.cpp
//g++ tetris.o -o tetris -l-graphics -l-window -l-system
