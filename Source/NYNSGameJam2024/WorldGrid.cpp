// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldGrid.h"

#include "IntVectorTypes.h"
#include "Logger.h"
#include "Engine/StaticMeshActor.h"

void AWorldGrid::SpawnTileGrid()
{
	auto World = GetWorld();
	if(World)
	{
		// Select some random positions within the grid to spawn villages
		TArray<UE::Geometry::FVector2i> VillagePositions;
		for (int i = 0; i < VillageCount; ++i)
		{
			int x = FMath::RandRange(0, GridSizeX - 1);
			int y = FMath::RandRange(0, GridSizeY - 1);
			VillagePositions.Add(UE::Geometry::FVector2i(x, y));
		}
		for (int y = 0; y < GridSizeY; ++y)
		{
			for (int x = 0; x < GridSizeX; ++x)
			{
				for (auto Position : VillagePositions)
				{
					if(Position.X == x && Position.Y == y)
					{
						// Spawn village actor
						FVector Location = FVector(x * TileSize, y * TileSize, 0);
						AActor* SpawnedVillage = World->SpawnActor(VillageActor, &Location);
						SpawnedVillage->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
					}
					auto Distance = Position.DistanceSquared(UE::Geometry::FVector2i(x, y));
					// Random bool, the less the value of distance, the more likely it is to be true, causes clumped up islands
					bool bIsIslandTile = FMath::RandRange(0, Distance - 1) == 0;
					if(bIsIslandTile)
					{
						FVector Location = FVector(x * TileSize, y * TileSize, 0);
						SpawnMesh(World, TileMesh, Location);
					}
				}
			}
		}
		//FVector MapCenter = FVector(GridSizeX * TileSize / 2, GridSizeY * TileSize / 2, 0);
		//World->GetFirstPlayerController()->GetPawn()->SetActorRelativeLocation(MapCenter);//SetActorLocation(MapCenter);
	}
}
// Called when the game starts or when spawned
void AWorldGrid::BeginPlay()
{
	Super::BeginPlay();
}

void AWorldGrid::SpawnMesh(UWorld* World, UStaticMesh* Mesh, FVector Location)
{
	FRotator Rotation = FRotator(0, 0, 0);
	FActorSpawnParameters SpawnInfo;
	AStaticMeshActor* SpawnedStaticMeshActor = World->SpawnActor<AStaticMeshActor>(
		AStaticMeshActor::StaticClass(),
		Location,
		Rotation,
		SpawnInfo
	);
	if(SpawnedStaticMeshActor)
	{
		SpawnedStaticMeshActor->SetMobility(EComponentMobility::Movable);
		SpawnedStaticMeshActor->GetStaticMeshComponent()->SetStaticMesh(Mesh);
		SpawnedStaticMeshActor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	}
}
