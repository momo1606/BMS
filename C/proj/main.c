#include<stdio.h>
#include<string.h>
struct mov
{
int time[4],price;
char name[50];
};

struct user
{
    char uname[50],movie[50];
    int unumber,seats,time,price;
};

void admin_enter_details()
{
FILE *f;
int i=0,j,r;
struct mov n;
f=fopen("Movies.dat","wb");
printf("\nEnter no of records you want to write");
scanf("%d",&r);
for(j=0;j<r;j++)
{
fflush(stdin);
printf("Enter name of the movie\n");
gets(n.name);
printf("Enter the four show timings one by one\n");
for(i=0;i<4;i++)
{
scanf("%d",&n.time[i]);
}
printf("Enter price of the ticket\n");
scanf("%d",&n.price);
fwrite(&n,sizeof(struct mov),1,f);
}
fclose(f);
}
void admin_display_table()
{
int i;
struct mov n;
FILE *f;
f=fopen("MOVIES.dat","rb");
fflush(stdin);
while(fread(&n,sizeof(struct mov),1,f)!=NULL)
{
printf("\nThe name of the movie is: ");
puts(n.name);
printf("The timings of the movie are: ");
for(i=0;i<4;i++)
{
printf(" %d ", n.time[i]);
}
printf("\nThe price of a ticket is: %d\n",n.price);
}
fclose(f);
}

void admin_display_one()
{
int i,c=0;
char name[50];
struct mov n;
FILE *f;
f=fopen("MOVIES.dat","rb");
printf("\nEnter name of movie you want\n");
scanf("%s",&name);
fflush(stdin);
while(fread(&n,sizeof(n),1,f)!=NULL)
{
if(strcmpi(n.name,name)==0)
{
c++;
printf("\nThe name of the movie is: ");
puts(n.name);
printf("The timings of the movie are: ");
for(i=0;i<4;i++)
{
printf(" %d ", n.time[i]);
}
printf("\nThe price of a ticket is: %d",n.price);
}
}
if(c!=1)
printf("\nMovie not found\n");
fclose(f);
}

void admin_delete()
{
int c;
char name[50];
FILE *f,*ft;
struct mov n;
f=fopen("MOVIES.dat","rb");
ft=fopen("TEMP.dat","wb");
printf("Enter name of the movie to be deleted\n");
scanf("%s",name);
fflush(stdin);
while(fread(&n,sizeof(n),1,f)!=NULL)
{
if(strcmpi(name,n.name)==0)
{
c++;
printf("The requested record has been deleted\n");
}
else
{
fwrite(&n,sizeof(struct mov),1,ft);
}
}
if(c==0)
printf("Record not found\n");
fclose(f);
fclose(ft);
remove("MOVIES.dat");
rename("TEMP.dat","MOVIES.dat");
}

void admin_replace()
{
int c=0,i;
long int recsize;
char name[50];
FILE *f;
struct mov n;
recsize=sizeof(n);
f=fopen("MOVIES.dat","wb+");
printf("Enter name of the movie being replaced\n");
gets(name);
rewind(f);
while(fread(&n,recsize,1,f)==1)
{
if(strcmp(name,n.name)==0)
{
c++;
fflush(stdin);
printf("Enter name of the movie to be replaced\n");
gets(n.name);
printf("Enter the four show timings one by one\n");
for(i=0;i<4;i++)
{
scanf("%d",&n.time[i]);
}
printf("Enter price of the ticket\n");
scanf("%d",&n.price);
fseek(f,-recsize,SEEK_CUR);
fwrite(&n,recsize,1,f);
}
break;
}
if(c==0)
printf("Record not found\n");
fclose(f);
}
void admin_append()
{
long int recsize;
int i;
char another;
FILE *f;
struct mov n;
recsize=sizeof(n);
f=fopen("MOVIES.dat","wb+");
fseek(f,0,SEEK_END);
another='Y';
while(another=='Y')
{
printf("Enter name of the movie to be added\n");
gets(n.name);
printf("Enter the four show timings one by one\n");
for(i=0;i<4;i++)
{
scanf("%d",&n.time[i]);
}
printf("Enter price of the ticket\n");
scanf("%d",&n.price);
fwrite(&n,recsize,1,f);
printf("\nAdd another record(Y/N)");
fflush(stdin);
another=getche();
}

}


void admin_replace()
{
int c=0,i;
char name[50];
FILE *f;
struct mov n;
f=fopen("MOVIES.dat","rb");
printf("Enter name of the movie being replaced\n");
gets(name);
while(fread(&n,sizeof(struct mov),1,f)!=NULL)
{
if(strcmpi(name,n.name)==0)
{
c++;
fflush(stdin);
printf("Enter name of the new movie\n");
gets(n.name);
printf("Enter the four show timings one by one\n");
for(i=0;i<4;i++)
{
scanf("%d",&n.time[i]);
}
printf("Enter price of the ticket\n");
scanf("%d",&n.price);
fwrite(&n,sizeof(struct mov),1,f);
}
break;
}
if(c==0)
printf("Record not found\n");
fclose(f);
}




void user_display()
{
    FILE *fs;
    struct user u;
    fs=fopen("user.txt","r");
    fscanf(fs,"%s","%d","%d","%s","%d",&u.uname,&u.unumber,&u.seats,&u.movie,&u.time);
    printf("\nCustomer Name:");
    printf("%s",u.uname);
    printf("\nMobile number:");
    printf("%d",u.unumber);
    printf("\nMovie:");
    printf("%s",u.movie);
    printf("\nNumber of seats:");
    printf("%d",u.seats);
    printf("\nShow timing:");
    printf("%d",u.time);
    printf("\nPrice of the movie is:");
    printf("%d",u.price);
    fclose(fs);
}

void user_details()
{
    FILE *fs;
    struct user u;
    fs=fopen("user.txt","w");
    printf("\nEnter your name \n");
    scanf("%s",&u.uname);
    printf("\nEnter your mobile number ");
    scanf("%d",&u.unumber);
    printf("\nEnter the number of seats ");
    scanf("%d",&u.seats);
    admin_display_table();
    printf("\nEnter the movie");
    scanf("%s",&u.movie);
    printf("\nEnter show time");
    scanf("%d",&u.time);
    fprintf(fs,"%s","%d","%d","%s","%d",u.uname,u.unumber,u.seats,u.movie,u.time);
    fclose(fs);
}


main()
{
int o=1,p=1,q;
//admin_enter_details();
//admin_display_table();
//admin_display_one();
//admin_delete();
//admin_replace();
//admin_append();
//admin_replace();
//user_details();
//user_booking();
//user_display();
while(o>0)
{
printf("\nEnter 1  for admin, 2 for customer, 0 to exit\n");
scanf("%d",&o);
if(o==1)
{
while(p!=5)
{
printf("\nEnter 1 for entering movie details\n");
printf("Enter 2 to display all the movies\n");
printf("Enter 3 to display specific movie\n");
printf("Enter 4 to delete a movie\n");
printf("Enter 5 to exit admin\n");
scanf("%d",&p);
if(p==1)
admin_enter_details();
if(p==2)
admin_display_table();
if(p==3)
admin_display_one();
if(p==4)
admin_delete();
}
}

if(o==2)
{
while(q!=3)
{
printf("\nEnter 1 for customer's details\n");
printf("Enter 2 to display customer's details\n");
printf("Enter 3 to exit user\n");
scanf("%d",&q);
if(q==1)
user_details();
if(q==2)
user_display();
}
}

}

}





