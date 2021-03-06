#include <iostream>
//  g++ chess.cpp  -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
// ./sfml-app
#include <string>
#include <fstream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;

class keys {
public:
    int x = 9;
    int y = 9;
    int team;
    
    Texture texturekey;
    Sprite spritekey;
    enum keytypes { king, queen, bishop, knight, rook, pawn, empt };
    keytypes keytype;
    string keyname;
    void move(int i, int j) {
        x = i;
        y = j;
    }
    virtual vector<vector<int>> posiablemoves(const point**){
        cout << "IN keys" << endl;
    }
};
class point {
public:
    keys* mohre;
};
class King : public keys {
public:
    King(int t) {
        team = t;
        keytype = king;
        if (team == 1) {
            keyname = "KW";
            texturekey.loadFromFile("texture/set800/wking.png", IntRect(0, 0, 100, 100));
        }
        else {
            texturekey.loadFromFile("texture/set800/bking.png", IntRect(0, 0, 100, 100));
            keyname = "KB";
        }
        spritekey.setTexture(texturekey);
        spritekey.setPosition(Vector2f((x*75), (y*75)));
    }
    virtual vector<vector<int>> posiablemoves(const point** myboard){
        int temp_ckeck_empty;
        vector<vector<int>> accessible (8, vector<int>(8,0));
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                temp_ckeck_empty = 1;
                if(myboard[i][j].mohre->team != myboard[x][y].mohre->team){
                    if ((abs(x - i) < 2 and abs(y - j) < 2)){
                        accessible[i][j] = 1;
                    }
                }
            }
        }
        return accessible;
    }
};
class Queen : public keys {
public:
    Queen(int t) {
        team = t;
        keytype = queen;
        if (team == 1) {
            keyname = "QW";
            texturekey.loadFromFile("texture/set800/wqueen.png", IntRect(0, 0, 100, 100));
        }
        else {
            keyname = "QB";
            texturekey.loadFromFile("texture/set800/bqueen.png", IntRect(0, 0, 100, 100));
        }
        spritekey.setTexture(texturekey);
        spritekey.setPosition(Vector2f((x*75), (y*75)));
    }
    virtual vector<vector<int>> posiablemoves(const point** myboard){
        int temp_ckeck_empty;
        vector<vector<int>> accessible (8, vector<int>(8,0));
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                if(myboard[i][j].mohre->team != myboard[x][y].mohre->team){
                    temp_ckeck_empty = 1;
                    if (abs(x-i) == abs(y-j)){
                        if (x < i){
                            if (y < j){
                                for (int l = 1; l < i-x; l++){
                                    if (myboard[x+l][y+l].mohre->keytype != keys::empt){
                                        temp_ckeck_empty = 0;
                                        break;
                                    }
                                }
                            }
                            else if ( y > j){
                                for (int l = 1; l < i-x; l++){
                                    if (myboard[x+l][y-l].mohre->keytype != keys::empt){
                                        temp_ckeck_empty = 0;
                                        break;
                                    }
                                }
                            }
                        }
                        else if (x > i){
                            if (y < j){
                                for (int l = 1; l < x-i; l++){
                                    if (myboard[x-l][y+l].mohre->keytype != keys::empt){
                                        temp_ckeck_empty = 0;
                                        break;
                                    }
                                }
                            }
                            else if ( y > j){
                                for (int l = 1; l < x-i; l++){
                                    if (myboard[x-l][y-l].mohre->keytype != keys::empt){
                                        temp_ckeck_empty = 0;
                                        break;
                                    }
                                }
                            }
                        }
                        if (temp_ckeck_empty == 1){
                            accessible[i][j] = 1;
                        }
                    }
                    if (x == i or y == j){
                        if (x == i){
                            if (y > j){
                                for (int l = y-1; l > j; l--){
                                    if (myboard[x][l].mohre->keytype != keys::empt){
                                        temp_ckeck_empty = 0;
                                        break;
                                    }
                                }
                                if (temp_ckeck_empty == 1){
                                    accessible[i][j] = 1;
                                }
                            }
                            else if (y < j){
                                for (int l = y+1; l < j; l++){
                                    if (myboard[x][l].mohre->keytype != keys::empt){
                                        temp_ckeck_empty = 0;
                                        break;
                                    }
                                }
                                if (temp_ckeck_empty == 1){
                                    accessible[i][j] = 1;
                                }
                            }
                        }
                        else if (y == j){
                            if (x > i){
                                for (int l = x-1; l > i; l--){
                                    if (myboard[l][y].mohre->keytype != keys::empt){
                                        temp_ckeck_empty = 0;
                                        break;
                                    }
                                }
                                if (temp_ckeck_empty == 1){
                                    accessible[i][j] = 1;
                                }
                            }
                            if (x < i){
                                for (int l = x+1; l < i; l++){
                                    if (myboard[l][y].mohre->keytype != keys::empt){
                                        temp_ckeck_empty = 0;
                                        // if (board[i][y].mohre->team != board[x][y].mohre->team){
                                        //     temp_ckeck_empty = 1;
                                        // }
                                        break;
                                    }
                                }
                                if (temp_ckeck_empty == 1){
                                    accessible[i][j] = 1;
                                }
                            }
                            
                        }
                    }
                }
            }
        }
        return accessible;
    }
};
class Bishop : public keys {
public:
    Bishop(int t) {
        team = t;
        keytype = bishop;
        if (team == 1) {
            keyname = "BW";
            texturekey.loadFromFile("texture/set800/wbishop.png", IntRect(0, 0, 100, 100));
        }
        else {
            keyname = "BB";
            texturekey.loadFromFile("texture/set800/bbishop.png", IntRect(0, 0, 100, 100));
        }
        spritekey.setTexture(texturekey);
        spritekey.setPosition(Vector2f((x*75), (y*75)));
    }
    virtual vector<vector<int>> posiablemoves(const point** myboard){
        int temp_ckeck_empty;
        vector<vector<int>> accessible (8, vector<int>(8,0));
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                temp_ckeck_empty = 1;
                if(myboard[i][j].mohre->team != myboard[x][y].mohre->team){
                    if (abs(x-i) == abs(y-j)){
                        if (x < i){
                            if (y < j){
                                for (int l = 1; l < i-x; l++){
                                    if (myboard[x+l][y+l].mohre->keytype != keys::empt){
                                        temp_ckeck_empty = 0;
                                        break;
                                    }
                                }
                            }
                            else if ( y > j){
                                for (int l = 1; l < i-x; l++){
                                    if (myboard[x+l][y-l].mohre->keytype != keys::empt){
                                        temp_ckeck_empty = 0;
                                        break;
                                    }
                                }
                            }
                        }
                        else if (x > i){
                            if (y < j){
                                for (int l = 1; l < x-i; l++){
                                    if (myboard[x-l][y+l].mohre->keytype != keys::empt){
                                        temp_ckeck_empty = 0;
                                        break;
                                    }
                                }
                            }
                            else if ( y > j){
                                for (int l = 1; l < x-i; l++){
                                    if (myboard[x-l][y-l].mohre->keytype != keys::empt){
                                        temp_ckeck_empty = 0;
                                        break;
                                    }
                                }
                            }
                        }
                        if (temp_ckeck_empty == 1){
                            accessible[i][j] = 1;
                        }
                    }
                }
            }
        }
        return accessible;
    }
};
class Knight : public keys {
public:
    Knight(int t) {
        team = t;
        keytype = knight;
        if (team == 1) {
            keyname = "NW";
            texturekey.loadFromFile("texture/set800/wknight.png", IntRect(0, 0, 100, 100));
        }
        else {
            keyname = "NB";
            texturekey.loadFromFile("texture/set800/bknight.png", IntRect(0, 0, 100, 100));
        }
        spritekey.setTexture(texturekey);
        spritekey.setPosition(Vector2f((x*75), (y*75)));
    }
    virtual vector<vector<int>> posiablemoves(const point** myboard){
        int temp_ckeck_empty;
        vector<vector<int>> accessible (8, vector<int>(8,0));
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                temp_ckeck_empty = 1;
                if(myboard[i][j].mohre->team != myboard[x][y].mohre->team){
                    if ((abs(x-i) + abs(y-j) == 3) and (abs((abs(x-i)-abs(y-j))) == 1)){
                        accessible[i][j] = 1;
                    }
                }
            }
        }
        return accessible;
    }
};
class Rook : public keys {
public:
    Rook(int t) {
        team = t;
        keytype = rook;
        if (team == 1) {
            keyname = "RW";
            texturekey.loadFromFile("texture/set800/wrook.png", IntRect(0, 0, 100, 100));
        }
        else {
            keyname = "RB";
            texturekey.loadFromFile("texture/set800/brook.png", IntRect(0, 0, 100, 100));
        }
        spritekey.setTexture(texturekey);
        spritekey.setPosition(Vector2f((x*100), (y*100)));
    }
    virtual vector<vector<int>> posiablemoves(const point** myboard){
        int temp_ckeck_empty;
        vector<vector<int>> accessible (8, vector<int>(8,0));
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                temp_ckeck_empty = 1;
                if(myboard[i][j].mohre->team != myboard[x][y].mohre->team){
                    if (x == i or y == j){
                        if (x == i){
                            if (y > j){
                                for (int l = y-1; l > j; l--){
                                    if (myboard[x][l].mohre->keytype != keys::empt){
                                        temp_ckeck_empty = 0;
                                        break;
                                    }
                                }
                                if (temp_ckeck_empty == 1){
                                    accessible[i][j] = 1;
                                }
                            }
                            else if (y < j){
                                for (int l = y+1; l < j; l++){
                                    if (myboard[x][l].mohre->keytype != keys::empt){
                                        temp_ckeck_empty = 0;
                                        break;
                                    }
                                }
                                if (temp_ckeck_empty == 1){
                                    accessible[i][j] = 1;
                                }
                            }
                        }
                        else if (y == j){
                            if (x > i){
                                for (int l = x-1; l > i; l--){
                                    if (myboard[l][y].mohre->keytype != keys::empt){
                                        temp_ckeck_empty = 0;
                                        break;
                                    }
                                }
                                if (temp_ckeck_empty == 1){
                                    accessible[i][j] = 1;
                                }
                            }
                            if (x < i){
                                for (int l = x+1; l < i; l++){
                                    if (myboard[l][y].mohre->keytype != keys::empt){
                                        temp_ckeck_empty = 0;
                                        // if (board[i][y].mohre->team != board[x][y].mohre->team){
                                        //     temp_ckeck_empty = 1;
                                        // }
                                        break;
                                    }
                                }
                                if (temp_ckeck_empty == 1){
                                    accessible[i][j] = 1;
                                }
                            }
                            
                        }
                    }
                }
            }
        }
        return accessible;
    }
};
class Pawn : public keys {
public:
    Pawn(int t) {
        team = t;
        keytype = pawn;
        if (team == 1) {
            keyname = "PW";
            texturekey.loadFromFile("texture/set800/wpawn.png", IntRect(0, 0, 100, 100));
        }
        else {
            keyname = "PB";
            texturekey.loadFromFile("texture/set800/bpawn.png", IntRect(0, 0, 100, 100));
        }
    }
    virtual vector<vector<int>> posiablemoves(const point** myboard){
        int temp_ckeck_empty;
        vector<vector<int>> accessible (8, vector<int>(8,0));
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                temp_ckeck_empty = 1;
                if(myboard[i][j].mohre->team != myboard[x][y].mohre->team){
                    if (myboard[x][y].mohre->team == 1){
                        if (myboard[i][j].mohre->team == 2 and (x - i == 1)){
                            if (abs(y - j) == 1){
                                accessible[i][j] = 1;
                            }
                        }
                        else{
                            if (x == 6){
                                if (y == j){
                                    if (((i == 4) and (myboard[5][j].mohre->keytype == keys::empt) and (myboard[4][j].mohre->keytype == keys::empt)) or ((i == 5))){
                                    accessible[i][j] = 1;
                                    } 
                                }
                            }
                            else if(x != 6 and y == j and x-i == 1){
                                    accessible[i][j] = 1;
                                }
                            }
                        }
                    else if (myboard[x][y].mohre->team == 2){
                        if (myboard[i][j].mohre->team == 1 and (i - x == 1)){
                            if (abs(y - j) == 1){
                                accessible[i][j] = 1;
                            }
                        }
                        else{
                            if (x == 1){
                                if (y == j){
                                    if (((i == 3) and (myboard[2][j].mohre->keytype == keys::empt)) or ((i == 2))){
                                    accessible[i][j] = 1;
                                    }
                                }
                            }
                            else if(x != 1 and y == j and i-x == 1){
                                    accessible[i][j] = 1;
                            }
                        }
                    }
                }
            }
        }
        return accessible;
    }
};
class Empty : public keys {
public:
    Empty() {
        team = 0;
        keytype = empt;
        keyname = "--";
    }

};
class selectedCells{
public:
    int x, y;

    selectedCells(int x1, int y1){
        x = x1 * 100 + 10; 
        y = y1 * 100 + 10;
    }
};
class defboard {
public:
    int mouseclicked = 0;
    int kings[3][3] = {{0,0,0}}; // {x_positon, y_positin, check & mate}
    keys* tempemohre;
    defboard() {
        board = new point * [8];
        for (int i = 0; i < 8; i++) {
            board[i] = new point[8];
        }
    }
    point** board;
    void printchess() {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                cout << board[i][j].mohre->keyname << " ";
            }
            cout << '\n';
        }
        cout << '\n';
    }
    void getboard(){
        ifstream inputFile;
        inputFile.open("input.text");
        //if (!inputFile){
        //    cout << "we fucked up :(" << endl;
        //}
        string temp_input;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                inputFile >> temp_input;
                if (temp_input == "--") {
                    board[i][j].mohre = new Empty;
                }
                else if (temp_input[0] == 'K') {
                    if (temp_input[1] == 'W') {
                        board[i][j].mohre = new King(1);
                        kings[1][0] = i;
                        kings[1][1] = j;
                    }
                    else {
                        board[i][j].mohre = new King(2);
                        kings[2][0] = i;
                        kings[2][1] = j;
                    }
                }
                else if (temp_input[0] == 'Q') {
                    if (temp_input[1] == 'W') {
                        board[i][j].mohre = new Queen(1);
                    }
                    else {
                        board[i][j].mohre = new Queen(2);
                    }
                }
                else if (temp_input[0] == 'B') {
                    if (temp_input[1] == 'W') {
                        board[i][j].mohre = new Bishop(1);
                    }
                    else {
                        board[i][j].mohre = new Bishop(2);
                    }
                }

                else if (temp_input[0] == 'N') {
                    if (temp_input[1] == 'W') {
                        board[i][j].mohre = new Knight(1);
                    }
                    else {
                        board[i][j].mohre = new Knight(2);
                    }
                }
                else if (temp_input[0] == 'R') {
                    if (temp_input[1] == 'W') {
                        board[i][j].mohre = new Rook(1);
                    }
                    else {
                        board[i][j].mohre = new Rook(2);
                    }
                }
                else if (temp_input[0] == 'P') {
                    if (temp_input[1] == 'W') {
                        board[i][j].mohre = new Pawn(1);
                    }
                    else {
                        board[i][j].mohre = new Pawn(2);
                    }
                }
                board[i][j].mohre->x = i;
                board[i][j].mohre->y = j;
            }
        }
        // cout << "White " << checkkings(1) << endl;
        // cout << "Black " << checkkings(2) << endl;
    }
    void move(int i, int j, int x, int y) {
        // cout << board[i][j].mohre->keyname << " -> " << board[x][y].mohre->keyname << endl;
        tempemohre = board[x][y].mohre;
        board[x][y].mohre = board[i][j].mohre;
        board[i][j].mohre = new Empty;
        // cout << tempemohre->keyname << endl;
        if (board[y][x].mohre->keytype == keys::king){
            kings[board[x][y].mohre->team][0] = x;
            kings[board[x][y].mohre->team][1] = y;
        }
    }
    void undomove(int i, int j, int x, int y){
        // cout << board[i][j].mohre->keyname << " -> " << board[x][y].mohre->keyname << endl;
        board[i][j].mohre = board[x][y].mohre;
        board[x][y].mohre = tempemohre;
        if (board[i][j].mohre->keytype == keys::king){
            kings[board[i][j].mohre->team][0] = i;
            kings[board[i][j].mohre->team][1] = j;
        }
    }
    vector<vector<int>> posiablemove(int x, int y) {
        int temp_ckeck_empty;
        vector<vector<int>> accessible (8, vector<int>(8,0));
        return accessible;
    }
    vector<vector<int>> checkmove(int x, int y){
        vector<vector<int>> accessibles (8, vector<int>(8,0));
        accessibles = board[x][y].mohre->posiablemoves(board);
        for (int k = 0; k < 8; k++){
            for (int l = 0; l < 8; l++){
                if (accessibles[k][l] == 1){
                    move(x, y, k, l);
                    if(checkkings(board[k][l].mohre->team) == 1){
                        accessibles[k][l] = 0;
                    }
                    undomove(x, y, k, l);
                }
            }
        }
        return accessibles;
    } 
    int checkkings(int team){
        vector<vector<int>> accessibles2 (8, vector<int>(8,0));
        for(int i=0; i < 8; i++){
            for(int j=0; j < 8; j++){
                if((board[i][j].mohre->keytype != keys::empt) and (board[i][j].mohre->team != team)){
                    accessibles2 = posiablemove(i,j);
                    if(accessibles2[kings[team][0]][kings[team][1]] == 1){
                        return 1;
                    }
                }
            }
        }
        return 0;
    }
        
    // void mousemove(Vector2i mousestate){
    //     int tx = mousestate.y;
    //     int ty = mousestate.x;
    //     mousex = (tx-(tx%100))/100;
    //     mousey = (ty-(ty%100))/100;
    //     selectedCells selectedcell(mousex, mousey);
    //     cout << mousex << "-" << mousey << endl;
    //     }
        // else {
        //     mouseclicked = 0;
        //     move (mousex , mousey , ((tx-(tx%100))/100), ((ty-(ty%100))/100));W
    // int cellckeck(int i, int j) {
    //     if (board[i][j].keytype == 0) {
    //         return 0;
    //     }
    //     if (board[i][j].team == 1) {
    //         return 1;
    //     }
    //     if (board[i][j].team == 2) {
    //         return 2;
    //     }
    // }
};
class GraphicCore{
public:
    void runGraphic(defboard myboard){
        RenderWindow window(VideoMode(800 ,800), "My Chess :)", Style::Titlebar | Style::Close);
        //CircleShape shape(50);
        window.setFramerateLimit(60);
        Texture textureboard;
        textureboard.loadFromFile("texture/set800/boardblue.jpg", IntRect(0, 0, 800, 800));
        Sprite spriteboard;
        spriteboard.setTexture(textureboard);
        RectangleShape selectioncell1(Vector2f((86), (86)));
        selectioncell1.setOutlineThickness(7);
        selectioncell1.setOutlineColor(Color(0, 255, 0, 255));
        selectioncell1.setFillColor(Color(0, 0, 0, 0));
        selectioncell1.setPosition(Vector2f((1900), (1900)));
        Texture temp4; 
        vector<vector<int>> accessible_cells;
        Sprite temp4sprite;
        // CircleShape accessible_cell(25);
        // accessible_cell.setFillColor(Color(0, 250, 0, 170));
        // accessible_cell.setPosition(Vector2f((3*100 + 25), (3*100 + 25)));
        int temp2[4];
        int mousecounter = 0;
        int turnteam = 2;
        int tempmousex;
        int tempmousey;
        //cout << myboard[0][0].mohre->keyname << endl;
        while (window.isOpen()){
            Event event;
            window.clear();
            window.draw(spriteboard);
            while (window.pollEvent(event))
                if (event.type == Event::Closed)
                    window.close();
                if (event.type == Event::MouseButtonPressed){
                    if (Mouse::isButtonPressed(Mouse::Left)){
                        Vector2i mousestate = Mouse::getPosition(window);
                        int mousey = (mousestate.x-(mousestate.x%100))/100;
                        int mousex = (mousestate.y-(mousestate.y%100))/100;
                        // cout << mousex << " " << mousey << endl;
                        if ((mousex >= 0 and mousex < 8) and ( mousey >= 0 and mousey < 8)){
                            //cout << "Enter 1" << endl;
                            if (mousecounter == 0){
                                //cout << "Enter 2" << endl;
                                if ((myboard.board[mousex][mousey].mohre->keyname != "--") and (myboard.board[mousex][mousey].mohre->team == turnteam)){
                                    //cout << "Enter 3" << endl;
                                    selectioncell1.setPosition(Vector2f((mousey*100 + 7), (mousex*100 + 7)));
                                    tempmousex = mousex;
                                    tempmousey = mousey;
                                    // cout << "cell selected" << endl;
                                    accessible_cells = myboard.checkmove(mousex, mousey);
                                    mousecounter = 1;
                                }
                            }
                            else {
                                //cout << "Enter 4" << endl;
                                if (tempmousex != mousex or tempmousey != mousey){
                                    if (accessible_cells[mousex][mousey] == 1){
                                        //cout << "Enter 5" << endl;
                                        // cout << tempmousex << " " << tempmousey << " -> " << mousey << " " << mousex << endl;
                                        myboard.move(tempmousex, tempmousey, mousex, mousey);
                                        //myboard.checkkings(1);
                                        // cout << "end of move" << endl;
                                        mousecounter = 0;
                                        selectioncell1.setPosition(Vector2f((1900), (1900)));
                                        if (turnteam == 1){
                                            turnteam = 2;
                                            }
                                        else{
                                            turnteam = 1;
                                            }
                                        // int temp5;
                                        // cin >> temp5;
                                        // cout << "next move" << endl;
                                    }
                                }
                            }
                        }
                    }
                    if (Mouse::isButtonPressed(Mouse::Right)){
                        mousecounter = 0;
                        selectioncell1.setPosition(Vector2f((1900), (1900)));
                        myboard.printchess();
                    }
                    if (Mouse::isButtonPressed(Mouse::Middle)){
                        mousecounter = 0;
                        turnteam = 1;
                        myboard.getboard();
                        myboard.printchess();
                    }
                }
            for (int i = 0; i < 8; i++){
                for (int j = 0; j < 8; j++){
                    if ( myboard.board[i][j].mohre->keyname != "--"){
                        temp4 = myboard.board[i][j].mohre->texturekey;
                        temp4sprite.setTexture(temp4);
                        temp4sprite.setPosition(Vector2f((j*100), (i*100)));
                        window.draw(temp4sprite);
                    }
                }
            }
            if (mousecounter == 1){
                for (int i = 0; i < 8; i++){
                    for (int j = 0; j < 8; j++){
                        if (accessible_cells[i][j] == 1){
                            CircleShape accessible_cell(25);
                            accessible_cell.setFillColor(Color(0, 255, 0, 200));
                            accessible_cell.setPosition(Vector2f((j*100 + 25), (i*100 + 25)));
                            window.draw(accessible_cell);
                        }
                    }
                }
            }
            window.draw(selectioncell1);
            window.display();
            // cout << "Enter the key origin and destination. for example: i j x y" << endl;
            // for (int i = 0; i < 4; i++) {
            //     cin >> temp2[i];
            // }
            // myboard.move(temp2[0]-1, temp2[1]-1, temp2[2]-1, temp2[3]-1);
            // myboard.printchess();
        }
    }

};
int main() {
    cout << " -- starting -- \n";
    defboard mainboard;
    mainboard.getboard();
    // ifstream inputFile;
    // inputFile.open("input.text");
    // if (!inputFile){
    //     cout << "we fucked up :(" << endl;
    // }
    // void getboard(){
    //     string temp_input;
    //     for (int i = 0; i < 8; ++i) {
    //         for (int j = 0; j < 8; ++j) {
    //             inputFile >> temp_input;
    //             if (temp_input == "--") {
    //                 mainboard.board[i][j].mohre = new Empty;
    //             }
    //             else if (temp_input[0] == 'K') {
    //                 if (temp_input[1] == 'W') {
    //                     mainboard.board[i][j].mohre = new King(1);
    //                 }
    //                 else {
    //                     mainboard.board[i][j].mohre = new King(2);
    //                 }
    //             }
    //             else if (temp_input[0] == 'Q') {
    //                 if (temp_input[1] == 'W') {
    //                     mainboard.board[i][j].mohre = new Queen(1);
    //                 }
    //                 else {
    //                     mainboard.board[i][j].mohre = new Queen(2);
    //                 }
    //             }
    //             else if (temp_input[0] == 'B') {
    //                 if (temp_input[1] == 'W') {
    //                     mainboard.board[i][j].mohre = new Bishop(1);
    //                 }
    //                 else {
    //                     mainboard.board[i][j].mohre = new Bishop(2);
    //                 }
    //             }

    //             else if (temp_input[0] == 'N') {
    //                 if (temp_input[1] == 'W') {
    //                     mainboard.board[i][j].mohre = new Knight(1);
    //                 }
    //                 else {
    //                     mainboard.board[i][j].mohre = new Knight(2);
    //                 }
    //             }
    //             else if (temp_input[0] == 'R') {
    //                 if (temp_input[1] == 'W') {
    //                     mainboard.board[i][j].mohre = new Rook(1);
    //                 }
    //                 else {
    //                     mainboard.board[i][j].mohre = new Rook(2);
    //                 }
    //             }
    //             else if (temp_input[0] == 'P') {
    //                 if (temp_input[1] == 'W') {
    //                     mainboard.board[i][j].mohre = new Pawn(1);
    //                 }
    //                 else {
    //                     mainboard.board[i][j].mohre = new Pawn(2);
    //                 }
    //             }
    //             mainboard.board[i][j].mohre->x = i;
    //             mainboard.board[i][j].mohre->y = j;
    //         }
    //     }
    // }
    // cout << '\n';
    GraphicCore maingraphics;
    maingraphics.runGraphic(mainboard);
    // int temp2[4];
    //cout << "Enter the key origin and destination. for example: i j x y" << endl;
    // while (1) {
    //     for (int i = 0; i < 4; i++) {
    //         cin >> temp2[i];
    //     }
    //     cout << "Enter the key origin and destination. for example: i j x y" << endl;
    //     mainboard.move(temp2[0]-1, temp2[1]-1, temp2[2]-1, temp2[3]-1);
    //     mainboard.printchess();
    //     maingraphics.runGraphic(mainboard.board);
    // }
    cout << "end of program" << endl;
    return 0;
}