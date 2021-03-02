#include "StartScreenFactory.h"



StartScreenFactory::StartScreenFactory(Texture * _textTex):Factory()
{
    pressStartStartTime = SDL_GetTicks();
    moveStartTime = SDL_GetTicks();
    updateInterval = cfg.START_SCREEN_W_UPDATE;
    Texture *w = new Texture("./res/startW.png"); //load in the texture for the W logo
    wTex = w;
    textTex = _textTex;

    wordVec.push_back(new WordBuilder("ROBOTRON:", 6,50,wordColor, 200,150,0)); //set up the words for the screen
    wordVec.push_back(new WordBuilder("2017", 6,50,wordColor, 100,50,0));
    wordVec.push_back(new WordBuilder("REMAKE BY TRI DEG NAW",5,30,wordColor, 300,-25,0));
    wordVec.push_back(new WordBuilder("PRESS START / ENTER",5,30,wordColor, 270,-75,0)); //always make sure this is the last one if you want it to flash

    createWs(); //create the ws

}

/*
create the ws that circle around the edge of the screen

*/
void StartScreenFactory::createWs()
{

    float wWidth = cfg.START_SCREEN_W_WIDTH;
    float wHeight = cfg.START_SCREEN_W_HEIGHT;
    int currentDir = cfg.RIGHT; //varibale for setting the direction that the w will be going from where it is origionally placed on the screen

    int wX = cfg.positiveXedge  - wWidth / 2 - 20; //for keeping track of the x and y values of where the current w has been drawn
    int wY = cfg.positiveYedge - wHeight / 2;


    while((wX - (wWidth / 2)) >= cfg.negativeXedge) //for top, moving to the right
    {

        wVec.push_back(new TextureSquare(wX ,wY,9,genRandColor(), 0,1,1,0)); //add a new texture square to the w vector
        wVec[wVec.size() - 1]->setDir(currentDir); //set the direction
        wX -= wWidth; //move the current x value as much as the separation

    }
   // wX += wWidth; //move to stop overlapping
    wY = cfg.positiveYedge - wHeight - 10;

    currentDir = cfg.DOWN;
    while((wY - (wHeight / 2 )) >= cfg.negativeYedge ) //for right, going down
    {
        wVec.push_back(new TextureSquare(cfg.negativeXedge + (wWidth/2) ,wY,9,genRandColor(), 0,1,1,0));
        wVec[wVec.size() - 1]->setDir(currentDir);
        wY -= wHeight;

    }
    //wY += wHeight / 2;
    wX = cfg.negativeXedge + (wWidth);

    currentDir = cfg.LEFT;

    while((wX + (wWidth / 2 )) < cfg.positiveXedge) //for bottom, going left
    {
        wVec.push_back(new TextureSquare(wX ,cfg.negativeYedge + (wHeight/2),9,genRandColor(), 0,1,1,0));
        wVec[wVec.size() - 1]->setDir(currentDir);
        wX += wWidth;

    }
    wX = cfg.positiveXedge  - wWidth / 2;
    wY = cfg.negativeYedge + wHeight - 30;

    currentDir = cfg.UP;

    while((wY + (wHeight / 2 )) < cfg.positiveYedge ) //for left, going up
    {
        wVec.push_back(new TextureSquare(wX ,wY,9,genRandColor(), 0,1,1,0));
        wVec[wVec.size() - 1]->setDir(currentDir);
        wY += wHeight;

    }


}

void StartScreenFactory::update(Shader * shader, Camera * camera)
{
    unsigned int currentTime = SDL_GetTicks();
    shader->Bind();
    textTex->Bind(); //bind the texture for the text
    togglePressStart(); //toggle the "press start / enter text if its time to toggle it
    for(int i = 0; i < wordVec.size(); i++)
    {
        if((i == wordVec.size() - 1) && !isPressStartShown) //dont draw if its the last word (press start/enter) and it isnt toggled on
        {
            continue;
        }
        else
        {
            wordVec[i]->update(shader, camera); //call the update method of the wordbuilder to draw the word to the screen
        }

    }


    if((currentTime - moveStartTime) > updateInterval) //check its time to move the ws
    {
        moveW(); //call the method to move the ws around the screen
        moveStartTime = currentTime;
    }
    wTex->Bind(); //bind the texture for the w texture


    for(int i = 0; i < wVec.size(); i++)
    {

        glDepthMask(GL_FALSE); //allows the textures transparent background to work
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

        shader->Update((*wVec[i]->getTransform()), *camera); //update the ws position, and then draw it
        wVec[i]->draw(cfg.NO_DIR);

        glDisable(GL_BLEND);
        glDepthMask(GL_TRUE);

    }
}
void StartScreenFactory::moveW()
{

    int dir;
    float tempX;
    float tempY;

    float wWidth = cfg.START_SCREEN_W_WIDTH;
    float wHeight = cfg.START_SCREEN_W_WIDTH;
    for(int i = 0; i < wVec.size(); i++)
    {

        tempX = wVec[i]->getTransform()->GetPos()->x; //retirve the x and y values in temp variables
        tempY = wVec[i]->getTransform()->GetPos()->y;

        dir = wVec[i]->getDir(); //get the current dir for the w

        //change direction based on whether the w has hit the edge
        if(((tempX - (wWidth / 2)) < cfg.negativeXedge)&& dir == cfg.RIGHT)
        {
            wVec[i]->setDir(cfg.DOWN);
        }
        else if(((tempX + (wWidth / 2)) > cfg.positiveXedge) && dir == cfg.LEFT)
        {
            wVec[i]->setDir(cfg.UP);
        }
        else if(((tempY - (wHeight / 2)) < cfg.negativeYedge) && dir == cfg.DOWN)
        {
            wVec[i]->setDir(cfg.LEFT);
        }
        else if(((tempY + (wHeight / 2)) > cfg.positiveYedge)&& dir == cfg.UP)
        {
            wVec[i]->setDir(cfg.RIGHT);
        }

        dir = wVec[i]->getDir(); //get the new direction if it has changed



        //move the w in the right direction for the dir it has
        if(dir == cfg.RIGHT)
        {
            wVec[i]->getTransform()->GetPos()->x -= cfg.START_SCREEN_W_SPEED;
        }
        else if(dir == cfg.DOWN)
        {
            wVec[i]->getTransform()->GetPos()->y -= cfg.START_SCREEN_W_SPEED;
        }
        else if(dir == cfg.LEFT)
        {
            wVec[i]->getTransform()->GetPos()->x += cfg.START_SCREEN_W_SPEED;
        }
        else if(dir == cfg.UP)
        {
            wVec[i]->getTransform()->GetPos()->y += cfg.START_SCREEN_W_SPEED;
        }
    }
}
void StartScreenFactory::togglePressStart() //checks whether the right time has passed and toggles whether the "press start/enter" message is on the screen
{

    unsigned int currentTime = SDL_GetTicks();
    if((currentTime - pressStartStartTime) > startFlashInterval)
    {
        if(isPressStartShown)
        {
            isPressStartShown = false;
        }
        else
        {
            isPressStartShown = true;
        }
        pressStartStartTime = currentTime;
    }


}

glm::vec4 StartScreenFactory::genRandColor() //generate a random color
{
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    return glm::vec4(r,g,b,1);

}

void StartScreenFactory::clean() //clear the vectors and delete the memory they point to
{
    for(int i = 0; i < wVec.size();i++)
    {
        delete wVec[i];
    }
    wVec.clear();

    for(int i = 0; i < wordVec.size();i++)
    {
        delete wordVec[i];
    }
    wordVec.clear();

    //delete wTex; causes segfault, maybe im overlooking something


}
