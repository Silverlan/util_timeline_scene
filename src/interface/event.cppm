// SPDX-FileCopyrightText: (c) 2024 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

module;


export module timeline_scene:event;

export import std.compat;

export namespace uts {
	class Channel;
	class Event : public std::enable_shared_from_this<Event> {
	  public:
		enum class State : uint32_t { Initial = 0u, Pending, Complete };
		template<class TEvent, typename... TARGS>
		static std::shared_ptr<Event> Create(Channel &channel, TARGS... args);
		virtual ~Event();
		virtual void Initialize() = 0;

		void SetTimeRange(float tStart, float tEnd);
		std::pair<float, float> GetTimeRange() const;
		float GetStartTime() const;
		float GetEndTime() const;

		virtual void Start();
		virtual void Stop();
		virtual void Reset();
		State GetState() const;

		Channel *GetChannel() const;
		State Tick(double t, double dt);
	  protected:
		Event(Channel &channel);
		virtual State HandleTick(double t, double dt);

		State m_state = State::Initial;
		float m_startTime = 0.f;
		float m_endTime = 0.f;
		mutable std::weak_ptr<Channel> m_channel = {};
	};
};

template<class TEvent, typename... TARGS>
std::shared_ptr<uts::Event> uts::Event::Create(Channel &channel, TARGS... args)
{
	return std::shared_ptr<Event>(new TEvent(channel, std::forward<TARGS>(args)...));
}
