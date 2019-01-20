#pragma once

#include "ofMain.h"
#include "ofxGif.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void drawGame();
        void drawImageScreen(int index);
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void movePacman(int direction);
        void drawPacman();
        void collectCoin();
        void moveEnemies();
        void createWallLine(char direction, int x, int y, int length, bool obstacle = true);
        void createCoins(char direction, int x, int y, int length);
        bool hasCollision(glm::vec3 position);
        int manhattanDistance(glm::vec3 A, glm::vec3 B);
        void createEnemy(int x, int y);
    
        // Library
        ofxGIF::fiGifLoader characterGif;
        ofxGIF::fiGifLoader coinGif;
        ofxGIF::fiGifLoader enemyGif;
		
};
