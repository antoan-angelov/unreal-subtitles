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
	void SetSubId(int id);
	int GetSubId();
	void SetRange(TRange<int32>* range);
	TRange<int32>* GetRange();
	void SetText(FString text);
	FString GetText();
	FText GetViewableText();
private:
	int id;
	TRange<int32>* range;
	FString text;
	FText viewableText;
	
	
};
