// SPDX-FileCopyrightText: (c) 2024 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

module;


export module timeline_scene:channel;

export import std;

export namespace uts {
	class TimelineScene;
	class Event;
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
