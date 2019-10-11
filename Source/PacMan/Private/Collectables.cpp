// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Collectables.h"

// Sets default values
ACollectables::ACollectables()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    SetActorEnableCollision(true);
    CollectableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollectableMesh"));
    BaseCollisionCompoent = CreateDefaultSubobject<USphereComponent>(TEXT("BaseCollisionCompoent"));
    CollectableMesh->AttachTo(BaseCollisionCompoent);
    

    //为什么要加分号
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
    if (Sphere.Succeeded()) {
        CollectableMesh->SetStaticMesh(Sphere.Object);
    }
    CollectableMesh->SetWorldScale3D(FVector(0.3, 0.3, 0.3));
    BaseCollisionCompoent->SetSphereRadius(16);
}

// Called when the game starts or when spawned
void ACollectables::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollectables::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

