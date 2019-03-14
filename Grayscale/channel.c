
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * colors[] = {"Red","Green","Blue"};

//filename then channel number 0,1,2
int main(int argc,char ** argv){


char * filename = argv[1];
int color = atoi(argv[2]);
char *outfile = malloc(sizeof(char) *100);


strcat(outfile,colors[color]); //append color name to output file
strcat(outfile,filename); //append file name to output file
//open files for reading and writing
FILE * in =fopen(filename,"r");
if(in == NULL){
    fprintf(stderr,"Failed to open %s for reading\n",filename);
    return 0;
}
FILE * out = fopen(outfile,"w");
if(out == NULL){
    fprintf(stderr,"Failed to open %s for writing\n",outfile);
    return 0;
}
//read and write details specifying details of file
char format[20];
int col,row,size;
fscanf(in,"%s %d %d\n%d",format,&col,&row,&size);
fprintf(out,"%s\n%d %d\n%d\n",format,col,row,size);

//read the rest of the file and gray scale it
for(int i=0;i<row;i++){
    for(int j=0;j<col;j++){
    int rgb[3];
    //read the three colors
    for(int c=0;c<3;c++){
        fscanf(in,"%d",&rgb[c]);
    }
    //write the color you want to greyscale with
     for(int c=0;c<3;c++){
        fprintf(out,"%d ",rgb[color]);
    }
     
    }
}



 

}


