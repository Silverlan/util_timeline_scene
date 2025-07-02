// SPDX-FileCopyrightText: (c) 2019 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

#if 0
#include <iostream>
#include "util_timeline_scene.hpp"
#include "util_timeline_channel.hpp"
#include "util_timeline_event.hpp"

int main(int argc,char *argv[])
{
	auto scene = uts::TimelineScene::Create<uts::TimelineScene>();
	auto channel = scene->AddChannel<uts::Channel>("Test");
	auto ev = channel->AddEvent<uts::Event>();

	return EXIT_SUCCESS;
}

#endif
