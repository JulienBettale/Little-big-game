/*
*  AttributeComponent.h
*
*      Create on : 27/03/2020
*             by : bettal_j
*
*/

#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H

class AttributeComponent
{
public:
	//Leveling
	int level;
	int exp;
	int expNext;
	int attributePoints;

	//Attributes
	int vitality;
	int strength;
	int dexterity;
	int agility;
	int intelligence;

	//Stats
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;
	int accuracy;
	int defence;
	int luck;

	//Constructeur / Destructeur
	AttributeComponent(int level);
	virtual ~AttributeComponent();

	//Fonctions
	std::string debugPrint() const;

	void loseHP(const int hp);
	void gainHP(const int hp);
	void loseEXP(const int exp);
	void gainExp(const int exp);

	const bool isDead() const;

	void updateStats(const bool reset);
	void updateLevel();

	void update();
};
#endif /* ATTRIBUTECOMPONENT_H */