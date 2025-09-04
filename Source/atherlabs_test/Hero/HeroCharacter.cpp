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
		// ...
	}
}

// Called when the game starts or when spawned
void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (AbilitySystemComponent && IsValid(PlayerInputComponent))
	{
		const FGameplayAbilityInputBinds Binds("AbilityConfirm", "AbilityCancel", FTopLevelAssetPath(), -1, -1);
		AbilitySystemComponent->BindAbilityActivationToInputComponent(PlayerInputComponent, Binds);
	}
}
