// Fill out your copyright notice in the Description page of Project Settings.


//#include "Public/PacManGameModeBase.h"
#include "Public/PacManCharacter.h"

void APacManGameModeBase::SetCurrentState(EGameState Evalue)
{
    CurrentState = Evalue;
}

EGameState APacManGameModeBase::GetCurrentState()const
{
    return CurrentState;
}

void APacManGameModeBase::BeginPlay() {
    SetCurrentState(EGameState::EPlaying);
}