// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "FirebaseTrace.generated.h"

/** Trace for Performance Monitoring */
UCLASS()
class ULTIMATEMOBILEKIT_API UFirebaseTrace : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	/** Creates a Trace object with given name and start the trace. */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Performance Monitoring", meta = (DisplayName = "Firebase Performance Monitoring Start Performance Trace"))
	static UFirebaseTrace* StartPerformanceTrace(const FString& Name);

	/** Stops the trace if the trace is active. */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Performance Monitoring", meta = (DisplayName = "Stop"))
	void Stop() const;

	/** Atomically increments the metric with the given name in this trace by the incrementBy value. */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Performance Monitoring", meta = (DisplayName = "Increment Metric"))
	void IncrementMetric(const FString& MetricName, int32 IncrementValue = 1) const;

	/** Sets the value of the metric with the given name in this trace to the value provided. */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Performance Monitoring", meta = (DisplayName = "Put Metric"))
	void PutMetric(const FString& MetricName, int32 Value) const;

	/** Gets the value of the metric with the given name in the current trace. */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Ultimate Mobile Kit|Performance Monitoring", meta = (DisplayName = "Get Metric"))
	const int32 GetMetric(const FString& MetricName) const;

	/** Sets a String value for the specified attribute. */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Performance Monitoring", meta = (DisplayName = "Put Attribute"))
	void PutAttribute(const FString& Attribute, const FString& Value) const;

	/** Removes an already added attribute from the Traces. */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Performance Monitoring", meta = (DisplayName = "Remove Attribute"))
	void RemoveAttribute(const FString& Attribute) const;

	/** Returns the value of an attribute. */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Ultimate Mobile Kit|Performance Monitoring", meta = (DisplayName = "Get Attribute"))
	const FString GetAttribute(const FString& Attribute) const;

private:
	FString TraceName;
};
