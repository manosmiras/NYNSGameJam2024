﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldGrid.h"

#include "IntVectorTypes.h"
#include "Logger.h"
#include "Engine/StaticMeshActor.h"

void AWorldGrid::SpawnTileGrid()
{
	auto World = GetWorld();
	if(World)
	{
		auto VillagePositions = GetRandomVillagePositions();
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
						if(VillageActor)
						{
							AActor* SpawnedVillage = World->SpawnActor(VillageActor, &Location);
							SpawnedVillage->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
						}
					}
					auto Distance = Position.DistanceSquared(UE::Geometry::FVector2i(x, y));
					Logger::Log("Distance: " + FString::SanitizeFloat(Distance));
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
		// Center grid
		SetActorLocation(FVector(0, -GridSizeY * TileSize, 0));
	}
}

TArray<UE::Geometry::FVector2i> AWorldGrid::GetRandomVillagePositions()
{
	auto GridFirstPosition = FVector(0, 0, 0);
	auto GridLastPosition = FVector(GridSizeX, GridSizeY, 0);
	// distance squared
	auto MaxDistance = FVector::DistSquared(GridFirstPosition, GridLastPosition);
		
	Logger::Log("Max distance: " + FString::SanitizeFloat(MaxDistance));
	
	TArray<UE::Geometry::FVector2i> VillagePositions;
	for (int i = 0; i < VillageCount; ++i)
	{
		auto AcceptableVillageDistance = MaxDistance / (VillageCount * 2);
		auto attempts = 0;
		while(true)
		{
			int x = FMath::RandRange(0, GridSizeX - 1);
			int y = FMath::RandRange(0, GridSizeY - 1);
			UE::Geometry::FVector2i Position(x, y);
			bool bIsAcceptableDistance = true;
			for (auto VillagePosition : VillagePositions)
			{
				auto Distance = Position.DistanceSquared(VillagePosition);
				if(Distance < AcceptableVillageDistance)
				{
					bIsAcceptableDistance = false;
					attempts++;
					if(attempts > 100)
					{
						AcceptableVillageDistance--;
					}
					break;
				}
			}
			if(bIsAcceptableDistance)
			{
				VillagePositions.Add(Position);
				break;
			}
		}
	}
	return VillagePositions;
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
