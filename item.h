#include<iostream>
#include<process.h>     //exit(1)
#include<fstream>      //file operations
#include<string.h>
#include <time.h>
#include <sys/time.h>
#include <limits>
#define MAXNUM 10
using namespace std;
time_t timer;
class brand//a single brand 
{
private:
    char brandName[20];
    int brandCode;
    float brandPrice;
public:
    int quantity;
    brand(){quantity = 0;strcpy(brandName , "0");}
    void set_brand(char *name,int code,float price){strcpy(brandName,name);brandCode = code;brandPrice = price;}
    brand(brand &brand){strcpy(brandName,brand.brandName);brandCode = brand.brandCode;brandPrice = brand.brandPrice;}
    
    friend class item;
};
class item//a single item with different brands
{
private:
    char itemName[10];
    int itemCode;
    char colour[10];
    brand brands[MAXNUM];//put all brands here
    int brandNumber;//number of brands.
public:
    int quantity;//sum of all brand's quantity 
    item(){ strcpy(itemName , "\0");quantity = 0;brandNumber = 0; }//default constructor
    item(char* name){strcpy(itemName , name);}//construct by name
    item(int code){itemCode = code;}//construct by code
    item(item &item);//copy constructor
    brand *get_brands(){return brands;}
    void set_item(char *name,int code,char *color,int number);//? new item when i = 1,?
    void set_brands_in_item(int number);
    void show();//show  item
    void maintenance();//make the brand number and quantity right
    void set_zero();
    bool compare_name(item &);//for name comparsion,return 1 or 0;
    bool compare_code(item &);//for code comparsion, return 1 or 0;
    int get_brandNumber(){return brandNumber;}
    int get_item_code(){return itemCode;}
    float print_outbound_item();
    float print_inbound_item();
    char *get_item_name(){return itemName;}
    friend class node;
};
item::item(item &item){
    strcpy(itemName,item.itemName);
    itemCode = item.itemCode;
    strcpy(colour,item.colour);
    brandNumber = item.brandNumber;
    int i;
    for ( i = 0; i < brandNumber; i++)
    {
        brands[i] = item.brands[i];
    }
}//copy constructor
void item::set_item(char *name,int code,char *color,int number){//? new item when i = 1,?
    strcpy(itemName,name);
    itemCode = code;
    strcpy(colour,color);
    brandNumber = number;   
}
void item::set_zero(){
    quantity = 0;int i;
    for ( i = 0; i < brandNumber; i++)
    {
        brands[i].quantity = 0;
    }
}
void item::set_brands_in_item(int number){
    int i;
    for (i = 0; i < number; i++)
    {
        cout<<"input brand "<<i+1<<" name,no more than 20 char."<<endl;char name[10];
        cin.ignore(numeric_limits <streamsize> ::max(), '\n');
        cin.getline(name,sizeof(name)+1);
        cout<<"input brand "<<i+1<<" code"<<endl;int code;
        cin>>code;
        cout<<"input brand "<<i+1<<" price"<<endl;float price;
        cin>>price;
        brands[i].set_brand(name,code,price);
    }
}
bool item::compare_name(item &itemToCompare){//for name comparsion,return 1(same) or 0(different);
	if(strcmp(itemName,itemToCompare.itemName))
		return 0;
	else
		return 1;
}
bool item::compare_code(item &itemToCompare){//for code comparsion, return 1 or 0;
    return(itemCode == itemToCompare.itemCode);
}
void item::show(){//show  item
    int i = 0;
    cout<<"Item name:"<<itemName<<"\t\tItem code:"<<itemCode<<"\tItem colour:"<<colour<<"\t\tItem quantity:"<<quantity<<"\t Num of Brands:"<<brandNumber<<"\n\n";
    for ( i = 0; i < brandNumber; i++)
    {
        cout<<"Brand"<<i+1<<"-> |Name:"<<brands[i].brandName<<"\t|Brand code:"<<brands[i].brandCode<<"\t|Brand quantity:"<<brands[i].quantity<<"\t|Brand price:"<<brands[i].brandPrice<<endl;
    }
    cout<<"----------------------------------------------------------------"<<endl;
    

}
void item::maintenance(){
    int i = 0;//brand number maintenance
    brandNumber = 0;
    while (strcmp(brands[i].brandName,"0"))
    {
        brandNumber++;
        i++;
    }
    quantity = 0;
    for ( i = 0; i < brandNumber; i++)//item quantity maintenance
    {
        quantity += brands[i].quantity;
    }
}

