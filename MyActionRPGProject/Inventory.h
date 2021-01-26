/*
*  Inventory.h
*
*      Create on : 31/03/2020
*             by : bettal_j
*
*/

#ifndef INVENTORY_H
#define INVENTORY_H

#include"Item.h"

class Inventory
{
private:
	Item** itemArray;
	unsigned nrOfItems;
	unsigned capacity;

	void initialize();
	void nullify(const unsigned from = 0);
	void freeMemory();

public:
	Inventory(unsigned capacity);
	virtual ~Inventory();

	//Accessoires
	const unsigned& size() const;
	const unsigned& maxSize() const;

	//Modificateurs

	//Fonctions
	void clear();
	const bool empty() const;

	const bool add(Item* item);
	const bool remove(const unsigned index);

	const bool saveToFile(const std::string fileName);
	const bool loadFromFile(const std::string fileName);
};

#endif /* INVENTORY_H */