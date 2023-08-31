// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAttributeComponent.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class USInteractionComponent;
class UCameraComponent;
class USpringArmComponent;
UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category =  "Attack")
	UAnimMontage* AttackAnim;

	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_Dash;
public:
	// Sets default values for this character's properties
	ASCharacter();
 
protected:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	//交互组件
	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComp;

	//属性
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USAttributeComponent* AttributeComp;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> DashProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> MagicProjectClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> BlackHoleProjectClass;
	
	//移动函数
	void MoveForward(float value);
	void MoveRight(float value);

	//攻击动作
	void PrimaryAttack();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//交互
	void PrimaryInteract();

	//普通攻击定时函数
	void PrimaryAttack_TimeElapsed();
	//闪烁
	void Dash();
	void Dash_TimeElapsed();
	//黑洞
	void BlackHole();
	void BlackHole_TimeElapsed();
	//子弹集成
	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);
	//绑定组件函数重写
	virtual void PostInitializeComponents() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

};
