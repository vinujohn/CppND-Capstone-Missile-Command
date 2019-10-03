//
// Created by Vinu on 9/21/19.
//

#ifndef SPACEINVADERS_GAMESTATE_H
#define SPACEINVADERS_GAMESTATE_H

enum class GameState{
    Started, Running, Won, Lost, Exited
};

class GameStateManager {
    friend class Game;
public:
    void ExitGame() {
        mCurrentState = GameState::Exited;
    };

private:
    GameState mCurrentState;

    void SetState(const GameState state){
        mCurrentState = state;
    };

    const GameState& GetState(){
        return mCurrentState;
    }
};

#endif //SPACEINVADERS_GAMESTATE_H
