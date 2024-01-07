// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldGrid.h"

#include "Engine/StaticMeshActor.h"

void AWorldGrid::SpawnTileGrid()
{
	auto World = GetWorld();
	if(World)
	{
		for (int y = 0; y < GridSizeY; ++y)
		{
			for (int x = 0; x < GridSizeX; ++x)
			{
				FVector Location = FVector(x * TileSize, y * TileSize, 0);
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
					SpawnedStaticMeshActor->GetStaticMeshComponent()->SetStaticMesh(TileMesh);
					SpawnedStaticMeshActor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
				}
			}
		}
	}
}
// Called when the game starts or when spawned
void AWorldGrid::BeginPlay()
{
	Super::BeginPlay();
}
