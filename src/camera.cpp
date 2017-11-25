#include "camera.h"

void Camera::init() {
	cameraRect.x = 0;
	cameraRect.y = 0;
	cameraRect.w = SCREEN_WIDTH;
	cameraRect.h = SCREEN_HEIGHT;

	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	nuke = Mix_LoadWAV("nuke.wav");
}

void Camera::draw(Graphics &graphics) {
	SDL_SetRenderDrawColor(graphics.getRenderer(), 255, 0, 255, 255);
	SDL_RenderDrawRect(graphics.getRenderer(), &cameraRect);
}

SDL_Rect Camera::getRect() {
	return cameraRect;
}

bool Camera::getShaking() {
	return shaking;
}

void Camera::shake() {
	if(!shaking) {
		//Mix_PlayChannel(-1, nuke, 0);
		startedShaking = SDL_GetTicks();
		shaking = true;
	}

	if(shaking && startedShaking + shakeDuration > SDL_GetTicks()) {
		if((startedShaking + shakeDuration) - SDL_GetTicks() <= shakeDuration - 100) {
		  random_device rd;
		  mt19937 gen(rd());
		  uniform_int_distribution<int> dis(-5, 5);

			cameraRect.x = dis(gen);
			cameraRect.y = dis(gen);
		}
	}

	if(shaking && startedShaking + shakeDuration <= SDL_GetTicks()) {
		cameraRect.x = 0;
		shaking = false;
	}
}

void Camera::clean() {
	Mix_FreeChunk(nuke);
	Mix_CloseAudio();
	cout << "Camera cleaned..." << endl;
}
