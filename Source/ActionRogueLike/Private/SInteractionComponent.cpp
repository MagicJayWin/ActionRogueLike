// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"

#include "DrawDebugHelpers.h"
#include "SGamePlayInterface.h"
#include "Evaluation/IMovieSceneEvaluationHook.h"

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USInteractionComponent::PrimaryInteract()
{
	//FHitResult 是 Unreal Engine 4 中用于表示碰撞检测结果的结构体。它包含了一些信息。
	//比如被碰撞到的物体的指针、碰撞点、法线等等。
	//我们可以使用 FHitResult 来判断游戏世界中的物体是否与其他物体发生了碰撞，并根据其返回的信息进行相应的处理。
	//FHitResult Hit;
	//包含了需要检测的物体类型（如 Static、Dynamic、Pawn、Vehicle 等）
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	
	AActor* Owner = GetOwner();
	FVector EyeLocation;
	FRotator EyeRotation;
	Owner -> GetActorEyesViewPoint(EyeLocation, EyeRotation);

	const FVector End = EyeLocation + (EyeRotation.Vector() * 1000);
	//bool bBlockingHit = GetWorld() -> LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);

	TArray<FHitResult> Hits;

	float Radius = 30.f;
	
	FCollisionShape Shape;
	Shape.SetSphere(Radius);
	
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);

	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;
	for (FHitResult Hit : Hits)
	{
		AActor* HitActor =  Hit.GetActor();
		if (HitActor)
		{
			if (HitActor -> Implements<USGamePlayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(Owner);
				ISGamePlayInterface::Execute_InterAct(HitActor, MyPawn);
			}
		}
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, LineColor, false, 2.0f);
	}
	
	DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f ,0 ,2.0f);
	
}