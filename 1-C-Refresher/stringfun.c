#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define BUFFER_SZ 50

//prototypes
void usage(char *);
void print_buff(char *, int);
int  setup_buff(char *, char *, int);

//prototypes for functions to handle required functionality
int  count_words(char *, int, int);
//add additional prototypes here
int reverse_words(char *, int);
int word_print(char *, int); 

int setup_buff(char *buff, char *user_str, int len){
    //TODO: #4:  Implement the setup buff as per the directions
    int count = 0;
    int i = 0;

    // the loop moves through the user provided string
    // and sets up the buffer with a cleaned up version of
    // the message.

    // Verify that either a character or a single space is
    // being added to the buffer. If there's numerous spaces,
    // pointer for user_str increments until it encounters
    // another character.
    while (user_str[i] != '\0') {
        if (user_str[i] != ' ' ) {
            buff[count] = user_str[i];
            ++count;
        } else if (user_str[i] == ' ' && user_str[i+1] != ' ') {
            buff[count] = user_str[i];
            ++count;
        }

        // error -1: the user supplied string is too large
        if (count > 50) {
            printf("error: Provided message is too long.\n");
            return -1;
        }
        ++i;
    }

    // pad the remaining space in the buffer with '.'
    int remaining = len - count;
    memset(buff + count, '.', remaining*sizeof(char));

    return count;
}

void print_buff(char *buff, int len){
    printf("Buffer:  [");
    for (int i=0; i<len; i++){
        putchar(*(buff+i));
    }
    printf("]");
    putchar('\n');
}

void usage(char *exename){
    printf("usage: %s [-h|c|r|w|x] \"string\" [other args]\n", exename);

}

int count_words(char *buff, int len, int str_len){
    int words = 0;

    // if str_len is 0, then avoid the extra work and return 0.
    if (str_len == 0) {
        return 0;
    }

    // loop moves through buffer and counts every space as the
    // start of a new word, ignores spaces at the beginning and
    // end of the buffer.
    for (int i=0; i<len; ++i) {
        if (buff[i] == ' ' && i != 0 && i != str_len-1) {
            ++words;
        } else if (buff[i] == '.') {
            ++words;
            break;
        }
    }

    return words;
}

int reverse_words(char *buff, int str_len) {
    int j = str_len-1;
    int i = 0;
    char temp;

    // if str_len is 0, then avoid the extra work and return 0.
    if (str_len == 0) {
        return 0;
    }

    // Loop moves through the buffer from two points, the
    // start and the end. It swaps characters then advances
    // the pointers. Loops ends when the pointers interset
    // each other and the buffer is reversed.
    while (i < j) {
        temp = buff[i];
        buff[i] = buff[j];
        buff[j] = temp;
        --j;
        ++i;
    }

    return 0;
}

int word_print(char *buff, int str_len) {
    int start = 1;
    int wordCount = 1;
    int charCount = 0;

    printf("Word Print\n");
    printf("----------\n");

    // if str_len is 0, then avoid the extra work and return 0.
    if (str_len == 0) {
        return 0;
    }

    // Loop moves through the buffer using a pointer
    // initialized at the start of the message.
    // Starts by verifying if the pointer is at the
    // start of a word. 
    // If it is, output the number it's on for word 
    // count, then continue.
    // If it isn't, verify the pointer isn't at a space
    // or a '.', then output the character and increase
    // the character count.
    // If the pointer is at a space, and the space isn't
    // a leading or trailing space, then indicate we're
    // at the start of a new word, set charCount to 0, and
    // increase word count.

    // Loops continues until it reaches the end of the string.
    for (int i=0; i<=str_len; ++i) {
        if (start == 1) {
            printf("%d. ", wordCount);
            start = 0;
        }

        if (buff[i] != ' ' && buff[i] != '.') {
            ++charCount;
            printf("%c", buff[i]);
        } else if (i != 0 && i != str_len-1){
            start = 1;
            ++wordCount;
            printf("(%d)\n", charCount);
            charCount = 0;
        }
    }

    printf("\n");
    return wordCount-1;
}

int main(int argc, char *argv[]){

    char *buff;             //placehoder for the internal buffer
    char *input_string;     //holds the string provided by the user on cmd line
    char opt;               //used to capture user option from cmd line
    int  rc;                //used for return codes
    int  user_str_len;      //length of user supplied string

    //TODO:  #1. WHY IS THIS SAFE, aka what if argv[1] does not exist?
    //      This is safe because the other condition verifies that
    //      there are at least 2 arguments provided for argv to access.
    if ((argc < 2) || (*argv[1] != '-')){
        usage(argv[0]);
        exit(1);
    }

    opt = (char)*(argv[1]+1);   //get the option flag

    //handle the help flag and then exit normally
    if (opt == 'h'){
        usage(argv[0]);
        exit(0);
    }

    //WE NOW WILL HANDLE THE REQUIRED OPERATIONS

    //TODO:  #2 Document the purpose of the if statement below
    //      Verify if there are enough user provided arguments (3 or more)
    //      so that the following usage of argv[2] functions properly. 
    //      If not, return exit code of 1
    if (argc < 3){
        usage(argv[0]);
        exit(1);
    }

    input_string = argv[2]; //capture the user input string

    //TODO:  #3 Allocate space for the buffer using malloc and
    //          handle error if malloc fails by exiting with a 
    //          return code of 2
    buff = (char*) malloc(BUFFER_SZ);

    if (buff == NULL) {
        exit(2);
    }


    user_str_len = setup_buff(buff, input_string, BUFFER_SZ);     //see todos

    if (user_str_len < 0){
        printf("Error setting up buffer, error = %d\n", user_str_len);
        exit(2);
    }

    switch (opt){
        case 'c':
            rc = count_words(buff, BUFFER_SZ, user_str_len);  //you need to implement
            if (rc < 0){
                printf("Error counting words, rc = %d\n", rc);
                exit(2);
            }
            printf("Word Count: %d\n", rc);
            break;
        
        case 'r':
            rc = reverse_words(buff, user_str_len);
            if (rc < 0) {
                printf("Error reversing words, rc = %d\n", rc);
                exit(2);
            }
            break;
        
        case 'w':
            rc = word_print(buff, user_str_len);
            if (rc < 0) {
                printf("Error printing words, rc = %d\n", rc);
                exit(2);
            }
            printf("Number of words returned: %d\n", rc);
            break;

        default:
            usage(argv[0]);
            exit(1);
    }

    //TODO:  #6 Dont forget to free your buffer before exiting
    print_buff(buff,BUFFER_SZ);
    free(buff);
    exit(0);
}

//TODO: #7  Notice all of the helper functions provided in the 
//          starter take both the buffer as well as the length.  Why
//          do you think providing both the pointer and the length
//          is a good practice, after all we know from main() that 
//          the buff variable will have exactly 50 bytes?
//  
//          It's good practice to include the pointer and the length
//          as it allows flexibility with the program. Now, if we chose to
//          increase or decrease the length, we don't have to go through
//          and change multiple areas of code and instead only have to edit
//          one or two spots.