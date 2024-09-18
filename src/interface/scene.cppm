/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

module;

#include <vector>
#include <memory>
#include <string>

export module timeline_scene.scene;

// This causes a compiler error with MSBuild
#ifdef __linux__
namespace uts {
	class Channel;
};
#endif

export namespace uts {
#ifdef _WIN32
	class Channel;
#endif
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
