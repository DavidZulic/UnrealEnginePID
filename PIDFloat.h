#pragma once

#include "CoreMinimal.h"
#include "PIDFloat.generated.h"

USTRUCT(BlueprintType)
struct QUADSKI_API FPIDFloat
{
	GENERATED_BODY()

	FPIDFloat()
	{
		Kp = 1.0f;
		Ki = 0.1f;
		Kd = 0.01f;
	}

	FPIDFloat(float InKp, float InKi, float InKd)
	{
		Kp = InKp;
		Ki = InKi;
		Kd = InKd;
	}

	float Compute(float CurrentValue, float TargetValue, float DeltaTime)
	{
		const float Error = TargetValue - CurrentValue;
		Integral += Error * DeltaTime;
		Integral = FMath::Clamp(Integral, -IntegralLimit, IntegralLimit);

		const float Derivative = (Error - PreviousError) / DeltaTime;
		PreviousError = Error;

		const float Output = (Kp * Error) + (Ki * Integral) + (Kd * Derivative);
		return FMath::Clamp(Output, -OutputLimit, OutputLimit);
	}

	// Proportional term
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Kp = 1.0f;

	// Integral term
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Ki = 0.1f;

	// Derivative term
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Kd = 0.01f;

	// Integral value limit, used for anti-windup 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float IntegralLimit = 10000000.f;

	// Output value limit, used for anti-windup
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float OutputLimit = 10000000.f;

private:
	// Stores the previous error value for the derivative calculation
	float PreviousError = 0.f;

	// Accumulates the integral of the error over time
	float Integral = 0.f;
};
