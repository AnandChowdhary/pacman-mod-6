#include "iostream"
#include "ofApp.h"
#include <stdio.h>
#include <vector>

using namespace std;

glm::vec3 pacmanPosition;

std::vector<glm::vec3> obstacles = {};
std::vector<glm::vec3> coins = {};

int currentDirection, previousDirection;
int points = 0;
int size = 25;
int rows = 31;
int columns = 21;
int currentTenths = 0;
int animationIndex = 0;
int coinIndex = 0;

ofImage coinSprite;
ofImage block;

//--------------------------------------------------------------
void ofApp::setup(){
    
    // Background color
    ofBackground(90, 143, 243);

    pacmanPosition.x = 10;
    pacmanPosition.y = 14;

    currentDirection = 1;
    previousDirection = 1;
    
    // Load images
    characterGif.load("images/mario-walking.gif");
    coinGif.load("images/coin.gif");
    block.load("images/block.png");
    
    // Add obstacles
    ofApp::createWallLine('h', 1, 1, 19); //Upper wall
    ofApp::createWallLine('v', 1, 1, 10); //Left Border
    ofApp::createWallLine('h', 1, 10, 4);
    ofApp::createWallLine('v', 4, 10, 4);
    ofApp::createWallLine('h', 1, 13, 4);
    ofApp::createWallLine('h', 1, 15, 4);
    ofApp::createWallLine('v', 4, 15, 4);
    ofApp::createWallLine('h', 1, 18, 4);
    ofApp::createWallLine('v', 1, 18, 12);
    ofApp::createWallLine('h', 1, 29, 19);
    
    ofApp::createWallLine('v', 19, 1, 10); //Right Border
    ofApp::createWallLine('h', 15, 10, 4);
    ofApp::createWallLine('v', 15, 10, 4);
    ofApp::createWallLine('h', 15, 13, 4);
    ofApp::createWallLine('h', 15, 15, 4);
    ofApp::createWallLine('v', 15, 15, 4);
    ofApp::createWallLine('h', 15, 18, 4);
    ofApp::createWallLine('v', 19, 18, 12);
    
    ofApp::createWallLine('h', 3, 3, 2); //Upper obstacles
    ofApp::createWallLine('h', 3, 4, 2);
    ofApp::createWallLine('h', 6, 3, 3);
    ofApp::createWallLine('h', 6, 4, 3);
    ofApp::createWallLine('v', 10, 2, 3);
    ofApp::createWallLine('h', 12, 3, 3);
    ofApp::createWallLine('h', 12, 4, 3);
    ofApp::createWallLine('h', 16, 3, 2);
    ofApp::createWallLine('h', 16, 4, 2);

    for (int i = 2; i < columns - 2; i++) {
        for (int j = 2; j < rows - 2; j++) {
            int hasSomething = false;
            for (glm::vec3 obstacle : obstacles) {
                if (obstacle.x == i && obstacle.y == j) hasSomething = true;
            }
            if (!hasSomething && (rand() % 3 + 1) == 3) {
                glm::vec3 newCoin;
                newCoin.x = i;
                newCoin.y = j;
                coins.push_back(newCoin);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::createWallLine(char direction, int x, int y, int length, bool obstacle){
    for (int i = 0; i < length; i++) {
        glm::vec3 newObstacle;
        int updatedX = x;
        int updatedY = y;
        if (direction == 'h') updatedX += i;
        if (direction == 'v') updatedY += i;
        newObstacle.x = updatedX;
        newObstacle.y = updatedY;
        if (obstacle) {
            obstacles.push_back(newObstacle);
        } else {
            coins.push_back(newObstacle);
        }
    }
}

//--------------------------------------------------------------
void ofApp::createCoins(char direction, int x, int y, int length){
    ofApp::createWallLine(direction, x, y, length, false);
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){

    // Draw grid
    ofSetColor(75, 121, 209);
    ofSetLineWidth(1);
    ofNoFill();
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            glm::vec3 position;
            position.x = i * size;
            position.y = j * size;
            ofDrawRectangle(position, size, size);
        }
    }

    // Draw Pacman
    ofApp::drawPacman();

    // Move Pacman, ten times per second
    // ofGetElapsedTimef(); returns a float, convert it to int
    int elapsedTenths = (int)(ofGetElapsedTimeMillis() / 100);
    if (elapsedTenths > currentTenths) {
        currentTenths++;
        ofApp::movePacman(currentDirection);
        animationIndex++;
        if (animationIndex > characterGif.pages.size() - 1) animationIndex = 0;
        coinIndex++;
        if (coinIndex > coinGif.pages.size() - 1) coinIndex = 0;
    }

    // Make an obstacle
    for (glm::vec3 obstacle : obstacles) {
        glm::vec3 trueObstaclePosition;
        trueObstaclePosition.x = obstacle.x * size;
        trueObstaclePosition.y = obstacle.y * size;
        block.draw(trueObstaclePosition, size, size);
    }

    // The following fixes a bug with RGB transforming to BGR in the library
    // Source: https://forum.openframeworks.cc/t/ofimage-from-gif-displays-with-blue-tint/22989/6
    /* fix */ ofSetColor(255, 255, 255, 255);
    /* fix */ coinSprite = coinGif.pages[coinIndex];
    /* fix */ ofPixels pix = coinSprite.getPixels();
    /* fix */ coinSprite.setFromPixels(pix);
    
    // Make a coin
    int coinPadding = 5;
    for (glm::vec3 coin : coins) {
        glm::vec3 trueObstaclePosition;
        trueObstaclePosition.x = coin.x * size + coinPadding;
        trueObstaclePosition.y = coin.y * size + coinPadding;
        //coinGif.pages[coinIndex].draw(trueObstaclePosition.x, trueObstaclePosition.y, size, size);
        coinSprite.draw(trueObstaclePosition.x, trueObstaclePosition.y, size - coinPadding * 2, size - coinPadding * 2);
    }

}

void ofApp::drawPacman() {
    // The following fixes a bug with RGB transforming to BGR in the library
    // Source: https://forum.openframeworks.cc/t/ofimage-from-gif-displays-with-blue-tint/22989/6
    /* fix */ ofSetColor(255, 255, 255, 255);
    /* fix */ ofImage img = characterGif.pages[animationIndex];
    /* fix */ ofPixels pix = img.getPixels();
    /* fix */ img.setFromPixels(pix);
    glm::vec3 truePacmanPosition;
    truePacmanPosition.x = pacmanPosition.x * size;
    truePacmanPosition.y = pacmanPosition.y * size;
    img.draw(truePacmanPosition.x, truePacmanPosition.y, size, size);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    previousDirection = currentDirection;
    switch (key) {
        case 57356:
            // Move left
            currentDirection = 3;
            break;
        case 57357:
            // Move up
            currentDirection = 0;
            break;
        case 57358:
            // Move right
            currentDirection = 1;
            break;
        case 57359:
            // Move down
            currentDirection = 2;
            break;
    }
}

//--------------------------------------------------------------
bool ofApp::hasCollision(glm::vec3 position){
    int collisionDetected = false;
    for (glm::vec3 obstacle : obstacles) {
        if (obstacle.x == position.x && obstacle.y == position.y) collisionDetected = true;
    }
    return collisionDetected;
}

//--------------------------------------------------------------
void ofApp::movePacman(int direction){
    glm::vec3 testPosition;
    switch (direction) {
        case 0:
            // Move Pacman up
            testPosition.x = pacmanPosition.x;
            testPosition.y = pacmanPosition.y - 1;
            break;
        case 1:
            // Move Pacman right
            testPosition.x = pacmanPosition.x + 1;
            testPosition.y = pacmanPosition.y;
            break;
        case 2:
            // Move Pacman down
            testPosition.x = pacmanPosition.x;
            testPosition.y = pacmanPosition.y + 1;
            break;
        default:
            // Move Pacman left
            testPosition.x = pacmanPosition.x - 1;
            testPosition.y = pacmanPosition.y;
            break;
    }
    if (
        testPosition.x < columns &&
        testPosition.y < rows &&
        testPosition.x > -1 &&
        testPosition.y > -1 &&
        !ofApp::hasCollision(testPosition)
    ) {
        pacmanPosition.x = testPosition.x;
        pacmanPosition.y = testPosition.y;
    }
    // Collect coins
    ofApp::collectCoin();
    // If you go all the way right, you reach left
    if (testPosition.x == columns) pacmanPosition.x = 0;
    if (testPosition.y == rows) pacmanPosition.y = 0;
    if (testPosition.x == -1) pacmanPosition.x = columns;
    if (testPosition.y == -1) pacmanPosition.y = rows;

}

//--------------------------------------------------------------
void ofApp::collectCoin(){
    int coinIndex = 0;
    for (glm::vec3 coin : coins) {
        if (coin.x == pacmanPosition.x && coin.y == pacmanPosition.y) {
            points++;
            coins.erase(coins.begin() + coinIndex);
            break;
        }
        coinIndex++;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------ofSetLineWidth(1);------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
