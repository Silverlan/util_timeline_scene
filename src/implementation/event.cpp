/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

module;

#include <utility>

module timeline_scene.event;

import timeline_scene.channel;

uts::Event::Event(Channel &channel) : m_channel(channel.shared_from_this()) {}
void uts::Event::SetTimeRange(float tStart, float tEnd)
{
	m_startTime = tStart;
	m_endTime = tEnd;
}
std::pair<float, float> uts::Event::GetTimeRange() const { return {m_startTime, m_endTime}; }
float uts::Event::GetStartTime() const { return m_startTime; }
float uts::Event::GetEndTime() const { return m_endTime; }
uts::Channel *uts::Event::GetChannel() const { return m_channel.lock().get(); }

uts::Event::State uts::Event::Tick(double t, double dt) { return HandleTick(t, dt); }

void uts::Event::Start() { m_state = State::Pending; }
void uts::Event::Stop() { m_state = State::Complete; }
void uts::Event::Reset() { m_state = State::Initial; }
uts::Event::State uts::Event::GetState() const { return m_state; }

uts::Event::State uts::Event::HandleTick(double t, double dt)
{
	if(t >= m_endTime)
		Stop();
	return GetState();
}
