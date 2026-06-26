#define BLACK           "\e[0;30m"
#define RED             "\e[0;31m"
#define GREEN           "\e[0;32m"
#define YELLOW          "\e[0;33m"
#define BLUE            "\e[0;34m"
#define MAGENTA         "\e[0;35m"
#define CYAN            "\e[0;36m"
#define WHITE           "\e[0;37m"

#define reset           "\e[0m"

#define pGreen(fmt) do{printf(GREEN fmt); \
printf(reset);}while(0)
