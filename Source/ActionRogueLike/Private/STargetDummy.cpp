 // Fill out your copyright notice in the Description page of Project Settings.


#include "STargetDummy.h"

#include "NavigationSystemTypes.h"
#include "SAttributeComponent.h"

 // Sets default values
ASTargetDummy::ASTargetDummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; 
	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = StaticMeshComp;

	AttributeComp->OnHealthChanged.AddDynamic(this,&ASTargetDummy::OnHealthChanged);
}

 void ASTargetDummy::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth,
	 float Delta)
 {
	
	if(Delta < 0.0f)
	{
		StaticMeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
 }

