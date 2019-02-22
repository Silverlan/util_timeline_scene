/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

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
