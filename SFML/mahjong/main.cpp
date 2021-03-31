#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>
#include <iostream>
#include <stack>
using namespace sf;
using namespace std;

const int screen_width = 1216;
const int screen_height = 576;
const int tile_width = 64;
const int tile_height = 96;
const int h_margin = 64;
const int v_margin = 96;
const string PATH = "images/";

vector<vector<int>> showingMahjong = vector<vector<int>>(4, vector<int>(17, 0));
vector<vector<int>> realMahjong = vector<vector<int>>(4, vector<int>(17, 0));

// initialize the random mahjong pair
void init(){
    for(int i = 1; i < 35; i++){
        int row;
        int col;
        // mahjong 1
        do{
            row = rand() % 4;
            col = rand() % 17;
        }while(realMahjong[row][col] != 0);
        realMahjong[row][col] = i;

        // mahjong 2
        do{
            row = rand() % 4;
            col = rand() % 17;
        }while(realMahjong[row][col] != 0);
        realMahjong[row][col] = i;
    }

    for(auto i : realMahjong){
        for(int j : i){
            cout << j << " ";
        }
        cout << endl;
    }
}

void drawMahjong(RenderWindow& window){
    for(int i = 0; i < showingMahjong.size(); i++){
        for(int j = 0; j < showingMahjong[i].size(); j++){
            int type = showingMahjong[i][j];

            RectangleShape mahjong(Vector2f(tile_width, tile_height));
            Texture texture;

            if(type == 0){
                texture.loadFromFile(PATH + "back.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 1){
                texture.loadFromFile(PATH + "man1.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 2){
                texture.loadFromFile(PATH + "man2.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 3){
                texture.loadFromFile(PATH + "man3.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 4){
                texture.loadFromFile(PATH + "man4.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 5){
                texture.loadFromFile(PATH + "man5.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 6){
                texture.loadFromFile(PATH + "man6.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 7){
                texture.loadFromFile(PATH + "man7.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 8){
                texture.loadFromFile(PATH + "man8.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 9){
                texture.loadFromFile(PATH + "man9.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 10){
                texture.loadFromFile(PATH + "pin1.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 11){
                texture.loadFromFile(PATH + "pin2.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 12){
                texture.loadFromFile(PATH + "pin3.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 13){
                texture.loadFromFile(PATH + "pin4.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 14){
                texture.loadFromFile(PATH + "pin5.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 15){
                texture.loadFromFile(PATH + "pin6.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 16){
                texture.loadFromFile(PATH + "pin7.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 17){
                texture.loadFromFile(PATH + "pin8.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 18){
                texture.loadFromFile(PATH + "pin9.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 19){
                texture.loadFromFile(PATH + "sou1.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 20){
                texture.loadFromFile(PATH + "sou2.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 21){
                texture.loadFromFile(PATH + "sou3.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 22){
                texture.loadFromFile(PATH + "sou4.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 23){
                texture.loadFromFile(PATH + "sou5.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 24){
                texture.loadFromFile(PATH + "sou6.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 25){
                texture.loadFromFile(PATH + "sou7.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 26){
                texture.loadFromFile(PATH + "sou8.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 27){
                texture.loadFromFile(PATH + "sou9.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 28){
                texture.loadFromFile(PATH + "ton.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 29){
                texture.loadFromFile(PATH + "nan.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 30){
                texture.loadFromFile(PATH + "shaa.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 31){
                texture.loadFromFile(PATH + "pei.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 32){
                texture.loadFromFile(PATH + "chun.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 33){
                texture.loadFromFile(PATH + "hatsu.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }else if(type == 34){
                texture.loadFromFile(PATH + "front.png");
                mahjong.setTexture(&texture);
                mahjong.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
            }

            if((type != 0) && (type != 34)){
                Texture bgTexture;
                bgTexture.loadFromFile(PATH + "front.png");
                RectangleShape bg(Vector2f(tile_width, tile_height));
                bg.setTexture(&bgTexture);
                bg.setPosition(j*tile_width+h_margin, i*tile_height+v_margin);
                window.draw(bg);
            }

            window.draw(mahjong);
        }
    }
}

int main(){
    RenderWindow window(VideoMode(screen_width, screen_height), "Mahjong");

    init();

    // set background
    Texture backgroundTexture;
    backgroundTexture.loadFromFile(PATH + "background.png");
    RectangleShape background(Vector2f(screen_width, screen_height));
    background.setPosition(0, 0);
    background.setTexture(&backgroundTexture);

    // game variables
    bool clicked = false;
    float showTime = 0.5;
    stack<int> mahjongSelected;
    stack<pair<int, int>> coordinates;

    while(window.isOpen()){
        Event e;

        while(window.pollEvent(e)){
            if(e.type == e.Closed){
                window.close();
            }
            if(Keyboard::isKeyPressed(Keyboard::Escape)){
                window.close();
            }
            if(e.type == e.MouseButtonReleased){
                if(e.mouseButton.button == Mouse::Left){
                    clicked = false;
                }
            }
            if(e.type == e.MouseButtonPressed){
                if((e.mouseButton.button == Mouse::Left) && !clicked){
                    int x = Mouse::getPosition(window).x;
                    int y = Mouse::getPosition(window).y;

                    if((y - v_margin >= 0) && (x - h_margin >= 0)){
                        int row = (y - v_margin) / tile_height;
                        int col = (x - h_margin) / tile_width;

                        if((row < 4) && (col < 17) && (showingMahjong[row][col] == 0)){
                            showingMahjong[row][col] = realMahjong[row][col];

                            mahjongSelected.push(realMahjong[row][col]);
                            coordinates.push(pair(row, col));

                            if(mahjongSelected.size() == 2){
                                int first = mahjongSelected.top();
                                mahjongSelected.pop();
                                int second = mahjongSelected.top();
                                mahjongSelected.pop();

                                if(second != first){
                                    Clock clock;
                                    clock.restart();

                                    float time = clock.getElapsedTime().asSeconds();
                                    while(time < showTime){
                                        time = clock.getElapsedTime().asSeconds();
                                        window.clear();
                                        window.draw(background);
                                        drawMahjong(window);
                                        window.display();
                                    }

                                    pair<int, int> coordinate1 = coordinates.top();
                                    coordinates.pop();
                                    showingMahjong[coordinate1.first][coordinate1.second] = 0;

                                    pair<int, int> coordinate2 = coordinates.top();
                                    coordinates.pop();
                                    showingMahjong[coordinate2.first][coordinate2.second] = 0;
                                }
                            }
                        }
                    }

                    clicked = true;
                }
            }
        }

        window.clear(Color::White);

        window.draw(background);
        drawMahjong(window);

        window.display();
    }
}
