// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IntVectorTypes.h"
#include "GameFramework/Actor.h"
#include "WorldGrid.generated.h"

UCLASS()
class NYNSGAMEJAM2024_API AWorldGrid : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly)
	int GridSizeX;
	UPROPERTY(EditInstanceOnly)
	int GridSizeY;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int TileSize;
	UPROPERTY(EditInstanceOnly)
	int VillageCount;
	UPROPERTY(EditInstanceOnly)
	UStaticMesh* TileMesh;
	UPROPERTY(EditInstanceOnly)
	TSubclassOf<AActor> VillageActor;
	UFUNCTION(BlueprintCallable)
	void SpawnTileGrid();
	TArray<UE::Geometry::FVector2i> GetRandomVillagePositions();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	void SpawnMesh(UWorld* World, UStaticMesh* Mesh, FVector Location);
};
