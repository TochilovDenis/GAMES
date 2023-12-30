#define isDown(b) input->buttons[b].isDown
#define pressed(b) (input->buttons[b].isDown && input->buttons[b].changed)
#define released(b) (!input->buttons[b].isDown && input->buttons[b].changed)

float playerPosX = 0.f;
float playerPosY = 0.f;

internalVarible void simulateGame(Input* input) {
	clearScreen(0x8fb398);
	if (pressed(BUTTON_UP)) playerPosY += 1.f;
	if (pressed(BUTTON_DOWN)) playerPosY -= 1.f;
	if (pressed(BUTTON_LEFT)) playerPosX -= 1.f;
	if (pressed(BUTTON_RIGHT)) playerPosX += 1.f;

	drawRectangle(playerPosX, playerPosY, 1, 1, 0xa265d80);
	drawRectangle(30, 30, 5, 5, 0xa3881c);
	drawRectangle(-20, 20, 8, 3, 0xa3881c);
}