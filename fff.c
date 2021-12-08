#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct polyy
{
    int p_digit[10];
    char p_notdigit[10][6];
}pp[5];


int power(int k)
{
    int product = 1;
    for(int i=1;i<=k;i++)
    {
        product *= 10;
    }
    return product;
}

int main()
{
    FILE*input;
    input = fopen("C://Users//USER//Desktop//beforetest.txt", "r");              

    if (input == NULL)
    {
        printf("\nUnable to open file.\n");
        printf("Please check if file exists and you have read/write privilege.\n");
        exit(0);
    }          
    char c;
    int num_space=1;
    int count = 0;
    int arr=0;
    int value_beforespace = 0;
    int num=0;
    //each char from file
    //arr=how many poly
    int afterenter=0;
    int poly_arr[]={0,0,0,0,0}; //count keep
    char each[6];
    int digit=0;        //digit or not
    int minus = 0;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<10;j++)
        {
            strcpy(pp[i].p_notdigit[j],"\0");
        }
    }
    while ((c = fgetc(input)) != EOF)
    {
        if(c == ' ' && value_beforespace == 1)                
        {
            if(num_space == 0)      //first space, this to clear many spaces
            {
                num_space=1;
                if(digit==0)
                {
                    int sum=0;
                    for(int i=0;i<num;i++)
                    {
                        int each_num = (int)each[num-i-1]-48;
                        if(i==0)
                            sum += each_num*1;
                        else if(each_num == -3)
                            minus = 1;
                        else
                            sum += each_num*power(i);
                    }
                    if(minus==1)
                    {
                        sum -= sum*2;
                        minus=0;
                    }
                    
                    pp[arr].p_digit[count] = sum;
                }
                else
                    strcpy(pp[arr].p_notdigit[count],each);
                num=0;                                  //num=number of each in one count
                digit=0;        
                count++;                                //count is how many coff in one poly count
                for(int i=0;i<6;i++)
                {
                    each[i]='\0';
                }
            }
            value_beforespace = 0;
        }
        else if(c=='\n' && value_beforespace == 1)
        {
            if(digit==0)
            {
                int sum=0;
                for(int i=num-1;i>=0;i--)
                {
                    int each_num = (int)each[i]-48;
                    if(i==num-1)
                        sum += each_num*1;
                    else if(each_num == -3)
                        minus=1;
                    else
                    {
                        sum += each_num*power(num-i-1);
                    }
                }
                if(minus==1)
                {
                    sum -= sum*2;
                    minus=0;
                }
                pp[arr].p_digit[count] = sum;
            }
            else
                strcpy(pp[arr].p_notdigit[count],each);
            poly_arr[arr]=count;
            count=0;
            afterenter=1;
            digit=0;
            num=0;
            num_space=0;
            for(int i=0;i<6;i++)
            {
                each[i]='\0';
            }
            value_beforespace = 0;
        }
        else                    //not space
        {
            if(c==' ' || c=='\n')
                continue;
            value_beforespace = 1;
            if(afterenter==1)
            {
                arr++;
                afterenter=0;
            }
            num_space=0;    //after space, not space
            if(num!=0)
            {
                if((isalpha(c) !=0 || isdigit(c)) !=0)
                    each[num]=c;
                else
                {
                    printf("Invalid input");
                    exit(1);
                }
            }
            else
            {
                if((isalpha(c) !=0 || isdigit(c)) !=0 || c == '-')
                    each[num]=c;
                else
                {
                    printf("Invalid input");
                    exit(1);
                }
            }
            if(isalpha(c)!=0)
                digit=1;
            num++;
        }
    }
    for(int i=0;i<=arr;i++)
    {
        printf("Polynomial %d:\n",i+1);
        for(int j=poly_arr[i];j>=0;j--)
        {
            if(strcmp(pp[i].p_notdigit[poly_arr[i]-j],"\0")==0) //digit
            {
                if(j==poly_arr[i] && pp[i].p_digit[poly_arr[i]-j]==1 && j>1)
                    printf(" x^%d",j);
                else if(j==poly_arr[i] && pp[i].p_digit[poly_arr[i]-j]==1 && j==1)
                    printf(" x");
                else if(j==poly_arr[i] && pp[i].p_digit[poly_arr[i]-j]==1 && j==0)
                    continue;
                else if(j==poly_arr[i] && j>1)
                    printf(" %dx^%d",pp[i].p_digit[poly_arr[i]-j],j);
                else if(j==poly_arr[i] && j==1)
                    printf(" %dx",pp[i].p_digit[poly_arr[i]-j]);
                else if(j==poly_arr[i] && j==0)
                    printf(" %d ",pp[i].p_digit[poly_arr[i]-j]);
                else if(j>1)
                {
                    if(pp[i].p_digit[poly_arr[i]-j]>0)
                        printf(" + %dx^%d",pp[i].p_digit[poly_arr[i]-j],j);             
                    else if(pp[i].p_digit[poly_arr[i]-j]<0)
                        printf(" %dx^%d",pp[i].p_digit[poly_arr[i]-j],j);
                }
                else if(j==1)
                {
                    if(pp[i].p_digit[poly_arr[i]-j]>0)
                        printf(" + %dx",pp[i].p_digit[poly_arr[i]-j]);             
                    else if(pp[i].p_digit[poly_arr[i]-j]<0)
                        printf(" %dx",pp[i].p_digit[poly_arr[i]-j]);
                }
                else
                {
                    if(pp[i].p_digit[poly_arr[i]-j]>0)
                        printf(" + %d",pp[i].p_digit[poly_arr[i]-j]);             
                    else if(pp[i].p_digit[poly_arr[i]-j]<0)
                        printf(" %d",pp[i].p_digit[poly_arr[i]-j]);
                }
            }
            else //ch
            {
                if(j==poly_arr[i] && j>1)
                    printf(" %sx^%d",pp[i].p_notdigit[poly_arr[i]-j],j);
                else if(j==poly_arr[i] && j==1)
                    printf(" %sx",pp[i].p_notdigit[poly_arr[i]-j]);
                else if(j==poly_arr[i] && j==0)
                    printf(" %s ",pp[i].p_notdigit[poly_arr[i]-j]);
                else if(j>1)
                {
                    if(pp[i].p_notdigit[poly_arr[i]-j][0]=='-')
                        printf(" %sx^%d",pp[i].p_notdigit[poly_arr[i]-j],j);
                    else
                        printf(" + %sx^%d",pp[i].p_notdigit[poly_arr[i]-j],j);
                }
                else if(j==1)
                {
                    if(pp[i].p_notdigit[poly_arr[i]-j][0]=='-')
                        printf(" %sx",pp[i].p_notdigit[poly_arr[i]-j]);
                    else
                        printf(" + %sx",pp[i].p_notdigit[poly_arr[i]-j]);
                }
                else
                {
                    if(pp[i].p_notdigit[poly_arr[i]-j][0]=='-')
                        printf(" %s",pp[i].p_notdigit[poly_arr[i]-j]);
                    else
                        printf(" + %s",pp[i].p_notdigit[poly_arr[i]-j]);
                }
            }
        }
        printf("\n");
    }
    
    if(arr<1)                       //exit if only 1 poly
        exit(1);

    int max=0;
    for(int i=0;i<=arr;i++)
    {
        if(max<poly_arr[i])
            max = poly_arr[i];
    }

    printf("Sum of these polynomial :\n");
    int result_sum;
    int each_max;               //each array poly has how many?
    char same_char[max+1][arr+1][6];
    for(int i=max;i>=0;i--)
    {
        int arr1=0;
        result_sum=0;
        for(int j=0;j<=arr;j++)
        {
            each_max=poly_arr[arr1];                
            arr1++;
            if(each_max-i<0)
                continue;
            else if(strcmp(pp[j].p_notdigit[each_max-i],"\0")==0)                   //0 char array first
            {
                result_sum += pp[j].p_digit[each_max-i];
            }
            else                                                                   //char
            {
                for(int e=0;e<6;e++)
                {
                    if(isalpha(pp[j].p_notdigit[each_max-i][e])!=0)
                        same_char[i][j][e] = pp[j].p_notdigit[each_max-i][e];
                }
            }
        }
        if(result_sum!=0)
        {
            if(result_sum>0 && i!=max)
            {
                if(result_sum==1)
                {
                    if(i>1)
                        printf(" + x^%d",i);
                    else if(i==1)
                        printf(" + x");
                    else
                    printf(" + 1");
                }
                
                else if(i>1)
                    printf(" + %dx^%d",result_sum,i);
                else if(i==1)
                    printf(" + %dx",result_sum);
                else
                    printf(" + %d",result_sum);
            }
            else
            {
                if(result_sum==1)
                {
                    if(i>1)
                        printf(" x^%d",i);
                    else if(i==1)
                        printf(" x");
                    else
                    printf(" 1");
                }
                else if(result_sum==-1)
                {
                    if(i>1)
                        printf(" -x^%d",i);
                    else if(i==1)
                        printf(" -x");
                    else
                    printf(" -1");
                }
                else if(i>1)
                    printf(" %dx^%d",result_sum,i);
                else if(i==1)
                    printf(" %dx",result_sum);
                else
                    printf(" %d",result_sum);
            }
        }
        for(int j=0;j<=arr;j++)
        {
            if(strcmp(same_char[i][j],"\0")!=0)
                printf("%s",same_char[i][j]);
        }
    }
    fclose(input);
    return 0;
}