// Fill out your copyright notice in the Description page of Project Settings.


#include "Key.h"
#include "KeyComponent.h"
// Sets default values
A_Key::A_Key()
{
	KeyComponent = CreateDefaultSubobject<UKeyComponent>(TEXT("KeyComponent"));
}
