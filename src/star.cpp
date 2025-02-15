#include "../include/star.h"
#include "raylib.h"
#include "raymath.h"
#include <ctime>
#include <cmath>


// ================================
//          Player Class
// ================================
Player::Player() 
	: name("_______"), Class("Unknown"), HP(0), maxHP(25), hasShield(false), SP(0), piloting(0), repair(0), bartering(0) {
		money = 0;
		debt = -250000;
		reward_upgrade_counter = 0;
		timeCost_upgrade_counter = 0;
		weapon_upgrade_counter = 0;
		reward_upgrade_modifier = tierPercentage[0];
		timeCost_upgrade_modifier = tierPercentage2[0];
		timeRemaining = 728;
	}

//+++++ Getters +++++

std::string Player::getName() {
	return name;
}

int Player::getMoney() {
	return money;
}

int Player::getDebt() {
	return debt;
}
float Player::getTimeRemaining(){
	return timeRemaining;
}

//+++++ Setters +++++

void Player::setName(std::string new_name)
{
	name = new_name;
}
void Player::setMoney(int newMoney)
{
	money = newMoney;
}
void Player::setDebt(int newDebt)
{
	debt = newDebt;
}
void Player::setHP(int HP)
{
	HP = HP;
}
void Player::setTimeRemaining(int time)
{
	timeRemaining = time;
}

//++++++++ METHODS +++++++

// add money to player account
void Player::addMoney(int money_to_add, float reward_upgrade_modifier)
{
	money += money_to_add + (money_to_add * reward_upgrade_modifier); // modifies player money stat with money + money * percent increase
}
// add money to negative debt total
void Player::loseTime(float time_lost, float timeCost_upgrade_modifier)
{
	timeRemaining -= time_lost * timeCost_upgrade_modifier; // reduces time lost as upgrade tier goes up
}
void Player::loseTimeGradually()
{
	timeRemaining -= 1/(float)FPS;
}

/*
void Player::payMarket(int purchase)
{
	money -= purchase;
}

void Player::loseSP(int damage)
{
	SP -= damage;
	if(SP <= 0)
		hasShield = false;
}

void Player::loseHP(int damage)
{
	HP -= damage;
	if(HP <= 0)
		;
}

void Player::lvlupHP()
{
	maxHP += 25;
}
*/

//-------------------------------------------------------------------------------
//			draw functions
//-------------------------------------------------------------------------------
void DrawBtnSelected(Rectangle rct, int btn) {
	if (btnHovered == btn) {
		DrawRectangleRec(rct, DARKBLUE);
	}
}

void DrawStatusBar(Player pilot, Vector2* sbar, float timeTilRepo) {
	DrawRectangleLinesEx((Rectangle) {0, 0, SCREENWIDTH, SBARHEIGHT}, 3, WHITE);

	for (int i=0; i<SBARNUMSEGS; i++) {
		DrawLine(SBARSEG[i], 0, SBARSEG[i], SBARHEIGHT, WHITE);
	}

	DrawTextEx(sagaFont, "PILOT: ", sbar[0], SBARFONTSIZE, 0, WHITE);
	DrawTextEx(sagaFont, pilot.getName().c_str(), (Vector2) {sbar[0].x + 60, sbar[0].y}, SBARFONTSIZE, 0, WHITE);

	DrawTextEx(sagaFont, "CURRENCY: ", sbar[1], SBARFONTSIZE, 0, WHITE);
	DrawTextEx(sagaFont, std::to_string(pilot.getMoney()).c_str(), (Vector2) {sbar[1].x + 100, sbar[0].y}, SBARFONTSIZE, 0, WHITE);

	DrawTextEx(sagaFont, "DEBT: ", sbar[2], SBARFONTSIZE, 0, WHITE);
	DrawTextEx(sagaFont, std::to_string(pilot.getDebt()).c_str(), (Vector2) {sbar[2].x + 100, sbar[0].y}, SBARFONTSIZE, 0, WHITE);

	DrawTextEx(sagaFont, "TIME LEFT TIL REPO: ", sbar[3], SBARFONTSIZE, 0, WHITE);
	DrawTextEx(sagaFont, std::to_string(timeTilRepo).c_str(), (Vector2) {sbar[3].x + 200, sbar[0].y}, SBARFONTSIZE, 0, WHITE);
}

void DrawMainBtns(GUIbtn *hubBtn) {
	for (int i=0; i<HUBNUMBTNS; i++) {
		DrawBtnSelected(hubBtn[i].border, i + 3);
		DrawRectangleLinesEx(hubBtn[i].border, 2, WHITE);
	}
	DrawTextEx(sagaFont, "Interface", hubBtn[0].origin, HUBMAINFONTSIZE, 0, WHITE);
	DrawTextEx(sagaFont, "Status", hubBtn[1].origin, HUBMAINFONTSIZE, 0, WHITE);
	DrawTextEx(sagaFont, "Give Up", hubBtn[2].origin, HUBMAINFONTSIZE, 0, WHITE);
}


//-------------------------------------------------------------------------------
//			menu functions - pop menu in and out based on activation
//-------------------------------------------------------------------------------
SubMenu::SubMenu(bool leftSide) {
	float menuWidth = SCREENWIDTH / 5,
	      menuHeight = SCREENHEIGHT / 1.5;

	if (leftSide) {
		pos = (Vector2) { 0 - menuWidth, SCREENHEIGHT / 5 };
		dim = (Vector2) { menuWidth, menuHeight };
		min_x = pos.x;
		max_x = pos.x + menuWidth;
	}
	else {
		pos = (Vector2) { SCREENWIDTH, SCREENHEIGHT / 5 };
		dim = (Vector2) { menuWidth, menuHeight };
		min_x = pos.x - menuWidth;
		max_x = pos.x;
	}

	isLeftSide = leftSide;
	border = (Rectangle){ pos.x, pos.y, dim.x, dim.y };
	isActive = false;
}

void SubMenu::HandleActivation() {
	if (isActive == false) {
		isActive = true;
	}
	else {
		isActive = false;
	}
}

void SubMenu::UpdateAndDrawSelf() {
		//draw the menu in certain positions based on activation
	if (isActive && isLeftSide) {
		pos.x = max_x;
		DrawRectangleLinesEx(border, 2, WHITE);
	}
	else if (isActive && !isLeftSide) {
		pos.x = min_x;
		DrawRectangleLinesEx(border, 2, WHITE);
	}
	else if (!isActive && isLeftSide) {
		pos.x = min_x;
	}
	else {
		pos.x = max_x;
	}

	border = (Rectangle){ pos.x, pos.y, dim.x, dim.y };
}

bool SubMenu::GetActive() {
	return isActive;
}


//-------------------------------------------------------------------------------
//			code utility
//-------------------------------------------------------------------------------
float  Timer::GetCounter() {
	return frameCounter;
}

void Timer::SetCounter(float counter) {
	frameCounter = counter;
}

void Timer::Reset() {
	frameCounter = 0;
}

void Timer::Run() {
	frameCounter++;
}

bool Timer::Wait(double mark){
	if (frameCounter > FPS * mark) {
		return true;
	}
	return false;
}

	//hypotenuse to find distance
float GetDist(Vector2 x1y1, Vector2 x2y2) {
	return sqrt(pow(x2y2.x - x1y1.x, 2) + pow(x2y2.y - x1y1.y, 2) );
}


//-------------------------------------------------------------------------------
//			animation scalers
//-------------------------------------------------------------------------------
float AlphaWaveAnim(float counter, float dur, float scale) {
		//cosine equation for ease in and ease out effects
	return scale * cos((2 * counter) / (dur / 3.14) ) + (1.0 - scale);
}

void AlphaLinearAnim(float& counter, float goal, float increment, bool increase) {
	if (increase == false && counter > goal) {
		counter -= increment;
	}
	else if (increase == true && counter < goal) {
		counter += increment;
	}
}





//DEPRECATED
/*
void DrawStatusScreen(Font sagaFont) {
		Vector2 menuPos[] = {
			(Vector2) { SCREENWIDTH / 5, SCREENHEIGHT / 9 },
			(Vector2) { SCREENWIDTH / 2 + SCREENWIDTH / 10, SCREENHEIGHT / 9 },
			(Vector2) { SCREENWIDTH / 2 + SCREENWIDTH / 10, SCREENHEIGHT / 2 }
		};
		
		Rectangle menuBor[] = {
			(Rectangle) { menuPos[0].x, menuPos[0].y, SCREENWIDTH/3, SCREENHEIGHT/1.2 },	
			(Rectangle) { menuPos[1].x, menuPos[1].y, SCREENWIDTH/3, SCREENHEIGHT/3   },	
			(Rectangle) { menuPos[2].x, menuPos[2].y, SCREENWIDTH/3, SCREENHEIGHT/2.5 }
		};
 
        //Ship
	DrawRectangleLinesEx(menuBor[0], 2, WHITE);

        DrawTextEx(sagaFont, "Ship", {menuPos[0].x + MARGIN, menuPos[0].y + 50}, HUBMAINFONTSIZE, 1, WHITE);
        DrawTextEx(sagaFont, "Weapon LVL:", {menuPos[0].x + MARGIN, menuPos[0].y + 100}, HUBMAINFONTSIZE, 1, WHITE);
        DrawTextEx(sagaFont, "Shield LVL:", {menuPos[0].x + MARGIN, menuPos[0].y + 150}, HUBMAINFONTSIZE, 1, WHITE);
        DrawTextEx(sagaFont, "Gathering Tool LVL:", {menuPos[0].x + MARGIN, menuPos[0].y + 200}, HUBMAINFONTSIZE, 1, WHITE);
        DrawTextEx(sagaFont, "Overall Speed:", {menuPos[0].x + MARGIN, menuPos[0].y + 250}, HUBMAINFONTSIZE, 1, WHITE);
   	    
	//Pilot
	DrawRectangleLinesEx(menuBor[1], 2, WHITE);

        DrawTextEx(sagaFont, "Pilot: XYZ", {menuPos[1].x + MARGIN, menuPos[1].y + 50}, HUBMAINFONTSIZE, 1, WHITE);
        DrawTextEx(sagaFont, "Registered Pilot Under", {menuPos[1].x + MARGIN, menuPos[1].y + 100}, HUBSUBFONTSIZE, 1, WHITE);
        DrawTextEx(sagaFont, "the SSE Administration", {menuPos[1].x + MARGIN, menuPos[1].y + 150}, HUBSUBFONTSIZE, 1, WHITE);
        DrawTextEx(sagaFont, "License Valid Until: 04/14/2248", {menuPos[1].x + MARGIN, menuPos[1].y + 200}, HUBSUBFONTSIZE, 1, WHITE);
        DrawTextEx(sagaFont, "Birthdate:           09/12/2223", {menuPos[1].x + MARGIN, menuPos[1].y + 250}, HUBSUBFONTSIZE, 1, WHITE);

        //Debt
	DrawRectangleLinesEx(menuBor[2], 2, WHITE);

        DrawTextEx(sagaFont, "This pilot is to pay of their debt to MORT CORP by", {menuPos[2].x + MARGIN, menuPos[2].y + 50}, HUBSUBFONTSIZE, 1, WHITE);
        DrawTextEx(sagaFont, "08/28/2242", {menuPos[2].x + MARGIN, menuPos[2].y + 100}, HUBSUBFONTSIZE, 1, WHITE);
        DrawTextEx(sagaFont, "for the loan of borrowed limbs or shall forfeit their life", {menuPos[2].x + MARGIN, menuPos[2].y + 150}, HUBSUBFONTSIZE, 1, WHITE);
        DrawTextEx(sagaFont, "and body for scientific and good purposes.", {menuPos[2].x + MARGIN, menuPos[2].y + 200}, HUBSUBFONTSIZE, 1, WHITE);
        DrawTextEx(sagaFont, "MORT CORP is protected under the Right to", {menuPos[2].x + MARGIN, menuPos[2].y + 250}, HUBSUBFONTSIZE, 1, WHITE);
        DrawTextEx(sagaFont, "Dismemberment Act and the Right to Slay Act.", {menuPos[2].x + MARGIN, menuPos[2].y + 300}, HUBSUBFONTSIZE, 1, WHITE);
        DrawTextEx(sagaFont, "Debt owed to MORT CORP: Debt", {menuPos[2].x + MARGIN, menuPos[2].y + 350}, HUBSUBFONTSIZE, 1, WHITE);
}
*/

/*
Dice::Dice() {
	static bool seeded = false;
	if (!seeded) {
		//std::srand(std::time(nullptr)); 	obsolete, switched to uniform_int_distribution
		seeded = true;
	}
}

int Dice::rollD6(int numRolls = 0) {
	int total = 0;
	for (int i=0; i<numRolls; ++i) {
		//total += std::rand() % 6 + 1;		obsolete, switched to uniform_int_distribution
	}
	return total;
}
*/