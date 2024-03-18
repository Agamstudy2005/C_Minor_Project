// ICS Minor Project

#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

// the function for rotating each character as many times as the key is called

char rotate(char data, int key){
    key = key % 26;

    // Here we check if the data lies between the characters a-z or A-Z
    // if it does, then the ASCII value of the character is increased by 'key' times

    int encryption = (int) data;
    if(data >= 'a' && data <= 'z'){
        if(encryption + key > 122){
            encryption = 96 + (encryption + key - 122) % 26;
        }
        else{
            encryption += key;
        }
    }
    else if(data >= 'A' && data <= 'Z'){
        if(encryption + key > 90){
            encryption = 64 + (encryption + key - 90) % 26;
        }
        else{
            encryption += key;
        }
    }

    // the encrypted data is returned back

    data = (char) encryption;
    return data;
}

// the function for encrypting the files is called

void encrypt(int key, char file[])
{
    FILE *f1, *f2;
    f1 = fopen (file , "r");

    char data[100000];

    // the data in file inputed by the user is stored in an array called data

    int i = 0;
    while(1)
    {
        data[i] = fgetc(f1);
        if(data[i] == EOF)
        {
            break;
        }

        i++;
    }

    f2 = fopen ("encrypted_caesar.txt", "w");

    i = 0;
    while(1)
    {
        if(data[i] == EOF)
        {
            break;
        }

        fputc(rotate(data[i], key), f2);
        i++;
    }

    // the data is encrypted and stored in a file called encrypted_caesar.txt

    fclose(f1);
    fclose(f2);
}

// the function for decrypting the file 

void decrypt(int size, int r1, char file[])
{
    FILE *f1;

    f1 = fopen(file, "r");

    char data[100000];

    int i = 0;
    while(1)
    {
        data[i] = fgetc(f1);
        if(data[i] == EOF)
        {
            break;
        }

        i++;
    }

    // the data in file inputed by the user is stored in an array called data

    fclose(f1);
 
    // an array of files is created and the decrypted data is stored in each of these files

    FILE *files[size + 1];

    for (int i = 0; i <= size; i++)
    {
        char filename[25];
        sprintf(filename, "decrypted_caesar_%d.txt", r1);
        files[i] = fopen(filename, "w");

        int j = 0;
        while(1)
        {
            if(data[j] == EOF)
            {
                break;
            }

            fputc(rotate(data[j], 26 - r1), files[i]);
            j++;
        }

        r1++;
        fclose(files[i]);
    }

}

#define WIDTH 80
#define HEIGHT 18

int startx = 0;
int starty = 0;

char* choices[] = {" Encryption ", " Decryption ", " EXIT "};
int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);

int error(WINDOW *win, char file[]);


int main(void)
{
    // WINDOW is a structure defined in ncurses.h library
    // highlight is a variable used to highlight the selected variable in the terminal UI
    // choice is a variable used to select the choice made by the user
    // c is a variable used to accept the input by the user in the terminal menu

    WINDOW *menu_win;
    int highlight = 1;
    int choice = 0;
    int c;

    // file and key are the strings inputed by the user

    char file[100];
    char key[100];

    initscr();
    clear();
    cbreak();

    startx = 0;
    starty = 0;

    menu_win = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(menu_win, TRUE);

    while(1)
    {
        print_menu(menu_win, highlight);

        noecho();
        int option;
        mvwprintw(menu_win, 3, 2, "Choose between encryption and decryption:-");
        
        choice = 0;

        while(1)
        {	c = wgetch(menu_win);
            switch(c)
            {	case KEY_UP:
                    if(highlight == 1)
                        highlight = n_choices;
                    else
                        --highlight;
                    break;
                case KEY_DOWN:
                    if(highlight == n_choices)
                        highlight = 1;
                    else 
                        ++highlight;
                    break;
                case 10:
                    choice = highlight;
                    break;
            }

            print_menu(menu_win, highlight);
            if(choice != 0)	/* User did a choice come out of the infinite loop */
                break;
        }	

        if(choice == 1)
        {
            // echo function allows inputed characters to be visible on the screen
            
            echo();
            mvwprintw(menu_win, 10, 2, "File: ");
            wrefresh(menu_win);
            mvwscanw(menu_win, 10, 8, "%s", file);

            // the above function is used to scan only the file name
            
            // checking if the file exists in the folder

            int z = error(menu_win, file);

            if(z == 1)
            {
                wgetch(menu_win);

                wclear(menu_win);

                continue;
            }

            int x = 0;

            for(int i = 0; i < strlen(file); i++)
            {
                if((int)file[i] == 32 || file[i] == '\n')
                {
                    // if there exists a space or a line break in the name of the file then user is asked to input file name again

                    mvwprintw(menu_win, 12, 2, "Please input correct File.");
                    wrefresh(menu_win);

                    wgetch(menu_win);

                    wclear(menu_win);

                    x = 1;
                    
                    break;
                }
            }

            if(x == 1)
            {
                continue;
            }


            mvwprintw(menu_win, 12, 2, "Key: ");
            wrefresh(menu_win);
            mvwscanw(menu_win, 12, 7, "%s", key);

            int key2;
            int l = 1;
            int m = 0;

            // checking if the key contains values between 0 and 9

            for(int i = 0; i < strlen(key); i++)
            {
                if ('0' <= key[i] && key[i] <= '9')
                {
                    key2 += (int) key[i] * l;
                    l *= 10;
                }
                else if(key[i] == '\n')
                {
                    mvwprintw(menu_win, 14, 2, "Please put correct key.");
                    wrefresh(menu_win);

                    wgetch(menu_win);

                    wclear(menu_win);

                    m = 1;

                    break;
                }
                else
                {
                    mvwprintw(menu_win, 14, 2, "Please put correct key.");
                    wrefresh(menu_win);

                    wgetch(menu_win);

                    wclear(menu_win);

                    m = 1;

                    break;
                }
            }

            if(m == 1)
            {
                continue;
            }

            // if key inputed is negative then the user is asked to enter a correct key

            if(key2 < 0)
            {
                mvwprintw(menu_win, 14, 2, "Please put correct key.");
                wrefresh(menu_win);

                wgetch(menu_win);

                wclear(menu_win);

                continue;
            }

            // The function to encrypt the file inputted by the function 
            encrypt(key2, file);

            mvwprintw(menu_win, 14, 2, "File has been Encrypted successfully!");
            wrefresh(menu_win);

            wgetch(menu_win);

            wclear(menu_win);

        }
        else if(choice == 2)
        {
            echo();

            // echo function allows inputed characters to be visible on the screen
            
            mvwprintw(menu_win, 10, 2, "File: " );
            wrefresh(menu_win);
            mvwscanw(menu_win, 10, 8, "%s", file);

            // the above function is used to scan only the file name

            // checking if the file exists in the folder

            int z = error(menu_win, file);

            if(z == 1)
            {
                wgetch(menu_win);

                wclear(menu_win);

                continue;
            }

            int x = 0;

            for(int i = 0; i < strlen(file); i++)
            {
                if((int)file[i] == 32 || file[i] == '\n')
                {
                    // if there exists a space in the name of the file then user is asked to input file name again

                    mvwprintw(menu_win, 12, 2, "Please input correct File.");
                    wrefresh(menu_win);

                    wgetch(menu_win);

                    wclear(menu_win);

                    x = 1;
                    
                    break;
                }
            }

            if(x == 1)
            {
                continue;
            }

            decrypt(25, 0, file);

            mvwprintw(menu_win, 14, 2, "File has been Decrypted sucessfully!");
            wrefresh(menu_win);

            wgetch(menu_win);

            wclear(menu_win);
        }
        else if(choice == 3)
        {
            refresh();
            endwin();
            return 0;
        }
    }

}

// this function is used to define the UI in the terminal

void print_menu(WINDOW *menu_win, int highlight)
{
	int x, y, i;	

	x = 1;
	y = 5;
	box(menu_win, 0, 0);

    
    wattron(menu_win, A_BOLD | A_UNDERLINE);
    mvwprintw(menu_win, 1, 33, "CAESAR CIPHER");
    wattroff(menu_win, A_BOLD | A_UNDERLINE);

	for(i = 0; i < n_choices; ++i)
	{	if(highlight == i + 1) /* High light the present choice */
		{	
            wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, y, x, "%s", choices[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choices[i]);
		++y;
	}

    wrefresh(menu_win);

}

// this function is used to check if the file inputed by the user exists or not
// if it doesn't, it returns an error that file does not exist

int error(WINDOW *win, char file[])
{
    FILE *f;
    int errnum;

    f = fopen(file , "r");

    if(f == NULL)
    {
        errnum = errno;
        mvwprintw(win, 12, 2, "%s", strerror(errnum));

        return 1;
    }

    return 0;
}
