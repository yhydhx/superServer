#include "head.h"

char *prompt="command> ";

main(){
	while(userin(prompt)!= EOF){
		procline();
	}
}
