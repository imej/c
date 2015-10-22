#include <lcthw/club.h>

int readyToExit = 0;

void flush_in()
{
/**
 * Remove trailing characters after the command.
 */
    int ch;
    do 
        ch = fgetc(stdin);
    while (ch != EOF && ch != '\n');

    clearerr(stdin);
}

void intro()
{
    // Welcome & help screen
    printf("###################################\n");
    printf("# Welcome to the People's DB v0.1 #\n");
    printf("# ------------------------------- #\n");
    printf("# Commands:                       #\n");
    printf("# e - exit                        #\n");
    printf("# l - list all                    #\n");
    printf("# c - clear - delete all          #\n");
    printf("# a - add person                  #\n");
    printf("# d - delete person               #\n");
    printf("# s - search for person           #\n");
    printf("# h - help                        #\n");
    printf("###################################\n");
}

void list_all()
{
    flush_in();
    printf("command l - list all\n");
    // TO DO
}

void bye()
{
    flush_in();
    printf("command e - exit\n");
    readyToExit = 1;
}

void clear()
{
    flush_in();
    printf("command c - clear\n");
    // TO DO
    printf("All persons have been deleted.\n");
}

void read_str(char *msg, char *out)
{
/**
 * Display the passed in message then read the input of the user
 */
    int mySize = 100;

    printf("%s", msg);

    fgets(out, mySize, stdin);
    assert(out != NULL);

    out[strlen(out)-1] = '\0';
}

void add()
{
    flush_in();

    Person *p = calloc(1, sizeof(Person));
    assert(p != NULL);

    char *msg = "Name: ";
    char *temp = calloc(100, sizeof(char));
    read_str(msg, temp);
    strcpy(p->name, temp);
    
    msg = "Address: ";
    read_str(msg, temp);
    strcpy(p->address, temp);

    msg = "Hobbies: ";
    read_str(msg, temp);
    strcpy(p->hobbies, temp);

    free(temp);

    Hashmap_set(pdb, bfromcstr(p->name), p);
    printf("Person '%s' was added successfully.\n", p->name);
    printf("PDB>");
}

void delete()
{
    flush_in();

    int mySize = 100;
    char *temp = calloc(100, sizeof(char));

    printf("Person to remove: ");

    fgets(temp, mySize, stdin);
    assert(temp != NULL);

    temp[strlen(temp)-1] = '\0';
    Hashmap_delete(pdb, bfromcstr(temp));

    if (temp != NULL) {
        free(temp);
    }

    printf("%s is deleted.\n", temp);
}

Person *search()
{
    flush_in();

    char *key = NULL;
    printf("command s - search for person: %s", key);
    // TO DO
    return NULL;
}

void init()
{
    // Create a hashmap for the database
    pdb = Hashmap_create(NULL, NULL);
    assert(pdb != NULL);

    char cmd;

    intro();
    printf("PDB>");

    do {
        scanf(" %c", &cmd);
	switch(cmd) {
	    case 'e':
	        bye();
		break;
	    case 'l':
	        list_all();
	        printf("PDB>");
		break;
	    case 'c':
	        clear();
	        printf("PDB>");
		break;
	    case 'a':
	        add();
		break;
	    case 'd':
	        delete();
		break;
	    case 's':
	        search();
		break;
	    case 'h':
	        intro();
	        printf("PDB>");
		break;
	    case '\n':
	        break;
	    default:
	        printf("Not a command, enter h for help.\n");
	        printf("PDB>");
		break;
	}
    } while (readyToExit == 0);
    
    Hashmap_destroy(pdb);
}
