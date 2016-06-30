// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "SubtitleEntity.generated.h"

/**
 * 
 */
UCLASS()
class EXAMPLEGAME_API USubtitleEntity : public UObject
{
	GENERATED_BODY()
	
public:
	void SetSubId(int SubId);
	int GetSubId();
	void SetRange(TRange<int32>* MillisRange);
	TRange<int32>* GetRange();
	void SetText(FString SubText);
	FString GetText();
	FText GetViewableText();
private:
	int SubId;
	TRange<int32>* MillisRange;
	FString SubText;
	FText SubViewableText;
	
	
};
