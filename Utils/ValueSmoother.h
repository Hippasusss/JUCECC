/*
  ==============================================================================

    ValueSmoother.h
    Created: 9 Mar 2020 6:00:32pm
    Author:  Danny Herbert

  ==============================================================================
*/

#pragma once
#include "juce_events/juce_events.h"
using namespace juce;

template <typename ValueType>

class ValueSmoother : Timer
{
public:
	ValueSmoother() : value(0), destinationValue(0){}
	ValueSmoother(ValueType initValue, int refreshRateHz);
	ValueSmoother(ValueType initValue, int refreshRateHz, float ARTime);
	ValueSmoother& operator=(ValueSmoother&& other) noexcept;
	ValueSmoother& operator=(const ValueSmoother& other) noexcept;
	ValueSmoother& operator=(ValueType other) noexcept;
	ValueType operator-(ValueType other) noexcept;
	ValueType operator+(ValueType other) noexcept;
	operator ValueType&();
	bool operator>(const ValueSmoother& other) noexcept;
	bool operator<(const ValueSmoother& other) noexcept;

	void setValue(ValueType val);
	void setAttack(float newRate);
	void setRelease(float newRate);
	void setRefreshRate(int newRate);
	ValueType getValue() const;

	void timerCallback() override;

private:
	ValueType value;
	ValueType destinationValue;
	float attack  = 0.5;
	float release = 0.5;
};

template <typename ValueType>
ValueSmoother<ValueType>::ValueSmoother(ValueType initValue, int refreshRateHz): value(initValue),
                                                                               destinationValue(initValue)
{
	startTimerHz(refreshRateHz);
}

template <typename ValueType>
ValueSmoother<ValueType>::ValueSmoother(ValueType initValue, int refreshRateHz, float ARTime): value(initValue),
                                                                                             destinationValue(initValue)
{
	release = ARTime;
	attack = ARTime;
	startTimerHz(refreshRateHz);
}

template <typename ValueType>
ValueSmoother<ValueType>& ValueSmoother<ValueType>::operator=(ValueSmoother&& other) noexcept
{
	if (this == &other)
		return other;
	return *this;
}

template <typename ValueType>
ValueSmoother<ValueType>& ValueSmoother<ValueType>::operator=(const ValueSmoother& other) noexcept
{
	destinationValue = other.destinationValue;
	return *this;
}

template <typename ValueType>
ValueSmoother<ValueType>& ValueSmoother<ValueType>::operator=(ValueType other) noexcept
{
	destinationValue = other;
	return *this;
}

template <typename ValueType>
ValueType ValueSmoother<ValueType>::operator-(ValueType other) noexcept
{
	return destinationValue - other;
}

template <typename ValueType>
ValueType ValueSmoother<ValueType>::operator+(ValueType other) noexcept
{
	return destinationValue + other;
}

template <typename ValueType>
ValueSmoother<ValueType>::operator ValueType&()
{
	return value;
}

template <typename ValueType>
bool ValueSmoother<ValueType>::operator>(const ValueSmoother& other) noexcept
{
	return destinationValue > other.destinationValue;
}

template <typename ValueType>
bool ValueSmoother<ValueType>::operator<(const ValueSmoother& other) noexcept
{
	return destinationValue < other.destinationValue;
}

template <typename ValueType>
void ValueSmoother<ValueType>::setValue(ValueType val)
{
	destinationValue = val;
}

template <typename ValueType>
void ValueSmoother<ValueType>::setAttack(float newRate)
{
	attack = newRate / getTimerInterval();
}

template <typename ValueType>
void ValueSmoother<ValueType>::setRelease(float newRate)
{
	release = newRate / getTimerInterval();
}

template <typename ValueType>
void ValueSmoother<ValueType>::setRefreshRate(int newRate)
{
	stopTimer();
	startTimerHz(newRate);
}

template <typename ValueType>
ValueType ValueSmoother<ValueType>::getValue() const
{
	return value;
}

template <typename ValueType>
void ValueSmoother<ValueType>::timerCallback()
{
	const float envelopeTime = destinationValue > value ? attack : release;
	const float timerInterval = static_cast<float>(getTimerInterval()) / 1000.0f;
	const float delta = destinationValue - value;
	value += delta / (envelopeTime / timerInterval);
}

