// Include necessary headers
#include "Character/AI/EnemyController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "NavigationSystem/Public/NavigationSystem.h"
#include "Character/SJGCharacterBase.h"
#include <Kismet/KismetMathLibrary.h>
#include "NavigationSystem.h"



AEnemyController::AEnemyController()
{
    PrimaryActorTick.bCanEverTick = true;


}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();



}



void AEnemyController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


}


void AEnemyController::MoveToRandomLocationAndLookAround()
{
    const FVector Origin = GetPawn()->GetActorLocation();
    const float Radius = 1000.0f;
    const FVector RandomLocation = UKismetMathLibrary::RandomPointInBoundingBox(Origin, FVector(Radius, Radius, 10.0f));

    // Use AI's built-in pathfinding to move the character to the random location.
    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
    if (NavSys)
    {
        FNavLocation OutLocation;
        if (NavSys->GetRandomPointInNavigableRadius(RandomLocation, Radius, OutLocation))
        {
            MoveToLocation(OutLocation.Location);
        }
    }

    // Pause for 3 seconds using a timer.
    GetWorldTimerManager().SetTimer(TimerHandle_LookAround, this, &AEnemyController::OnLookAroundComplete, 3.0f, false);
}

void AEnemyController::OnLookAroundComplete()
{

    MoveToRandomLocationAndLookAround();
}

void AEnemyController::EnteringScaryMode()
{
   
}

void AEnemyController::MoveToASafeLocation()
{
}


