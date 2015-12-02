#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LIMIT 30 
#define VALUE_LIMIT 50
#define FIELD_SIZE sizeof(struct Field)


typedef enum {
	INTEGER='I',
	DATE='D',
	TEXT='T',
} FieldType;

typedef enum {
	LESS_THAN,
	LESS_THAN_OR_EQ,
	GREATER_THAN,
	GREATER_THAN_OR_EQ,
	EQUAL,
	NOT_EQUAL,
} whereType;

struct Field {
	char * name;
	char * value;
	FieldType fieldType;
};


struct Field* createField(char*, char*, FieldType);
void empty();
void empty2();


int main (void) {
	int i = 0;
	int field_count;
	
	struct Field* fields = calloc(6, FIELD_SIZE);
	
	empty2();

	i=0;
	
	(fields+i)->name = "People";
	(fields+i)->value = "12";
	(fields+i)->fieldType = 'T';
	i++;	
	(fields+i)->name = "QTY";
	(fields+i)->value = "4";
	(fields+i)->fieldType = 'D';
	i++;
	(fields+i)->name = "Things";
	(fields+i)->value = "All of them";
	(fields+i)->fieldType = 'I';
	i++;
	(fields+i)->name = "Hats";
	(fields+i)->value = "Fedora";
	(fields+i)->fieldType = 'T';
	i++;
	(fields+i)->name = "Woop";
	(fields+i)->value = "above";
	(fields+i)->fieldType = 'D';
	i++;
	
	empty();
	
	return 0;

} // end mainf()


struct Field* createField (char* name, char* value, FieldType type) {
	struct Field* field = (struct Field*) calloc(2, sizeof(struct Field));
	
	if (name) {
		field->name = name;
	} else {
		field->name = "field_name";
	}

	if (value) {
		field->value = value;
	} else {
		field->value = "field_value";
	}

	field->fieldType = type;	

	return field;

} // end createField()

void empty() {
	printf("ALL DONE!\n");
}


void empty2() {
	printf("Just Getting Started\n");
}
