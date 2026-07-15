#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "EnemyCharacter.generated.h"

class UEnemyAIComponent;

UCLASS()
class FOX_API AEnemyCharacter: public ACharacter {
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UEnemyAIComponent* AIComponent;

	AEnemyCharacter();
};
