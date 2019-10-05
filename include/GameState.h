//
// Created by Vinu on 9/21/19.
//

#ifndef SPACEINVADERS_GAMESTATE_H
#define SPACEINVADERS_GAMESTATE_H

enum class GameState {
    Started, Running, Won, Lost, ExitCalled
};

class GameStateManager {
    friend class Game;

public:
    void ExitGame() {
        mCurrentState = GameState::ExitCalled;
    };

private:
    GameState mCurrentState;
    bool mExitNow = false;

    void SetState(const GameState state) {
        mCurrentState = state;
    };

    const GameState GetState() {
        return mCurrentState;
    }

    bool ShouldExitNow(){
        return mExitNow;
    }
};

#endif //SPACEINVADERS_GAMESTATE_H
