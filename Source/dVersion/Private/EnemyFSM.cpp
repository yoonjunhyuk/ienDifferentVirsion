#include "EnemyFSM.h"
#include "MyCharacter.h"
#include "Enemy.h"
#include "EnemyAnimInstance.h"

// Sets default values for this component's properties
UEnemyFSM::UEnemyFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();

	auto Actor = UGameplayStatics::GetActorOfClass(GetWorld(), AMyCharacter::StaticClass());
	Target = Cast<AMyCharacter>(Actor);
	Me = Cast<AEnemy>(GetOwner());

	Anim = Cast<UEnemyAnimInstance>(Me->GetMesh()->GetAnimInstance());
}


// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (State)
	{
	case EEnemyState::Idle:
		IdleState();
		break;
	case EEnemyState::Move:
		MoveState();
		break;
	case EEnemyState::Attack:
		AttackState();
		break;
	case EEnemyState::Damage:
		DamageState();
		break;
	case EEnemyState::Die:
		DieState();
		break;
	}
}

void UEnemyFSM::IdleState()
{
	UE_LOG(LogTemp, Warning, TEXT("Idle"));

	CurrentTime += GetWorld()->DeltaTimeSeconds;

	if (CurrentTime > IdleDelayTime)
	{
		State = EEnemyState::Move;
		CurrentTime = 0;

		Anim->AnimState = State;
	}
}

void UEnemyFSM::MoveState()
{
	UE_LOG(LogTemp, Warning, TEXT("Move"));

	FVector Destination = Target->GetActorLocation();
	FVector Direction = Destination - Me->GetActorLocation();
	Me->AddMovementInput(Direction.GetSafeNormal());

	if (Direction.Size() < AttackRange)
	{
		State = EEnemyState::Attack;

		Anim->AnimState = State;
		Anim->bAttackPlay = true;
		CurrentTime = AttackDelayTime;
	}
}

void UEnemyFSM::AttackState()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack Ready"));

	CurrentTime += GetWorld()->DeltaTimeSeconds;
	if (CurrentTime > AttackDelayTime)
	{
		CurrentTime = 0;
		UE_LOG(LogTemp, Warning, TEXT("Attack!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));
		Anim->bAttackPlay = true;
	}

	float Distance = FVector::Distance(Target->GetActorLocation(), Me->GetActorLocation());
	if (Distance > AttackRange)
	{
		State = EEnemyState::Move;

		Anim->AnimState = State;
	}
}

void UEnemyFSM::DamageState()
{
	UE_LOG(LogTemp, Warning, TEXT("Damage"));

	CurrentTime += GetWorld()->DeltaTimeSeconds;
	if (CurrentTime > DamageDelayTime)
	{
		State = EEnemyState::Idle;
		CurrentTime = 0;

		Anim->AnimState = State;
	}
}

void UEnemyFSM::DieState()
{
	UE_LOG(LogTemp, Warning, TEXT("Die"));

	FVector P0 = Me->GetActorLocation();
	FVector vt = FVector::DownVector * DieSpeed * GetWorld()->DeltaTimeSeconds;
	FVector P = P0 + vt;
	Me->SetActorLocation(P);

	if (P.Z < -200.0f)
	{
		Me->Destroy();
	}
}

void UEnemyFSM::OnDamageProcess()
{
	UE_LOG(LogTemp, Warning, TEXT("OnDamageProcess"));

	hp = hp - 10;
	if (hp > 0)
	{
		State = EEnemyState::Damage;
	}
	else
	{
		State = EEnemyState::Die;
		Me->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	Anim->AnimState = State;
}