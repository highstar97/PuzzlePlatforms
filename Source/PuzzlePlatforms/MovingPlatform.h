#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void AddActiveTrigger();
	void RemoveActiveTrigger();

private:
	UPROPERTY(EditAnywhere)
	float Speed = 20.0f;

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	FVector TargetLocation;

	FVector GlobalStartLocation;
	FVector GlobalTargetLocation;

	UPROPERTY(EditAnywhere)
	int32 NeedTriggerToActive = 1;

	UPROPERTY(EditAnywhere)
	int32 ActiveTrigger = 1;
};