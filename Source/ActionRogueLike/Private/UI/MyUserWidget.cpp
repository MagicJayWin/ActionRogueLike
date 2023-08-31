// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MyUserWidget.h"

#include "SCharacter.h"
#include "Components/TextBlock.h"

void UMyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//获取玩家Character
	APawn* MyPawn = GetOwningPlayerPawn();
	ASCharacter* PlayerCharacter = Cast<ASCharacter>(MyPawn);
	//获取Character组件
	USAttributeComponent* AttributeComponent = PlayerCharacter->FindComponentByClass<USAttributeComponent>();
	if (AttributeComponent)
	{
		AttributeComponent->OnHealthChanged.AddDynamic(this, &UMyUserWidget::OnHealthChanged);
	}
}

void UMyUserWidget::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth,
	float Delta)
{
	UTextBlock* HealthText = Cast<UTextBlock>(this->GetWidgetFromName(TEXT("HealthText")));
	//SanitizeFloat格式化为String再转为FText
	FText NewText = FText::FromString(FString::SanitizeFloat(NewHealth));
	HealthText->SetText(NewText);
}

