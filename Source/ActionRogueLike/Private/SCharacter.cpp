// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

#include "SInteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//弹簧臂初始化
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp -> SetupAttachment(RootComponent);
	//跟随controller旋转
	SpringArmComp -> bUsePawnControlRotation = true;

	//相机
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp -> SetupAttachment(SpringArmComp);

	//交互组件
	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");

	//自身禁止旋转
	bUseControllerRotationYaw = false;

	//角色同步侧向移动转身
	GetCharacterMovement() -> bOrientRotationToMovement = true;

}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//前后移动
	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	//左右移动
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
	//鼠标视角
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	//绑定动作
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);
	//交互
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);
}

void ASCharacter::MoveForward(float value)
{
	FRotator controlRot = GetControlRotation();
	controlRot.Pitch = 0.0f;
	controlRot.Roll = 0.0f;
	AddMovementInput(controlRot.Vector(), value);
	
}

void ASCharacter::MoveRight(float value)
{
	FRotator controlRot = GetControlRotation();
	controlRot.Pitch = 0.0f;
	controlRot.Roll = 0.0f;
	//左手坐标系 X = Forward = red
	//Y = Wight = green
	//Z = Up = blue
	const FVector wightVector = FRotationMatrix(controlRot).GetScaledAxis(EAxis::Y);
	
	AddMovementInput(wightVector, value);
}

//攻击动作
void ASCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, 0.2f);
	
}

void ASCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp -> PrimaryInteract();
	}
}

void ASCharacter::PrimaryAttack_TimeElapsed()
{
	const FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	const FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);
	FActorSpawnParameters SpawnParam;

	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParam.Instigator = this;
	GetWorld() ->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParam);
}