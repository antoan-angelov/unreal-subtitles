// Fill out your copyright notice in the Description page of Project Settings.

#include "ExampleGame.h"
#include "SubtitleEntity.h"

void USubtitleEntity::SetSubId(int SubId)
{
	this->SubId = SubId;
}

int USubtitleEntity::GetSubId()
{
	return SubId;
}

void USubtitleEntity::SetRange(TRange<int32>* MillisRange)
{
	this->MillisRange = MillisRange;
}

TRange<int32>* USubtitleEntity::GetRange()
{
	return MillisRange;
}

void USubtitleEntity::SetText(FString SubText) {
	this->SubText = SubText;
	this->SubViewableText = FText::FromString(SubText);
}

FString USubtitleEntity::GetText()
{
	return SubText;
}

FText USubtitleEntity::GetViewableText()
{
	return SubViewableText;
}




