// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "BetterSubtitleManager.generated.h"

/**
 * 
 */
UCLASS()
class EXAMPLEGAME_API UBetterSubtitleManager : public UObject
{
	GENERATED_BODY()
	
public:
	void ParseSrtString(const TCHAR* srtPath);
	void StartSubtitledAudio(const char* AudioPath, UObject* World);
	FText SubtitleForTick(float DeltaTime);

private:
	int32 StringToMilliseconds(FString& DateAsString);
	USoundWave* GetSoundWaveFromFile(const FString& FilePath);
	
	
};
