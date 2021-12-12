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

void check_file(FILE*input)   //to check whether there is file or not.If not create new and exit the program
{
    if (input == NULL)
    {
        input = fopen("beforetest.txt", "w");
        printf("\nYou haven't create the file in the correct place\n");
        printf("Now we have create new text input for u. Please go write your input on beforetest.txt\n");
        fclose(input);
        exit(0);
    }  
}


int get_sumfor_samechar(char digit_forsame[],int result_forsame_each)
{
    int mm=0;                           //to minus
    int pow=0;                 
    for(int o=5;o>=0;o--)
    {
        if(digit_forsame[o]!='\0' && isalpha(digit_forsame[o])==0)
        {        
            if(digit_forsame[o]=='-')
                mm=1;
            else if(pow==0)
                result_forsame_each += (int)digit_forsame[o]-48;
            else
                result_forsame_each += ((int)digit_forsame[o]-48)*(10*pow);
                                        
            if(mm==1)
            {
                result_forsame_each -= result_forsame_each*2;
                mm=0;
            }
            pow++;
        }
    }
    return result_forsame_each;
}

int get_max_length(int arr,int poly_arr[])
{
    int max=0;
    for(int i=0;i<=arr;i++)
    {
        if(max<poly_arr[i])
            max = poly_arr[i];
    }
    return max;
}

int print_sumdigit_eachpoly(int start,int result_sum,int i,int max)
{
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
        return 1;
    }
}

int main()
{
    FILE*input;
    input = fopen("beforetest.txt", "r"); 
    check_file(input); //send to function to check
    char c;
    int num_space=1;            //avoid many space
    int count = 0;              //count coefficient in each poly
    int arr=0;                  //how many poly
    int value_beforespace = 0;  //there is value before space
    int num=0;                  //receive how many char in each coefficient
    //each char from file
    //arr=how many poly
    int afterenter=0;           //arr will add by 1 after newline
    int poly_arr[]={0,0,0,0,0}; //count keep
    char each[6];
    int digit=0;        //digit or not
    int minus = 0;
    ////////// receive all the coefficient in the polynomial from the file////////////

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


   //print all coefficient of each polynomial


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
    
     
    //exit if only 1 poly because they dont have other poly to add

    if(arr<1)                       
        exit(1);


    /////////find the max length of these poly////////////////

    int max = get_max_length(arr,poly_arr);

    /////////print out the sum of these polynomial/////////////////////

    printf("Sum of these polynomial :\n");
    int result_sum;
    int each_max;               //each array poly has how many?
    char same_char[arr+1][6];
    int result_forsame = 0;
    int result_forsame_each = 0;
    int eachsame_result[arr+1];     //for same char
    char digit_forsame[6];
    int start=0;
    for(int i=max;i>=0;i--)
    {
        result_sum=0;
        for(int k=0;k<=arr;k++)
        {
            for(int ii=0;ii<6;ii++)
            {
                same_char[k][ii]='\0';                  //set as null
            }
        }

        
        for(int j=0;j<=arr;j++)
        {
            /////////sum of digit///////
            each_max=poly_arr[j];                
            if(each_max-i<0)
                continue;
            else if(strcmp(pp[j].p_notdigit[each_max-i],"\0")==0)                   //0 char array first
            {
                result_sum += pp[j].p_digit[each_max-i];
            }
            else                                                                   //char
            {
                
                int index=0;
                for(int e=0;e<6;e++)
                {
                    if(isalpha(pp[j].p_notdigit[each_max-i][e])!=0)
                    {
                        same_char[j][index] = pp[j].p_notdigit[each_max-i][e];
                        index++;
                    }
                }
            }
        }

        start=print_sumdigit_eachpoly(start,result_sum,i,max);

        //calculate or print the char coefficient each poly
        for(int j=0;j<=arr;j++)
        {
            int countt=0;
            int first_time=0;
            if(strcmp(same_char[j],"\0")!=0)
            {
                for(int k=0;k<=arr;k++)
                {
                    eachsame_result[k] = 0;                                             //to know which is equal
                }
                int delete = 0;                                                         //for delete the current char in poly
                for(int check=0;check<=arr;check++)
                {
                    if(strcmp(same_char[j],same_char[check])==0)
                    {
                        eachsame_result[j] = 1;
                        countt++;
                        eachsame_result[check] = 1;
                        if(j!=check)
                            strcpy(same_char[check],"\0");
                        delete=1;
                    }
                }
                if(delete==1)
                {
                    result_forsame = 0;
                    for(int cal=0;cal<=arr;cal++)
                    {
                        int result_forsame_each =0;             //for to keep each same and add afterward
                        each_max=poly_arr[cal];  
                        if(eachsame_result[cal] == 1)
                        {
                            for(int k=0;k<6;k++)
                            {
                                digit_forsame[k] = '\0';                        //digit
                            }
                            for(int u=0;u<6;u++)
                            {
                                if(each_max-i<0)
                                    continue;
                                if(isdigit(pp[cal].p_notdigit[each_max-i][u])!=0 || pp[cal].p_notdigit[each_max-i][u]=='-')
                                    digit_forsame[u] = pp[cal].p_notdigit[each_max-i][u];
                            }
    
                            result_forsame_each=get_sumfor_samechar(digit_forsame,result_forsame_each);
                        }
                        eachsame_result[cal] == 0;
                        result_forsame += result_forsame_each;
                    }
                }
                if(countt>1)
                {
                    if(result_forsame!=0)
                    {
                        if(i>1)
                        {
                            if(result_forsame<0 || start==0)
                                printf(" %d%sx^%d",result_forsame,same_char[j],i);
                            else
                                printf(" + %d%sx^%d",result_forsame,same_char[j],i);
                        }
                        else if(i==1)
                        {
                            if(result_forsame<0 || start==0)
                                printf(" %d%sx",result_forsame,same_char[j]);
                            else
                                printf(" + %d%sx",result_forsame,same_char[j]);
                        }
                        else
                        {
                            if(result_forsame<0 || start==0)
                                printf(" %d%s",result_forsame,same_char[j]);
                            else
                                printf(" + %d%s",result_forsame,same_char[j]);
                        }
                        strcpy(same_char[j],"\0");
                    }
                    else
                    {
                        if(i>1)
                        {
                            if(result_forsame<0 || start==0)
                                printf(" %sx^%d",same_char[j],i);
                            else
                                printf(" + %sx^%d",same_char[j],i);
                        }
                        else if(i==1)
                        {
                            if(result_forsame<0 || start==0)
                                printf(" %sx",same_char[j]);
                            else
                                printf(" + %sx",same_char[j]);
                        }
                        else
                        {
                            if(result_forsame<0 || start==0)
                                printf(" %s",same_char[j]);
                            else
                                printf(" + %s",same_char[j]);
                        }
                        strcpy(same_char[j],"\0");
                    }
                }
                else
                {
                    each_max=poly_arr[j];  
                    if(i>1)
                    {
                        if(pp[j].p_notdigit[each_max-i][0]=='-' || start==0)
                            printf(" %sx^%d",pp[j].p_notdigit[each_max-i],i);
                        else
                            printf(" + %sx^%d",pp[j].p_notdigit[each_max-i],i);
                    }
                    else if(i==1)
                    {
                        if(pp[j].p_notdigit[each_max-i][0]=='-' || start==0)
                            printf(" %sx",pp[j].p_notdigit[each_max-i]);
                        else
                            printf(" + %sx",pp[j].p_notdigit[each_max-i]);
                    }
                    else
                    {
                        if(pp[j].p_notdigit[each_max-i][0]=='-' || start==0)
                            printf(" %s",pp[j].p_notdigit[each_max-i]);
                        else
                            printf(" + %s",pp[j].p_notdigit[each_max-i]);
                    }
                }
            }
        }
    }
    fclose(input);
    return 0;
}
