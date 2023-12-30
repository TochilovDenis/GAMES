#define isDown(b) input->buttons[b].isDown
#define pressed(b) (input->buttons[b].isDown && input->buttons[b].changed)
#define released(b) (!input->buttons[b].isDown && input->buttons[b].changed)

float playerPosX = 0.f;
float playerPosY = 0.f;

internalVarible void simulateGame(Input* input) {
	clearScreen(0x8fb398);

	// Игрок
	if (pressed(BUTTON_UP)) playerPosY += 1.f;
	if (pressed(BUTTON_DOWN)) playerPosY -= 1.f;
	if (pressed(BUTTON_LEFT)) playerPosX -= 1.f;
	if (pressed(BUTTON_RIGHT)) playerPosX += 1.f;
	drawRectangle(playerPosX, playerPosY, 1, 1, 0xa265d80);

	// Прямоугольник 1
	static float posX1 = 30.f;
	static float posY1 = 30.f;
	if (pressed(BUTTON_UP)) posY1 += 1.f;
	if (pressed(BUTTON_DOWN)) posY1 -= 1.f;
	if (pressed(BUTTON_LEFT)) posX1 -= 1.f;
	if (pressed(BUTTON_RIGHT)) posX1 += 1.f;
	drawRectangle(posX1, posY1, 5, 5, 0xa3881c);

	// Прямоугольник 2
	static float posX2 = -20.f;
	static float posY2 = 20.f;
	if (pressed(BUTTON_UP)) posY2 += 1.f;
	if (pressed(BUTTON_DOWN)) posY2 -= 1.f;
	if (pressed(BUTTON_LEFT)) posX2 -= 1.f;
	if (pressed(BUTTON_RIGHT)) posX2 += 1.f;
	drawRectangle(posX2, posY2, 8, 3, 0xa3881c);
}