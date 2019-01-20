#include "iostream"
#include "ofApp.h"
#include <stdio.h>
#include <vector>

using namespace std;

glm::vec3 pacmanPosition;

std::vector<glm::vec3> obstacles = {};

int currentDirection, previousDirection;
int size = 25;
int rows = 31;
int columns = 21;
int currentSeconds = 0;
int animationIndex = 0;

//--------------------------------------------------------------
void ofApp::setup(){
    pacmanPosition.x = 10;
    pacmanPosition.y = 14;

    currentDirection = 1;
    previousDirection = 1;
    
    // Load character image
    gifloader.load("images/mario-walking.gif");
    
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
}

//--------------------------------------------------------------
void ofApp::createWallLine(char direction, int x, int y, int length){
    for (int i = 0; i < length; i++) {
        glm::vec3 newObstacle;
        int updatedX = x;
        int updatedY = y;
        if (direction == 'h') updatedX += i;
        if (direction == 'v') updatedY += i;
        newObstacle.x = updatedX;
        newObstacle.y = updatedY;
        obstacles.push_back(newObstacle);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){

    // Draw grid
    ofSetColor(150, 150, 150);
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

    // Move Pacman, once per second
    // ofGetElapsedTimef(); returns a float, convert it to int
    int elapsedSeconds = (int)(ofGetElapsedTimeMillis() / 100);
    if (elapsedSeconds > currentSeconds) {
        currentSeconds++;
        animationIndex++;
        if (animationIndex > gifloader.pages.size() - 1) animationIndex = 0;
        ofApp::movePacman(currentDirection);
    }

    // Make an obstacle
    ofSetColor(50, 50, 50);
    ofFill();
    // (sizeof(obstacles) / sizeof(obstacles[0])) is used to get the true size of the array
    for (glm::vec3 obstacle : obstacles) {
        glm::vec3 trueObstaclePosition;
        trueObstaclePosition.x = obstacle.x * size;
        trueObstaclePosition.y = obstacle.y * size;
        ofDrawRectangle(trueObstaclePosition, size, size);
    }

}

void ofApp::drawPacman() {
    // The following fixes a bug with RGB transforming to BGR in the library
    // Source: https://forum.openframeworks.cc/t/ofimage-from-gif-displays-with-blue-tint/22989/6
    /* fix */ ofSetColor(255, 255, 255, 255);
    /* fix */ ofImage img = gifloader.pages[animationIndex];
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
    } else {
//        currentDirection = previousDirection;
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
