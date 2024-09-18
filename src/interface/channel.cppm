/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

module;

#include <vector>
#include <string>
#include <memory>

export module timeline_scene.channel;

// This causes a compiler error with MSBuild
#ifdef __linux__
namespace uts {
	class TimelineScene;
	class Event;
};
#endif

export namespace uts {
#ifdef _WIN32
	class TimelineScene;
	class Event;
#endif
	class Channel : public std::enable_shared_from_this<Channel> {
	  public:
		template<class TChannel, typename... TARGS>
		static std::shared_ptr<Channel> Create(TimelineScene &scene, const std::string &name, TARGS... args);
		virtual ~Channel() = default;
		virtual void Initialize();

		const std::vector<std::shared_ptr<Event>> &GetEvents() const;
		std::vector<std::shared_ptr<Event>> &GetEvents();

		const std::string &GetName() const;
		void SetName(const std::string &name);

		TimelineScene *GetScene() const;
		void Tick(double t, double dt);
		void Reset();

		template<class TEvent, typename... TARGS>
		std::shared_ptr<Event> AddEvent(TARGS... args);
	  protected:
		Channel(TimelineScene &scene, const std::string &name);
		virtual void HandleTick(double t, double dt);

		std::vector<std::shared_ptr<Event>> m_events = {};
		std::string m_name = {};
		mutable std::weak_ptr<TimelineScene> m_scene = {};
	};
};
