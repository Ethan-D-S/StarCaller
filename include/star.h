#ifndef STAR_H
#define STAR_H

#define _USE_MATH_DEFINES

//includes
#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <string>
#include <vector>
#include <sstream>

//defines
#define FPS 60
#define MAINMENUFONTSIZE 30
#define HUBNUMBTNS 4
#define HUBMAINFONTSIZE 36
#define HUBSUBFONTSIZE 24
#define HUBBTNWIDTH 250
#define HUBBTNHEIGHT 40 
#define SBARHEIGHT 30
#define SBARFONTSIZE 22
#define SBARNUMSEGS 3
#define NUMPLANETS 7
#define NUMMISSIONS 5
#define MAXSTARPTX 200
#define ORBITALPOINTS 10
#define ORBITALPOINTSFULL 50
#define PLANETBOUNDS 100
#define NUMALPHACHANNELS 10

//screen dimensions
const int SCREENWIDTH = 1920,
          SCREENHEIGHT = 1080;

const float SBARSEG[SBARNUMSEGS] = {200, 400, 600},
			MARGIN = 30,
			BTNPADDING = 2;

//upgrade tier modifers
const float tierPercentage[6] = {0.05, 0.1, 0.25, 0.40, 0.75, 1.0}; // access to assign values to player upgrade tiers
const float tierPercentage2[6] = {1.0, 0.9, 0.8, 0.6, 0.4, 0.2}; // access to assign values to player upgrade tiers

//enums
typedef enum GameScreen { LOGO = 0, TITLE, MAINMENU, INTRO, HUB, GAMEOVER, RETRY, SUCCESS } GameScreen;
typedef enum Buttons { NOBTN, NEWGAMEBTN, EXITBTN,
			BOARDBTN, STATUSBTN, MARKETBTN, GIVEUPBTN,
			ODDJOBBTN, GATHERBTN, SALVAGEBTN, BOUNTYBTN, RAIDBTN,
			BACKBTN
} Buttons;

enum Missions { ODDJOBMISSION, GATHERMISSION, SALVAGEMISSION, BOUNTYMISSION, RAIDMISSION };


//structs
typedef struct GUIbtn {
	Rectangle border;
	Vector2 origin;
} GUIbtn;

typedef struct PTXstar {
	float dist;
	int life;
	Vector2 pos;
	Color color;
	float alpha;
} PTXstar;

//global variables
extern GameScreen currentScreen;
extern Buttons btnHovered;
extern Font sagaFont;

//functions
float GetDist(Vector2, Vector2);


//-------------------------------------------------------------------------------
//			player
//-------------------------------------------------------------------------------
class Player {
	private: 
	std::string	name = "Jeremy";
	std::string Class;
	
	int HP;
	const int maxHP;
	bool hasShield;
	int SP;
	int piloting;
	int repair;
	int bartering;
	float timeRemaining;

	
	public:

	int money;
	int debt;

	float reward_upgrade_modifier; // for addMoney()
	float weapon_upgrade_modifier;
	float timeCost_upgrade_modifier; // for loseTime
	float cooldown_upgrade_modifier; // IMPLEMENT LATER
	float movespeed_upgrade_modifier; // IMPLEMENT LATER

	int reward_upgrade_counter = 0;
	int timeCost_upgrade_counter = 0;
	int weapon_upgrade_counter = 0;

	Player();
	// getters
	std::string getName();
	int getMoney();
	int getDebt();
	int getHP();
	int getSP();
	int getPilot();
	int getRepair();
	int getBarter();
	float getTimeRemaining();

	// setters
	void setName(std::string);
	void setMoney(int);
	void setDebt(int);
	void setHP(int);
	void setSP(int);
	void setPilot(int);
	void setRepair(int);
	void setBarter(int);
	void setTimeRemaining(int);

	// methods
	void addMoney(int, float); // int = amount, int = upgrade tier
	void loseTime(float, float); // int = amount, int = upgrade tier
	void loseTimeGradually();
	/*
	void payMarket(int);
	void loseSP(int);
	void loseHP(int);
	void lvlupHP();
	
	void ApplyUpgrade(int);
	void ShowUpgrades() const;
	*/
};

class Ship {
	private:
    Vector2 destination,	
	    position,
	    velocity;
    float distance;
	std::string name;
	int HP;
	int maxHP;
	bool hasShield;
	int shield;
	int maxShield;
	int cargo;
	int cargoCapacity;
	int speed;
	int weapon;
	int gatheringTool;

	
    public:
    Ship(Vector2);
    void DrawSelf(float, Color);
    void UpdateDestination(Vector2);
    void SetPosition(Vector2);
    bool IsAtDestination(float);


	Ship() 
	: name("Unknown"), HP(0), maxHP(25), hasShield(false), shield(0), maxShield(25), cargo(0), cargoCapacity(25), speed(25) {
    }

	//getters
	std::string getName();
	int getHP();
	int getMaxHP();
	int getShield();
	int getmaxShield();
	int getCargo();
	int getCargoCapacity();
	int getSpeed();
	int getWeapon();
	int getGatheringTool();
	//getUpgrades();
	

	//setters
	void setHP(int);
	void setMaxHP(int);
	void setShield(int);
	void setmaxShield(int);
	void setCargo(int);
	void setCargoCapacity(int);
	void setSpeed(int);
	void setWeapon(int);
	void setGatheringTool(int);
	void setUpgrades();
	

	//Upgrade 
	void ApplyUpgrade(int);
	void ShowUpgrades() const;

	//Combat Methods
	void TakeDamage(int);
	void Repair(int);

	void Refuel(int);

	void AddCargo(int);
	void RemoveCargo(int);

	void FireWeapons();

};


//====================================
//     Mission Class Header 
//====================================
class Mission
{
    // ==========
    // Attributes
    // ==========
    private:
    std::string name;
    int reward;
    float timeCost;
    float cooldownTime;
    float currentCooldown;
    Rectangle button;
    bool onCooldown;
	

    public:

    // Constructor
    Mission(std::string name, int reward, float timeCost, float cooldownTime, Rectangle rect);

    // Getters
    std::string getName();
    int getReward();
    float getTimeCost();
    float getCooldownTime();
    float getCurrentCooldown();

    // Setters
    void setName(std::string& name);
    void setReward(int reward);
    void setTimeCost(int timeCost);
    void setCooldownTime(float cooldownTime);
    void setCurrentCooldown(float currentCooldown);
    void setButton(Rectangle);

    //      =======
    //      Methods
    //      =======

    void updateTimer();
    void resetCooldown();
    void DrawButton(Player, bool);
    bool IsClicked();
    void CompleteMission(Player& player, Ship ship);
};

//====================================
//     MarketUpgrade Class Header 
//====================================
class MarketUpgrade
{
	private:
	std::string name; // in universe name
	float tier; // Initialize with TIERnum
	std::string type; // flight speed, yield, reward, timeCost
	int cost;
	bool isBought; // when BuyUpgrade(), flag true. may not be necessary
	bool isMax; // when TIER5 is reached, isMax = true and button changes to display
	Rectangle button;

	public:

	//counters moved to player class
	//int reward_upgrade_counter = 0; // track how many upgrades have been bought
	//int timeCost_upgrade_counter = 0;

	/*
	float TIER0 = 0.00; 
	float TIER1 = 0.05;
	float TIER2 = 0.10;
	float TIER3 = 0.25;
	float TIER4 = 0.50;
	float TIER5 = 1.00;
	*/

	//constructor
	//MarketUpgrade();

	MarketUpgrade(std::string name, float tier, std::string type, int cost, Rectangle button);
	//methods
	void DrawButton(Player); // tier_num is just for display purposes
	bool IsClicked();
	bool IsRClicked();
	void BuyUpgrade(Player& player, Ship& ship); //reference Player addMoney and others to update multiplier
		// may flag isBought, but also may just initialize 




};


//-------------------------------------------------------------------------------
//			solar system and planet classes
//-------------------------------------------------------------------------------
class Sun {
	public:
	Vector2 sunPos;
	float sunRadius;
	bool sunClicked;

	Sun();
	void DrawSun();
};

class Planet : private Sun {
	int numMissionsAvail;
	float mass,
	      radius,
	      orbitAngle,
	      startingAngle,
	      orbitDistance,
	      orbitRadius,
	      conicScale,
	      conicRotation,
	      distFromMouse,
	      distFromSun,
	      alpha;
	Vector2 pos,
		angle,
		axisLengths,
		orbitPointsFull[ORBITALPOINTSFULL],
		orbitPointsAhead[ORBITALPOINTS],
		orbitPointsBehind[ORBITALPOINTS];
	Color color,
	      orbitColor;
	bool orbitOn,
	     isShipDest;
	std::vector<Mission> missionsAvail;

	public:
	Planet();
	void GenerateMissions(GUIbtn*, bool);
	void DrawPlanet(bool);
	void UpdatePlanet(Player);
	void RegisterClick();
	void MissionHandler(Player&, Ship, bool);
	Vector2 GetPos();
	float GetRadius();
	int GetNumMissions();
};

class HubPort : private Sun {
	float mass,
	      radius,
	      orbitAngle,
	      orbitDistance,
	      orbitRadius,
	      conicScale,
	      conicRotation,
	      distFromMouse,
	      distFromSun;
	Vector2 pos,
		angle,
		axisLengths,
		orbitPointsFull[ORBITALPOINTSFULL],
		orbitPointsAhead[ORBITALPOINTS],
		orbitPointsBehind[ORBITALPOINTS];
	bool orbitOn,
	     isShipDest;
	std::vector<MarketUpgrade> rewardUpgrade;
	std::vector<MarketUpgrade> timeCostUpgrade;
	std::vector<MarketUpgrade> weaponUpgrade;
	std::vector<MarketUpgrade> payDebt;	

	public:
	HubPort(float, float);
	void GenerateMarket(GUIbtn*);
	void DrawHubPort(bool, Texture2D);
	void UpdateHubPort(Player);
	void RegisterClick();
	void MarketHandler(Player& pilot, Ship& ship);
	Vector2 GetPos();
	float GetRadius();
};


//-------------------------------------------------------------------------------
//			particle classes
//-------------------------------------------------------------------------------
class PTXstarmanager {
	PTXstar ptxstar[MAXSTARPTX];
	char starFX[3];
	float lifetime;
	Vector2 area;
	int counter, updateTime;
		//functions
	void GenerateStar(PTXstar&);
	void UpdateSelf(PTXstar&);
	void DrawSelf(PTXstar&);

	public:
	PTXstarmanager();
	void LifeCycle();
};

//-------------------------------------------------------------------------------
//			menu
//-------------------------------------------------------------------------------
class SubMenu {
	Vector2 pos, dim;
	float min_x, max_x;
	Rectangle border;
	bool isActive, isLeftSide;

	public:
	SubMenu(bool leftSide);
	void HandleActivation();
	void UpdateAndDrawSelf();
	bool GetActive();
};

//-------------------------------------------------------------------------------
//			code utility classes
//-------------------------------------------------------------------------------
class MapPlanetMenu {
	Rectangle dimensions;
};

class Timer {
	float	frameCounter;
	static double	waitTime;

	public:
	float	GetCounter();
	void	SetCounter(float);
	void	Reset();
	void	Run();
	bool 	Wait(double);
};

class Dice {
	public:
	Dice();
	int rollD6(int);
};


#endif
