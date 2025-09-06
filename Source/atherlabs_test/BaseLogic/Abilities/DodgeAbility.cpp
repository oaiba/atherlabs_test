// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgeAbility.h"

#include "AbilitySystemComponent.h"
#include "CONSTANTs.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "BaseLogic/BaseData.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

UDodgeAbility::UDodgeAbility()
{
	SetAssetTags(FGameplayTagContainer(ATGameplayTags::TAG_Combat_Dodge));
	ActivationBlockedTags.AddTag(ATGameplayTags::TAG_State_IsStunned);
	// ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.IsAttacking")));
	ActivationOwnedTags.AddTag(ATGameplayTags::TAG_State_IsDodging);
}

void UDodgeAbility::OnMontageTaskCompleted()
{
}

void UDodgeAbility::OnMontageTaskInterrupted()
{
}

bool UDodgeAbility::IsCharacterInAir()
{
	if (const ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo()); IsValid(Character) && IsValid(
		Character->GetCharacterMovement()))
	{
		return !Character->GetCharacterMovement()->IsMovingOnGround();
	}

	UE_LOG(LogTemp, Warning,
	       TEXT(
		       "[UDodgeAbility::IsCharacterInAir] - Cannot determine if character is in air. Character or MovementComponent is not valid."
	       ));
	return false;
}

bool UDodgeAbility::IsCharacterMoving()
{
	if (const ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo()); IsValid(Character) && IsValid(
		Character->GetCharacterMovement()))
	{
		const FVector Velocity = Character->GetVelocity();

		return !Velocity.IsNearlyZero();
	}

	UE_LOG(LogTemp, Warning,
	       TEXT(
		       "[UDodgeAbility::IsCharacterMoving] - Cannot determine if character is moving. Character or MovementComponent is not valid."
	       ));
	return false;
}

void UDodgeAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo,
                                    const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	const ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo());

	if (!IsValid(Character))
	{
		UE_LOG(LogTemp, Error, TEXT("[%s::%hs] - Character is not valid."), *GetName(), __FUNCTION__);
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	// 1. Determine the dodge direction based on player input/movement.
	FDodgeData DodgeData;
	DodgeData.DodgeDirection = CalculateDodgeDirection();
	DodgeData.bIsInAir = IsCharacterInAir();
	DodgeData.bIsMoving = IsCharacterMoving();
	FDodgeOutData OutData;
	CalculateDodgeMontage(DodgeData, Character, OutData);

	if (!IsValid(OutData.DodgeMontage))
	{
		UE_LOG(LogTemp, Error, TEXT("[%s::%hs] - DodgeMontage is not valid."), *GetName(), __FUNCTION__);
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	// Commit the ability first to check for cost and cooldown
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		UE_LOG(LogTemp, Error, TEXT("[%s::%hs] - CommitAbility failed."), *GetName(), __FUNCTION__);
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	// // Apply tags before playing montage
	// ActorInfo->AbilitySystemComponent->AddLooseGameplayTags(DodgeData->BlockAbilitiesTags);
	ActorInfo->AbilitySystemComponent->AddLooseGameplayTag(ATGameplayTags::TAG_State_IsDodging);

	// Create and activate the UAbilityTask_PlayMontageAndWait task
	UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this,
		FName("Play Dodge Montage"),
		OutData.DodgeMontage,
		OutData.DodgePlayRate, // Play Rate
		NAME_None, // Start Section
		true, // Stop when ability ends,
		1.0f,
		OutData.DodgeStartTime,
		false
	);

	// Bind the delegates to our callback functions
	MontageTask->OnCompleted.AddDynamic(this, &UDodgeAbility::OnMontageTaskCompleted);
	MontageTask->OnInterrupted.AddDynamic(this, &UDodgeAbility::OnMontageTaskInterrupted);
	MontageTask->OnCancelled.AddDynamic(this, &UDodgeAbility::OnMontageTaskInterrupted);
	// Use the same function for cancellation

	MontageTask->ReadyForActivation();

	// // Handle the character's movement.
	// FVector DodgeDirectionVector = UKismetMathLibrary::GetDirectionVector(
	//     GetAvatarActorFromActorInfo()->GetActorLocation(),
	//     GetAvatarActorFromActorInfo()->GetActorLocation() + GetAvatarActorFromActorInfo()->GetActorRotation().Vector() * DodgeData->DodgeDistance
	// );
	// GetAvatarActorFromActorInfo()->AddActorWorldOffset(DodgeDirectionVector);
}

void UDodgeAbility::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	// Clean up and end the ability when the montage finishes.
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, bInterrupted);
}

void UDodgeAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                               const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
                               bool bWasCancelled)
{
	if (!IsActive())
	{
		// Ability is already inactive, return
		return;
	}

	// Remove the blocking and dodging tags.
	// We need to find the correct data to get the tags, as we don't store the activated DodgeData.
	// A better approach would be to store the FHeroDodgeData in a member variable during activation.

	// For simplicity, we can just remove a hardcoded tag.
	ActorInfo->AbilitySystemComponent->RemoveLooseGameplayTag(ATGameplayTags::TAG_State_IsDodging);

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

EDodgeDirection UDodgeAbility::CalculateDodgeDirection() const
{
	const ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	if (!IsValid(Character))
	{
		return EDodgeDirection::None;
	}

	if (const UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement(); !MovementComponent)
	{
		return EDodgeDirection::None;
	}

	// Get the character's forward vector and input direction
	const FVector CharacterForward = Character->GetActorForwardVector();
	const FVector CharacterRight = Character->GetActorRightVector();
	const FVector PlayerInputVector = Character->GetLastMovementInputVector();

	// If there is no input, the player can only dodge backward (if applicable) or in place.
	if (PlayerInputVector.IsNearlyZero())
	{
		return EDodgeDirection::Backward;
	}

	// Calculate the dot product to determine the direction
	const float DotForward = FVector::DotProduct(PlayerInputVector, CharacterForward);
	const float DotRight = FVector::DotProduct(PlayerInputVector, CharacterRight);

	// Return the appropriate direction based on dot products
	// You can adjust the thresholds (e.g., 0.7f) to make the directions more lenient or strict
	if (DotForward > 0.7f)
	{
		if (DotRight > 0.3f) return EDodgeDirection::ForwardRight;
		if (DotRight < -0.3f) return EDodgeDirection::ForwardLeft;
		return EDodgeDirection::Forward;
	}

	if (DotForward < -0.7f)
	{
		if (DotRight > 0.3f) return EDodgeDirection::BackwardRight;
		if (DotRight < -0.3f) return EDodgeDirection::BackwardLeft;
		return EDodgeDirection::Backward;
	}

	if (DotRight > 0.7f) return EDodgeDirection::Right;
	if (DotRight < -0.7f) return EDodgeDirection::Left;

	return EDodgeDirection::None;
}
