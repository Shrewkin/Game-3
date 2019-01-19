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
#include "Sprite.h"

namespace Behaviors
{

	Health::Health(int maxHealth, float invTime)
		: Component("Health"), maxHealth(maxHealth), currHealth(maxHealth), invincibilityTime(invTime), flashTimer(0.2f),
		  timer1(invTime), timer2(0.1f), invincible(false), invAlpha(0.5f)
	{
	}

	Component* Health::Clone() const
	{
		return new Health(*this);
	}

	void Health::Initialize()
	{
		sprite = static_cast<Sprite*>(GetOwner()->GetComponent("Sprite"));
	}

	void Health::Update(float dt)
	{
		if (invincible)
		{
			timer1 -= dt;
			timer2 -= dt;

			if (timer2 <= 0)
			{
				timer2 = flashTimer;

				if (sprite->GetAlpha() == invAlpha)
				{
					sprite->SetAlpha(1.0f);
				}
				else
				{
					sprite->SetAlpha(invAlpha);
				}
			}

			if (timer1 <= 0)
			{
				timer1 = invincibilityTime;
				invincible = false;
				sprite->SetAlpha(1.0f);
			}
		}
	}

	void Health::Add(int toAdd)
	{
		currHealth += toAdd;
		CheckCap();
	}

	void Health::Subtract(int toSubtract)
	{
		if(!invincible)
		{
			currHealth -= toSubtract;
			invincible = true;
			if (currHealth <= 0)
			{
				GetOwner()->Destroy();
			}
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
}