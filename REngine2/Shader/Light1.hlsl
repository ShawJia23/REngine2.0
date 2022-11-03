
struct Light
{
	float3 LightIntensity;
	float  StartAttenuation;
	float3 LightDirection;
	float  EndAttenuation;
	float3 Position;
	int LightType;

	float InnerCorner;
	float OuterCorner;
	float x1;
	float x2;
};

float3 GetLightDirection(Light L, float3 Pos) 
{
	if (L.LightType == 0) 
	{
		return L.LightDirection;
	}
	else if (L.LightType == 1)
	{
		//Spot
		return  L.Position - Pos;
	}
	else if (L.LightType == 2)
	{
		//Point
		return  L.Position-Pos;
	}
	return L.LightDirection;
}

float3 LinearAttenuationPointLight(Light L,float Distance)
{
	float AttenuationRange = L.EndAttenuation - L.StartAttenuation;

	return  Distance / AttenuationRange;
}

float3 SquareAttenuationPointLight(Light L, float Distance,float C,float I,float Q)
{
	return 1 / (C + I * Distance + pow(Q, 2.0f) * Distance);
}

float3 ComputeLightStrength(Light L, float3 LightDir)
{
	if (L.LightType == 0)
	{
		return L.LightIntensity;
	}
	else if (L.LightType == 1) 
	{
		//Spot
		float Distance = length(LightDir);

		if (Distance < L.EndAttenuation) 
		{
			float DotValue = dot(LightDir, L.LightDirection);

			float3 LightStrength = L.LightIntensity;

			float Theta1 = acos(DotValue);
			if (Theta1 == 0.f)
			{
				return LightStrength;
			}
			else if (Theta1 <= L.InnerCorner)
			{
				return LightStrength;
			}
			else if (Theta1 <= L.OuterCorner)
			{
				float OuterInnerDistance = L.OuterCorner - L.InnerCorner;
				float CurrentDistance = OuterInnerDistance - (Theta1 - L.InnerCorner);

				return (CurrentDistance / OuterInnerDistance) * LightStrength;
			}
			else if (Theta1 > L.OuterCorner) 
			{
				return (0, 0, 0);
			}
		}

		
	}
	else if (L.LightType == 2)
	{
		//Point
		float Distance = length(LightDir);

		if (Distance < L.EndAttenuation)
		{
			return LinearAttenuationPointLight(L, Distance) * L.LightIntensity;
			//return SquareAttenuationPointLight(L, Distance,0,0.4f,2.6f);
		}
	}

	return L.LightIntensity;
}