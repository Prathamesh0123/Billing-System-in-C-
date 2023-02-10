#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

//functions to generate bills...
//structure section->
struct items
{
    char items[20];
    float price;
    int qty;
};

struct orders
{
    char customer[50];
    char date[50];
    int numOfitem;
    struct items itm[50];
};
//Functions section:Bill hedar->
void generateBillheader(char name[50],char date[30])
{
    printf("\n\n");
      printf("\t   PRA.Restaurant");
      printf("\n\t  ===============");
      printf("\nDate:%s",date);
      printf("\nInvoice To:%s",name);
      printf("\n");
      printf("=====================================\n");
      printf("item\t\t");
      printf("Qty\t\t");
      printf("Total\t\t");
      printf("\n======================================");
      printf("\n\n");
}
//Bill Body->
void generateBullbody(char item[30],int qty,float price)
{
      printf("%s\t\t",item);
      printf("%d\t\t",qty);
      printf("%.2f\t\t",qty*price);
      printf("\n");
}
//Bill Footer means total->
void generateBillFooter(float total)
{
    printf("\n");
      float dis=0.1*total;
      float netTotal=total-dis;
      float cgst=0.09*netTotal,grandTotal=netTotal+2*cgst;
      printf("====================================\n");
      printf("sub total\t\t\t%.2f",total);
      printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
      printf("\n\t\t\t\t=======");
      printf("\nNet Total\t\t\t%.2f",netTotal);
      printf("\nCGST@9%s\t\t\t%.2f",",",cgst);
      printf("\nSGST@9%s\t\t\t%.2f",",",cgst);
      printf("\n===================================");
      printf("\nGrand Total\t\t\t%.2f",grandTotal);
      printf("\n=======================\n");
}

int main()
{   //All function declaration->
    float total;
    int opt,n;
    char name[50];
    struct orders ord;
    struct orders order;
    FILE *fp;
    char savebill='y',contflag='y';
    time_t t;
    time(&t);
    //Dashboard
    while(contflag=='y')
    {
    system("cls");
    float total=0;
    int invoicefound=0;
    printf("\t=============PRA.RASTAURANT===========");
    printf("\n\nPlease select your Preferred options\n");
    printf("\n\n1.Generate Invoice");
    printf("\n2.Generate all Invoices");
    printf("\n3.search Invoice");
    printf("\n4.Exit");

    printf("\n\n");


    scanf("%d",&opt);
    fgetc(stdin);
    switch(opt)
    {

    case 1:
        system("cls");
        printf("\nPlease enter the name of the customer:\t");
        fgets(ord.customer,50,stdin);
        ord.customer[strlen(ord.customer)-1]=0;
        strcpy(ord.date,ctime(&t));
         //Add the date here....
        printf("\nPlease enter the number of items:\t");
        scanf("%d",&n);
        ord.numOfitem=n;
        for(int i=0;i<n;i++)
        {
            fgetc(stdin);
            printf("\n\n");
            printf("Please Enter the item %d:\t",i+1);
            fgets(ord.itm[i].items,20,stdin);
            ord.itm[i].items[strlen(ord.itm[i].items)-1]=0;
            printf("Please enter the quantity:\t");
            scanf("%d",&ord.itm[i].qty);
            printf("Please enter the unit price:\t");
            scanf("%f",&ord.itm[i].price);
            total+=ord.itm[i].qty*ord.itm[i].price;
        }

        generateBillheader(ord.customer,ord.date);
        for(int i=0;i<ord.numOfitem;i++)
        {
            generateBullbody(ord.itm[i].items,ord.itm[i].qty,ord.itm[i].price);
        }
        generateBillFooter(total);
        printf("\nyou want to save invoice[y/n]:\t");
        scanf("%s",&savebill);

        if(savebill=='y')
        {
            fp=fopen("RestaurantBill.exe","a+");
            fwrite(&ord,sizeof(struct orders),1,fp);

            if(fwrite!=0)
                printf("\nsuccessfully saved");
            else
                printf("\nError saving");
            fclose(fp);
        }
        break;

    case 2:
        system("cls");
        fp=fopen("RestaurantBill.exe","r");
        printf("\n *******Your Previous invoices*******");
        while(fread(&order,sizeof(struct orders),1,fp))
        {
            float tot=0;
            generateBillheader(order.customer,order.date);
        for(int i=0;i<order.numOfitem;i++)
        {
        generateBullbody(order.itm[i].items,order.itm[i].qty,order.itm[i].price);
        tot+=order.itm[i].qty*order.itm[i].price;
        }
        generateBillFooter(tot);
        }
        fclose(fp);
        break;

    case 3:
        printf("\nEnter the name of the customer:\t");
       // fgetc(stdin);
        fgets(name,50,stdin);
        name[strlen(name)-1]=0;

        system("cls");
        fp=fopen("RestaurantBill.exe","r");
        printf("\t*******invoices Of %s*******",name);
        while(fread(&order,sizeof(struct orders),1,fp))
        {
            float tot=0;
            if(!strcmp(order.customer,name))
            {
                  generateBillheader(order.customer,order.date);
        for(int i=0;i<order.numOfitem;i++)
        {
        generateBullbody(order.itm[i].items,order.itm[i].qty,order.itm[i].price);
        tot+=order.itm[i].qty*order.itm[i].price;
        }
        generateBillFooter(tot);
        invoicefound=1;
        }

        }
        if(!invoicefound)
        {
            printf("sorry for invoice for %s doesn't exisits",name);
        }
        fclose(fp);
        break;

    case 4:
        printf("\n\t\t bye bye:)\n\n");
        exit(0);
        break;

    default:
        printf("sorry invalid option");
        break;
    }
      printf("do you want to perform another operation?[y/n]:\t");
      scanf("%s",&contflag);
    }
    printf("\n\t\t Thank You:)\n\n");
    printf("\n\n");
    return 0;
}
