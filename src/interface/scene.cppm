// SPDX-FileCopyrightText: (c) 2024 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

module;

#include <vector>
#include <memory>
#include <string>

export module timeline_scene:scene;

export namespace uts {
	class Channel;
	class TimelineScene : public std::enable_shared_from_this<TimelineScene> {
	  public:
		enum class State : uint32_t { Initial = 0, Playing, Paused, Stopped };

		template<class TTimelineScene, typename... TARGS>
		static std::shared_ptr<TimelineScene> Create(TARGS... args);
		virtual ~TimelineScene() = default;

		const std::vector<std::shared_ptr<Channel>> &GetChannels() const;
		std::vector<std::shared_ptr<Channel>> &GetChannels();

		std::shared_ptr<Channel> GetChannel(const std::string &name);
		bool HasChannel(const std::string &name);
		void RemoveChannel(const Channel &channel);

		template<class TChannel, typename... TARGS>
		std::shared_ptr<Channel> AddChannel(const std::string &name, TARGS... args);

		void Play();
		void Pause();
		void Stop();
		void Rewind();
		void Tick(double dt);
		State GetState() const;
		bool IsPlaying() const;
		bool IsPaused() const;
		bool IsStopped() const;
	  protected:
		TimelineScene() = default;
		virtual void OnStateChanged(State oldState, State newState);
		virtual void HandleTick(double dt);

		std::vector<std::shared_ptr<Channel>> m_channels = {};
		double m_time = 0.0;
		State m_state = State::Initial;

		std::vector<std::shared_ptr<Channel>>::iterator FindChannel(const std::string &name);
	};
};
