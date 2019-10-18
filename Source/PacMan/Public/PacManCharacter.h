// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Engine/Engine.h"
#include "PacManGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "PacManCharacter.generated.h"

UCLASS()
class PACMAN_API APacManCharacter : public ACharacter
{
	GENERATED_BODY()


public:	
    // Sets default values for this character's properties
    APacManCharacter();
    virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void moveXAxis(float AxisValue);
    void moveYAxis(float AxisValue);
    void ReStart();
    void NewGame();
    void Pause();
    void Bekilled();

    UFUNCTION()
    void OnCollision(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

private:
    FVector CurrentVelocity;
    FVector StartPoint;
    APacManGameModeBase *GameMode;
    int CollectablesCntToEat;
    int lives;
};
