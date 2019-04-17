//
//  Game.hpp
//  Project 1
//
//  Created by Harsh Chobisa on 1/10/19.
//  Copyright © 2019 Harsh Chobisa. All rights reserved.
//

#ifndef Game_h
#define Game_h

class Arena;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nZombies);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
};

int decodeDirection(char dir);
#endif /* Game_hpp */
