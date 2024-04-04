#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);

	
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
	
	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ActiveTrigger >= NeedTriggerToActive)
	{
		if (HasAuthority())
		{
			FVector Location = GetActorLocation();
			float LengthToMove = (GlobalTargetLocation - GlobalStartLocation).Size();
			float LengthMoved = (Location - GlobalStartLocation).Size();

			if (LengthMoved > LengthToMove)
			{
				FVector TempToSwap = GlobalStartLocation;
				GlobalStartLocation = GlobalTargetLocation;
				GlobalTargetLocation = TempToSwap;
			}

			FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
			Location += Speed * DeltaTime * Direction;
			SetActorLocation(Location);
		}
	}
}

void AMovingPlatform::AddActiveTrigger()
{
	++ActiveTrigger;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	ActiveTrigger = FMath::Max(--ActiveTrigger, 0);
}