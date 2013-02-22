#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    
	ofBackground(255,255,0);
    
    //declare a new renderer with 1 layer, 10000 tiles per layer, default layer of 0, tile size of 32
	droneRenderer = new ofxSpriteSheetRenderer(1, 10000, 0, 128);
    // load the spriteSheetExample.png texture of size 256x256 into the sprite sheet. set it's scale mode to nearest since it's pixel art
	droneRenderer->loadTexture("DronesSpritesheet.png", 1024, GL_NEAREST);
    spriteAdded = false;

}

//--------------------------------------------------------------
void testApp::update(){
	droneRenderer->clear(); // clear the sheet
	droneRenderer->update(ofGetElapsedTimeMillis()); //update the time in the renderer, this is necessary for animations to advance
    
    
    	if(sprites.size()>0) // if we have sprites
    	{
    		for(int i=sprites.size()-1;i>=0;i--) //go through them
    		{
    			sprites[i]->pos.y+=sprites[i]->speed; //add their speed to their y
    			sprites[i]->pos.x-=sprites[i]->speed; //add their speed to their y
    
    			if(sprites[i]->pos.y > ofGetHeight()+16)
                    //if they are past the bottom of the screen
    			{
    				sprites[i]->pos.x = ofRandom(0,800);
     				sprites[i]->pos.y = 0;
   			} else {
                        droneRenderer->addCenteredTile(&sprites[i]->animation, sprites[i]->pos.x, sprites[i]->pos.y);
                    // add them to the sprite renderer (add their animation at their position, there are a lot more options for what could happen here, scale, tint, rotation, etc, but the animation, x and y are the only variables that are required)
    
                }
                
                        
    		}
    	}

    
    	if(spriteAdded == false){
    		basicSprite * newSprite = new basicSprite(); // create a new sprite
    		newSprite->pos.set(ofRandom(30,700),100); //set its position
    		newSprite->speed=ofRandom(1,5); //set its speed
            newSprite->sheetRow = 0;
    		newSprite->animation = flyingAnimation; //set its animation to the walk animation we declared
    		newSprite->animation.frame_duration /= newSprite->speed; //adjust its frame duration based on how fast it is walking (faster = smaller)
    		newSprite->animation.index = newSprite->sheetRow*8; //change the start index of our sprite. we have 4 rows of animations and our spritesheet is 8 tiles wide, so our possible start indicies are 0, 8, 16, and 24
    		sprites.push_back(newSprite); //add our sprite to the vector
            if (sprites.size() > 20) {
                spriteAdded = true;
            }
            
    	}


}

//--------------------------------------------------------------
void testApp::draw(){
    ofEnableAlphaBlending();
    droneRenderer->draw();

    ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}