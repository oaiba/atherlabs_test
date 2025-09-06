// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace ATGameplayTags
{
	ATHERLABS_TEST_API FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString = false);

	ATHERLABS_TEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Combat_Dodge);
	ATHERLABS_TEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Combat_PrimaryAttack);

	inline const FName SOCKET_RIGHT_HAND = TEXT("SOCKET_Right_Hand");
}
