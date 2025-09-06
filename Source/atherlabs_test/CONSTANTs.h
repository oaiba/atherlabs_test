// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace ATGameplayTags
{
	ATHERLABS_TEST_API FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString = false);

	ATHERLABS_TEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Combat_Dodge);
	ATHERLABS_TEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Combat_PrimaryAttack);

	ATHERLABS_TEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_IsDodging);
	ATHERLABS_TEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_IsStunned);

	inline const FName SOCKET_RIGHT_HAND = TEXT("SOCKET_Right_Hand");
}
