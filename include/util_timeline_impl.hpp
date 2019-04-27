/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef __UTIL_TIMELINE_SCENE_IMPL_HPP__
#define __UTIL_TIMELINE_SCENE_IMPL_HPP__

#include "util_timeline_scene.hpp"
#include "util_timeline_channel.hpp"
#include "util_timeline_event.hpp"

template<class TTimelineScene,typename... TARGS>
	std::shared_ptr<uts::TimelineScene> uts::TimelineScene::Create(TARGS ...args) {return std::shared_ptr<TimelineScene>(new TTimelineScene(std::forward<TARGS>(args)...));}

template<class TChannel,typename... TARGS>
	std::shared_ptr<uts::Channel> uts::TimelineScene::AddChannel(const std::string &name,TARGS ...args)
{
	auto r = Channel::Create<TChannel,TARGS...>(*this,name,std::forward<TARGS>(args)...);
	m_channels.push_back(r);
	r->Initialize();
	return r;
}

template<class TChannel,typename... TARGS>
	std::shared_ptr<uts::Channel> uts::Channel::Create(TimelineScene &scene,const std::string &name,TARGS ...args) {return std::shared_ptr<Channel>(new TChannel(scene,name,std::forward<TARGS>(args)...));}

template<class TEvent,typename... TARGS>
	std::shared_ptr<uts::Event> uts::Channel::AddEvent(TARGS ...args)
{
	auto r = Event::Create<TEvent,TARGS...>(*this,std::forward<TARGS>(args)...);
	m_events.push_back(r);
	r->Initialize();
	return r;
}

#endif
