//
// Created by Vinu on 9/21/19.
//

#ifndef SPACEINVADERS_GAMESTATE_H
#define SPACEINVADERS_GAMESTATE_H

enum class GameState{
    Loaded, Started, Running, Ending, Ended
};

class GameStateManager {
    friend class Game;
public:
    const GameState CurrentGameState(){
        return mCurrentState;
    };

    void EndGame() {
        mCurrentState = GameState::Ending;
    };

    void SetState(GameState state){
        mCurrentState = state;
    };

private:
    GameState mCurrentState;
};

#endif //SPACEINVADERS_GAMESTATE_H
