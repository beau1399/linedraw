#include <stdio.h>
#include <ctype.h>

#define INPUT_FILE "c:/coco/as11/M.OUT"
#define OUTPUT_FILE "c:/coco/as11/line.bas"

#define OUTPUT_FORMAT1 "%d"
#define OUTPUT_FORMAT2 ",%d"
#define INPUT_FORMAT "%2x"
#define SREC_HEADER 7
#define COCO_LINE_SPACING 10

static char COCO_TRAILER[]=
	"2010 READ K\n\n"
	"2020 POKE 14252+I,K\n\n"
	"2030 NEXT I\n\n"
	"2050 REM BEGIN CLIENT SECTION\n\n";

int main(int argc, char* argv[])
{

	FILE * fin;
	FILE * fout;
	
	fin=fopen(INPUT_FILE,"r");
	fout=fopen(OUTPUT_FILE,"w");

	char row[SREC_HEADER];

	::fgetc(fin);

	int lineno=0;

	fputs("\nNEW\n\n1 REM COCO2 BASIC OUTPUT ENSURE CAPS LOCK OFF PC KEYBOARD MODE\n\n",fout);

	bool done1=false;
	int datacount=0;
	
	do
	{
	 if(fread(row,1,SREC_HEADER,fin) < SREC_HEADER) break;	//header

	 fprintf(fout,"%d DATA ",lineno+=COCO_LINE_SPACING);

	 int dat;
  	 fscanf(fin,INPUT_FORMAT,&dat);
	 fprintf(fout,OUTPUT_FORMAT1,dat);
	 ++datacount;

     for(int i=1; i<=31; ++i)
	 {		
	    char inter[3];
		inter[0]=fgetc(fin);
		inter[1]=fgetc(fin);
		inter[2]=0;
        if(inter[0]=='\r'||inter[0]=='\n'){done1=true;break;}		
		sscanf(inter,INPUT_FORMAT,&dat);
		fprintf(fout,OUTPUT_FORMAT2,dat);
		++datacount;
	 }

	 if(done1){fprintf(fout,"\n\n");break;}

	 fscanf(fin,INPUT_FORMAT,&dat);

	 do{ char ch=::fgetc(fin); if(!::isspace(ch)){  break; } } while (true);

	 fprintf(fout,"\n\n");
	}while(true);


	fprintf(fout,"2000 FOR I=0 TO %d\n\n",datacount-1);
	fputs(COCO_TRAILER,fout );

	fclose(fin);
	fclose(fout);

	return 0;	
}

