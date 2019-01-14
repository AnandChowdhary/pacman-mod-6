#include "iostream"
#include "ofApp.h"
#include <stdio.h>

glm::vec3 pacmanPosition;

//--------------------------------------------------------------
void ofApp::setup(){
    pacmanPosition.x = 0;
    pacmanPosition.y = 0;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
int size = 50;
int rows = 15;
int columns = 20;
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
    ofSetColor(150, 0, 0);
    ofFill();
    glm::vec3 truePacmanPosition;
    truePacmanPosition.x = pacmanPosition.x * size;
    truePacmanPosition.y = pacmanPosition.y * size;
    ofDrawRectangle(truePacmanPosition, size, size);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch (key) {
        case 57356:
            // Move left
            if (pacmanPosition.x > 0) pacmanPosition.x--;
            break;
        case 57357:
            // Move up
            if (pacmanPosition.y > 0) pacmanPosition.x--;
            break;
        case 57358:
            // Move right
            if (pacmanPosition.x < rows) pacmanPosition.x++;
            break;
        case 57359:
            // Move down
            if (pacmanPosition.y < columns) pacmanPosition.x++;
            break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
