#ifndef CLASS_H
#define CLASS_H

typedef struct s_class
{
    char    name[20];
    int health;
    int damage;
    char    sprite[30];
} t_class;

t_class create_empty_class();
t_class create_knight();
t_class create_mage();
t_class choose_class(int class_idx);

#endif