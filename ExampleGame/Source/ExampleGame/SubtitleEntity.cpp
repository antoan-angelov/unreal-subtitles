// Fill out your copyright notice in the Description page of Project Settings.

#include "ExampleGame.h"
#include "SubtitleEntity.h"

void USubtitleEntity::SetSubId(int id)
{
	this->id = id;
}

int USubtitleEntity::GetSubId()
{
	return id;
}

void USubtitleEntity::SetRange(TRange<int32>* range)
{
	this->range = range;
}

TRange<int32>* USubtitleEntity::GetRange()
{
	return range;
}

void USubtitleEntity::SetText(FString text) {
	this->text = text;
	this->viewableText = FText::FromString(text);
}

FString USubtitleEntity::GetText()
{
	return text;
}

FText USubtitleEntity::GetViewableText()
{
	return viewableText;
}




