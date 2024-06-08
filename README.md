
# UnrealEnginePID
The FPIDFloat struct is a blueprintable data structure designed for implementing a PID (Proportional, Integral, Derivative) controller in Unreal Engine. This struct provides the necessary functionality to compute control output based on the current and target values, with parameters for tuning the PID controller.

## Constructors

### FPIDFloat()
Default constructor that initializes the PID parameters with default values:\
**Kp** = *1.0f*\
**Ki** = *0.1f*\
**Kd** = *0.01f*

### FPIDFloat(float InKp, float InKi, float InKd)
Parameterized constructor that allows initialization with custom PID parameters.

Parameters:\
**InKp**: Proportional gain.\
**InKi**: Integral gain.\
**InKd**: Derivative gain.

## Example Usage

### Initialization
FPIDFloat PIDController = FPIDFloat(1.0f, 0.1f, 0.01f);

PID controller output can be computed using the following call. Usually this is done inside of a looping function, like Tick() or similar: 

    float ControlOutput = PIDController.Compute(CurrentValue, TargetValue, DeltaTime);

FPIDFloat struct is a BlueprintType, so it can be exposed as a Blueprint variable using the following decorator:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Desired Category")  
    FPIDFloat PIDController;
