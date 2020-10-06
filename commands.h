#define MAXPATH 2048

enum commands { GOTODRIVE, CURRDIR, GOTODIR, PREVDIR, COMPARE, COUNT, HELP, EXIT, BLAH, LAST };

extern char* cmds[LAST+1];
extern char* cmddesc[LAST+1];

void command(char*);
int findcmd(char*);
void cmd_gotodrive(char*);
void cmd_currdir(char);
void cmd_gotodir(char*);
void cmd_prevdir(void);
void cmd_compare(const char*);
void cmd_count(char*);
void cmd_help(void);
void cmd_exit(void);
void cmd_blah(void);