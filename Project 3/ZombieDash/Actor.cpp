#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>
using namespace std;

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

// ----------------------------------- ACTOR CLASS  -----------------------------------

Actor::Actor(StudentWorld* w, int imageID, double x, double y, int dir = 0, int depth = 0): GraphObject(imageID, x, y, dir, depth)
{
    m_isDead = false;
    m_studentWorldptr = w;
}

StudentWorld* Actor::world() const{
    return m_studentWorldptr;
}

bool Actor:: isDead() const{
    return m_isDead;
}

void Actor:: setDead(){
    m_isDead = true;
}

// the following functions do not need to be defined for the Actor class.
void Actor:: activateIfAppropriate(Actor *a){
    return;
}

void Actor::useExitIfAppropriate(){
    return;
}

void Actor::dieByFallOrBurnIfAppropriate(){
    return;
}

void Actor:: beVomitedOnIfAppropriate(){
    return;
}

void Actor::pickUpGoodieIfAppropriate(Goodie *g){
    return;
}

bool Actor:: blocksMovement() const{
    return false;
}

bool Actor:: blocksFlame() const{
    return false;
}

bool Actor:: triggersOnlyActiveLandmines() const{
    return false;
}

bool Actor:: triggersZombieVomit() const{
    return false;
}

bool Actor:: threatensCitizens() const{
    return false;
}

bool Actor:: triggersCitizens() const{
    return false;
}

// ----------------------------------- AGENT CLASS  -----------------------------------
Agent::Agent(StudentWorld* w, int imageID, double x, double y, int dir):
Actor(w, imageID, x, y, 0, 0){
    
}
//Returns true as agents block movement.
bool Agent:: blocksMovement() const{
    return true;
}
//Returns true as agents trigger active landmines.
bool Agent:: triggersOnlyActiveLandmines() const{
    return true;
}

// ----------------------------------- HUMAN CLASS  -----------------------------------

Human::Human(StudentWorld* w, int imageID, double x, double y):
Agent(w, imageID, x, y, right)
{
    m_infectionCount = 0;
}

//This handles what happens when a human is vomited on.
void Human:: beVomitedOnIfAppropriate(){
    if (m_infectionCount == 0)
    {
        if (!triggersCitizens())
            world()->playSound(SOUND_CITIZEN_INFECTED);
    }

    m_infectionCount++;

}
//Returns true as humans trigger zombie vomit.
bool Human:: triggersZombieVomit() const{
    return true;
}
//Uninfects the human
void Human:: clearInfection(){
    m_infectionCount = 0;
}

//this function is used to increment the infection count and also handle what happens if the infection count reaches 500
//if that happens, the object is set to dead and a new zombies is created.
//the zombie is smart 30% of the time
void Human:: increaseInfectionCount()
{
    if (m_infectionCount != 0)
    {
        m_infectionCount++;
        if (m_infectionCount >= 500)
        {
            int x = randInt(1, 10);
            if(x <= 7)
            {
                Actor * zombie = new DumbZombie(world(), getX(), getY());
                world()->addActor(zombie);
            }
            else
            {
                Actor * zombie = new SmartZombie(world(), getX(), getY());
                world()->addActor(zombie);
            }
            world()->playSound(SOUND_ZOMBIE_BORN);
            dieByInfection();
            
        }
    }
}

int Human::getInfectionDuration() const{
    return m_infectionCount;
}


// ----------------------------------- PENELOPE CLASS  -----------------------------------

Penelope::Penelope( StudentWorld* s, double x, double y):
Human(s, IID_PLAYER, x, y){
    m_vaccines = 0;
    m_flamethrowerCharges = 0;
    m_landmines = 0;
}

//Get the key press from the user, and based on the key press, move the actor or deploy a goodie or a flamethrower or uses a goodie.
void Penelope::doSomething()
{
    increaseInfectionCount();
    int ch;
    if(world() -> getKey(ch))
    {
        switch (ch) {
            case KEY_PRESS_UP:
                setDirection(up);
                if(world() -> isAgentMovementBlockedAt(getX(), getY()+4, this) == false)
                {
                    moveTo(getX(), getY()+4);
                }
                break;
            case KEY_PRESS_DOWN:
                setDirection(down);
                if(world() -> isAgentMovementBlockedAt(getX(), getY()-4, this) == false)
                {
                    moveTo(getX(), getY()-4);
                }
                
                break;
            case KEY_PRESS_LEFT:
                setDirection(left);
                if(world() -> isAgentMovementBlockedAt(getX()-4, getY(), this) == false)
                {
                    moveTo(getX()-4, getY());
                }
                break;
                
            case KEY_PRESS_RIGHT:
                setDirection(right);
                if(world() -> isAgentMovementBlockedAt(getX()+4, getY(), this) == false)
                {
                    moveTo(getX()+4, getY());
                }
                break;
            case KEY_PRESS_SPACE:
            {
                if (m_flamethrowerCharges > 0)
                {
                    m_flamethrowerCharges--;
                    for (int i = 1; i<= 3; i++)
                    {
                        int startX = getX();
                        int startY = getY();
                        switch (getDirection())
                        {
                            case up:
                                startY += i*SPRITE_HEIGHT;
                                break;
                            case down:
                                startY -= i*SPRITE_HEIGHT;
                                break;
                            case left:
                                startX -= i*SPRITE_WIDTH;
                                break;
                            case right:
                                startX += i*SPRITE_WIDTH;
                                break;
                            default:
                                break;
                        }
                        if (world()->isFlameBlockedAt(startX, startY))
                            break;
                        Actor *flame = new Flame(world(), startX, startY, getDirection());
                        world()->playSound(SOUND_PLAYER_FIRE);
                        world()->addActor(flame);
                     }
                    
                }
                break;
            }
            case KEY_PRESS_TAB:
            {
                if (m_landmines > 0)
                {
                    Actor * landmine = new Landmine(world(), getX(), getY());
                    world()->addActor(landmine);
                    m_landmines--;
                }
                break;
            }
            case KEY_PRESS_ENTER:
            {
                if (m_vaccines > 0)
                {
                    clearInfection();
                    m_vaccines--;
                }
            }
                break;
            default:
                break;
        }
    }

}
//returns false as Penelope does not threaten citizens
bool Penelope::threatensCitizens() const
{
    return false;
}
//returns true as Pnelope does trigger citizens
bool Penelope::triggersCitizens() const{
    return true;
}

//if there are no more citizens, end the level
void Penelope:: useExitIfAppropriate(){
    
    if (world()->noMoreCitizens())
    {
        world()->playSound(SOUND_LEVEL_FINISHED);
        world()->recordLevelFinishedIfAllCitizensGone();
    }
}

//Sets Penelope to dead and tells student world to end the game.
void Penelope:: dieByFallOrBurnIfAppropriate(){
    world()->playSound(SOUND_PLAYER_DIE);
    world()->decLives();
    setDead();
}

//Sets the actor to dead by calling dieByFallOrBurnIfAppropriate.
void Penelope::dieByInfection()
{
    dieByFallOrBurnIfAppropriate();
}

//tells penelope to pick up the goodie passed in
void Penelope:: pickUpGoodieIfAppropriate(Goodie *g){
    g->pickUp(this);
}

//the following three functions increase goodie coun ts for penelope
void Penelope:: increaseFlameCharges(){
    m_flamethrowerCharges += 5;
}

void Penelope:: increaseVaccines(){
    m_vaccines++;
}

void Penelope:: increaseLandmines(){
    m_landmines += 2;
}
//following three functions are getters for the number of goodies.
int Penelope:: getNumVaccines() const{
    return m_vaccines;
}

int Penelope:: getNumLandmines() const{
    return m_landmines;
}

int Penelope:: getNumFlameCharges() const{
    return m_flamethrowerCharges;
}

// ----------------------------------- WALL CLASS  -----------------------------------


Wall::Wall(StudentWorld* s, double x, double y)
:Actor(s, IID_WALL, x, y){
    
}

//A WALL does not do anything during a tick
void Wall::doSomething(){
}

//This function is virtual as it overwrites the base class and we need to be able
//to call it with an Actor pointer. Returns true, as walls block movement.
bool Wall::blocksMovement() const{
    return true;
}

//This function is virtual as it overwrites the base class and we need to be able to call it
//with an Actor pointer. Returns true, as walls block flames.
bool Wall::blocksFlame() const{
    return true;
}

// ----------------------------------- EXIT CLASS  -----------------------------------


Exit::Exit(StudentWorld* w, double x, double y): ActivatingObject(w, IID_EXIT, x, y, 1, right)
{
    
}
//This function is virtual as it overwrites the base class and we need to be able to call it
//with an Actor pointer. Actor asks the world if anything is touching it by calling activate on appropriate actors by passing itself in.
void Exit::doSomething()
{
    world()->activateOnAppropriateActors(this);
}
//This function tells the actor a to use the exit if appropriate.
void Exit::activateIfAppropriate(Actor* a)
{
    a->useExitIfAppropriate();
}
//This function returns false as Exit does not block flames.
bool Exit::blocksFlame() const
{
    return true;
}


// ----------------------------------- ACTIVATING OBJECT CLASS  -----------------------------------

ActivatingObject::ActivatingObject(StudentWorld* w, int imageID, double x, double y, int depth, int dir) : Actor(w, imageID, x, y, 0, depth)
{
    
}


// ----------------------------------- GOODIE CLASS  -----------------------------------

Goodie::Goodie(StudentWorld* w, int imageID, double x, double y) : ActivatingObject(w, imageID, x, y, 1, right)
{
}

//Tells the actor a to pick up the goodie if it can.
void Goodie::activateIfAppropriate(Actor* a)
{
    a->pickUpGoodieIfAppropriate(this);
}
//Sets the goodie to dead if hit by a flame.
void Goodie::dieByFallOrBurnIfAppropriate()
{
    setDead();
}


// Have p pick up this goodie and increase the score. Use grant specific reward to do something different for all Goodies.
void Goodie::pickUp(Penelope *p)
{
    setDead();
    world()->increaseScore(50);
    world()->playSound(SOUND_GOT_GOODIE);
    grantSpecificReward(p);
}


// ----------------------------------- VACCINE GOODIE CLASS  -----------------------------------

VaccineGoodie::VaccineGoodie(StudentWorld* w, double x, double y) : Goodie(w, IID_VACCINE_GOODIE, x, y)
{
    
}
//Tell the world to activate on this object.
void VaccineGoodie::doSomething()
{
    if (isDead())
    {
        return;
    }
    
    world()->activateOnAppropriateActors(this);
    
}

//increase the vaccine count of penelope
void VaccineGoodie::grantSpecificReward(Penelope* p)
{
    p->increaseVaccines();
}


// ----------------------------------- GAS CAN GOODIE CLASS  -----------------------------------

GasCanGoodie::GasCanGoodie(StudentWorld* w, double x, double y) : Goodie(w, IID_GAS_CAN_GOODIE, x, y)
{
    
}
//Tell the world to activate on this object.
void GasCanGoodie::doSomething()
{
    if (isDead())
    {
        return;
    }
    
    world()->activateOnAppropriateActors(this);
}

//increase the flame charge count of penelope
void GasCanGoodie::grantSpecificReward(Penelope* p)
{
    p->increaseFlameCharges();
}

// ----------------------------------- LANDMINE GOODIE CLASS  -----------------------------------

LandmineGoodie::LandmineGoodie(StudentWorld* w, double x, double y) : Goodie(w, IID_LANDMINE_GOODIE, x, y)
{
    
}
//Tell the world to activate on this object.
void LandmineGoodie::doSomething()
{
    if (isDead())
    {
        return;
    }
    
    world()->activateOnAppropriateActors(this);
}

//increase the gas can count of penelope
void LandmineGoodie::grantSpecificReward(Penelope* p)
{
    p->increaseLandmines();
}

// ----------------------------------- PIT CLASS  -----------------------------------

Pit::Pit(StudentWorld* w, double x, double y): ActivatingObject(w, IID_PIT, x, y, 0, right)
{
    
}
//This function is virtual as it overwrites the base class and we need to be able to call it with an Actor pointer.
//Actor asks the world if anything is touching it by calling activate on appropriate actors by passing itself in.
void Pit::doSomething()
{
    world()->activateOnAppropriateActors(this);
}
//This function tells the actor a to die by fall or burn if appropriate.
void Pit::activateIfAppropriate(Actor* a)
{
    a->dieByFallOrBurnIfAppropriate();
}

// ----------------------------------- FLAME CLASS  -----------------------------------
Flame::Flame(StudentWorld* w, double x, double y, int dir): ActivatingObject(w, IID_FLAME, x, y, 0, right)
{
    m_ticksAlive = 0;
}

//This function is virtual as it overwrites the base class and we need to be able to call it
//with an Actor pointer. Actor asks the world if anything is touching it by calling activate on appropriate actors by passing itself in.
void Flame::doSomething()
{
    if (!isDead())
    {
        m_ticksAlive++;
        world()->activateOnAppropriateActors(this);
        if (m_ticksAlive==3)
            setDead();
    }
    

}
//This function tells the actor a to die by fall or burn if appropriate.
void Flame::activateIfAppropriate(Actor* a)
{
    a->dieByFallOrBurnIfAppropriate();
}

// ----------------------------------- VOMIT CLASS  -----------------------------------

Vomit::Vomit(StudentWorld* w, double x, double y): ActivatingObject(w, IID_VOMIT, x, y, 0, right)
{
    m_numTicksAlive = 0;
}

//This function is virtual as it overwrites the base class and we need to be able to call it
//with an Actor pointer. Actor asks the world if anything is touching it by calling activate on
//appropriate actors by passing itself in. It also counts the number of ticks it has been alive, and
//if this count reaches 2, then the vomit is set to dead.
void Vomit::doSomething()
{
    
    if (isDead())
        return;
    if (m_numTicksAlive == 2)
        setDead();
    m_numTicksAlive++;
    world()->activateOnAppropriateActors(this);
    
}

//This function tells the actor a to get infected if appropriate.
void Vomit::activateIfAppropriate(Actor* a)
{
    if (a->triggersZombieVomit())
        a->beVomitedOnIfAppropriate();
}

// ----------------------------------- LANDMINE CLASS  -----------------------------------

Landmine::Landmine(StudentWorld* w, double x, double y): ActivatingObject(w, IID_LANDMINE, x, y, 1, right)
{
    m_safetyTicks = 30;
    m_isActive = false;
}

//This function is virtual as it overwrites the base class and we need to be able to call it with an Actor pointer.
//Actor asks the world if anything is touching it by calling activate on appropriate actors by passing itself in.
//It also counts the number of ticks it has been alive, and if this count reaches 30, then the landmine is set to active.
void Landmine::doSomething()
{
    if (isDead())
    {
        return;
    }
    if (m_safetyTicks == 0)
    {
        m_isActive = true;
    }
    else
    {
        m_safetyTicks = m_safetyTicks - 1;
    }
    if (m_isActive) {
        world()->activateOnAppropriateActors(this);
    }
    
    

}
//If the actor a triggers active landmines, call die by fall or burn.
void Landmine::activateIfAppropriate(Actor* a)
{
    if (!isDead())
    {
        if (a->triggersOnlyActiveLandmines()) {
            dieByFallOrBurnIfAppropriate();
        }
    }

    
}
//Explodes the landmine if it hits by a flame. Determines where the flames should go and makes sure they are not blocked.
void Landmine::dieByFallOrBurnIfAppropriate()
{
    setDead();
    
    world()->playSound(SOUND_LANDMINE_EXPLODE);
    
    if (!world()->isFlameBlockedAt(getX() + SPRITE_WIDTH, getY())) {
        Actor* f = new Flame(world(), getX() + SPRITE_WIDTH, getY(), up);
        world()->addActor(f);
    }
    if (!world()->isFlameBlockedAt(getX() + SPRITE_WIDTH, getY()) - SPRITE_HEIGHT) {
        Actor* f = new Flame(world(), getX() + SPRITE_WIDTH, getY() - SPRITE_HEIGHT, up);
        world()->addActor(f);
    }
    if (!world()->isFlameBlockedAt(getX() + SPRITE_WIDTH, getY() + SPRITE_HEIGHT)) {
        Actor* f = new Flame(world(), getX() + SPRITE_WIDTH, getY() + SPRITE_HEIGHT, up);
        world()->addActor(f);
    }
    if (!world()->isFlameBlockedAt(getX() - SPRITE_WIDTH, getY())) {
        Actor* f = new Flame(world(), getX() - SPRITE_WIDTH, getY(), up);
        world()->addActor(f);
    }
    if (!world()->isFlameBlockedAt(getX() - SPRITE_WIDTH, getY() - SPRITE_HEIGHT)) {
        Actor* f = new Flame(world(), getX() - SPRITE_WIDTH, getY() - SPRITE_HEIGHT, up);
        world()->addActor(f);
    }
    if (!world()->isFlameBlockedAt(getX() - SPRITE_WIDTH, getY() + SPRITE_HEIGHT)) {
        Actor* f = new Flame(world(), getX() - SPRITE_WIDTH, getY() + SPRITE_HEIGHT, up);
        world()->addActor(f);
    }
    if (!world()->isFlameBlockedAt(getX(), getY() + SPRITE_HEIGHT)) {
        Actor* f = new Flame(world(), getX(), getY() + SPRITE_HEIGHT, up);
        world()->addActor(f);
    }
    if (!world()->isFlameBlockedAt(getX(), getY() - SPRITE_HEIGHT)) {
        Actor* f = new Flame(world(), getX(), getY() - SPRITE_WIDTH, up);
        world()->addActor(f);
    }
    
    Actor* p = new Pit(world(), getX(), getY());
    world()->addActor(p);
}



// ----------------------------------- CITIZEN CLASS  -----------------------------------

Citizen::Citizen(StudentWorld* w,  double x, double y): Human(w, IID_CITIZEN, x, y)
{
    m_isParalyzed = false;
}

//returns value is is paralyzed
bool Citizen::isParalyzed()
{
    return m_isParalyzed;
}

//switches paralysis state
void Citizen::switchParalyzed()
{
    if (m_isParalyzed)
    {
        m_isParalyzed = false;
    }
    else
    {
        m_isParalyzed = true;
    }
}

//If the citizen is not alive or paralyzed, return. Else, update infection status and move either toward Penelope or away from zombies.
void Citizen::doSomething()
{
    if(isDead()) {
        return;
    }
    if(isParalyzed())
    {
        switchParalyzed();
        return;
    }
    increaseInfectionCount();
    double x = 0, y = 0, distance = 0.0;
    bool issaThreat = false;
    if(!world()->locateNearestCitizenTrigger(getX(), getY(), x, y, distance, issaThreat))
    {
        return;
    }
    move(x, y, distance, issaThreat);
    switchParalyzed();
}

//Moves the actor in a direction depending on what information is given to it on the direction it should move in towards penelope
void Citizen::moveHelper(double &destX, double &destY, double &XtoMove, double &YtoMove, double &dist)
{
    if (getX() == XtoMove)
    {
        moveinYDirection(YtoMove, destY);
        
    }
    else if (getY() == YtoMove)
    {
        moveinXDirection(XtoMove, destX);
        
    }
    else
    {
        int rand = randInt(1,2);
        if (rand == 1)
        {
            if (!moveinXDirection(XtoMove, destX))
            {
                if(!moveinYDirection(YtoMove, destY))
                {
                    runAwayFromZombie(dist, destX, destY);
                }
            }
        }
        else
        {
            if(!moveinYDirection(YtoMove, destY))
            {
                if(!moveinXDirection(XtoMove, destX))
                {
                    runAwayFromZombie(dist, destX, destY);
                }
            }
        }
    }
}

//moves the citizen away from zombie or towards penelope
void Citizen::move(double XtoMove, double YtoMove, double dist, double issaThreat)
{
    // if citizen wants to follow Penelope:
    // cerr << "Citizen x: " << getX() << " y: " << getY() << endl;
    // cerr << "Other is: " << x << " y: " << y << endl;
    double destX = getX();
    double destY = getY();
    if (!issaThreat)
    {
        moveHelper(destX, destY, XtoMove, YtoMove, dist);
    }
    else
    {
        runAwayFromZombie(dist, destX, destY);
    }
    
    if(!world()->isAgentMovementBlockedAt(destX, destY, this))
    {
        moveTo(destX, destY);
    }
}

//a function to run away from zombies that are within 80 pixels of it
void Citizen::runAwayFromZombie(double dist, double &destX, double &destY)
{
    int maxDir = getDirection();
    double maximum = dist;
    double potX = 0;
    double potY = 0;
    double potentialDistance = dist;
    for (int k = 0; k <= 270; k+=90)
    {
        switch (k) {
            case up:
                if (!world()->isAgentMovementBlockedAt(getX(), getY() + 1, this) && !world()->isAgentMovementBlockedAt(getX(), getY() + 2, this))
                {
                    world()->locateNearestCitizenThreat(getX(), getY() + 2, potX, potY, potentialDistance);
                    if (potentialDistance > maximum) {
                        maximum = potentialDistance;
                        maxDir = k;
                    }
                }
                break;
            case down:
                if (!world()->isAgentMovementBlockedAt(getX(), getY() - 1, this) && !world()->isAgentMovementBlockedAt(getX(), getY() - 2, this))
                {
                    world()->locateNearestCitizenThreat(getX(), getY() - 2, potX, potY, potentialDistance);
                    if (potentialDistance > maximum) {
                        maximum = potentialDistance;
                        maxDir = k;
                    }
                }
                break;
            case left:
                if (!world()->isAgentMovementBlockedAt(getX() - 1, getY(), this) && !world()->isAgentMovementBlockedAt(getX()-2, getY(), this))
                {
                    world()->locateNearestCitizenThreat(getX() - 2, getY(), potX, potY, potentialDistance);
                    if (potentialDistance > maximum) {
                        maximum = potentialDistance;
                        maxDir = k;
                    }
                }
                break;
            case right:
                if (!world()->isAgentMovementBlockedAt(getX() + 1, getY(), this) && !world()->isAgentMovementBlockedAt(getX()+2, getY(), this))
                {
                    world()->locateNearestCitizenThreat(getX() + 2, getY(), potX, potY, potentialDistance);
                    if (potentialDistance > maximum) {
                        maximum = potentialDistance;
                        maxDir = k;
                    }
                }
                break;
        }
    }
    setDirection(maxDir);
    switch (maxDir) {
        case up:
            destY += 2;
            break;
        case down:
            destY -= 2;
            break;
        case right:
            destX += 2;
            break;
        case left:
            destX -= 2;
            break;
    }

}

//This method is called if the citizen decides to move in the x direction
bool Citizen::moveinXDirection(double x, double& potX){
    if (x - getX() > 0) {
        if ( (!world()->isAgentMovementBlockedAt(getX() +2, getY(), this) && (!world()->isAgentMovementBlockedAt(getX() +1, getY(), this)))) {
            potX += 2;
            setDirection(right);
            return true;
        }
    } else {
        if ((!world()->isAgentMovementBlockedAt(getX() -2, getY(), this) && (!world()->isAgentMovementBlockedAt(getX() -1, getY(), this))))
        {
            potX -= 2;
            setDirection(left);
            return true;
        }
    }
    return false;
}

//This method is called if the citizen decides to move in the y direction
bool Citizen::moveinYDirection(double y, double& potY) {
    if (y - getY() > 0)
    {
        if ( (!world()->isAgentMovementBlockedAt(getX(), getY()+2, this) && (!world()->isAgentMovementBlockedAt(getX(), getY()+1, this))) )
        {
            potY += 2;
            setDirection(up);
            return true;
        }
    }
    else
    {
        if ( (!world()->isAgentMovementBlockedAt(getX(), getY()-2, this) && (!world()->isAgentMovementBlockedAt(getX(), getY()-1, this))) )
        {
            potY -= 2;
            setDirection(down);
            return true;
        }
    }
    return false;
}



//takes the citizen out of the game and gives the user points
void Citizen::useExitIfAppropriate()
{
    setDead();
    world()->recordCitizenGone();
    world()->increaseScore(500);
    world()->playSound(SOUND_CITIZEN_SAVED);
    
    
}
//Set the citizen to dead, play a sound, and decrement the appropriate amount of points.
void Citizen::dieByFallOrBurnIfAppropriate()
{
    setDead();
    world()->recordCitizenGone();
    world()->playSound(SOUND_CITIZEN_DIE);
    world()->increaseScore(-1000);
}
//Plays a sound and the calls dieByFallOrBurnIfAppropriate.
void Citizen::dieByInfection()
{
    world()->playSound(SOUND_ZOMBIE_BORN);
    setDead();
    world()->recordCitizenGone();
    world()->increaseScore(-1000);
}


// ----------------------------------- ZOMBIE CLASS  -----------------------------------


Zombie::Zombie(StudentWorld* w,  double x, double y): Agent( w, IID_ZOMBIE, x, y, right)
{
    m_paralyzed = false;
    m_movementPlanDist = 0;
}

//gets a random direction
int Zombie::getRandDir()
{
    int num = randInt(1, 4);
    if (num == 1 )
        return up;
    if (num == 2 )
        return down;
    if (num == 3 )
        return left;
    return right;
}

//Returns true as Zombies threaten citizens
bool Zombie::threatensCitizens() const
{
    return true;
}
//Returns true as Zombies triggers citizens.
bool Zombie:: triggersCitizens() const{
    return true;
}

//determines if the zombie should vomit, and then vomits if there is a target.
bool Zombie::vomit()
{
    int startX = getX();
    int startY = getY();
    switch (getDirection()) {
        case up:
            startY+=SPRITE_HEIGHT;
            break;
        case down:
            startY-=SPRITE_HEIGHT;
            break;
        case left:
            startX-= SPRITE_WIDTH;
            break;
        case right:
            startX+= SPRITE_WIDTH;
            break;
        default:
            break;
    }
    if (world()->isZombieVomitTriggerAt(startX, startY, this))
    {
        if(randInt(1, 3) == 1)
        {
            world()->playSound(SOUND_ZOMBIE_VOMIT);
            Actor* vomit = new Vomit(world(), startX, startY);
            world()->addActor(vomit);
            return true;
        }
    }
    return false;

}

//If the zombie is not paralyzed, move the zombie using either the SmartZombie functionality or the
//DumbZombie functionality depending on what type of Zombie it is. This function is virtual because
//it overwrites the doSomething method from actor.
void Zombie::doSomething()
{
    if (!isDead())
    {
        if (m_paralyzed)
        {
            m_paralyzed = false;
            if (vomit())
                return;
            if (m_movementPlanDist == 0)
            {
                determineMovementPlan();
            }
            int startX = getX();
            int startY = getY();
            switch (getDirection()) {
                case up:
                    startY++;
                    break;
                case down:
                    startY--;
                    break;
                case left:
                    startX--;
                    break;
                case right:
                    startX++;
                    break;
                default:
                    break;
            }
            if (world()->isAgentMovementBlockedAt(startX, startY, this))
                m_movementPlanDist = 0;
            else
            {
                moveTo(startX, startY);
                m_movementPlanDist--;
            }
        }
        else
            m_paralyzed = true;
    }
}

//default movement plan for dumb zombies specifically
void Zombie::determineMovementPlan()
{
    m_movementPlanDist = randInt(3, 10);
    setDirection(getRandDir());
}

//sets the distance of movement plan to the parameter passed in
void Zombie::setMovementPlanDist(int dist)
{
    m_movementPlanDist = dist;
}


// ----------------------------------- DUMB ZOMBIE CLASS  -----------------------------------


DumbZombie::DumbZombie(StudentWorld* w,  double x, double y): Zombie(w, x, y)
{

}

//Set the zombie to dead and increase the amount of points in student world. Drops a vaccine goodie ten percent of the time.
void DumbZombie::dieByFallOrBurnIfAppropriate()
{
    setDead();
    world()->playSound(SOUND_ZOMBIE_DIE);
    world()->increaseScore(1000);
    if (randInt(1, 10) == 1)
    {
        int dir = getRandDir();
        double startX = getX();
        double startY = getY();
        switch (dir) {
            case up:
                startY += SPRITE_HEIGHT;
                break;
            case down:
                startY -= SPRITE_HEIGHT;
                break;
            case right:
                startX += SPRITE_WIDTH;
                break;
            case left:
                startX -= SPRITE_WIDTH;
                break;
                
            default:
                break;
        }
        if (!world()->overlappingActors(startX, startY))
        {
            Actor* goodie = new VaccineGoodie(world(), startX, startY);
            world()->addActor(goodie);
        }
        
    }
}

// ----------------------------------- SMART ZOMBIE CLASS  -----------------------------------

SmartZombie::SmartZombie(StudentWorld* w,  double x, double y): Zombie(w, x, y)
{
}


//Set the zombie to dead and increase the amount of points in student world.
void SmartZombie::dieByFallOrBurnIfAppropriate()
{
    setDead();
    world()->playSound(SOUND_ZOMBIE_DIE);
    world()->increaseScore(2000);
}

//Determine which way the Zombie should move to go towards Penelope or a Citizen of they are in range.
//Else, use the same movement plan as a dumb zombie and randomly pick direction.
void SmartZombie::determineMovementPlan()
{
    setMovementPlanDist(randInt(3, 10));
    double toCompareX;
    double toCompareY;
    double dist;
    world()->locateNearestVomitTrigger(getX(), getY(), toCompareX, toCompareY, dist);
    if (dist <= 6400)
    {
        int rand = randInt(1,2);

        if(getX() - toCompareX <=2 && getX() - toCompareX >= -2)
        {
            if(toCompareY > getY())
            {
                setDirection(up);
            }
            else
            {
                setDirection(down);
            }
        }
        else if(getY() - toCompareY <=2 && getY() - toCompareY >= -2)
        {
            if(toCompareX > getX())
            {
                setDirection(right);
            }
            else
            {
                setDirection(left);
            }
        }
        
        else if(toCompareX > getX() && toCompareY > getY())
        {
            if(rand == 1)
            {
                setDirection(up);
            }
            else
            {
                setDirection(right);
            }
        }
        else if(toCompareX < getX() && toCompareY > getY())
        {
            if(rand == 1)
            {
                setDirection(up);
            }
            else
            {
                setDirection(left);
            }
        }
        else if(toCompareY < getY() && toCompareX < getX())
        {
            if(rand == 1)
            {
                setDirection(down);
            }
            else
            {
                setDirection(left);
            }
        }
        else
        {
            if(rand == 1)
            {
                setDirection(right);
            }
            else
            {
                setDirection(down);
            }
        }
    
    }
    else
    {
        Zombie::determineMovementPlan();
    }
}
