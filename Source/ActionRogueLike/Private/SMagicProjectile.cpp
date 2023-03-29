// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"

#include "NavigationSystemTypes.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//实例化球体组件，设置为根节点
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;

	effectComp = CreateDefaultSubobject<UParticleSystemComponent>("effectComp");
	effectComp -> SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	//初始化速度
	MovementComp -> InitialSpeed = 1000.0f;
	//每帧更新旋转匹配速度方向
	MovementComp -> bRotationFollowsVelocity = true;
	//在本地空间初始化
	MovementComp -> bInitialVelocityInLocalSpace = true;
}

// Called when the game starts or when spawned
void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

