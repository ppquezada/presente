#ifndef FILES_H
#define FILES_H

//This funtion return the actual hiscore to show in screen
int show_hiscore();
// If the player beat the actual high score, overwrite the high score with the player actual score
void change_hiscore(int *score);

#endif