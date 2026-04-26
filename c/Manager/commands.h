#ifndef COMMANDS_H
#define COMMANDS_H

int sv_Console(char *args);
int sv_StopServer();
int sv_Migrate(char *oldID, char *newID);

#endif
