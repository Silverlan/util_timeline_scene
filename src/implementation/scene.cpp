// SPDX-FileCopyrightText: (c) 2024 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

module;

#include <memory>
#include <cctype>
#include <algorithm>
#include <string>
#include <vector>
#include <string_view>

module timeline_scene;

import :scene;
import :channel;

template<class TTimelineScene, typename... TARGS>
std::shared_ptr<uts::TimelineScene> uts::TimelineScene::Create(TARGS... args)
{
	return std::shared_ptr<TimelineScene>(new TTimelineScene(std::forward<TARGS>(args)...));
}

template<class TChannel, typename... TARGS>
std::shared_ptr<uts::Channel> uts::TimelineScene::AddChannel(const std::string &name, TARGS... args)
{
	auto r = Channel::template Create<TChannel, TARGS...>(*this, name, std::forward<TARGS>(args)...);
	m_channels.push_back(r);
	r->Initialize();
	return r;
}

const std::vector<std::shared_ptr<uts::Channel>> &uts::TimelineScene::GetChannels() const { return const_cast<TimelineScene *>(this)->GetChannels(); }
std::vector<std::shared_ptr<uts::Channel>> &uts::TimelineScene::GetChannels() { return m_channels; }

static bool ichar_equals(char a, char b) { return std::tolower(static_cast<unsigned char>(a)) == std::tolower(static_cast<unsigned char>(b)); }
std::vector<std::shared_ptr<uts::Channel>>::iterator uts::TimelineScene::FindChannel(const std::string &name)
{
	return std::find_if(m_channels.begin(), m_channels.end(), [&name](const std::shared_ptr<Channel> &channel) { return std::ranges::equal(channel->GetName(), name, ichar_equals); });
}
std::shared_ptr<uts::Channel> uts::TimelineScene::GetChannel(const std::string &name)
{
	auto it = FindChannel(name);
	return (it != m_channels.end()) ? *it : nullptr;
}
bool uts::TimelineScene::HasChannel(const std::string &name) { return (GetChannel(name) != nullptr) ? true : false; }
void uts::TimelineScene::RemoveChannel(const Channel &channel)
{
	auto it = std::find_if(m_channels.begin(), m_channels.end(), [&channel](const std::shared_ptr<Channel> &channelOther) { return channelOther.get() == &channel; });
	if(it == m_channels.end())
		return;
	m_channels.erase(it);
}
void uts::TimelineScene::OnStateChanged(State oldState, State newState) {}
void uts::TimelineScene::Play()
{
	if(IsPlaying())
		return;
	auto old = m_state;
	m_state = State::Playing;
	OnStateChanged(old, m_state);
}
void uts::TimelineScene::Pause()
{
	if(IsPaused())
		return;
	auto old = m_state;
	m_state = State::Paused;
	OnStateChanged(old, m_state);
}
void uts::TimelineScene::Stop()
{
	if(IsPaused())
		return;
	auto old = m_state;
	m_state = State::Stopped;
	Rewind();
	OnStateChanged(old, m_state);
}
void uts::TimelineScene::Rewind()
{
	m_time = 0.0;
	for(auto &channel : m_channels)
		channel->Reset();
}
void uts::TimelineScene::Tick(double dt)
{
	if(IsPlaying() == false || dt <= 0.0)
		return;
	HandleTick(dt);
}
void uts::TimelineScene::HandleTick(double dt)
{
	m_time += dt;
	for(auto &channel : m_channels)
		channel->Tick(m_time, dt);
}
uts::TimelineScene::State uts::TimelineScene::GetState() const { return m_state; }
bool uts::TimelineScene::IsPlaying() const { return m_state == State::Playing; }
bool uts::TimelineScene::IsPaused() const { return m_state == State::Paused; }
bool uts::TimelineScene::IsStopped() const { return m_state == State::Stopped; }
