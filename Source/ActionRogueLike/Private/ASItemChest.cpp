// Fill out your copyright notice in the Description page of Project Settings.


#include "ASItemChest.h"

// Sets default values
AASItemChest::AASItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh -> SetupAttachment(BaseMesh);

}

// Called when the game starts or when spawned
void AASItemChest::BeginPlay()
{
 
	Super::BeginPlay();
	
}

// Called every frame
void AASItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

