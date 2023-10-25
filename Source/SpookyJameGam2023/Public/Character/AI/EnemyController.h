#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NPCS.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"
#include "EnemyController.generated.h"

UCLASS()
class SPOOKYJAMEGAM2023_API AEnemyController : public AAIController
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

public:
    AEnemyController();

public:
    TObjectPtr<ANPCS>Npc;

    FTimerHandle TimerHandle_LookAround;


    UFUNCTION()
	void MoveToRandomLocationAndLookAround();

    void OnLookAroundComplete();

    void EnteringScaryMode();

    void MoveToASafeLocation();
};