#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetFrameRate(30);
	ofBackground(0,0,0);
    
    //declare a new renderer with 1 layer, 10000 tiles per layer, default layer of 0, tile size of 32
	droneRenderer = new ofxSpriteSheetRenderer(1, 10000, 0, 128);
    // load the spriteSheetExample.png texture of size 256x256 into the sprite sheet. set it's scale mode to nearest since it's pixel art
	droneRenderer->loadTexture("DronesSpritesheet.png", 1024, GL_NEAREST);
    droneAdded = false;
    timeCode = 0.0;
//    windSpeed=ofRandom(0.05,1);
    windSpeed = 0.3;
    addDirt();
}

//--------------------------------------------------------------
void testApp::update(){
    timeCode += 0.01;

	droneRenderer->clear(); // clear the sheet
	droneRenderer->update(ofGetElapsedTimeMillis()); //update the time in the renderer, this is necessary for animations to advance
    
    
    	if(sprites.size()>0){
            // DIRT
    		for(int i=dirtSprites.size()-1;i>=0;i--){
                droneRenderer->addCenteredTile(&dirtSprites[i]->animation, dirtSprites[i]->pos.x, dirtSprites[i]->pos.y);
    		}

            // DRONES
    		for(int i=sprites.size()-1;i>=0;i--){
    			sprites[i]->pos.y+=(sprites[i]->speed)/2; //add their speed to their y
    			sprites[i]->pos.y += sin(timeCode*5)*0.7;
    			sprites[i]->pos.x-=sprites[i]->speed; //add their speed to their y
                
    			if(sprites[i]->pos.y > ofGetHeight()+16)
                    //if they are past the bottom of the screen
    			{
    				sprites[i]->pos.x = ofRandom(100,1800);
     				sprites[i]->pos.y = -50;
                } else {
                    droneRenderer->addCenteredTile(&sprites[i]->animation, sprites[i]->pos.x, sprites[i]->pos.y);
                    // add them to the sprite renderer (add their animation at their position, there are a lot more options for what could happen here, scale, tint, rotation, etc, but the animation, x and y are the only variables that are required)
                    
                }
                
                
    		}
            // CLOUDS
    		for(int i=cloudSprites.size()-1;i>=0;i--){
    			cloudSprites[i]->pos.x-=windSpeed; //add their speed to their y
                
    			if(cloudSprites[i]->pos.x < -200){
    				cloudSprites[i]->pos.x = ofGetWidth()+200;
     				cloudSprites[i]->pos.y = ofRandom(0,800);
                } else {
                    droneRenderer->addCenteredTile(&cloudSprites[i]->animation, cloudSprites[i]->pos.x, cloudSprites[i]->pos.y);
                    // add them to the sprite renderer (add their animation at their position, there are a lot more options for what could happen here, scale, tint, rotation, etc, but the animation, x and y are the only variables that are required)
                    
                }
                
                
    		}
    	}

    //
    // ADDING SPRITES
    //
    
    if(droneAdded == false){
        droneSprite * newSprite = new droneSprite(); // create a new sprite
        newSprite->pos.set(ofRandom(100,1800),200); //set its position
        newSprite->speed=ofRandom(1,5); //set its speed
        newSprite->sheetRow = 0;
        newSprite->animation = flyingAnimation; //set its animation to the walk animation we declared
        newSprite->animation.frame_duration /= newSprite->speed; //adjust its frame duration based on how fast it is walking (faster = smaller)
        newSprite->animation.index = newSprite->sheetRow*8; //change the start index of our sprite. we have 4 rows of animations and our spritesheet is 8 tiles wide, so our possible start indicies are 0, 8, 16, and 24
        sprites.push_back(newSprite); //add our sprite to the vector
        if (sprites.size() > 5) {
            droneAdded = true;
        }
    }
    if(cloudsAdded == false){
        cloudSprite * newCloud = new cloudSprite(); // create a new sprite
        newCloud->pos.set(ofRandom(100,1800),ofRandom(0,800)); //set its position
        newCloud->offset = ofRandom(0,3);
        newCloud->animation = staticAnimation; //set its animation to the walk animation we declared
        newCloud->animation.index = 8 + newCloud->offset; //change the start index of our sprite. we have 4 rows of animations and our spritesheet is 8 tiles wide, so our possible start indicies are 0, 8, 16, and 24
        cloudSprites.push_back(newCloud); //add our sprite to the vector
        if (cloudSprites.size() > 20) {
            cloudsAdded = true;
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
void testApp::addDirt(){
    dirtPenX = 0;
    dirtPenY = -20;
    while (dirtSprites.size() < 42) {
        dirtSprite * newDirt = new dirtSprite(); 
        newDirt->pos.set(dirtPenX,dirtPenY); 
        newDirt->animation = staticAnimation;
        newDirt->animation.index = 16 + ofRandom(0,8);
        dirtSprites.push_back(newDirt);
        dirtPenX += 128;
        if (dirtPenX > 800) {
            dirtPenX = 0;
            dirtPenY += 128;
        }
    }
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