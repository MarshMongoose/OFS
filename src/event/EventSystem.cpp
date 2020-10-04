#include "EventSystem.h"

int32_t EventSystem::FunscriptActionsChangedEvent = 0;
int32_t EventSystem::FunscriptActionClickedEvent = 0;

int32_t EventSystem::WakeupOnMpvEvents = 0; 
int32_t EventSystem::WakeupOnMpvRenderUpdate = 0;

int32_t EventSystem::FileDialogOpenEvent = 0;
int32_t EventSystem::FileDialogSaveEvent = 0;

int32_t EventSystem::FfmpegAudioProcessingFinished = 0;

int32_t EventSystem::MpvVideoLoaded = 0;

void EventSystem::setup()
{
	FunscriptActionsChangedEvent = SDL_RegisterEvents(1);
	FunscriptActionClickedEvent = SDL_RegisterEvents(1);
	WakeupOnMpvEvents = SDL_RegisterEvents(1);
	WakeupOnMpvRenderUpdate = SDL_RegisterEvents(1);
	FileDialogOpenEvent = SDL_RegisterEvents(1);
	FileDialogSaveEvent = SDL_RegisterEvents(1);
	FfmpegAudioProcessingFinished = SDL_RegisterEvents(1);
	MpvVideoLoaded = SDL_RegisterEvents(1);
}

void EventSystem::PushEvent(SDL_Event& event)
{
	for (auto& handler : handlers) {
		if (handler.eventType == event.type)
			handler.func(event);
	}
}

void EventSystem::Subscribe(int32_t eventType, void* listener, EventHandlerFunc handler)
{
	handlers.emplace_back(eventType, listener, handler);
	LOGF_INFO("Total event listeners: %d", (int)handlers.size());
}

void EventSystem::Unsubscribe(int32_t eventType, void* listener)
{
	auto it = std::find_if(handlers.begin(), handlers.end(),
		[&](auto& handler) {
			return handler.listener == listener;
	});

	if (it != handlers.end()) {
		handlers.erase(it);
		LOGF_INFO("Total event listeners: %d", (int)handlers.size());
	}
	else {
		LOG_ERROR("Failed to unsubscribe event.");
		FUN_ASSERT(false, "please investigate");
	}
}
