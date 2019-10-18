// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PacManGameModeBase.generated.h"
enum EGameState {
    EPlaying,
    EPause,
    EWin,
    EGameOver,
    EMenu
};

/**
 * 
 */
UCLASS()
class PACMAN_API APacManGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    EGameState GetCurrentState()const;
    void SetCurrentState(EGameState Evalue);
    virtual void BeginPlay() override;

private:
    EGameState CurrentState;
};
