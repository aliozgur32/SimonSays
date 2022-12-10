#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int generateRandomNumber();

int main() {

    //Assigned variables
    int level = 1;
    char highscore[4];
    char inputString[210];
    char answer[210];
    char name[50];
    int rand = 0;
    int index = 0;
    char num;
    int isCorrect = 1;
    int highscoreInt = 0;
    int nameLength = 0;

    //Opens and reads file
    FILE *file;
    file = fopen("highscore.txt","r");
    if (file != NULL){
        //Instantiates variables
        char c = ' ';
        int  i = 0;
        int j = 0;
        int swtch = 0;

        //Reads string and gets name
        //This part reads the code until encountering
        //a semicolon. Once a semicolon is read the switch
        //is turned on and the rest is put into the highscore
        //section rather than the name section
        do {
            c = fgetc(file);
            if (c == ';' || swtch == 1){
                swtch = 1;
                if (c == ';'){
                } else {
                    highscore[j] = c;
                    j++;
                }
            } else {
                name[i] = c;
                i++;
            }
        } while (c != EOF);
    }
    //Closes file
    fclose(file);

    highscoreInt = atoi(highscore);


    //This is the game loop. It only stops when q is entered by the user.
    //Through the loop the first element of inputString is used as the
    //user choice.
    while(1){

        //This code is in an if statement to prevent it from working when the game has already been started.
        if (inputString[0] != '1'){
            //Prints the main game.
            printf("===TAU SAYS===\t\t\t\t\t(HIGHSCORE: %s (Level #%d))\n",name,highscoreInt);
            printf("1)Start Game\n2)Highscore\nq: Quit\n");

            //This takes user input.
            scanf("%s", &inputString);
        }


        //Stops code if level 100 has been reached or q has been entered.
        if (inputString[0] == 'q' || level == 100){
            exit(0);
        } else if (inputString[0] == '2') {
            //Prints the highscore
            printf("Name: %s\t\tScore: %s\n",name,highscore);

        } else if (inputString[0] == '1'){
            //Starts game
            printf("Current Level: %d\n",level);

            //Generates a random number
            rand = generateRandomNumber();

            //Turns the number into a character
            num = rand + '0';

            //This part adds new number to the rest of the number
            if (level == 1){
                index = 1;
                answer[0] = num;
            } else {
                answer[index] = ' ';
                index++;
                answer[index] = num;
                index++;
            }

            //This parts prints the number and then deletes it
            printf("Numbers: ");
            for (int p = 0; p < index; p++){
                printf("%c",answer[p]);
            }
            printf("\n");

            //GETS INPUT
            fgets(inputString,199,stdin);
            scanf("%[^'\n']s",inputString);

            isCorrect = 1;

            for (int l = 0; l < 210; l++){
                if (!(inputString[l] == '0' || inputString[l] == '1' || inputString[l] == '2' || inputString[l] == '3' || inputString[l] == '4' || inputString[l] == '5' || inputString[l] == '6' || inputString[l] == '7' || inputString[l] == '8' || inputString[l] == '9' || inputString[l] == ' ')){
                    if (index < l){
                        isCorrect = 0;
                    }
                    l = 300;
                } else {
                }
            }

            for (int k = 0; k < index; k++){
                if (inputString[k] != answer[k]){
                    isCorrect = 0;
                }
            }

            if (isCorrect == 0){
                if (inputString[0] == 'q'){
                    exit(0);
                }
                printf("Wrong! Game Over!\n");

                if (level > highscoreInt){
                    highscoreInt = level;
                    printf("You have highscore(%d), enter your name: ",level);
                    scanf("%s",name);

                    FILE *file1;
                    file1 = fopen("C:\\Users\\admin\\Desktop\\simonSays\\highscore.txt","w");
                    if (file1 == NULL){
                        printf("ANAN");
                    }
                    fprintf(file1,"%s;%d",name,highscoreInt);

                }
                level = 1;
                memset(answer,0,strlen(answer));
                inputString[0] = '2';
            } else{
                printf("Correct!\n");
                level++;
                inputString[0] = '1';

            }
        } else {
            printf("ERROR: UNKOWN INPUT");
        }

    }
}

//This method returns a random number using time.
int generateRandomNumber(){
    srand(time(NULL));
    return rand() % 10;
}


