#include "camera.h"

Camera::Camera() {
	cameraRect.x = 0;
	cameraRect.y = 0;
	cameraRect.w = SCREEN_WIDTH;
	cameraRect.h = SCREEN_HEIGHT;
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
		startedShaking = SDL_GetTicks();
		shaking = true;
	}

	if(shaking && startedShaking + shakeDuration > SDL_GetTicks()) {
	  random_device rd;
	  mt19937 gen(rd());;
	  uniform_int_distribution<int> dis(-5, 5);

		// if(cameraRect.x <= 0) {
			cameraRect.x = dis(gen);
		// } else {
		// 	cameraRect.x = -dis(gen);
		// }

		// if(cameraRect.y <= 0) {
			cameraRect.y = dis(gen);
		// } else {
		// 	cameraRect.y = -dis(gen);
		// }
	}

	if(shaking && startedShaking + shakeDuration <= SDL_GetTicks()) {
		cameraRect.x = 0;
		shaking = false;
	}
}
