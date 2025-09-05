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

	// if (AbilitySystemComponent && IsValid(PlayerInputComponent))
	// {
	// 	const FGameplayAbilityInputBinds Binds("AbilityConfirm", "AbilityCancel", FTopLevelAssetPath(), -1, -1);
	// 	AbilitySystemComponent->BindAbilityActivationToInputComponent(PlayerInputComponent, Binds);
	// }

	// Casting the generic UInputComponent to the Enhanced one
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!EnhancedInputComponent || !IsValid(AbilitySystemComponent))
	{
		// Logging a warning for better debugging
		UE_LOG(LogTemp, Warning, TEXT("[%s::%s] - EnhancedInputComponent or AbilitySystemComponent is not valid."), *GetName(), *FString(__func__));
		return;
	}

	// Getting the local player and adding the input mapping context
	if (const APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (const ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				InputSubsystem->AddMappingContext(HeroInputMappingContext, 0);
			}
		}
	}

	// Bind the input actions to the character's member functions
	if (IsValid(PrimaryAttackAction))
	{
		EnhancedInputComponent->BindAction(PrimaryAttackAction, ETriggerEvent::Started, this, &AHeroCharacter::OnPrimaryAttackStarted);
		EnhancedInputComponent->BindAction(PrimaryAttackAction, ETriggerEvent::Completed, this, &AHeroCharacter::OnPrimaryAttackCompleted);
	}
    
	if (IsValid(DodgeAction))
	{
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Started, this, &AHeroCharacter::OnDodgeStarted);
	}

	// You can also use this loop to bind actions if they are all in a TMap.
	// This is more flexible and data-driven.
	// for (const TPair<TObjectPtr<UInputAction>, FGameplayTag>& Pair : InputActionTags)
	// {
	//    if (IsValid(Pair.Key))
	//    {
	//       EnhancedInputComponent->BindAction(Pair.Key, ETriggerEvent::Started, this, &AHeroCharacter::ActivateAbilityByTag, Pair.Value);
	//    }
	// }
}

void AHeroCharacter::OnPrimaryAttackStarted(const FInputActionValue& Value)
{
	if (AbilitySystemComponent)
	{
		// Request a gameplay tag and activate the ability
		FGameplayTag AttackTag = FGameplayTag::RequestGameplayTag(FName("Input.Action.AttackPrimary"));
		// AbilitySystemComponent->TryActivateAbilitiesByTag(AttackTag);
	}
}

void AHeroCharacter::OnPrimaryAttackCompleted(const FInputActionValue& Value)
{
	// In a souls-like game, you might use the completed event to signal the end of a combo window or a charge attack.
	// For now, we can just log a message.
	UE_LOG(LogTemp, Warning, TEXT("[%s::%s] - Primary Attack Input Completed."), *GetName(), *FString(__func__));
}

void AHeroCharacter::OnDodgeStarted(const FInputActionValue& Value)
{
	if (AbilitySystemComponent)
	{
		// Request a gameplay tag and activate the ability
		FGameplayTag DodgeTag = FGameplayTag::RequestGameplayTag(FName("Input.Action.Dodge"));
		// AbilitySystemComponent->TryActivateAbilitiesByTag(DodgeTag);
	}
}
