/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

module;

#include <memory>

export module timeline_scene.event;

export namespace uts {
	class Event : public std::enable_shared_from_this<Event> {
	  public:
		enum class State : uint32_t { Initial = 0u, Pending, Complete };
		template<class TEvent, typename... TARGS>
		static std::shared_ptr<Event> Create(class Channel &channel, TARGS... args);
		virtual ~Event() = default;
		virtual void Initialize() = 0;

		void SetTimeRange(float tStart, float tEnd);
		std::pair<float, float> GetTimeRange() const;
		float GetStartTime() const;
		float GetEndTime() const;

		virtual void Start();
		virtual void Stop();
		virtual void Reset();
		State GetState() const;

		class Channel *GetChannel() const;
		State Tick(double t, double dt);
	  protected:
		Event(class Channel &channel);
		virtual State HandleTick(double t, double dt);

		State m_state = State::Initial;
		float m_startTime = 0.f;
		float m_endTime = 0.f;
		mutable std::weak_ptr<class Channel> m_channel = {};
	};
};

template<class TEvent, typename... TARGS>
std::shared_ptr<uts::Event> uts::Event::Create(class Channel &channel, TARGS... args)
{
	return std::shared_ptr<Event>(new TEvent(channel, std::forward<TARGS>(args)...));
}
