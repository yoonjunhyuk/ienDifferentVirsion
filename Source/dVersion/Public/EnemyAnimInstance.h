// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "dVersion.h"
#include "Animation/AnimInstance.h"
#include "EnemyFSM.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DVERSION_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FSM)
	EEnemyState AnimState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FSM)
	bool bAttackPlay = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FSM)
	bool bDieDone = false;

	UFUNCTION(BlueprintCallable, Category = FSM)
	void OnAttackEndAnimation();

	UFUNCTION(BlueprintImplementableEvent, Category = FSM)
	void PlayDamageAnim(FName SectionName);
};