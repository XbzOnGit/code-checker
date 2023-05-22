#include<stdio.h>
#define MAXBUF 10001
char temp[MAXBUF];
int main(int argc,char** argv)
{
   if(argc!=3)
   {
        fprintf(stderr,"cll for check-line-length\nusage: cll <filename> <max chars perline>\n");
        return -1;
   }
   char* filename = argv[1];
   char* strnum = argv[2];
   while(strnum[0]=='0')
    {
        strnum++;
    }
   unsigned long long max = 0;
   int pt = 0;
   while(strnum[pt])
   {
        if(!(strnum[pt]>='0'&&strnum[pt]<='9'))
        {
            fprintf(stderr,"error number\n");
            fprintf(stderr,"cll for check-line-length\nusage: cll <filename> <max chars perline>\n");
            return -1;
        }
        max = max * 10 + strnum[pt] - '0';
        if(max >= MAXBUF)
        {
            fprintf(stderr,"The argument you put in will exceed the MAX_BUFFER_SIZE\n");
            return -1;
        }
        pt++;
   }
   if(freopen(filename,"r",stdin)==NULL)
   {
        fprintf(stderr,"cannot open the file\n");
        fprintf(stderr,"cll for check-line-length\nusage: cll <filename> <max chars perline>\n");
        return -1;
   }
   /* the followings should be printed into stdout */
   unsigned long long cnt = 1;
   int flag = 0;
   while(1)
   {
        unsigned long long tlen = 0;
        char ch;
        int overflow = 0;
        while(1)
        {
            ch = getchar();
            if(ch == '\n' || ch == EOF)
            {
                temp[tlen] = 0;
                break;
            }
            temp[tlen] = ch;
            tlen++;
            if(tlen >= MAXBUF)
            {
            	overflow = 1;
            	break;
            }
        }
        if(overflow)
        {
            printf("a line has exceeded %lu chars\n",(unsigned long)MAXBUF);
            printf("This is the current MAX_BUFFER_SIZE\n");
            printf("at line %lu\n",cnt);
            int ii;
            for(ii=0;ii<MAXBUF;ii++)
            {
            	putchar(temp[ii]);
            }
            putchar('\n');
            putchar('\n');
            putchar('\n');
            flag = 1;
            ch = getchar();
            while(ch != '\n' && ch != EOF)
            {
            	ch = getchar();
            }
        }
        else
        {
            if(tlen > max)
            {
                printf("a line has exceeded %lu chars\n",max);
                printf("at line %lu\n",cnt);
                printf("%s\n",temp);
                printf("this line has %lu chars\n\n\n",tlen);
                flag = 1;
            }
        }
        if(ch == EOF)
        {
            if(tlen == 0)
            {
                break;
            }
            else
            {
                cnt++;
                break;
            }
        }
        cnt++; 
   }
   if(!flag)
   {
       printf("not exceeded, correct\n");
   }
   return flag;
}
