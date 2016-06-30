// Fill out your copyright notice in the Description page of Project Settings.

#include "ExampleGame.h"
#include "SubtitleActor.h"
#include "BetterSubtitleManager.h"

UBetterSubtitleManager* SubtitleManager;

// Sets default values
ASubtitleActor::ASubtitleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SubtitleManager = NewObject<UBetterSubtitleManager>();
	SubtitleManager->ParseSrtString(UTF8_TO_TCHAR("C:\\Users\\Antoan\\Desktop\\Game Engine Architectures Repo\\ExampleGame\\Resources\\Sia-Chandelier-resync.srt"));
}

// Called when the game starts or when spawned
void ASubtitleActor::BeginPlay()
{
	Super::BeginPlay();
	SubtitleManager->StartSubtitledAudio("C:\\Users\\Antoan\\Desktop\\Game Engine Architectures Repo\\ExampleGame\\Resources\\Sia_Chandlier.wav", GetWorld());
}

// Called every frame
void ASubtitleActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	SubtitleText = SubtitleManager->SubtitleForTick(DeltaTime);
}

