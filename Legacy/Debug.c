string 	debug[8];
int current = 0;
void changeDebug(int line, const char * mes){
	debug[line] = mes;
}
int addDebug(int level, const char * mes){
	if(current>7) current=0;
	debug[current] = mes;
	current++;
	return current-1;
}
task debugger(){
	while (true)
	{
		int line = 0;
		eraseDisplay();
		while(line<8){

				nxtDisplayString(line, "%s", debug[line]);
				line++;
		}
		wait1Msec(25);
	}
}
