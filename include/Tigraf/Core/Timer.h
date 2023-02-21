#pragma once

namespace Tigraf
{
	class Application;

	struct TimeStep
	{
		double m_TotalTime = 0.0;
		double m_FrameTime = 0.0f;
	
		operator float() const { return m_FrameTime; }
	};

	class Timer
	{
		friend class Application;

	protected:
		Timer() = default;

		TimeStep m_TimeStep;

		const TimeStep& getTimeStep() const { return m_TimeStep; }
		virtual const TimeStep& advance() = 0;
		virtual void calibrate() = 0;
	};

	class glfwTimer : public Timer
	{
	public:
		glfwTimer() = default;

	protected:
		virtual const TimeStep& advance() override;
		virtual void calibrate() override;
	};

	class sdlTimer : public Timer
	{
	public:
		sdlTimer() = default;

	protected:
		virtual const TimeStep& advance() override;
		virtual void calibrate() override;
	};

	class ChronoTimer : public Timer
	{
	public:
		ChronoTimer() = default;

	protected:
		virtual const TimeStep& advance() override;
		virtual void calibrate() override;
	};
}