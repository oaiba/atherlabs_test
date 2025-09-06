// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Net/UnrealNetwork.h"

ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	bReplicates = true;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	// // Init ASC owner/actor info
	// if (AbilitySystemComponent)
	// {
	// 	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	// }
	//
	// InitializeAbilities();
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseCharacter::InitializeAbilities()
{
	if (!IsValid(CharacterData))
	{
		UE_LOG(LogTemp, Error, TEXT("[%s::%hs] - CharacterData is not valid."), *GetName(), __FUNCTION__);
		return;
	}
	
	if (HasAuthority() && IsValid(AbilitySystemComponent))
	{
		// Grant any default abilities here
		for (TSubclassOf<UGameplayAbility> AbilityClass : CharacterData->DefaultAbilities)
		{
			if (IsValid(AbilityClass))
			{
				FGameplayAbilitySpec AbilitySpec(AbilityClass, 1, 0); // Level 1, InputID 0 (can be changed)
				DefaultAbilityHandles.Add(AbilitySystemComponent->GiveAbility(AbilitySpec));
			}
		}

		// Apply default effects (e.g., permanent buffs)
		for (TSubclassOf<UGameplayEffect> EffectClass : CharacterData->DefaultGameplayEffects)
		{
			if (IsValid(EffectClass))
			{
				FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
				FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(EffectClass, 1.0f, ContextHandle);
				AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
		}
	}
}

void ABaseCharacter::InitializeAttributes()
{
    // Can be implemented in Blueprint or specific character classes
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Only the server can do this
	if (AbilitySystemComponent && HasAuthority())
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		InitializeAbilities();
		InitializeAttributes();
	}
}

void ABaseCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// // For clients, we need to initialize the ASC when the PlayerState is replicated.
	// if (AbilitySystemComponent)
	// {
	// 	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	// 	InitializeAbilities();
	// 	InitializeAttributes();
	// }
}

void ABaseCharacter::GrantAbilities()
{
}
