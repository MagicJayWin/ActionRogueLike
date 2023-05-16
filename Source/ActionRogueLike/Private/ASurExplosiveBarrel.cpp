// Fill out your copyright notice in the Description page of Project Settings.


#include "ASurExplosiveBarrel.h"

#include "DrawDebugHelpers.h"

// Sets default values
AASurExplosiveBarrel::AASurExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");

	MeshComp -> SetSimulatePhysics(true);
	RootComponent = MeshComp;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp -> SetupAttachment(MeshComp);

	ForceComp -> Radius = 1000.0f;//爆炸范围
	ForceComp -> ImpulseStrength = 999.0f;//冲击力
	ForceComp -> bImpulseVelChange = true;
}

// Called when the game starts or when spawned
void AASurExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AASurExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AASurExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	MeshComp->OnComponentHit.AddDynamic(this, &AASurExplosiveBarrel::OnActorHit);
}

void AASurExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ForceComp ->FireImpulse();
	FString CombinedString;
	CombinedString = FString::Printf(TEXT("hIT AT LOCATION %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.0f, true);
}

