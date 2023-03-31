// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGamePlayInterface.h"
#include "GameFramework/Actor.h"
#include "ASItemChest.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AASItemChest : public AActor, public ISGamePlayInterface
{
	GENERATED_BODY()


	
	
public:	
	// Sets default values for this actor's properties
	AASItemChest();
	UPROPERTY(EditAnywhere)
	float TargetPitch;
	void InterAct_Implementation(APawn* InstigatorPawn) ;
	

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMesh;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
