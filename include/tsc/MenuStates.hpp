#ifndef MENUSTATES_HPP
#define MENUSTATES_HPP
//------------------------------------------------------------------------
//
// Name: MenuStates.hpp
//
// Desc: All the states that can be assigned to the Menu class
//
// Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"

class MenuClass;

// Provide easy access
#define MenuIdleState MenuIdle::Instance()
#define MenuMainState MenuMain::Instance()
#define MenuHelpState MenuHelp::Instance()
#define MenuNewState MenuNew::Instance()
#define MenuIntroState MenuIntro::Instance()
#define MenuLoadState MenuLoad::Instance()
#define MenuSaveState MenuSave::Instance()
#define MenuGuardianState MenuGuardian::Instance()
#define MenuNpcState MenuNpc::Instance()
#define MenuGameState MenuGame::Instance()
#define MenuEquipInvState MenuEquipInv::Instance()
#define MenuWeaponInvState MenuWeaponInv::Instance()
#define MenuShieldInvState MenuShieldInv::Instance()
#define MenuArmourInvState MenuArmourInv::Instance()
#define MenuAccessoryInvState MenuAccessoryInv::Instance()
#define MenuItemInvState MenuItemInv::Instance()
#define MenuEquipShopState MenuEquipShop::Instance()
#define MenuEquipShopBuyState MenuEquipShopBuy::Instance()

#define MenuEquipShopBuyWeaponState MenuEquipShopBuyWeapon::Instance()
#define MenuEquipShopBuyShieldState MenuEquipShopBuyShield::Instance()
#define MenuEquipShopBuyArmourState MenuEquipShopBuyArmour::Instance()
#define MenuEquipShopBuyAccessoryState MenuEquipShopBuyAccessory::Instance()

#define MenuEquipShopSellState MenuEquipShopSell::Instance()

#define MenuEquipShopSellWeaponState MenuEquipShopSellWeapon::Instance()
#define MenuEquipShopSellShieldState MenuEquipShopSellShield::Instance()
#define MenuEquipShopSellArmourState MenuEquipShopSellArmour::Instance()
#define MenuEquipShopSellAccessoryState MenuEquipShopSellAccessory::Instance()

#define MenuItemShopState MenuItemShop::Instance()
#define MenuItemShopBuyState MenuItemShopBuy::Instance()
#define MenuItemShopSellState MenuItemShopSell::Instance()
#define MenuFerryState MenuFerry::Instance()
#define MenuInnState MenuInn::Instance()
#define MenuRestState MenuRest::Instance()
#define MenuDeathState MenuDeath::Instance()
#define MenuUIState MenuUI::Instance()

//------------------------------------------------------------------------
//
// This is the Idle State for the MenuClass
//
//------------------------------------------------------------------------
class MenuIdle : public State<MenuClass>
{
private:
	
	MenuIdle(){}

	// Copy ctor and assignment should be private
	MenuIdle(const MenuIdle&);
	MenuIdle &operator=(const MenuIdle&);
 
public:

	// This is a singleton
	static MenuIdle *Instance();
	
	void Enter(MenuClass *menu);
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu);
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Main Menu State for the MenuClass
//
//------------------------------------------------------------------------
class MenuMain : public State<MenuClass>
{
private:
	
	MenuMain(){}

	// Copy ctor and assignment should be private
	MenuMain(const MenuMain&);
	MenuMain &operator=(const MenuMain&);
 
public:

	// This is a singleton
	static MenuMain *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the New Game Screen State for the MenuClass
//
//------------------------------------------------------------------------
class MenuNew : public State<MenuClass>
{
private:

	MenuNew(){}
	
	// Copy ctor and assignment should be private
	MenuNew(const MenuNew&);
	MenuNew &operator=(const MenuNew&);

public:

	// This is a singleton
	static MenuNew *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Load Screen State for the MenuClass
//
//------------------------------------------------------------------------
class MenuLoad : public State<MenuClass>
{
private:
	
	MenuLoad(){}

	// Copy ctor and assignment should be private
	MenuLoad(const MenuLoad&);
	MenuLoad &operator=(const MenuLoad&);
 
public:

	// This is a singleton
	static MenuLoad *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Save Screen State for the MenuClass
//
//------------------------------------------------------------------------
class MenuSave : public State<MenuClass>
{
private:
	
	MenuSave(){}

	// Copy ctor and assignment should be private
	MenuSave(const MenuSave&);
	MenuSave &operator=(const MenuSave&);
 
public:

	// This is a singleton
	static MenuSave *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Intro Screen State for the MenuClass
//
//------------------------------------------------------------------------
class MenuIntro : public State<MenuClass>
{
private:

	MenuIntro(){}
	
	// Copy ctor and assignment should be private
	MenuIntro(const MenuIntro&);
	MenuIntro &operator=(const MenuIntro&);

public:

	// This is a singleton
	static MenuIntro *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Help Screen State for the MenuClass
//
//------------------------------------------------------------------------
class MenuHelp : public State<MenuClass>
{
private:

	MenuHelp(){}
	
	// Copy ctor and assignment should be private
	MenuHelp(const MenuHelp&);
	MenuHelp &operator=(const MenuHelp&);

public:

	// This is a singleton
	static MenuHelp *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Game Menu State for the MenuClass
//
//------------------------------------------------------------------------
class MenuGame : public State<MenuClass>
{
private:

	MenuGame(){}
	
	// Copy ctor and assignment should be private
	MenuGame(const MenuGame&);
	MenuGame &operator=(const MenuGame&);

public:

	// This is a singleton
	static MenuGame *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Equip Inventory Menu State for the MenuClass
//
//------------------------------------------------------------------------
class MenuEquipInv : public State<MenuClass>
{
private:

	MenuEquipInv(){}
	
	// Copy ctor and assignment should be private
	MenuEquipInv(const MenuEquipInv&);
	MenuEquipInv &operator=(const MenuEquipInv&);

public:

	// This is a singleton
	static MenuEquipInv *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Weapon Inventory Menu State for the MenuClass
//
//------------------------------------------------------------------------
class MenuWeaponInv : public State<MenuClass>
{
private:

	MenuWeaponInv(){}
	
	// Copy ctor and assignment should be private
	MenuWeaponInv(const MenuWeaponInv&);
	MenuWeaponInv &operator=(const MenuWeaponInv&);

public:

	// This is a singleton
	static MenuWeaponInv *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Shield Inventory Menu State for the MenuClass
//
//------------------------------------------------------------------------
class MenuShieldInv : public State<MenuClass>
{
private:

	MenuShieldInv(){}
	
	// Copy ctor and assignment should be private
	MenuShieldInv(const MenuShieldInv&);
	MenuShieldInv &operator=(const MenuShieldInv&);

public:

	// This is a singleton
	static MenuShieldInv *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Armour Inventory Menu State for the MenuClass
//
//------------------------------------------------------------------------
class MenuArmourInv : public State<MenuClass>
{
private:

	MenuArmourInv(){}
	
	// Copy ctor and assignment should be private
	MenuArmourInv(const MenuShieldInv&);
	MenuArmourInv &operator=(const MenuShieldInv&);

public:

	// This is a singleton
	static MenuArmourInv *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Accessory Inventory Menu State for the MenuClass
//
//------------------------------------------------------------------------
class MenuAccessoryInv : public State<MenuClass>
{
private:

	MenuAccessoryInv(){}
	
	// Copy ctor and assignment should be private
	MenuAccessoryInv(const MenuShieldInv&);
	MenuAccessoryInv &operator=(const MenuShieldInv&);

public:

	// This is a singleton
	static MenuAccessoryInv *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Item Inventory Menu State for the MenuClass
//
//------------------------------------------------------------------------
class MenuItemInv : public State<MenuClass>
{
private:

	MenuItemInv(){}
	
	// Copy ctor and assignment should be private
	MenuItemInv(const MenuItemInv&);
	MenuItemInv &operator=(const MenuItemInv&);

public:

	// This is a singleton
	static MenuItemInv *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Guardian Menu State for the MenuClass
//
//------------------------------------------------------------------------
class MenuGuardian : public State<MenuClass>
{
private:
	
	MenuGuardian(){}

	// Copy ctor and assignment should be private
	MenuGuardian(const MenuGuardian&);
	MenuGuardian &operator=(const MenuGuardian&);
 
public:

	// This is a singleton
	static MenuGuardian *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Npc Menu State for the MenuClass
//
//------------------------------------------------------------------------
class MenuNpc : public State<MenuClass>
{
private:
	
	MenuNpc(){}

	// Copy ctor and assignment should be private
	MenuNpc(const MenuNpc&);
	MenuNpc &operator=(const MenuNpc&);
 
public:

	// This is a singleton
	static MenuNpc *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Item Shop Menu State for the MenuClass
//
//------------------------------------------------------------------------
class MenuItemShop : public State<MenuClass>
{
private:
	
	MenuItemShop(){}

	// Copy ctor and assignment should be private
	MenuItemShop(const MenuItemShop&);
	MenuItemShop &operator=(const MenuItemShop&);
 
public:

	// This is a singleton
	static MenuItemShop *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Item Shop Buy Menu State for the MenuClass
//
//------------------------------------------------------------------------
class MenuItemShopBuy : public State<MenuClass>
{
private:
	
	MenuItemShopBuy(){}

	// Copy ctor and assignment should be private
	MenuItemShopBuy(const MenuItemShopBuy&);
	MenuItemShopBuy &operator=(const MenuItemShopBuy&);
 
public:

	// This is a singleton
	static MenuItemShopBuy *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Item Shop Sell Menu State for the MenuClass
//
//------------------------------------------------------------------------
class MenuItemShopSell : public State<MenuClass>
{
private:
	
	MenuItemShopSell(){}

	// Copy ctor and assignment should be private
	MenuItemShopSell(const MenuItemShopSell&);
	MenuItemShopSell &operator=(const MenuItemShopSell&);
 
public:

	// This is a singleton
	static MenuItemShopSell *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Equip Shop Menu State for the MenuClass
//
//------------------------------------------------------------------------
class MenuEquipShop : public State<MenuClass>
{
private:
	
	MenuEquipShop(){}

	// Copy ctor and assignment should be private
	MenuEquipShop(const MenuEquipShop&);
	MenuEquipShop &operator=(const MenuEquipShop&);
 
public:

	// This is a singleton
	static MenuEquipShop *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Equip Shop Buy Menu State for the MenuClass
//
//------------------------------------------------------------------------
class MenuEquipShopBuy : public State<MenuClass>
{
private:
	
	MenuEquipShopBuy(){}

	// Copy ctor and assignment should be private
	MenuEquipShopBuy(const MenuEquipShopBuy&);
	MenuEquipShopBuy &operator=(const MenuEquipShopBuy&);
 
public:

	// This is a singleton
	static MenuEquipShopBuy *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Equip Shop Buy Weapon Menu State for the MenuClass
//
//------------------------------------------------------------------------
class MenuEquipShopBuyWeapon : public State<MenuClass>
{
private:
	
	MenuEquipShopBuyWeapon(){}

	// Copy ctor and assignment should be private
	MenuEquipShopBuyWeapon(const MenuEquipShopBuyWeapon&);
	MenuEquipShopBuyWeapon &operator=(const MenuEquipShopBuyWeapon&);
 
public:

	// This is a singleton
	static MenuEquipShopBuyWeapon *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Equip Shop Buy Shield Menu State for the MenuClass
//
//------------------------------------------------------------------------
class MenuEquipShopBuyShield : public State<MenuClass>
{
private:
	
	MenuEquipShopBuyShield(){}

	// Copy ctor and assignment should be private
	MenuEquipShopBuyShield(const MenuEquipShopBuyShield&);
	MenuEquipShopBuyShield &operator=(const MenuEquipShopBuyShield&);
 
public:

	// This is a singleton
	static MenuEquipShopBuyShield *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Equip Shop Buy Armour Menu State for the MenuClass
//
//------------------------------------------------------------------------
class MenuEquipShopBuyArmour : public State<MenuClass>
{
private:
	
	MenuEquipShopBuyArmour(){}

	// Copy ctor and assignment should be private
	MenuEquipShopBuyArmour(const MenuEquipShopBuyArmour&);
	MenuEquipShopBuyArmour &operator=(const MenuEquipShopBuyArmour&);
 
public:

	// This is a singleton
	static MenuEquipShopBuyArmour *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Equip Shop Buy Accessory Menu State for the MenuClass
//
//------------------------------------------------------------------------
class MenuEquipShopBuyAccessory : public State<MenuClass>
{
private:
	
	MenuEquipShopBuyAccessory(){}

	// Copy ctor and assignment should be private
	MenuEquipShopBuyAccessory(const MenuEquipShopBuyAccessory&);
	MenuEquipShopBuyAccessory &operator=(const MenuEquipShopBuyAccessory&);
 
public:

	// This is a singleton
	static MenuEquipShopBuyAccessory *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Equip Shop Sell Menu State for the MenuClass
//
//------------------------------------------------------------------------
class MenuEquipShopSell : public State<MenuClass>
{
private:
	
	MenuEquipShopSell(){}

	// Copy ctor and assignment should be private
	MenuEquipShopSell(const MenuEquipShopSell&);
	MenuEquipShopSell &operator=(const MenuEquipShopSell&);
 
public:

	// This is a singleton
	static MenuEquipShopSell *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Equip Shop Sell Weapon Menu State for the MenuClass
//
//------------------------------------------------------------------------
class MenuEquipShopSellWeapon : public State<MenuClass>
{
private:
	
	MenuEquipShopSellWeapon(){}

	// Copy ctor and assignment should be private
	MenuEquipShopSellWeapon(const MenuEquipShopSellWeapon&);
	MenuEquipShopSellWeapon &operator=(const MenuEquipShopSellWeapon&);
 
public:

	// This is a singleton
	static MenuEquipShopSellWeapon *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Equip Shop Sell Shield Menu State for the MenuClass
//
//------------------------------------------------------------------------
class MenuEquipShopSellShield : public State<MenuClass>
{
private:
	
	MenuEquipShopSellShield(){}

	// Copy ctor and assignment should be private
	MenuEquipShopSellShield(const MenuEquipShopSellShield&);
	MenuEquipShopSellShield &operator=(const MenuEquipShopSellShield&);
 
public:

	// This is a singleton
	static MenuEquipShopSellShield *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Equip Shop Sell Armour Menu State for the MenuClass
//
//------------------------------------------------------------------------
class MenuEquipShopSellArmour : public State<MenuClass>
{
private:
	
	MenuEquipShopSellArmour(){}

	// Copy ctor and assignment should be private
	MenuEquipShopSellArmour(const MenuEquipShopSellArmour&);
	MenuEquipShopSellArmour &operator=(const MenuEquipShopSellArmour&);
 
public:

	// This is a singleton
	static MenuEquipShopSellArmour *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Equip Shop Sell Accessory Menu State for the MenuClass
//
//------------------------------------------------------------------------
class MenuEquipShopSellAccessory : public State<MenuClass>
{
private:
	
	MenuEquipShopSellAccessory(){}

	// Copy ctor and assignment should be private
	MenuEquipShopSellAccessory(const MenuEquipShopSellAccessory&);
	MenuEquipShopSellAccessory &operator=(const MenuEquipShopSellAccessory&);
 
public:

	// This is a singleton
	static MenuEquipShopSellAccessory *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Inn Menu State for the MenuClass
//
//------------------------------------------------------------------------
class MenuInn : public State<MenuClass>
{
private:
	
	MenuInn(){}

	// Copy ctor and assignment should be private
	MenuInn(const MenuInn&);
	MenuInn &operator=(const MenuInn&);
 
public:

	// This is a singleton
	static MenuInn *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Ferry Menu State for the MenuClass
//
//------------------------------------------------------------------------
class MenuFerry : public State<MenuClass>
{
private:
	
	MenuFerry(){}

	// Copy ctor and assignment should be private
	MenuFerry(const MenuFerry&);
	MenuFerry &operator=(const MenuFerry&);
 
public:

	// This is a singleton
	static MenuFerry *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Rest Screen State for the MenuClass
//
//------------------------------------------------------------------------
class MenuRest : public State<MenuClass>
{
private:
	
	MenuRest(){}

	// Copy ctor and assignment should be private
	MenuRest(const MenuRest&);
	MenuRest &operator=(const MenuRest&);
 
public:

	// This is a singleton
	static MenuRest *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Death Screen State for the MenuClass
//
//------------------------------------------------------------------------
class MenuDeath : public State<MenuClass>
{
private:
	
	MenuDeath(){}

	// Copy ctor and assignment should be private
	MenuDeath(const MenuDeath&);
	MenuDeath &operator=(const MenuDeath&);
 
public:

	// This is a singleton
	static MenuDeath *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Aux State for the MenuClass
//
//------------------------------------------------------------------------
class MenuUI : public State<MenuClass>
{
private:
	
	MenuUI(){}

	// Copy ctor and assignment should be private
	MenuUI(const MenuUI&);
	MenuUI &operator=(const MenuUI&);
 
public:

	// This is a singleton
	static MenuUI *Instance();
	
	void Enter(MenuClass *menu){}
	bool Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MenuClass *menu);
	void Exit(MenuClass *menu){}
	bool Receive(MenuClass *menu, const Message &msg);

};

#endif
