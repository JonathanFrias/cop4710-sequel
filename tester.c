/*	A small tester for the
 *
 *
 *
 */



// libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




// defines
#define NAME_LIMIT 30 
#define VALUE_LIMIT 50
#define FIELD_SIZE sizeof(struct Field)



// structs and enums
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



// prototypes
struct Field* addField(char*, char*, FieldType, struct Field* old_fields);
void empty();
void empty2();



// main()
int main (void) {
	int i = 0;
	int field_count = 0;
	char* name1 = "PEOPLE";
	char* name2 = "QTY";
	char* name3 = "Things";
	char* val1 = "12";
	char* val2 = "4";
	char* val3 = "All of them";
	struct Field* fields = calloc(6, FIELD_SIZE);
	fields->name = NULL;	

	empty2();

	fields = addField(name1, val1, 'T', field_count, fields);
	field_count++;
	fields = addField(name2, val2, 'D', field_count, fields);
	field_count++;
	fields = addField(name3, val3, 'I', field_count, fields);
	field_count++;

	/*	
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
	*/	

	empty();
	
	return 0;

} // end mainf()


struct Field* addField (char* name, char* value, FieldType type,
				struct Field* old_fields) {
	
	//struct Field* field = (struct Field*) calloc(2, sizeof(struct Field));
	int i;

	for(i=0; (old_fields+i)->name != NULL; i++) 
		;

	struct Field* new_fields = (struct Field*)calloc(i+2, FIELD_SIZE);
	
	for(i=0; (old_fields+i)->name != NULL; i++) {
		(new_fields+i)->name = (old_fields+i)->name;
		(new_fields+i)->value = (old_fields+i)->value;
		(new_fields+i)->fieldType = (old_fields+i)->fieldType;
	} 
	
	(new_fields+i)->name = name;
	(new_fields+i)->value = value;
	(new_fields+i)->fieldType = type;
	
	/*
	(new_fields+i+1)->name = NULL;
	(new_fields+i+1)->value = NULL;
	(new_fields+i+1)->fieldType = 'D';
	*/
	
	/*
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
	*/
	
	/*
	// free memory
	for(i=0; (old_fields+i)->name != NULL; i++) {
		free((old_fields+i)->name);
		free((old_fields+i)->value);
	} 
	free(old_fields);
	*/	

	return new_fields;

} // end createField()

void empty() {
	printf("ALL DONE!\n");
}


void empty2() {
	printf("Just Getting Started\n");
}
