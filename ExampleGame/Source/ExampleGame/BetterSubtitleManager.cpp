// Fill out your copyright notice in the Description page of Project Settings.

#include "ExampleGame.h"
#include "SubtitleEntity.h"
#include "Regex.h"
#include "BetterSubtitleManager.h"

const FRegexPattern TIME_RANGE_PATTERN(TEXT("^(\\d\\d:\\d\\d:\\d\\d,[\\d]+) --> (\\d\\d:\\d\\d:\\d\\d,[\\d]+)$"));
const FRegexPattern TIME_PATTERN(TEXT("^(\\d\\d):(\\d\\d):(\\d\\d),([\\d]+)$"));
const FRegexPattern ID_PATTERN(TEXT("^[\\d]+$"));

const int32 SECOND_TO_MILLIS = 1000;
const int32 MINUTE_TO_MILLIS = 60 * SECOND_TO_MILLIS;
const int32 HOUR_TO_MILLIS = 60 * MINUTE_TO_MILLIS;

double TimeCounter;
int32 LastIndex;

TArray<USubtitleEntity*> SubtitleEntities;

void UBetterSubtitleManager::ParseSrtString(const TCHAR* SrtPath)
{
	SubtitleEntities.Empty();
	FString Content;
	FFileHelper::LoadFileToString(Content, SrtPath, 0U);
	TArray<FString>* SrtLines = new TArray<FString>();
	Content.ParseIntoArrayLines(*SrtLines, false);

	for (auto It = SrtLines->CreateConstIterator(); It; ++It) {
		USubtitleEntity* SubtitleEntity = NewObject<USubtitleEntity>(USubtitleEntity::StaticClass());

		// subtitle id
		FRegexMatcher IdMatcher(ID_PATTERN, *It);
		if (IdMatcher.FindNext())
		{
			int32 SubId = FCString::Atoi(*IdMatcher.GetCaptureGroup(0));
			SubtitleEntity->SetSubId(SubId);
			++It;
		}

		// time range
		FRegexMatcher TimeRangeMatcher(TIME_RANGE_PATTERN, *It);
		if (TimeRangeMatcher.FindNext())
		{
			FString FromText = TimeRangeMatcher.GetCaptureGroup(1);
			FString ToText = TimeRangeMatcher.GetCaptureGroup(2);
			int32 FromMillis = StringToMilliseconds(FromText);
			int32 ToMillis = StringToMilliseconds(ToText);
			TRange<int32>* MillisRange = new TRange<int32>(FromMillis, ToMillis);
			SubtitleEntity->SetRange(MillisRange);
			++It;
		}

		// subtitle text
		FString SubText = "";
		while (!(*It).IsEmpty()) {
			FString Replaced = (*It).Replace(UTF8_TO_TCHAR("<br/>"), UTF8_TO_TCHAR("\n"));
			SubText.Append(Replaced);
			++It;
			if (!(*It).IsEmpty()) {
				SubText.AppendChar('\n');
			}
		}
		SubtitleEntity->SetText(SubText);

		// add to array
		SubtitleEntities.Add(SubtitleEntity);
	}
}

void UBetterSubtitleManager::StartSubtitledAudio(const char* AudioPath, UObject* World) {
	TimeCounter = 0;
	LastIndex = 0;

	// start audio here
	USoundWave* Sound = GetSoundWaveFromFile(AudioPath);
	UGameplayStatics::PlaySound2D(World, Sound);
}

FText UBetterSubtitleManager::SubtitleForTick(float DeltaTime) {
	TimeCounter += DeltaTime * SECOND_TO_MILLIS;
	FText Subtitle;

	for (int32 i = LastIndex; i < SubtitleEntities.Num(); i++) {
		TRange<int32>* LastRange = SubtitleEntities[i]->GetRange();

		if (LastRange->Contains(TimeCounter)) {
			LastIndex = i;
			Subtitle = SubtitleEntities[i]->GetViewableText();
			break;
		}
		else if (TimeCounter < LastRange->GetLowerBoundValue()) {
			break;
		}
	}

	return Subtitle;
}

int32 UBetterSubtitleManager::StringToMilliseconds(FString& DateAsString) {
	FRegexMatcher TimeMatcher(TIME_PATTERN, DateAsString);
	int32 Result = -1;

	if (TimeMatcher.FindNext())
	{
		int32 Hour = FCString::Atoi(*TimeMatcher.GetCaptureGroup(1));
		int32 Minute = FCString::Atoi(*TimeMatcher.GetCaptureGroup(2));
		int32 Second = FCString::Atoi(*TimeMatcher.GetCaptureGroup(3));
		int32 Millisecond = FCString::Atoi(*TimeMatcher.GetCaptureGroup(4));
		Result = Hour * HOUR_TO_MILLIS
			+ Minute * MINUTE_TO_MILLIS
			+ Second * SECOND_TO_MILLIS
			+ Millisecond;
	}

	return Result;
}

USoundWave* UBetterSubtitleManager::GetSoundWaveFromFile(const FString& FilePath)
{
	USoundWave* Sound = NewObject<USoundWave>(USoundWave::StaticClass());

	if (!Sound)
		return nullptr;

	TArray < uint8 > RawFile;

	FFileHelper::LoadFileToArray(RawFile, FilePath.GetCharArray().GetData());
	FWaveModInfo WaveInfo;

	if (WaveInfo.ReadWaveInfo(RawFile.GetData(), RawFile.Num()))
	{
		Sound->InvalidateCompressedData();

		Sound->RawData.Lock(LOCK_READ_WRITE);
		void* LockedData = Sound->RawData.Realloc(RawFile.Num());
		FMemory::Memcpy(LockedData, RawFile.GetData(), RawFile.Num());
		Sound->RawData.Unlock();

		int32 DurationDiv = *WaveInfo.pChannels * *WaveInfo.pBitsPerSample * *WaveInfo.pSamplesPerSec;
		if (DurationDiv)
		{
			Sound->Duration = *WaveInfo.pWaveDataSize * 8.0f / DurationDiv;
		}
		else
		{
			Sound->Duration = 0.0f;
		}
		Sound->SampleRate = *WaveInfo.pSamplesPerSec;
		Sound->NumChannels = *WaveInfo.pChannels;
		Sound->RawPCMDataSize = WaveInfo.SampleDataSize;
		Sound->SoundGroup = ESoundGroup::SOUNDGROUP_Default;
	}
	else {
		return nullptr;
	}

	return Sound;
}


