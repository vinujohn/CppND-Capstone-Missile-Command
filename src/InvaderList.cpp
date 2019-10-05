//
// Created by Vinu on 9/29/19.
//
#include "InvaderList.h"
#include <random>

void InvaderList::Update(int referenceTicks) {
    if (referenceTicks - mFrameStart > mCurrentAnimateSpeedMs) {
        mFrameStart = referenceTicks;

        // hide destroyed invaders in list
        for (auto &inv : *this) {
            if (inv->Destroyed()) {
                inv->Hide();
            }
        }

        SetNextMove();
        Move();

        DropBomb();
    }
}

void InvaderList::Move() {
    for (auto &inv : *this) {
        inv->Animate();
        switch (mCurrentDirection) {
            case Direction::Right:
                inv->MoveRight();
                break;
            case Direction::Left:
                inv->MoveLeft();
                break;
            case Direction::Down:
                inv->MoveDown();
                break;
        }
    }
}

bool InvaderList::Landed() {
    for (auto &inv : *this) {
        if (!inv->CanMoveDown(mLowerBound)) {
            return true;
        }
    }
    return false;
}

void InvaderList::SetNextMove() {

    switch (mCurrentDirection) {
        case Direction::Right:
            for (auto &inv : *this) {
                if (!inv->Destroyed() && !inv->CanMoveRight(mRightBound)) {
                    mCurrentDirection = Direction::Down;
                    break;
                }
            }
            break;
        case Direction::Left:
            for (auto &inv : *this) {
                if (!inv->Destroyed() && !inv->CanMoveLeft(mLeftBound)) {
                    mCurrentDirection = Direction::Down;
                    break;
                }
            }
            break;
        case Direction::Down:
            mCurrentDirection = mNextDirectionAfterDown;
            if (mNextDirectionAfterDown == Direction::Left) {
                mNextDirectionAfterDown = Direction::Right;
            } else {
                mNextDirectionAfterDown = Direction::Left;
            }
            break;
    }

}

void InvaderList::IncreaseAnimationSpeed() {
    mCurrentAnimateSpeedMs -= 20;
}

void InvaderList::DropBomb() {
    if (!mBomb->Displayed() && this->size() > 0) {
        // choose random invader
        std::vector<std::shared_ptr<Invader>> aliveInvaders;
        std::copy_if(this->begin(), this->end(), std::back_inserter(aliveInvaders),
                     [](std::shared_ptr<Invader> i) { return !i->Destroyed(); });

        std::uniform_int_distribution<int> dist(0, static_cast<int>(aliveInvaders.size() - 1));
        std::shared_ptr<Invader> randomInvader = aliveInvaders[dist(mRandomEngine)];

        int x = randomInvader->X() - 3 + (randomInvader->W() / 2);
        int y = randomInvader->Y() + randomInvader->H();
        mBomb->Move(x, y);
        mBomb->Display();
    }
}

void InvaderList::Reset() {
    mCurrentDirection = Direction::Right;
    mNextDirectionAfterDown = Direction::Left;
    mFrameStart = 0;
    mCurrentAnimateSpeedMs = mStartAnimateSpeedMs;

    for (auto &inv : *this) {
        inv->Reset();
    }
}

bool InvaderList::Destroyed() {
    for (auto &inv : *this) {
        if (!inv->Destroyed()) {
            return false;
        }
    }

    return true;
}
