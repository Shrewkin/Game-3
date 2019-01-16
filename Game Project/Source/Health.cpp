//------------------------------------------------------------------------------
//
// File Name:	Health.cpp
// Author(s):	Bar Ben-zvi
// Project:		Game Prototype 3
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Health.h"
#include "GameObject.h"


Health::Health(int maxHealth)
	: Component("Health"), maxHealth(maxHealth), currHealth(maxHealth)
{
}

Component* Health::Clone() const
{
	return new Health(*this);
}

void Health::Add(int toAdd)
{
	currHealth += toAdd;
	CheckCap();
}

void Health::Subtract(int toSubtract)
{
	currHealth -= toSubtract;
	if (currHealth <= 0)
	{
		GetOwner()->Destroy();
	}
}

int Health::GetHealth()
{
	return currHealth;
}

int Health::GetMaxHealth()
{
	return maxHealth;
}

void Health::CheckCap()
{
	if (currHealth > maxHealth)
	{
		currHealth = maxHealth;
	}
}