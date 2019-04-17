#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <sstream>
#include <iomanip>
#include "Actor.h"
#include "Level.h"

using namespace std;

class Actor;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

StudentWorld::StudentWorld(std::string assetDir):
GameWorld(assetDir)
{
    m_numCitizens = 0;
    m_finished = false;
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

// Initializes the level and places all the actors where they need to be based on the level text file specification.
int StudentWorld::init()
{
    Level lev(assetPath());
    updateLevelString();
    string levelFile = m_levelString;
    //string levelFile = "level03.txt";
    m_numCitizens = 0;
    m_finished = false;
    Level::LoadResult result = lev.loadLevel(levelFile);
    if (result == Level::load_fail_file_not_found)
        cerr << "Cannot find level01.txt data file" << endl;
    else if (result == Level::load_fail_bad_format)
        cerr << "Your level was improperly formatted" << endl;
    else if (result == Level::load_success)
    {
        cerr << "Successfully loaded level" << endl;
        for (int x = 0; x < LEVEL_WIDTH; x++)
        {
            for (int y = 0; y < LEVEL_HEIGHT; y++)
            {
                Level::MazeEntry ge = lev.getContentsOf(x,y); // level_x=5, level_y=10
                double startX = x * 16;
                double startY = y * 16;
                switch (ge) // so x=80 and y=160
                {
                    case Level::empty:
                        //cout << "Location 80,160 is empty" << endl; break;
                        break;
                    case Level::player:
                    {
                        cout << "Location " << startX << "," << startY << " starts with the player" << endl;
                        m_penelope = new Penelope(this, startX,startY);
                        //cout << typeid(*m_penelope).name() << endl;
                        break;
                    }
                    case Level::wall:
                    {
                        cout << "Location " << startX << "," << startY << " starts with a wall" << endl;
                        Actor *wll = new Wall(this, startX,startY);
                        //cout << typeid(*wll).name() << endl;
                        m_actors.push_back(wll);
                        break;
                    }
                    case Level::dumb_zombie:
                    {
                        cout << "Location " << startX << "," << startY << " starts with a dumb zombie" << endl;
                        Actor *dz = new DumbZombie(this, startX, startY);
                        m_actors.push_back(dz);
                        break;
                    }
                    case Level::smart_zombie:
                    {
                        cout << "Location " << startX << "," << startY << " starts with a smart zombie" << endl;
                        Actor *sz = new SmartZombie(this, startX, startY);
                        m_actors.push_back(sz);
                        break;
                        
                    }
                    case Level::citizen:
                    {
                        cout << "Location " << startX << "," << startY << " starts with a citizen" << endl;
                        Actor *cz = new Citizen(this, startX, startY);
                        m_actors.push_back(cz);
                        m_numCitizens++;
                        break;
                    }
                        
                    case Level::exit:
                    {
                        cout << "Location " << startX << "," << startY << " starts with a exit" << endl;
                        Actor *ex = new Exit(this, startX, startY);
                        m_actors.push_back(ex);
                        break;
                    }
                    case Level::pit:
                    {
                        cout << "Location " << startX << "," << startY << " starts with a pit" << endl;
                        Actor *p = new Pit(this, startX, startY);
                        m_actors.push_back(p);
                        break;
                    }
                    case Level::vaccine_goodie:
                    {
                        cout << "Location " << startX << "," << startY << " starts with a vaccine goodie" << endl;
                        Actor *vcc = new VaccineGoodie(this, startX, startY);
                        m_actors.push_back(vcc);
                        break;
                    }
                    case Level::gas_can_goodie:
                    {
                        cout << "Location " << startX << "," << startY << " starts with a gas can goodie" << endl;
                        Actor *gs = new GasCanGoodie(this, startX, startY);
                        m_actors.push_back(gs);
                        break;
                    }
                    case Level::landmine_goodie:
                    {
                        cout << "Location " << startX << "," << startY << " starts with a landmine goodie" << endl;
                        Actor *lm = new LandmineGoodie(this, startX, startY);
                        m_actors.push_back(lm);
                        break;
                    }
                }
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
    
}

//This function uses GameWorld’s virtual move(). The function runs the doSomething() for all actors.
//If Penelope dies, we end the game. If the level is finished, we end the game.
int StudentWorld::move()
{

    m_penelope->doSomething();
    vector<Actor*>:: iterator it;
    it = m_actors.begin();
    setGameStatText(createTitleString());
    while (it != m_actors.end())
    {
        if (!((*it)->isDead()))
        {
            (*it)->doSomething();
            if ((m_penelope->isDead()))
                return GWSTATUS_PLAYER_DIED;
        }
        else{
            vector<Actor*>:: iterator temp;
            temp = it;
            it--;
            delete *temp;
            m_actors.erase(temp);
        }
        it++;
    }
    
    cout << m_numCitizens << endl;
    if (m_penelope->isDead())
    {
        return GWSTATUS_PLAYER_DIED;
    }
    
    if (m_finished)
    {
        if (getLevel() == 6)
            return GWSTATUS_PLAYER_WON;
        return GWSTATUS_FINISHED_LEVEL;
    }
    return GWSTATUS_CONTINUE_GAME;
}

//This function essentially creates the destructor by freeing up all of the dynamically allocated memory by deleting all the actors and Penelope.
void StudentWorld::cleanUp()
{
    for (vector<Actor *>::iterator iter = m_actors.begin(); iter != m_actors.end(); )
    {
        delete *iter;
        iter = m_actors.erase(iter);
    }
    delete m_penelope;
}

//For each actor that overlaps with A and is alive, take the appropriate action on A, such as burning it or picking up a goodie etc.
void StudentWorld::activateOnAppropriateActors(Actor * a)
{
    if (!m_penelope->isDead() && overlap(m_penelope, a))
    {
        (a)->activateIfAppropriate(m_penelope);
    }
    
    vector<Actor*>:: iterator it;
    it = m_actors.begin();
    while (it != m_actors.end())
    {
        if (!(*it)->isDead() && overlap((*it), a) && (*it) != a)
        {
            (a)->activateIfAppropriate(*it);
        }
        it++;
    }
    
}

//Adds dynamically created actors to the vector of actors I have.
void StudentWorld::addActor(Actor * a)
{
    m_actors.push_back(a);
}

//Decrements m_numCitizens every time a citizen dies.
void StudentWorld::recordCitizenGone()
{
    m_numCitizens--;
}

//If all the citizens are gone and Penelope exits, record that the level is finished and set m_finished to true.
void StudentWorld::recordLevelFinishedIfAllCitizensGone()
{
    m_finished = true;
}

//Returns true if any actors that block movement’s bounding box intersect with the point x and y and that the blocking actor is not a.
bool StudentWorld::isAgentMovementBlockedAt(double x, double y, Actor* a) const ///HOW DO I STOP IT FROM BLOCKING ITSELF??????
{
    int otherX = m_penelope->getX();
    int otherY = m_penelope->getY();
    if (x < otherX + SPRITE_WIDTH - 1 && x + SPRITE_WIDTH - 1 > otherX &&
        y < otherY + SPRITE_HEIGHT - 1 && y + SPRITE_HEIGHT - 1 > otherY && m_penelope != a)
        return true;
    
    for (int i = 0; i < m_actors.size(); i++) {
        if (m_actors[i]->blocksMovement() && m_actors[i] != a) {

            otherX = m_actors[i]->getX();
            otherY = m_actors[i]->getY();
            if (x < otherX + SPRITE_WIDTH - 1 && x + SPRITE_WIDTH - 1 > otherX &&
                y < otherY + SPRITE_HEIGHT - 1 && y + SPRITE_HEIGHT - 1 > otherY)
                return true;
            
        }
    }
    return false;
}


//Returns true is vomit is triggered at the point x,y.
bool StudentWorld::isZombieVomitTriggerAt(double x, double y, Actor * a) const
{
    if (overlapPos(x, y, m_penelope))
        return true;
    
    for (int i = 0; i < m_actors.size(); i++)
    {
        if (m_actors[i]->triggersZombieVomit())
        {
            if (overlapPos(x, y, m_actors[i]))
            {
                return true;
            }
        }
    }
    return false;
}

//Finds the nearest Citizen or Penelope from the point x , y and sets distance to the distance of the actor found.
//Set otherX and otherY to the location of that object.
bool StudentWorld::locateNearestVomitTrigger(double x, double y, double & otherX, double & otherY, double & distance)
{
    
    double smallestDist = (eucDist(x, y, m_penelope->getX(), m_penelope->getY()));
    otherX = m_penelope->getX();
    otherY = m_penelope->getY();
    distance = smallestDist;
    
    for(int z = 0; z < m_actors.size(); z ++)
    {
        if(m_actors[z]->triggersZombieVomit())
        {
            int x2 = m_actors[z]->getX();
            int y2 = m_actors[z]->getY();
            double temp = (eucDist(x, y, x2, y2));
            if(temp < smallestDist)
            {
                otherX = x2;
                otherY = y2;
                distance = temp;
            }
        }
    }
    return true;
}

//Finds the nearest Penelope or Zombie to x, y and sets distance to the distance of the actor found.
//Set otherX and otherY to the location of that object. If we find a Penelope, set isThreat to true, else set it to false.
bool StudentWorld::locateNearestCitizenTrigger(double x, double y, double & otherX, double & otherY, double & distance, bool & isThreat) const
{
    // compares closest zombie to penelope
    double zombieX = 0, zombieY = 0, zombieDistance = 0.0;
    double penelopeDistance = eucDist(x, y, m_penelope->getX(), m_penelope->getY());
    if(!locateNearestCitizenThreat(x, y, zombieX, zombieY, zombieDistance) && penelopeDistance <= 6400)
    {
        otherX = m_penelope->getX();
        otherY = m_penelope->getY();
        distance = penelopeDistance;// getEuclideanDistance(x, y, otherX, otherY);
        isThreat = false;
        return true;
    }
    if(penelopeDistance < zombieDistance && penelopeDistance <= 6400)
    {
        //cerr << "Penelope: " << penelopeDistance << ", " << "Zombie: " << zombieDistance << endl;
        otherX = m_penelope->getX();
        otherY = m_penelope->getY();
        distance = penelopeDistance;
        isThreat = false;
        return true;
    }
    if(zombieDistance <= 6400)
    {
        otherX = zombieX;
        otherY = zombieY;
        distance = zombieDistance;
        isThreat = true;
        return true;
    }
    return false;

}

//Finds the nearest to Zombie to x, y and sets distance to the distance of the actor found. Set otherX and otherY to the location of that object
bool StudentWorld::locateNearestCitizenThreat(double x, double y, double & otherX, double & otherY, double & distance) const
{
    int zombieCount = 0;
    if(m_actors.size() == 0)
    {
        return false;
    }
    distance = 9000 * 9000;
    
    for(int i = 0; i < m_actors.size(); i++)
    {
        if(m_actors[i]->threatensCitizens())
        {

            zombieCount++;
            int x2 = m_actors[i]->getX();
            int y2 = m_actors[i]->getY();
            double tempDistance = eucDist(x, y, x2, y2);
            if (tempDistance < distance)
            {
                distance = tempDistance;
                otherX = x2;
                otherY = y2;
            }
        }
    }
    if (zombieCount == 0) return false;
    return true;


}

//returns the euclidian distance between two points
double StudentWorld::eucDist(double x1, double y1, double x2, double y2) const
{
    
    double xdiff = ((x1 + SPRITE_WIDTH/ 2)   - (x2 + SPRITE_WIDTH/ 2));
    double ydiff = ((y1 + SPRITE_HEIGHT/ 2)   - (y2 + SPRITE_HEIGHT/ 2));
    xdiff = xdiff * xdiff;
    ydiff = ydiff * ydiff;
    
    return (xdiff + ydiff);
}

//returns true is the two objects overlap
bool StudentWorld::overlap(Actor *a, Actor *b) const
{
    return ((eucDist(a->getX(), a->getY(), b->getX(), b->getY())) <= 100);
}

//returns true is the an object and an object at point X,Y overlap
bool StudentWorld::overlapPos(double X, double Y, Actor *b) const
{
    return ((eucDist(X, Y, b->getX(), b->getY())) <= 100);
}

//Returns true is flames are blocked at the point x,y.
bool StudentWorld::isFlameBlockedAt(double x, double y) const
{
    
    for (int z = 0; z < m_actors.size(); z++)
    {
        if (m_actors[z]->blocksFlame())
        {
            int otherX = m_actors[z]->getX();
            int otherY = m_actors[z]->getY();
            if (x < otherX + SPRITE_WIDTH - 1 && x + SPRITE_WIDTH - 1 > otherX &&
                y < otherY + SPRITE_HEIGHT - 1 && y + SPRITE_HEIGHT - 1 > otherY)
                return true;
        }
    }
    return false;
}

//uses stringstreams to create the status bar of the game
string StudentWorld::createTitleString()
{
    ostringstream oss;
    oss << "Score: ";
    oss.fill('0');
    if (getScore() >= 0) {
        oss << setw(6) << getScore() << "  ";
    }
    else {
        oss << "-" << setw(5) << -getScore() << "  ";
    }
    oss << "Level: ";
    oss << getLevel() << "  ";
    oss << "Lives: ";
    oss << getLives() << "  ";
    oss << "Vaccines: ";
    oss << m_penelope->getNumVaccines() << "  ";
    oss << "Flames: ";
    oss << m_penelope->getNumFlameCharges() << "  ";
    oss << "Mines: ";
    oss << m_penelope->getNumLandmines() << "  ";
    oss << "Infected: ";
    oss << m_penelope->getInfectionDuration() << endl;
    
    return oss.str();

}

//increments the level string to move to the next level
void StudentWorld::updateLevelString()
{
    if (getLevel() < 7)
    {
        ostringstream oss;
        oss << "level";
        oss.fill('0');
        oss << setw(2) << getLevel() << ".txt";
        m_levelString =  oss.str();
    }
}

//returns true if m_numCitizens is equal to zero.
bool StudentWorld::noMoreCitizens()
{
    if (m_numCitizens == 0)
        return true;
    return false;
}

//returns true is there are overlapping actors at point X,Y
bool StudentWorld::overlappingActors(double x, double y) const
{
    if (overlapPos(x, y, m_penelope))
        return true;
    for(int x = 0; x < m_actors.size(); x++)
    {
        if (overlapPos(x, y, m_actors[x]))
            return true;
    }
    return false;
    
}
