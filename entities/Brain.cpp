#include "Brain.h"

void Brain:: init()
{

    ModelLoader mLoader(1);
	mLoader.readMTLfile("./res/brain/brains_down1.mtl");
	mLoader.readOBJfile("./res/brain/brains_down1.obj");

	addMesh(new Mesh(mLoader.getVertices(), mLoader.getIndices(), mLoader.getColourList(), true, false, false), cfg.NO_DIR);

	mLoader.clearMaterials();
	clearVectors();

	mLoader.readMTLfile("./res/brain/brains_down1.mtl");
	mLoader.readOBJfile("./res/brain/brains_down1.obj");
	addMesh(new Mesh(mLoader.getVertices(), mLoader.getIndices(), mLoader.getColourList(), true, false, false), cfg.DOWN);
	mLoader.clearMaterials();
	clearVectors();

	mLoader.readMTLfile("./res/brain/brain_down2.mtl");
	mLoader.readOBJfile("./res/brain/brain_down2.obj");
	addMesh(new Mesh(mLoader.getVertices(), mLoader.getIndices(), mLoader.getColourList(), true, false, false), cfg.DOWN);
	mLoader.clearMaterials();
	clearVectors();

	mLoader.readMTLfile("./res/brain/brain_down3.mtl");
	mLoader.readOBJfile("./res/brain/brain_down3.obj");
	addMesh(new Mesh(mLoader.getVertices(), mLoader.getIndices(), mLoader.getColourList(), true, false, false), cfg.DOWN);
	mLoader.clearMaterials();
	clearVectors();

	mLoader.readMTLfile("./res/brain/brain_up1.mtl");
	mLoader.readOBJfile("./res/brain/brain_up1.obj");
	addMesh(new Mesh(mLoader.getVertices(), mLoader.getIndices(), mLoader.getColourList(), true, false, false), cfg.UP);
	mLoader.clearMaterials();
	clearVectors();

	mLoader.readMTLfile("./res/brain/brain_up2.mtl");
	mLoader.readOBJfile("./res/brain/brain_up2.obj");
	addMesh(new Mesh(mLoader.getVertices(), mLoader.getIndices(), mLoader.getColourList(), true, false, false), cfg.UP);
	mLoader.clearMaterials();
	clearVectors();

	mLoader.readMTLfile("./res/brain/brain_up3.mtl");
	mLoader.readOBJfile("./res/brain/brain_up3.obj");
	addMesh(new Mesh(mLoader.getVertices(), mLoader.getIndices(), mLoader.getColourList(), true, false, false), cfg.UP);
	mLoader.clearMaterials();
	clearVectors();


	mLoader.readMTLfile("./res/brain/brain_left1.mtl");
	mLoader.readOBJfile("./res/brain/brain_left1.obj");
	addMesh(new Mesh(mLoader.getVertices(), mLoader.getIndices(), mLoader.getColourList(), true, false, false), cfg.RIGHT);
	mLoader.clearMaterials();
	clearVectors();

	mLoader.readMTLfile("./res/brain/brain_left2.mtl");
	mLoader.readOBJfile("./res/brain/brain_left2.obj");
	addMesh(new Mesh(mLoader.getVertices(), mLoader.getIndices(), mLoader.getColourList(), true, false, false), cfg.RIGHT);
	mLoader.clearMaterials();
	clearVectors();

	mLoader.readMTLfile("./res/brain/brain_left3.mtl");
	mLoader.readOBJfile("./res/brain/brain_left3.obj");
	addMesh(new Mesh(mLoader.getVertices(), mLoader.getIndices(), mLoader.getColourList(), true, false, false), cfg.RIGHT);
	mLoader.clearMaterials();
	clearVectors();


    mLoader.readMTLfile("./res/brain/brain_right1.mtl");
	mLoader.readOBJfile("./res/brain/brain_right1.obj");
	addMesh(new Mesh(mLoader.getVertices(), mLoader.getIndices(), mLoader.getColourList(), true, false, false), cfg.LEFT);
	mLoader.clearMaterials();
	clearVectors();

	mLoader.readMTLfile("./res/brain/brain_right2.mtl");
	mLoader.readOBJfile("./res/brain/brain_right2.obj");
	addMesh(new Mesh(mLoader.getVertices(), mLoader.getIndices(), mLoader.getColourList(), true, false, false), cfg.LEFT);
	mLoader.clearMaterials();
	clearVectors();

	mLoader.readMTLfile("./res/brain/brain_right3.mtl");
	mLoader.readOBJfile("./res/brain/brain_right3.obj");
	addMesh(new Mesh(mLoader.getVertices(), mLoader.getIndices(), mLoader.getColourList(), true, false, false), cfg.LEFT);
	mLoader.clearMaterials();
	clearVectors();





}
void Brain::seekClosest()
{
    float brainX = getTransform()->GetPos()->x;
    float brainY = getTransform()->GetPos()->y;

    float familyX;
    float familyY;
    float distance = 0;

    int initialIndex = 0;

    float tempDistance = 0;
    m_closestFamilyMemX = 0;
    m_closestFamilyMemY = 0;

    for(int i = 0; i < familyVec->size(); i++)
    {

       // cout << i <<"  " <<familyVec->at(i)->isProg() << endl;
        familyX = familyVec->at(i)->getTransform()->GetPos()->x;
        familyY = familyVec->at(i)->getTransform()->GetPos()->y;

        if(i == initialIndex)
        {
            if(familyVec->at(i)->isProg())
            {
                initialIndex++;
            }
            else
            {
                distance = sqrt(pow( (brainX - familyX ) ,2 )+ pow((brainY - familyY), 2));
                m_closestFamilyMemX = familyVec->at(i)->getTransform()->GetPos()->x;
                m_closestFamilyMemY = familyVec->at(i)->getTransform()->GetPos()->y;

                familyTarget = familyVec->at(i);

            }

        }
        else
        {

        if(!(familyVec->at(i)->isProg()))
        {
            tempDistance = sqrt(pow( (brainX - familyX ) ,2 )+ pow((brainY - familyY), 2));

            if(tempDistance < distance)
            {
                distance = tempDistance;
                m_closestFamilyMemX = familyVec->at(i)->getTransform()->GetPos()->x;
                m_closestFamilyMemY = familyVec->at(i)->getTransform()->GetPos()->y;
                familyTarget = familyVec->at(i);
            }
        }

        }

    }

}

void Brain::move(Player * player)
{



    checkIfTimeTOShoot();

    updateAnimation();


    seekClosest(); //function to find the closest human

    if((getTimeWithOffSet() - m_progMakeStartTime) > m_progDelay) //if the time is up for making a prog, allow the brain to move again
    {
        m_makingProg = false;

    }

    if(!m_makingProg) //while making a prog, dont move
    {

        if (getTimeWithOffSet() - moveStartTime > updateInterval)
        {

            if(m_closestFamilyMemX == 0 && m_closestFamilyMemY == 0) //the default for the family member is 0,0, meaning if its this value, there are no family left, so move randomly
            {
                moveRandomly();
            }
            else
            {
                //moveRandomly();
                moveToClosestHuman();
            }

            moveStartTime = getTimeWithOffSet();

        }
    }
}

void Brain::moveToClosestHuman()
{
    float x = getTransform()->GetPos()->x;
    float y = getTransform()->GetPos()->y;


    if(y > m_closestFamilyMemY) //move the correct way towards the closest family member based on the member variables, set the dir accordingly so the correct mesh is drawn
    {
        dir = cfg.DOWN;
        getTransform()->GetPos()->y -=  m_moveSpeed;
    }
    if(y < m_closestFamilyMemY)
    {
        dir = cfg.UP;
        getTransform()->GetPos()->y += m_moveSpeed;
    }
    if(x > m_closestFamilyMemX)
    {
        dir = cfg.RIGHT;
        getTransform()->GetPos()->x -= m_moveSpeed;
    }

    if(x < m_closestFamilyMemX)
    {
        dir = cfg.LEFT;
        getTransform()->GetPos()->x += m_moveSpeed;
    }

}

void Brain::moveRandomly()
{

    float x = getTransform()->GetPos()->x;
    float y = getTransform()->GetPos()->y;

    updateRandomDir();

    checkBoundaryCollides(); //check if the entity has hit any of the boundaries and reverse thier motion if they have

    defaultMovementForDir();

}
