// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCharacter.h"

#include "Components/HeroAbilitySysComp.h"
#include "GameFramework/PlayerState.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AHeroCharacter::AHeroCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UHeroAbilitySysComp>(TEXT("AbilitySystemComponent")))
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (APlayerState* PS = GetPlayerState())
	{
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);
		InitializeAbilities();
		InitializeAttributes();
	}
}

void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHeroCharacter::ActivateAbilityByTag(const FInputActionValue& InputActionValue, const FGameplayTag GameplayTag)
{
	UE_LOG(LogTemp, Warning, TEXT("[%s::%hs] - Activating Ability: InputValue=%s, GameplayTag=%s"),
	       *GetName(), __FUNCTION__, *InputActionValue.ToString(), *GameplayTag.ToString());

	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(GameplayTag);
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);
	}
}

void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!EnhancedInputComponent || !IsValid(AbilitySystemComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s::%hs] - EnhancedInputComponent or AbilitySystemComponent is not valid."),
		       *GetName(), __FUNCTION__);
		return;
	}

	if (const APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (const ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<
				UEnhancedInputLocalPlayerSubsystem>())
			{
				InputSubsystem->AddMappingContext(HeroData->HeroInputMappingContext, 1);
			}
		}
	}

	for (const TPair<TObjectPtr<UInputAction>, FGameplayTag>& Pair : HeroData->InputActionTags)
	{
		if (IsValid(Pair.Key))
		{
			EnhancedInputComponent->BindAction(Pair.Key, ETriggerEvent::Started, this,
			                                   &AHeroCharacter::ActivateAbilityByTag, Pair.Value);
		}
	}
}
