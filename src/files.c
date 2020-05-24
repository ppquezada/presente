#include "files.h"

#include <stdlib.h>
#include <stdio.h>

int show_hiscore(){ 
    FILE *archive;
    int hiscore;
    archive = fopen("resources/hiscore.txt", "r");
    fscanf(archive, "%d", &hiscore);
    fclose(archive);
    return hiscore;

}

void change_hiscore(int *score){ 
    FILE *archive;
    int hiscore = show_hiscore();
    if(*score > hiscore){
        archive = fopen("resources/hiscore.txt", "w");
        fprintf(archive, "%d", *score);
        fclose(archive);
    }
}



    
