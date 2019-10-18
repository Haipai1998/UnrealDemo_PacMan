// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/PacManCharacter.h"
#include "Public/Collectables.h"
#include "Math/Vector.h"
#include "Components/CapsuleComponent.h"
#include "EngineUtils.h"
#include "UObject/UObjectBaseUtility.h"
// Sets default values
APacManCharacter::APacManCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APacManCharacter::BeginPlay()
{
	Super::BeginPlay();
    GameMode = (APacManGameModeBase*)UGameplayStatics::GetGameMode(this);
    GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APacManCharacter::OnCollision);
    lives = 3;
    StartPoint = GetActorLocation();
    UE_LOG(LogTemp, Warning, TEXT("StartPoint = %s"), *StartPoint.ToString());
    CollectablesCntToEat = 0;
    for (TActorIterator<ACollectables> AcollectableIterator(GetWorld()); AcollectableIterator; ++AcollectableIterator) {
        ++CollectablesCntToEat;
    }
    //UE_LOG(LogTemp, Warning, TEXT("InitCollectablesCount = %d"), CollectablesCntToEat);
}

// Called every frame
void APacManCharacter::Tick(float DeltaTime)
{
    //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("PluginFunciton_OK"));
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APacManCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("SetupPlayerInputComponent"));
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &APacManCharacter::moveXAxis);
    PlayerInputComponent->BindAxis("MoveBackward", this, &APacManCharacter::moveYAxis);

    PlayerInputComponent->BindAction("NewGame", IE_Pressed, this, &APacManCharacter::NewGame);
    PlayerInputComponent->BindAction("ReStart", IE_Pressed, this, &APacManCharacter::ReStart);
    PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &APacManCharacter::Pause);

}

void APacManCharacter::moveXAxis(float AxisValue)
{
    //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("MOVEX"));
    CurrentVelocity.X = AxisValue;
    AddMovementInput(CurrentVelocity);
}

void APacManCharacter::moveYAxis(float AxisValue)
{
    //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("MOVEY"));
    CurrentVelocity.Y = AxisValue;
    AddMovementInput(CurrentVelocity);
}

void APacManCharacter::ReStart()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("ReStart"));
    GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("RestartLevel"));
}

void APacManCharacter::NewGame()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("NewGame"));
    EGameState TempGameState = GameMode->GetCurrentState();
    if (TempGameState == EGameState::EMenu) {
        GameMode->SetCurrentState(EGameState::EPlaying);
    }
}

void APacManCharacter::Pause()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Pause"));
    EGameState TempGameState = GameMode->GetCurrentState();
    if (TempGameState == EGameState::EPlaying) {
        GameMode->SetCurrentState(EGameState::EPause);
    }
    else if (TempGameState == EGameState::EPause) {
        GameMode->SetCurrentState(EGameState::EPlaying);
    }
}

void APacManCharacter::Bekilled()
{
    --lives;
    if (lives == 0) {
        GameMode->SetCurrentState(EGameState::EGameOver);
    }
    else {
        SetActorLocation(StartPoint);
    }
}

void APacManCharacter::OnCollision(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    if (GameMode->GetCurrentState() == EGameState::EPlaying) {
        if (OtherActor->IsA(ACollectables::StaticClass())) {
            OtherActor->Destroy();
            if (--CollectablesCntToEat == 0) {
                GameMode->SetCurrentState(EGameState::EWin);
            }
            //UE_LOG(LogTemp, Warning, TEXT("NowCollectablesCount = %d"), CollectablesCntToEat);
        }
    }
}

