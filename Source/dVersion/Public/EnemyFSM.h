// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "dVersion.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle,
	Move,
	Attack,
	Damage,
	Die,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DVERSION_API UEnemyFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	EEnemyState State = EEnemyState::Idle;

	UPROPERTY(VisibleAnywhere, Category = FSM)
	class AMyCharacter* Target;

	UPROPERTY()
	class AEnemy* Me;

	UPROPERTY(EditDefaultsOnly, Category = FSM)
	float IdleDelayTime = 1;

	UPROPERTY(EditAnywhere, Category = FSM)
	float AttackRange = 200.0f;

	UPROPERTY(EditAnywhere, Category = FSM)
	float AttackDelayTime = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FSM)
	int32 hp = 30;

	UPROPERTY(EditAnywhere, Category = FSM)
	float DamageDelayTime = 3.0f;

	UPROPERTY(EditAnywhere, Category = FSM)
	float DieSpeed = 50.0f;

	UPROPERTY()
	class UEnemyAnimInstance* Anim;

	void IdleState();
	void MoveState();
	void AttackState();
	void DamageState();
	void DieState();
	void OnDamageProcess();

	float CurrentTime = 0;
};
