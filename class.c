#include <string.h>
#include "class.h"

t_class create_empty_class()
{
    t_class empty_class;
    strcpy(empty_class.name, "");
    empty_class.health = 0;
    empty_class.damage = 0;
    return (empty_class);
}
t_class create_knight()
{
    t_class cavaliere;
    strcpy(cavaliere.name, "Cavaliere");
    cavaliere.health = 100;
    cavaliere.damage = 100;
    strcpy(cavaliere.sprite, "resources/cavaliere.png");
    return (cavaliere);
}
t_class create_mage()
{
    t_class mago;
    strcpy(mago.name, "Mago");
    mago.health = 60;
    mago.damage = 150;
    strcpy(mago.sprite, "resources/mago.png");
    return (mago);
}
t_class create_enemy()
{
    t_class enemy;
    strcpy(enemy.name, "Enemy");
    enemy.health = 300;
    enemy.damage = 200;
    strcpy(enemy.sprite, "resources/evil_cat.png");
    return (enemy);
}
t_class	choose_class(int class_idx)
{
	switch(class_idx)
	{
		case 1:
			return	(create_knight());
		case 2:
			return	(create_mage());
		default:
			return	(create_empty_class());
	}
}